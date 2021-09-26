
#ifndef _EVENT_HANDLER_ED_H
#define _EVENT_HANDLER_ED_H
#include <string>  
#include <map>  
#include <vector>
#include <iostream>  

#include <boost/serialization/singleton.hpp>
#include "ADODatabase/ADODatabase.h"
#include "Manage/Order_Manage.h"
#include "Core/Task_Chain_Manage.h"
#include "Manage/AGV_Manage.h"
#include "Manage/Storage_Manage.h"
#include "Manage/Manage_Define.h"
#include "Manage/Parking_Manage.h"
#include "Task_Define.h"
#include "ADODatabase//WCS_Database.h"

class Event_Handler 
{  
public:  

	Event_Handler();  

	~Event_Handler();  

	void Initial();

	void Data_Transfer_Event();

	void Data_Update_Event();

	void Data_Write_Event();

	void Parking_Event();

	void High_Priority_Battery_Event();

	void Low_Priority_Battery_Event();

	void Task_Dispatch_Event();

	void Sub_Task_Dispatch_Event(Sub_Task* current_sub_task,Task_Chain* task);

	void Pallet_Task_Event();

	void System_Status_Event();

	bool Task_Dispatcher_AGV(AGV* current_AGV);
	
	bool Pallet_Task_Dispatcher_1T(AGV* current_AGV);

	void Halt_System();

	void Start_System();

	std::string Get_System_Status_String();

	void Feedback_Event();

	void Task_Fetcher_Event();

	//bool Assign_AGV_Current_Order(int &agv_id);

	bool Assign_AGV_Current_Order(int &agv_id);

	void splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c);

	bool getStandardStorage(std::string &storage, const std::string& status);

	std::string createFloor2StorageName(int row, int col);

public:

	std::vector<Oreder_Task*>Executing_List_;
//	std::vector<std::string>storage_down_list;


protected:  

private:

	int NUM;

	Oreder_Task *Backup_point_id;

	SYSTEM_STATUS System_Status_;

	std::map<int, Order> New_Order_List_;

	std::map<int, Order> Processing_Order_List_;

	std::vector<std::string> DLOC_List_;

	WCS_Database* WCS_CON_;

	std::vector<int>WCS_TASK_ID_;


	//int Task_ID;

	Task_Dispatch Task_Dispatch_;

	AGV* Associate_AGV_;

	std::map<std::string, int> *existstorages;
	

}; 

typedef boost::serialization::singleton<Event_Handler> Singleton_Event_Handler;
#define EVENT_HANDLER Singleton_Event_Handler::get_mutable_instance()

#endif //_EVENT_HANDLER_ED_H