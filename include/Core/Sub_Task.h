
#ifndef _SUB_TASK_ED_H
#define _SUB_TASK_ED_H
#include <string>  
#include <map> 
#include <vector>
#include <iostream>  

#include "Core/Task_Define.h"
#include "Common/Common.h"
#include "ADODatabase/DatabaseManage.h"
//#include "Manage/Location_Manage.h" 



class Sub_Task 
{  
public:  

	Sub_Task();  

	~Sub_Task();  

	void Sub_Task_Initial(std::string from, std::string to, int priority, int agv_type, SUB_TASK_TYPE task_type, int auto_dp, int agv_id, std::string carry_type, std::string task_mode, int task_extra_param_type, std::string task_extra_param);

	int Get_AGV_ID();

	void Update_AGV_ID(int agv_id);

	//bool Dispatch(std::string to);

	Task_Dispatch Dispatch(std::string from,std::string to);

	//wu
	//void Check_Sub_Task_State();

	bool Check_Locked(std::string& TARGETED);

	//std::string Select_To_Storage(std::string SLOC, std::string DLOC);

	void Set_Begin_Chain_Status(TASK_CHAIN_STATUS status);

	void Set_Over_Chain_Status(TASK_CHAIN_STATUS status);

	TASK_CHAIN_STATUS Begin_Chain_Status();

	TASK_CHAIN_STATUS Over_Chain_Status();

	SUB_TASK_STATUS Get_Sub_Task_Status();

	void Set_Sub_Task_Status(SUB_TASK_STATUS status);

	std::string order_from_;

	std::string order_to_;

	std::string parking;

	SUB_TASK_STATUS sub_task_status_;

	int task_extra_param_type_;

	std::string task_extra_param_;

private:
	int generate_task_id();

public:

	int task_id_;

	std::string task_from_;

	std::string task_to_;

	int priority_;

	int agv_type_;

	SUB_TASK_TYPE task_type_;

	int auto_dispatch_;

	int agv_id_;

	bool dispatched;

	std::string carry_type_;

	std::string task_mode_;
	 
	TASK_CHAIN_STATUS Begin_Status_;

	TASK_CHAIN_STATUS Over_Status_;
	
	WCS_Database* wcs_database;

}; 

#endif //_SUB_TASK_ED_H