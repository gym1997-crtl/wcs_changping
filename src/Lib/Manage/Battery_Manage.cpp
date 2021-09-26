#include "iostream"
#include <sstream>
#include <fstream>
#include "Manage/Battery_Manage.h"
#include "Manage/AGV_Manage.h"
#include "Core/Task_Chain_Manage.h"
#include "comm/simplelog.h"


Battery_Manage::Battery_Manage()
{
	getBatteryConfig();
}

Battery_Manage::~Battery_Manage()
{

}

void Battery_Manage::High_Priority_Battery_Monitor_System()
{
	std::vector<AGV*> Free_AGV_List;

	AGV_MANAGE.Get_Free_AGV(Free_AGV_List);

	for (std::vector<AGV*>::iterator it = Free_AGV_List.begin(); it != Free_AGV_List.end(); ++it)
	{
		AGV* current_AGV = *it;

		if (AGV_MANAGE.Is_Parking(current_AGV))  //在充电点，电量低于30，且不在充电中;
		{
			if (current_AGV->Is_Charging_ == CHARGING_STATUS::CHANRING_STOP && current_AGV->Battery_Level_ <= battery_low_range_)
			{
				if (current_AGV->Parking_Is_Charging_ == "YES")
				{
					AGV_MANAGE.Set_Lock(current_AGV->ID_);
					AGV_MANAGE.setBusy(current_AGV->ID_);
					current_AGV->Is_Charging_ = CHARGING_STATUS::CHANRING_PENDING;
					Generate_Charging_Task(current_AGV);
				}
			}
		}
	}
}

void Battery_Manage::Low_Priority_Battery_Monitor_Subsystem()
{
	std::vector<AGV*> Free_AGV_List;

	AGV_MANAGE.Get_Free_AGV(Free_AGV_List);

	for(std::vector<AGV*>::iterator it=Free_AGV_List.begin(); it!=Free_AGV_List.end(); ++it)
	{
		AGV* current_AGV=*it;
		if (AGV_MANAGE.Is_Parking(current_AGV) && current_AGV->Is_Charging_ == CHARGING_STATUS::CHANRING_STOP && current_AGV->Battery_Level_ < battery_high_range_ && current_AGV->Battery_Level_ > battery_low_range_ && current_AGV->Resource_Status_ == 0)     //满足条件后开始充电
		{
			if (current_AGV->Parking_Is_Charging_ == "YES")
			{
				current_AGV->Is_Charging_ = CHARGING_STATUS::CHANRING_PENDING;
				Generate_Charging_Task(current_AGV);
			}
		}
	}
}

void Battery_Manage::Charging_AGV_Monitor()
{
	std::vector<AGV*> Locked_AGV_List;
	
	AGV_MANAGE.Get_Locked_AGV(Locked_AGV_List);
	
	for(std::vector<AGV*>::iterator it=Locked_AGV_List.begin(); it!=Locked_AGV_List.end(); ++it)
	{
		AGV* current_AGV=*it;

		if (current_AGV->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING && current_AGV->Battery_Level_ > unlock_battery_level_ && current_AGV->Charging_Status_)
		{
			current_AGV->Charging_Status_ = false;
			AGV_MANAGE.setIdel(current_AGV->ID_);
			AGV_MANAGE.Set_Unlock(current_AGV->ID_);
	
			std::stringstream ss;
			ss<< "AGV_" << current_AGV->ID_ << " Battery Level > 50 , AGV Unlocked";
			log_info_color(log_color::blue, ss.str().c_str());
		}
	}
}

bool Battery_Manage::Generate_Charging_Task(AGV* associate_AGV)
{
	if (TASK_CHAIN_MANAGE.Create_Charging_Task_Chain(associate_AGV))
	{
		return true;
	}
	else{
		return false;
	}
}

bool Battery_Manage::Generate_Parking_Task(AGV* associate_AGV)
{
	if (TASK_CHAIN_MANAGE.Create_Parking_Task_Chain(associate_AGV))
	{
		return true;
	}
	else{
		return false;
	}
}

bool Battery_Manage::Check_Low_Power(AGV* associate_AGV)
{
	if (associate_AGV->Battery_Level_<battery_low_range_)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Battery_Manage::getBatteryConfig()
{
	if (Config_.FileExist("config.txt"))
	{
		Config_.ReadFile("config.txt");
	}
	if (Config_.KeyExists("Battery_High_Range"))
	{
		std::stringstream battery_high_range(Config_.Read<std::string>("Battery_High_Range"));
		battery_high_range >> battery_high_range_;
	}
	if (Config_.KeyExists("Battery_Low_Range"))
	{
		std::stringstream battery_low_range(Config_.Read<std::string>("Battery_Low_Range"));
		battery_low_range >> battery_low_range_;
	}
	if (Config_.KeyExists("Unlock_Battery_Level"))
	{
		std::stringstream unlock_battery_level(Config_.Read<std::string>("Unlock_Battery_Level"));
		unlock_battery_level >> unlock_battery_level_;
	}
}

void Battery_Manage::splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}