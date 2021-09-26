
#ifndef _AGV_MANAGE_ED_H
#define _AGV_MANAGE_ED_H
#include <string>  
#include <map> 
#include <vector>
#include <iostream>  
#include <boost/serialization/singleton.hpp>
#include "Common/Config.h"
#include "Manage/Manage_Define.h"
#include "ADODatabase/WCS_Database.h"
#include "ADODatabase/ACS_Database.h"
#include "ADODatabase/MAP_Database.h"

#define P1_AGV_ID 51
#define P2_AGV_ID 52
#define P3_AGV_ID 53
#define P4_AGV_ID 54
#define P5_AGV_ID 55

class AGV_Manage 
{  
public:  

	AGV_Manage();  

	~AGV_Manage();  

	void Initial();

	bool Get_Free_AGV(std::vector<AGV*> &free_agv_list);

	bool getFreeHighBatteryAGV(std::vector<AGV*> &free_agv_list, int order_agv_type);

	bool getCurrentAgvFreeStatus(int agv_id);

	void updateParkingManage();

	void Get_All_AGV(std::vector<AGV*> &all_agv_list);

	void Get_Locked_AGV(std::vector<AGV*> &locked_agv_list);

	bool Set_Lock(int agv_id);

	bool Set_Unlock(int agv_id);

	bool setManualUnlock(int agv_id);

	bool invokeParking(int agv_id);

	bool setBusy(int agv_id);

	bool setIdel(int agv_id);

	bool Get_AGV_Status(int agv_id, RESOURCE_STATUS &status);

	bool Get_AGV_Sub_Status(int agv_id, AGV_SUB_STATUS &status);

	bool Is_Parking(AGV* agv);

	void stopCharging(AGV* agv);

	void Update_AGV_Data_From_ACS_Event();

	void Update_AGV_Data_To_WCS();

	bool All_agv_is_parking();

	bool getCurrentAGVIsOnlineStatus(int agv_id);

	void splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c);

	void getBatteryConfig();

	// AGV是否在区域中
	bool isInArea(AGV point_agv, int area_id);
	inline bool isInArea(AGV *point_agv, int area_id) { return isInArea(*point_agv, area_id); };
	// 区域中所有AGV信息
	std::map<int, AGV*> agvsInfoInArea(int area_id);
	// 区域中AGV数量
	inline int agvNumInArea(int area_id) { return agvsInfoInArea(area_id).size(); };
	// 区域中仅有指定AGV
	inline bool onlyPointAgvInArea(AGV point_agv, int area_id) { return agvNumInArea(area_id) == 1 && isInArea(point_agv, area_id); };
	inline bool onlyPointAgvInArea(AGV *point_agv, int area_id) { return onlyPointAgvInArea(*point_agv, area_id); };

	// 指定站点最近的AGV
	AGV* nearestAgv(std::string station_name);
	// 指定站点最近的空闲AGV
	AGV* nearestFreeAgv(std::string station_name);
	// 指定站点最远的AGV
	AGV* farthestAgv(std::string station_name);
	// 指定站点最远的空闲AGV
	AGV* farthestFreeAgv(std::string station_name);
	// 与指定站点距离排序
	std::vector<int> sortByDistance(std::string station_name);
	// 计算两点距离的平方
	long long calDistance(Pos_Info a, Pos_Info b);

	std::map<int, AGV*> Get_All_AGV()
	{
		return AGV_List_;
	}

protected:  


private:

	bool Is_Locked(int agv_id);

	std::string AGV_ID_;
	std::string Parking_Station_;

	std::map<int, AGV*> AGV_List_;
	std::map<int, AGV*> FAKE_CHARGING_AGV_List_;
	Config_File Config_;
	float battery_high_range_;
	float battery_low_range_;
	float unlock_battery_level_;
	WCS_Database* WCS_CON_;
	ACS_Database* ACS_CON_;
	MAP_Database* MAP_CON_;
	
	std::map<int, std::vector<Pos_Info>> all_area;
	bool readAreaInfo();
	bool isPointInPolygon(Pos_Info p, std::vector<Pos_Info> points);
}; 

typedef boost::serialization::singleton<AGV_Manage> Singleton_AGV_Manage;
#define AGV_MANAGE Singleton_AGV_Manage::get_mutable_instance()

#endif //_AGV_MANAGE_ED_H