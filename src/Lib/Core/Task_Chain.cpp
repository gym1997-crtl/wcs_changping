#include <windows.h>
#include <sstream>
#include "Core/Task_Chain.h" 
#include "Core/Task_Chain_Manage.h" 
#include "ADODatabase/DatabaseManage.h"
#include <fstream>
#include <iostream>
#include "comm/simplelog.h"

Task_Chain::Task_Chain()
{
	Task_Type_ = TASK_CHAIN_TYPE::NONE_TASK;
	Task_ID_ = 0;
	WCS_DB_ = DATABASE_MANAGE.Get_WCS_DB();
	getBatteryConfig();
}

Task_Chain::~Task_Chain()
{

}


TASK_CHAIN_STATUS Task_Chain::Task_Chain_Initial(int index, std::string order_id, std::string start, std::string target, std::string mode, std::string type, AGV* associate_AGV, int task_id, std::string palletno)
{
	Task_ID_ = task_id;
	Associate_AGV_ = associate_AGV;
	Order_ID_ = order_id;
	Index_ = index;
	Start_Time_ = " ";
	Stop_Charge_ = false;

	setStart(start);
	setTargeted(target);
	setMode(mode);
	setType(type);
	setPalletno(palletno);

	if (mode == "TRAY")
	{
		setTrayPut(start);
		return createTrayStorageTaskChain();
	}
	else if (mode == "GOODS")
	{
		setGoodsGet(start);
		return createGoodsStorageTaskChain();
	}
}

TASK_CHAIN_STATUS Task_Chain::Parking_Initial(int index, AGV* associate_AGV)
{
	Associate_AGV_ = associate_AGV;
	Index_ = index;
	Stop_Charge_ = false;
	Start_Time_ = " ";
	setStart(associate_AGV->AGV_In_Station_);
	setTargeted(associate_AGV->Parking_Station_);
	setMode("PARKING");
	setType("PARKING");
	return  createParingTaskChain();
}

TASK_CHAIN_STATUS Task_Chain::forceParkingInitial(int index, AGV* associate_AGV)
{
	std::string parking_turn_station = associate_AGV->AGV_In_Station_ + "-TURN";
	setTurnStation(parking_turn_station);

	Associate_AGV_ = associate_AGV;
	Index_ = index;
	Stop_Charge_ = false;
	Start_Time_ = " ";
	setStart(associate_AGV->AGV_In_Station_);
	setTargeted(associate_AGV->Parking_Station_);
	setMode("PARKING");
	setType("PARKING");
	return  createForcedChargeTaskChain();
}


TASK_CHAIN_STATUS Task_Chain::Charging_Initial(int index, AGV* associate_AGV)
{
	Associate_AGV_ = associate_AGV;
	Index_ = index;
	Stop_Charge_ = false;

	Start_Time_ = " ";

	setStart(associate_AGV->AGV_In_Station_);
	setTargeted(associate_AGV->Parking_Point);
	setMode("CHARGING");
	setType("CHARGING");
	associate_AGV->Charging_Status_ = true;

	return  createChargingTaskChain();
}

TASK_CHAIN_STATUS Task_Chain::createMoveStorageTaskChain()    //业务流程
{
	Task_Type_ = TASK_CHAIN_TYPE::CARRY_TASK;

	if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING && Associate_AGV_->Battery_Level_ > battery_low_range_)
	{
		Associate_AGV_->Is_Charging_ = CHARGING_STATUS::CHARGING_PAUSE;
		AGV_MANAGE.stopCharging(Associate_AGV_);
		stopChargingLog();
		return BLOCKED;
	}
	if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING && Associate_AGV_->Battery_Level_ <= battery_low_range_)
	{
		AGV_MANAGE.Set_Lock(Associate_AGV_->AGV_ID_);
		AGV_MANAGE.setBusy(Associate_AGV_->AGV_ID_);
		return BLOCKED;
	}
	else if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_STOP)
	{
		/*取放货相关流程*/

		// 1-1. 前往缓存区取一个空轮; 
		Create_Sub_Task("NA", "NA", 1, Associate_AGV_->AGV_Type_, DIRECT_FORWARD_GET, 0, Associate_AGV_->ID_, "BUFFER_GET", "MOVE", BUFFER_GET, BUFFER_GET_CHECK);

		// 1-2. 前往输送线放空轮确认点; 
		Create_Sub_Task("NA", getStart() + "-P-W", 1, Associate_AGV_->AGV_Type_, FORWARD_BACKWARD, 0, Associate_AGV_->ID_, "EQUIP_PUT", "MOVE", EQUIP_PUT, EQUIP_PUT_CHECK);

		// 1-2. 前往输送线放空轮; 
		Create_Sub_Task("NA", getStart() + "-P", 1, Associate_AGV_->AGV_Type_, BACKWARD_PUT, 0, Associate_AGV_->ID_, "EQUIP_PUT", "MOVE", EQUIP_PUT, EQUIP_PUT_CHECK);

		// 1-2. 前往输送线取满轮; 
		Create_Sub_Task("NA", getStart() + "-G", 1, Associate_AGV_->AGV_Type_, DIRECT_FORWARD_GET, 0, Associate_AGV_->ID_, "EQUIP_GET", "MOVE", EQUIP_GET, EQUIP_GET_CHECK);

		// 1-4. 前往缓存区放一个满轮; 
		Create_Sub_Task("NA", "NA", 1, Associate_AGV_->AGV_Type_, DIRECT_FORWARD_PUT, 0, Associate_AGV_->ID_, "BUFFER_PUT", "MOVE", BUFFER_PUT, BUFFER_PUT_CHECK);

		std::stringstream ss;
		ss << Associate_AGV_->AGV_ID_ << ":Begin createInStorageTaskChain";
		log_info(ss.str().c_str());

		Set_Status(TASK_CHAIN_STATUS::BEGIN);
		Set_Start_Time();
		return TASK_CHAIN_STATUS::BEGIN;
	}
}

TASK_CHAIN_STATUS Task_Chain::createTrayStorageTaskChain()    //业务流程
{
	Task_Type_ = TASK_CHAIN_TYPE::CARRY_TASK;

	if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING && Associate_AGV_->Battery_Level_ > battery_low_range_)
	{
		Associate_AGV_->Is_Charging_ = CHARGING_STATUS::CHARGING_PAUSE;
		AGV_MANAGE.stopCharging(Associate_AGV_);
		stopChargingLog();
		return BLOCKED;
	}
	if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING && Associate_AGV_->Battery_Level_ <= battery_low_range_)
	{
		AGV_MANAGE.Set_Lock(Associate_AGV_->AGV_ID_);
		AGV_MANAGE.setBusy(Associate_AGV_->AGV_ID_);
		return BLOCKED;
	}
	else if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_STOP)
	{
		/*取放货相关流程*/

		// 1-1. 前往缓存区取一个空轮; 
		Create_Sub_Task("NA", "NA", 1, Associate_AGV_->AGV_Type_, DIRECT_FORWARD_GET, 0, Associate_AGV_->ID_, "BUFFER_GET", "TRAY", BUFFER_GET, BUFFER_GET_CHECK);

		// 1-2. 前往输送线放空轮确认点; 
		Create_Sub_Task("NA", getStart() + "-P-W", 1, Associate_AGV_->AGV_Type_, FORWARD_BACKWARD, 0, Associate_AGV_->ID_, "EQUIP_PUT_CONFIRM", "TRAY", EQUIP_PUT_CONFIRM, EQUIP_PUT_CONFIRM_CHECK);

		// 1-3. 前往输送线放空轮; 
		Create_Sub_Task("NA", getStart() + "-P", 1, Associate_AGV_->AGV_Type_, BACKWARD_PUT, 0, Associate_AGV_->ID_, "EQUIP_PUT", "TRAY", EQUIP_PUT, EQUIP_PUT_CHECK);

		// 1-4. 退出输送线放空轮确认点; 
		Create_Sub_Task("NA", getStart() + "-P-W", 1, Associate_AGV_->AGV_Type_, DIRECT_FORWARD_PATH, 0, Associate_AGV_->ID_, "EQUIP_PUT_RELEASE", "TRAY", EQUIP_PUT_RELEASE, EQUIP_PUT_RELEASE_CHECK);


		std::stringstream ss;
		ss << Associate_AGV_->AGV_ID_ << ":Begin createTrayStorageTaskChain";
		log_info(ss.str().c_str());

		Set_Status(TASK_CHAIN_STATUS::BEGIN);
		Set_Start_Time();
		return TASK_CHAIN_STATUS::BEGIN;
	}
}

TASK_CHAIN_STATUS Task_Chain::createGoodsStorageTaskChain()    //业务流程
{
	Task_Type_ = TASK_CHAIN_TYPE::CARRY_TASK;

	if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING && Associate_AGV_->Battery_Level_ > battery_low_range_)
	{
		Associate_AGV_->Is_Charging_ = CHARGING_STATUS::CHARGING_PAUSE;
		AGV_MANAGE.stopCharging(Associate_AGV_);
		stopChargingLog();
		return BLOCKED;
	}
	if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING && Associate_AGV_->Battery_Level_ <= battery_low_range_)
	{
		AGV_MANAGE.Set_Lock(Associate_AGV_->AGV_ID_);
		AGV_MANAGE.setBusy(Associate_AGV_->AGV_ID_);
		return BLOCKED;
	}
	else if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_STOP)
	{
		// 1-2. 前往输送线放空轮确认点; 
		Create_Sub_Task("NA", getStart() + "-G-W", 1, Associate_AGV_->AGV_Type_, FORWARD_BACKWARD, 0, Associate_AGV_->ID_, "EQUIP_GET_CONFIRM", "GOODS", EQUIP_GET_CONFIRM, EQUIP_GET_CONFIRM_CHECK);

		// 1-2. 前往输送线取满轮; 
		Create_Sub_Task("NA", getStart() + "-G", 1, Associate_AGV_->AGV_Type_, BACKWARD_GET, 0, Associate_AGV_->ID_, "EQUIP_GET", "GOODS", EQUIP_GET, EQUIP_GET_CHECK);

		// 1-4. 前往缓存区放一个满轮; 
		Create_Sub_Task("NA", "NA", 1, Associate_AGV_->AGV_Type_, DIRECT_FORWARD_PUT, 0, Associate_AGV_->ID_, "BUFFER_PUT", "GOODS", BUFFER_PUT, BUFFER_PUT_CHECK);

		std::stringstream ss;
		ss << Associate_AGV_->AGV_ID_ << ":Begin createGoodsStorageTaskChain";
		log_info(ss.str().c_str());

		Set_Status(TASK_CHAIN_STATUS::BEGIN);
		Set_Start_Time();
		return TASK_CHAIN_STATUS::BEGIN;
	}
}
TASK_CHAIN_STATUS Task_Chain::createParingTaskChain()
{
	Task_Type_ = TASK_CHAIN_TYPE::PARKING_TASK;

	// 1-2. 停车任务
	Create_Sub_Task("NA", Associate_AGV_->Parking_Station_, 1, Associate_AGV_->AGV_Type_, PARKING_FORWARD, 0, Associate_AGV_->ID_, "PARKING", "PARKING", PARKING, PARKING_CHECK);

	std::stringstream ss;
	ss << Associate_AGV_->AGV_ID_ << ":Begin createParingTaskChain sub Task Flow";
	log_info(ss.str().c_str());

	Set_Status(TASK_CHAIN_STATUS::BEGIN);
	Set_Start_Time();

	return TASK_CHAIN_STATUS::BEGIN;
}

TASK_CHAIN_STATUS Task_Chain::createForcedChargeTaskChain()    //强制去充电点;
{
	Task_Type_ = TASK_CHAIN_TYPE::PARKING_TASK;
	if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING)
	{
		Associate_AGV_->Is_Charging_ = CHARGING_STATUS::CHARGING_PAUSE;
		AGV_MANAGE.stopCharging(Associate_AGV_);
		//	stopChargingLog();
		//	return BLOCKED;
	}
	if (Associate_AGV_->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING && Associate_AGV_->Battery_Level_ <= battery_low_range_)
	{
		AGV_MANAGE.Set_Lock(Associate_AGV_->AGV_ID_);
		AGV_MANAGE.setBusy(Associate_AGV_->AGV_ID_);
		AGV_MANAGE.stopCharging(Associate_AGV_);
	}
	std::string aa = getTurnStation();
	// 1-1. 停车任务
	Create_Sub_Task("NA", Associate_AGV_->Parking_Station_, 1, Associate_AGV_->AGV_Type_, PARKING_FORWARD, 0, Associate_AGV_->ID_, "PARKING", "FOCE_PARKING", PARKING, PARKING_CHECK);

	std::stringstream ss;
	ss << Associate_AGV_->AGV_ID_ << ":Begin create Forced Charge Task Chain sub Task Flow";
	log_info(ss.str().c_str());

	Set_Status(TASK_CHAIN_STATUS::BEGIN);
	Set_Start_Time();
	return TASK_CHAIN_STATUS::BEGIN;
}


TASK_CHAIN_STATUS Task_Chain::createChargingTaskChain()
{
	Task_Type_ = TASK_CHAIN_TYPE::CHARGING_TASK;
	std::cout << "AGV " << Associate_AGV_->ID_ << " Charging!" << std::endl;
	std::string extra_param;
	if (Associate_AGV_->AGV_In_Station_ == "P1")
	{
		extra_param = "5";
	}
	else if (Associate_AGV_->AGV_In_Station_ == "P2")
	{
		extra_param = "6";
	}

	Create_Sub_Task(Associate_AGV_->AGV_In_Station_, Associate_AGV_->AGV_In_Station_, 1, Associate_AGV_->AGV_Type_, AGV_IN_SITU_CHARGING, 0, Associate_AGV_->ID_, "CHARGING", "CHARGING", 5, extra_param, IS_CHARGING);

	std::stringstream ss;
	ss << Associate_AGV_->AGV_ID_ << ":Begin createChargingTaskChain sub Task Flow";
	log_info(ss.str().c_str());

	Set_Status(TASK_CHAIN_STATUS::BEGIN);
	Set_Start_Time();
	return TASK_CHAIN_STATUS::BEGIN;
}

bool Task_Chain::Create_Sub_Task(std::string from, std::string to, int priority, int agv_type, SUB_TASK_TYPE task_type, int auto_dp, int agv_id, std::string carry_type, std::string task_mode, TASK_CHAIN_STATUS Begin_Status, TASK_CHAIN_STATUS Over_Status)
{

	Sub_Task *New_Sub_Task = new Sub_Task();

	New_Sub_Task->Sub_Task_Initial(from, to, priority, agv_type, task_type, auto_dp, agv_id, carry_type, task_mode, -1, "");

	New_Sub_Task->Set_Begin_Chain_Status(Begin_Status);

	New_Sub_Task->Set_Over_Chain_Status(Over_Status);

	Sub_Task_Chain_.push_back(New_Sub_Task);

	return true;
}

bool Task_Chain::Create_Sub_Task(std::string from, std::string to, int priority, int agv_type, SUB_TASK_TYPE task_type, int auto_dp, int agv_id, std::string carry_type, std::string task_mode, int task_extra_param_type, std::string task_extra_param, TASK_CHAIN_STATUS Begin_Status, TASK_CHAIN_STATUS Over_Status)
{

	Sub_Task *New_Sub_Task = new Sub_Task();

	New_Sub_Task->Sub_Task_Initial(from, to, priority, agv_type, task_type, auto_dp, agv_id, carry_type, task_mode, task_extra_param_type, task_extra_param);

	New_Sub_Task->Set_Begin_Chain_Status(Begin_Status);

	New_Sub_Task->Set_Over_Chain_Status(Over_Status);

	Sub_Task_Chain_.push_back(New_Sub_Task);

	return true;
}

Sub_Task* Task_Chain::Move_To_Next_Sub_Task(Sub_Task * Current_Sub_Task, std::string current_carry_type)
{
	std::list<Sub_Task*>::iterator it;

	for (it = Sub_Task_Chain_.begin(); it != Sub_Task_Chain_.end();)
	{
		int AGV_ID = Current_Sub_Task->Get_AGV_ID();

		Sub_Task* st = *it;
		if (st->carry_type_ == current_carry_type)
		{
			Sub_Task * Next_Sub_Task = *it;
			Next_Sub_Task->Update_AGV_ID(AGV_ID);
			return Next_Sub_Task;
		}
		else
		{
			it++;
		}
	}
}

void Task_Chain::Set_Status(int status)
{
	Task_Status_ = status;
}

TASK_CHAIN_STATUS Task_Chain::Get_Status()
{
	boost::mutex::scoped_lock lock(mu_chain_status_);
	return Chain_Status_;
}

void Task_Chain::Set_Status(TASK_CHAIN_STATUS chain_status)
{
	boost::mutex::scoped_lock lock(mu_chain_status_);
	Chain_Status_ = chain_status;
}

void Task_Chain::Check_Feedback(Sub_Task *Current_Sub_Task)
{
	switch (Task_Status_)
	{
	case -1:
		Current_Sub_Task->Set_Sub_Task_Status(SUB_TASK_STATUS::REJECTED);
		break;
	case 5:
		Current_Sub_Task->Set_Sub_Task_Status(SUB_TASK_STATUS::DONE);
		break;
	case 6:
		Current_Sub_Task->Set_Sub_Task_Status(SUB_TASK_STATUS::ABORTED);
		break;
	case 7:
		Current_Sub_Task->Set_Sub_Task_Status(SUB_TASK_STATUS::FAILED);
		break;
	case 9:
		Current_Sub_Task->Set_Sub_Task_Status(SUB_TASK_STATUS::CHARGING);
		break;
	case 10:
		Current_Sub_Task->Set_Sub_Task_Status(SUB_TASK_STATUS::FORCE_COMPLETED);
		break;
	default:
		Current_Sub_Task->Set_Sub_Task_Status(SUB_TASK_STATUS::ONGOING);
		break;
	}
}

void Task_Chain::Set_Start_Time()
{
	struct tm *tm_now;
	time(&start_time);
	tm_now = localtime(&start_time);
	std::stringstream ss;
	ss << tm_now->tm_year + 1900 << "/" << tm_now->tm_mon + 1 << "/" << tm_now->tm_mday << " " << tm_now->tm_hour << ":" << tm_now->tm_min << ":" << tm_now->tm_sec;
	Start_Time_ = ss.str();
}

void Task_Chain::Set_Over_Time_And_Duration()
{
	time_t t, t1;
	struct tm *tm_now;
	time(&t);
	t1 = t - start_time;
	tm_now = localtime(&t);
	std::stringstream ss, ss1;

	ss << tm_now->tm_year + 1900 << "/" << tm_now->tm_mon + 1 << "/" << tm_now->tm_mday << " " << tm_now->tm_hour << ":" << tm_now->tm_min << ":" << tm_now->tm_sec;

	int a;
	a = t1 % 60;
	if (a < 10)
	{
		ss1 << t1 / 60 << 0 << t1 % 60;
	}
	else
	{
		ss1 << t1 / 60 << t1 % 60;
	}
	Over_Time_ = ss.str();
	Duration_ = ss1.str();
}

std::string Task_Chain::Get_Start_Time()
{
	return Start_Time_;
}

std::string Task_Chain::Get_Over_Time()
{
	return Over_Time_;
}

std::string Task_Chain::Get_Duration()
{
	return Duration_;
}

void Task_Chain::setStart(std::string START)
{
	START_ = START;
}

void Task_Chain::setTargeted(std::string TARGETED)
{
	TARGETED_ = TARGETED;
}

void Task_Chain::setTrayGet(std::string TRAY_GET)
{
	TRAY_GET_ = TRAY_GET;
}

void Task_Chain::setTrayPut(std::string TRAY_PUT)
{
	TRAY_PUT_ = TRAY_PUT;
}

void Task_Chain::setGoodsGet(std::string GOODS_GET)
{
	GOODS_GET_ = GOODS_GET;
}

void Task_Chain::setGoodsPut(std::string GOODS_PUT)
{
	GOODS_PUT_ = GOODS_PUT;
}

void Task_Chain::setTurnStation(std::string turn_station)
{
	turn_station_ = turn_station;
}

void Task_Chain::setSafeStation(std::string safe_station)
{
	safe_station_ = safe_station;
}

void Task_Chain::setConfirmStation(std::string confirm_station)
{
	confirm_station_ = confirm_station;
}

void Task_Chain::setMode(std::string MODE)
{
	MODE_ = MODE;
}

void Task_Chain::setPalletno(std::string palletno)
{
	PALLETNO_ = palletno;
}

void Task_Chain::setType(std::string TYPE)
{
	TYPE_ = TYPE;
}

void Task_Chain::Set_Last_Direct(std::string Direct)
{
	Direct_ = Direct;
}

std::string Task_Chain::getStart()
{
	return START_;
}

std::string Task_Chain::getPalletno()
{
	return PALLETNO_;
}

std::string Task_Chain::getTargeted()
{
	return TARGETED_;
}

std::string Task_Chain::getTurnStation()
{
	return turn_station_;
}

std::string Task_Chain::getConfirmStation()
{
	return confirm_station_;
}

std::string Task_Chain::getStackWaitStation()
{
	return stackStation_;
}

std::string Task_Chain::getSafeStation()
{
	return safe_station_;
}

std::string Task_Chain::getInConfirmStation()
{
	return in_confirm_station_;
}

std::string Task_Chain::getOutConfirmStation()
{
	return out_confirm_station_;
}

std::string Task_Chain::getMode()
{
	return MODE_;
}

std::string Task_Chain::getType()
{
	return TYPE_;
}

std::string Task_Chain::Get_Last_Direct()
{
	return Direct_;
}

AGV* Task_Chain::Get_Associate_AGV()
{
	return Associate_AGV_;
}



std::string Task_Chain::getTrayGet()
{
	return TRAY_GET_;
}

std::string Task_Chain::getTrayPut()
{
	return TRAY_PUT_;
}

std::string Task_Chain::getGoodsGet()
{
	return GOODS_GET_;
}

std::string Task_Chain::getGoodsPut()
{
	return GOODS_PUT_;
}

void Task_Chain::stopChargingLog()
{
	struct tm *tm_now;
	time(&start_time);
	tm_now = localtime(&start_time);
	std::stringstream ss;
	ss << tm_now->tm_year + 1900 << "-" << tm_now->tm_mon + 1 << "-" << tm_now->tm_mday << " " << tm_now->tm_hour << ":" << tm_now->tm_min << ":" << tm_now->tm_sec;
	std::ofstream outf;
	outf.open("stop_charing_log.txt", std::ios::app);
	outf << "stop charging !!!!" << ss.str() << std::endl;
	outf.close();
}

void Task_Chain::getBatteryConfig()
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

void Task_Chain::splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c)
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