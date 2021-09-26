
#ifndef _Task_Chain_Manage_ED_H
#define _Task_Chain_Manage_ED_H
#include <string>  
#include <map> 
#include <vector>
#include <iostream>  
#include <boost/serialization/singleton.hpp>
#include "Core/Task_Chain.h"
#include "Core/Sub_Task.h"
#include "Core/Task_Define.h"
#include "Manage/Manage_Define.h"
#include "ADODatabase/WCS_Database.h"
#include "RabbitMQService.h"

class Task_Chain_Manage
{
public:

	Task_Chain_Manage();

	~Task_Chain_Manage();

	void Initial();

	bool Create_Task_Chain(std::string order_id, std::string start, std::string target, std::string mode, std::string type, AGV* associate_AGV,std::string palletno);

	bool Create_Parking_Task_Chain(AGV* associate_AGV);

	bool createForceParkingTaskChain(AGV* associate_AGV);

	bool Create_Charging_Task_Chain(AGV* associate_AGV);

	void Task_Status_Check_Event();

	int Generate_New_Sub_Task_ID();

	void Add_to_full_list_if_not_exist(int id, int state);

	void Set_Status(TASK_CHAIN_STATUS chain_status);

	void cancelTaskChain(std::string order_id, int task_id);

	Sub_Task* Move_To_Next_Sub_Task(Sub_Task * Current_Sub_Task);

	int now_parking_;

	std::vector<Task_Chain*>  Get_Full_Task_List();

	std::vector<Task_Chain*>  Get_Active_Task_List();

	std::vector<Task_Chain*>  Get_Inactive_Task_List();

	std::string getReportPoint(std::string target_point);

	std::map<int, int> Full_Sub_Task_List_;

	std::vector<Task_Chain*> Active_Task_List_;

	float ReadNum(std::string str);

	void splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c);

	bool Is_AGV_In_Parking_Station(AGV* current_agv);

	std::string getStartTime();

protected:

private:

	void Add_to_full_task_list(Task_Chain* the_task);

	void Add_to_active_task_list(Task_Chain* the_task);

	void Add_to_inactive_task_list(Task_Chain* the_task);

	std::string Order_ID_;

	int Task_ID_;

	int Index_;

	TASK_CHAIN_STATUS Chain_Status_;

	std::vector<Task_Chain*> Full_Task_List_;

	std::vector<Task_Chain*> Inactive_Task_List_;

	std::map<std::string, std::string>  Report_Point_Map_;

	WCS_Database* WCS_DB_;

};

typedef boost::serialization::singleton<Task_Chain_Manage> Singleton_Task_Chain_Manage;
#define TASK_CHAIN_MANAGE Singleton_Task_Chain_Manage::get_mutable_instance()

#endif //_Task_Chain_Manage_ED_H