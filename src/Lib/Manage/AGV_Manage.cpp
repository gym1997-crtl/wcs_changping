#include "Manage/AGV_Manage.h"  
#include "ADODatabase/DatabaseManage.h"
#include "iostream"
#include <sstream>
#include <fstream>
#include <vector>
#include <deque>
#include <map>
#include "comm/simplelog.h"
#include "Manage/Config_Manage.h"

AGV_Manage::AGV_Manage()
{
	getBatteryConfig();
}

AGV_Manage::~AGV_Manage()
{

}

void AGV_Manage::Initial()
{
	ACS_CON_ = DATABASE_MANAGE.Get_ACS_DB();
	WCS_CON_ = DATABASE_MANAGE.Get_WCS_DB();
	MAP_CON_ = DATABASE_MANAGE.Get_MAP_DB();

}

void AGV_Manage::Update_AGV_Data_From_ACS_Event()
{
	std::vector<AGV*> agv_list;
	ACS_CON_->Download_AGV_Info(agv_list);

	for(std::vector<AGV*>::iterator it=agv_list.begin(); it!=agv_list.end(); ++it)
	{
		AGV* current_agv=*it;

		std::map<int, AGV*>::iterator it2=AGV_List_.find(current_agv->ID_);
		if(it2!=AGV_List_.end())
		{
			AGV* found_agv=it2->second;
			
			found_agv->AGV_ID_=current_agv->AGV_ID_;
			found_agv->AGV_Status_=current_agv->AGV_Status_;
			found_agv->Error_Code_=current_agv->Error_Code_;
			found_agv->AGV_Type_=current_agv->AGV_Type_;
			found_agv->AGV_Pos_=current_agv->AGV_Pos_;
			found_agv->AGV_In_Station_ = current_agv->AGV_In_Station_;
			found_agv->Parking_Point = current_agv->Parking_Point;
			found_agv->Is_Assign_=current_agv->Is_Assign_;
			found_agv->Is_Online_=current_agv->Is_Online_;
			found_agv->Battery_Level_=current_agv->Battery_Level_;   
			found_agv->Is_Serving_ = current_agv->Is_Serving_;

			delete(current_agv);
		}
		else{
			current_agv->Resource_Status_=RESOURCE_STATUS::UNLOCKED;
			current_agv->Is_Charging_ = CHARGING_STATUS::CHANRING_STOP;
			current_agv->Invoke_AGV_Parking_ = INVOKE_STATUS::STOP_INVOKE;
			AGV_List_[current_agv->ID_] = current_agv;
		}
	}

}

void AGV_Manage::updateParkingManage()
{
	std::vector<AGV*> agv_list;
	ACS_CON_->Download_AGV_Info(agv_list);
	if (agv_list.size() != 0)
	{
		for (std::vector<AGV*>::iterator it = agv_list.begin(); it != agv_list.end(); ++it)
		{
			AGV* current_agv = *it;

			if (current_agv->AGV_In_Station_ == "P1" || current_agv->AGV_In_Station_ == "P2" || current_agv->AGV_In_Station_ == "P3" ||
				current_agv->AGV_In_Station_ == "P4" || current_agv->AGV_In_Station_ == "P5" || current_agv->AGV_In_Station_ == "P6")
			{
				WCS_CON_->reserveCurrentParkingStation(current_agv->AGV_In_Station_);
			}
		}
	}

}

bool AGV_Manage::Set_Lock(int agv_id)
{
	std::map<int, AGV*>::iterator it=AGV_List_.find(agv_id);
	if(it!=AGV_List_.end())
	{
		AGV * current_AGV=it->second;
		current_AGV->Resource_Status_=RESOURCE_STATUS::LOCKED;
		return true;
	}
	return false;
}

bool AGV_Manage::Set_Unlock(int agv_id)
{
	std::map<int, AGV*>::iterator it=AGV_List_.find(agv_id);
	if(it!=AGV_List_.end())
	{
		AGV * current_AGV=it->second;
		if (current_AGV->Oreder_Status_==RESOURCE_STATUS::IDEL)
		{
			current_AGV->Resource_Status_=RESOURCE_STATUS::UNLOCKED;
			
			return true;
		}
	}
	return false;
}

bool AGV_Manage::setManualUnlock(int agv_id)
{
	std::map<int, AGV*>::iterator it = AGV_List_.find(agv_id);
	if (it != AGV_List_.end())
	{
		AGV * current_AGV = it->second;
		if (current_AGV->Oreder_Status_ == RESOURCE_STATUS::IDEL)
		{
			current_AGV->Resource_Status_ = RESOURCE_STATUS::UNLOCKED;
			return true;
		}
	}
	return false;
}

bool AGV_Manage::invokeParking(int agv_id)
{
	std::map<int, AGV*>::iterator it = AGV_List_.find(agv_id);
	if (it != AGV_List_.end())
	{
		AGV * current_AGV = it->second;
		
		current_AGV->Invoke_AGV_Parking_ = INVOKE_STATUS::BEGING_INVOKE;
		return true;
		
	}
	return false;
}

bool AGV_Manage::setBusy(int agv_id)
{
	std::map<int, AGV*>::iterator it=AGV_List_.find(agv_id);
	if(it!=AGV_List_.end())
	{
		AGV * current_AGV=it->second;
		current_AGV->Oreder_Status_=RESOURCE_STATUS::BUSY;
		return true;
	}
	return false;
}

bool AGV_Manage::setIdel(int agv_id)
{
	std::map<int, AGV*>::iterator it=AGV_List_.find(agv_id);
	if(it!=AGV_List_.end())
	{
		AGV * current_AGV=it->second;
		current_AGV->Oreder_Status_=RESOURCE_STATUS::IDEL;
		return true;
	}
	return false;
}

bool AGV_Manage::Is_Parking(AGV* agv)
{
	//if (((agv->AGV_In_Station_ == "P1") || (agv->AGV_In_Station_ == "P2") || (agv->AGV_In_Station_ == "P3") || (agv->AGV_In_Station_ == "P4") || (agv->AGV_In_Station_ == "P5") || (agv->AGV_In_Station_ == "P6")) && (agv->AGV_Status_ == 0))
	if (((agv->AGV_In_Station_ == "P1") || (agv->AGV_In_Station_ == "P2" || (agv->AGV_In_Station_ == "P3") || (agv->AGV_In_Station_ == "P4"))) && (agv->AGV_Status_ == 0))
	{
		if (WCS_CON_->getCurrentStationIsCharging(agv->AGV_In_Station_))
		{
			agv->Parking_Is_Charging_ = "NO";
		}
		else
		{
			agv->Parking_Is_Charging_ = "YES";
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool AGV_Manage::All_agv_is_parking()
{
	for(std::map<int, AGV*>::iterator it=AGV_List_.begin(); it!=AGV_List_.end(); ++it)
	{
		AGV* current_agv=it->second;

		if(!Is_Parking(current_agv))
		{
			return false;
		}	
	}
	return true;
}

void AGV_Manage::Get_All_AGV(std::vector<AGV*> &all_agv_list)    
{
	for (std::map<int, AGV*>::iterator it = AGV_List_.begin(); it != AGV_List_.end(); ++it)
	{
		AGV* current_agv = it->second;

		if (current_agv->Is_Online_ == 1 && current_agv->AGV_Status_ == 0)
		{
			all_agv_list.push_back(current_agv);
		}
	}
}

bool AGV_Manage::Get_Free_AGV(std::vector<AGV*> &free_agv_list)
{
	for(std::map<int, AGV*>::iterator it=AGV_List_.begin(); it!=AGV_List_.end(); ++it)
	{
		AGV* current_agv=it->second;

		if(current_agv->Resource_Status_==RESOURCE_STATUS::UNLOCKED && current_agv->Is_Online_==1&& current_agv->Is_Serving_ == 1 &&current_agv->AGV_Status_ == 0)
		{
			free_agv_list.push_back(current_agv);
		}
	}
	if (free_agv_list.size()==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
/**
 * 获取AGV列表：1、电量高于最低电量；2、空闲
 */
bool AGV_Manage::getFreeHighBatteryAGV(std::vector<AGV*> &free_agv_list, int order_agv_type)
{
	for (std::map<int, AGV*>::iterator it = AGV_List_.begin(); it != AGV_List_.end(); ++it)
	{
		AGV* current_agv = it->second;

		if (current_agv->Resource_Status_ == RESOURCE_STATUS::UNLOCKED && current_agv->Is_Online_ == 1 && current_agv->Is_Serving_ == 1
			&& current_agv->AGV_Status_ == 0 && current_agv->AGV_Type_ == order_agv_type && current_agv->Battery_Level_ > battery_low_range_)
		{
			free_agv_list.push_back(current_agv);
		}
	}
	if (free_agv_list.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AGV_Manage::getCurrentAgvFreeStatus(int agv_id)
{
	for (std::map<int, AGV*>::iterator it = AGV_List_.begin(); it != AGV_List_.end(); ++it)
	{
		AGV* current_agv = it->second;

		if (current_agv->Resource_Status_ == RESOURCE_STATUS::UNLOCKED && current_agv->Is_Online_ == 1 && current_agv->Is_Serving_ == 1 && current_agv->AGV_Status_ == 0)
		{
			if (current_agv->AGV_ID_==agv_id)
			{
				return true;
			}
		}
	}
	return false;
}

void AGV_Manage::Get_Locked_AGV(std::vector<AGV*> &locked_agv_list)
{
	for(std::map<int, AGV*>::iterator it=AGV_List_.begin(); it!=AGV_List_.end(); ++it)
	{
		AGV* current_agv=it->second;

		if(current_agv->Resource_Status_==RESOURCE_STATUS::LOCKED && current_agv->Is_Online_==1)
		{
			locked_agv_list.push_back(current_agv);
		}
	}
}

void AGV_Manage::stopCharging(AGV* agv)
{
	//int current_charging_task;
	std::stringstream ss;
	WCS_CON_->stopCurrentCharging(agv);	
	ss << "AGV:" << agv->AGV_ID_ << "Stop charging successful";

	log_info_color(log_color::green, ss.str().c_str());

}


bool AGV_Manage::getCurrentAGVIsOnlineStatus(int agv_id)
{
	if (ACS_CON_->getCurrentAGVIsOnline(agv_id))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void AGV_Manage::splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c)
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

void AGV_Manage::getBatteryConfig()
{
	std::string a;
	if (CONFIG_MANAGE.readConfig("Battery_High_Range", &a))
	{
		battery_high_range_ = atof(a.c_str());
	}
	if (CONFIG_MANAGE.readConfig("Battery_Low_Range", &a))
	{
		battery_low_range_ = atof(a.c_str());
	}
	if (CONFIG_MANAGE.readConfig("Unlock_Battery_Level", &a))
	{
		unlock_battery_level_ = atof(a.c_str());
	}
}

//************************************
// Method:     inArea
// FullName:   AGV_Manage::inArea
// Access:     public 
// Returns:    bool
// Parameter:  AGV point_agv
// Parameter:  int area_id
// Author:     Meixu
// Date:	   2021/08/04
// Description:判断车是否在编号为 area_id 的区域中
//************************************
bool AGV_Manage::isInArea(AGV point_agv, int area_id) {
	if (all_area.empty())
	{
		if (!readAreaInfo())
		{
			return false;
		}
	}
	if (all_area.find(area_id) == all_area.end())
	{
		return false;
	}
	return isPointInPolygon(point_agv.AGV_Pos_, all_area[area_id]);
}

//************************************
// Method:     agvsInArea
// FullName:   AGV_Manage::agvsInArea
// Access:     public 
// Returns:    std::map<int, AGV*>
// Parameter:  int area_id
// Author:     Meixu
// Date:	   2021/08/04
// Description:
//************************************
std::map<int, AGV*> AGV_Manage::agvsInfoInArea(int area_id) {
	std::map<int, AGV*> result;
	if (all_area.empty())
	{
		if (!readAreaInfo())
		{
			return result;
		}
	}
	for each (auto point_agv in AGV_List_)
	{
		if (isInArea(point_agv.second, area_id))
		{
			result.insert(point_agv);
		}
	}
	return result;
}

//************************************
// Method:     readAreaInfo
// FullName:   AGV_Manage::readAreaInfo
// Access:     private 
// Returns:    bool
// Author:     Meixu
// Date:	   2021/08/04
// Description:更新所有区域信息
//************************************
bool AGV_Manage::readAreaInfo() {
	if (WCS_CON_!=nullptr)
	{
		return WCS_CON_->readAreaInfo(&all_area);
	}
	return false;
}

//************************************
// Method:     isPointInPolygon
// FullName:   AGV_Manage::isPointInPolygon
// Access:     private 
// Returns:    bool
// Parameter:  Pos_Info p
// Parameter:  std::vector<Pos_Info> points
// Author:     Meixu
// Date:	   2021/08/04
// Description: 判断点是否在闭合区域内
//************************************
bool AGV_Manage::isPointInPolygon(Pos_Info p, std::vector<Pos_Info> points)
{
	//vector<Point> points:表示闭合区域由这些点围成
	double minX = points[0].x;
	double maxX = points[0].x;
	double minY = points[0].y;
	double maxY = points[0].y;
	for (unsigned int i = 1; i < points.size(); i++)
	{
		Pos_Info q = points[i];
		minX = min(q.x, minX);
		maxX = max(q.x, maxX);
		minY = min(q.y, minY);
		maxY = max(q.y, maxY);
	}

	if (p.x < minX || p.x > maxX || p.y < minY || p.y > maxY)
	{
		return false;
	}

	bool inside = false;
	for (unsigned int i = 0, j = points.size() - 1; i < points.size(); j = i++)
	{
		if ((points[i].y > p.y) != (points[j].y > p.y) &&
			p.x < (points[j].x - points[i].x) * (p.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)
		{
			inside = !inside;
		}
	}

	return inside;
}

//************************************
// Method:     nearestFreeAgv
// FullName:   AGV_Manage::nearestFreeAgv
// Access:     public 
// Returns:    int
// Parameter:  std::string station_name
// Author:     Meixu
// Date:	   2021/08/05
// Description:获取指定station附近最近的空闲AGV编号；没有时返回nullptr
//************************************
AGV* AGV_Manage::nearestFreeAgv(std::string station_name) {
	int result = -1;
	for each (auto var in sortByDistance(station_name))
	{
		if (AGV_List_.at(var)->Resource_Status_ == RESOURCE_STATUS::UNLOCKED && AGV_List_.at(var)->Is_Online_ == 1 && AGV_List_.at(var)->Is_Serving_ == 1 && AGV_List_.at(var)->AGV_Status_ == 0) {
			result = var;
			break;
		}
	}
	return result == -1 ? nullptr : AGV_List_.at(result);
}

//************************************
// Method:     nearestAgv
// FullName:   AGV_Manage::nearestAgv
// Access:     public 
// Returns:    int
// Parameter:  std::string station_name
// Author:     Meixu
// Date:	   2021/08/05
// Description:获取指定station附近最近的AGV编号；没有时返回nullptr
//************************************
AGV* AGV_Manage::nearestAgv(std::string station_name) {
	int result = -1;
	for each (auto var in sortByDistance(station_name))
	{
		result = var;
		break;
	}
	return result == -1 ? nullptr : AGV_List_.at(result);
}

//************************************
// Method:     farthestFreeAgv
// FullName:   AGV_Manage::farthestFreeAgv
// Access:     public 
// Returns:    int
// Parameter:  std::string station_name
// Author:     Meixu
// Date:	   2021/08/05
// Description:获取指定station附近最远的空闲AGV编号；没有时返回nullptr
//************************************
AGV* AGV_Manage::farthestFreeAgv(std::string station_name) {
	int result = -1;
	for each (auto var in sortByDistance(station_name))
	{
		if (AGV_List_.at(var)->Resource_Status_ == RESOURCE_STATUS::UNLOCKED && AGV_List_.at(var)->Is_Online_ == 1 && AGV_List_.at(var)->Is_Serving_ == 1 && AGV_List_.at(var)->AGV_Status_ == 0) {
			result = var;
		}
	}
	return result == -1 ? nullptr : AGV_List_.at(result);
}

//************************************
// Method:     farthestAgv
// FullName:   AGV_Manage::farthestAgv
// Access:     public 
// Returns:    int
// Parameter:  std::string station_name
// Author:     Meixu
// Date:	   2021/08/05
// Description:获取指定station附近最远的AGV编号；没有时返回nullptr
//************************************
AGV* AGV_Manage::farthestAgv(std::string station_name) {
	int result = -1;
	for each (auto var in sortByDistance(station_name))
	{
		result = var;
	}
	return result == -1 ? nullptr : AGV_List_.at(result);
}

//************************************
// Method:     sortByDistance
// FullName:   AGV_Manage::sortByDistance
// Access:     public 
// Returns:    std::vector<int>
// Parameter:  std::string station_name
// Author:     Meixu
// Date:	   2021/08/05
// Description:获取指定station名，按距离排序的所有AGV
//************************************
std::vector<int> AGV_Manage::sortByDistance(std::string station_name)
{
	std::vector<int> result;// 结果
	Pos_Info station;
	if (MAP_CON_->getStationPos(station_name, &station))
	{
		std::map<int, long long> distance;// AGV号对应的距离
		for each (auto var in AGV_List_)
		{
			distance[var.first] = calDistance(var.second->AGV_Pos_, station);
		}
		// 冒泡
		while (distance.size() >= 2)
		{
			int max = distance.begin()->first, min = distance.begin()->first;
			for each (auto var in distance)
			{
				if (distance.at(max) < var.second)
				{
					max = var.first;
				}
				else if (distance.at(min) > var.second)
				{
					min = var.first;
				}
			}
			result.insert(result.begin() + (int)((AGV_List_.size() - distance.size()) / 2), min);
			result.insert(result.begin() + (int)((AGV_List_.size() - distance.size()) / 2 + 1), max);
			distance.erase(max);
			distance.erase(min);
		}
		
	}
	
	return result;
}

// 计算两点间距离
long long AGV_Manage::calDistance(Pos_Info a, Pos_Info b) {
	return ((long long)(a.x - b.x)*(a.x - b.x)) + (a.y - b.y)*(a.y - b.y);
}