#ifndef BATTERY_MANAGE_H
#define BATTERY_MANAGE_H
#include <string>  
#include <map> 
#include <vector>
#include <iostream>  
#include <boost/serialization/singleton.hpp>
#include "Common/Config.h"
#include "Manage/Manage_Define.h"

class Battery_Manage
{

public:
	
	Battery_Manage();
	~Battery_Manage();

	void High_Priority_Battery_Monitor_System();

	void Low_Priority_Battery_Monitor_Subsystem();

	int Now_Parking_;

	void Charging_AGV_Monitor();

	bool Check_Low_Power(AGV* associate_AGV);

	

private:

	void getBatteryConfig();

	bool Generate_Parking_Task(AGV* associate_AGV);
	
	bool Generate_Charging_Task(AGV* associate_AGV);

	void splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c);

	float battery_high_range_;
	float battery_low_range_;
	float unlock_battery_level_;
	Config_File Config_;
};

typedef boost::serialization::singleton<Battery_Manage> Singleton_Battery_Manage;
#define BATTERY_MANAGE Singleton_Battery_Manage::get_mutable_instance()

#endif