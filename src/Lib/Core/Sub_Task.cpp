#include "Core/Sub_Task.h"  
#include "Core/Task_Chain_Manage.h"  

#include <sstream>

Sub_Task::Sub_Task()
{
	Begin_Status_ = TASK_CHAIN_STATUS::NONE;
	Over_Status_ = TASK_CHAIN_STATUS::NONE; 
}

Sub_Task::~Sub_Task()
{
	//Consider to do something if necessary when destruct!
}

void Sub_Task::Sub_Task_Initial(std::string from, std::string to, int priority, int agv_type, SUB_TASK_TYPE task_type, int auto_dp, int agv_id, std::string carry_type, std::string task_mode, int task_extra_param_type, std::string task_extra_param)
{
	task_id_ = generate_task_id();

	task_from_ = from;

	task_to_ = to;

	priority_ = priority;

	agv_type_ = agv_type;

	task_type_ = task_type;

	auto_dispatch_ = auto_dp;

	agv_id_ = agv_id;

	carry_type_ = carry_type;

	task_mode_ = task_mode;

	task_extra_param_type_ = task_extra_param_type;

	task_extra_param_ = task_extra_param;

	dispatched = false;

	sub_task_status_ = SUB_TASK_STATUS::NEW;

	wcs_database = DATABASE_MANAGE.Get_WCS_DB();
}

void Sub_Task::Update_AGV_ID(int agv_id)
{
		agv_id_=agv_id;
}
 

Task_Dispatch Sub_Task::Dispatch(std::string from,std::string to)
{
	Task_Dispatch task_dispatch;

	task_dispatch.task_id_ = task_id_;
	task_dispatch.task_from_ = from;
	task_dispatch.task_to_ = to;
	task_dispatch.priority_ = 1;
	task_dispatch.agv_type_ = agv_type_;
	task_dispatch.task_type_ = (int)task_type_;
	task_dispatch.auto_dispatch_ = auto_dispatch_;
	task_dispatch.agv_id_ = agv_id_;
	task_dispatch.dispatched = false;
	task_dispatch.task_extra_param_ = task_extra_param_;
	task_dispatch.task_extra_param_type_ = task_extra_param_type_;

	return task_dispatch;
}

int Sub_Task::Get_AGV_ID()
{
	return agv_id_;
}

int Sub_Task::generate_task_id()
{
	return TASK_CHAIN_MANAGE.Generate_New_Sub_Task_ID();
}

void Sub_Task::Set_Begin_Chain_Status(TASK_CHAIN_STATUS status)
{
	Begin_Status_ = status;
}

void Sub_Task::Set_Over_Chain_Status(TASK_CHAIN_STATUS status)
{
	Over_Status_ = status;
}

//The Begin_Status of Sub_Task and the Type of Sub_Task
TASK_CHAIN_STATUS Sub_Task::Begin_Chain_Status()
{
	return Begin_Status_;
}

TASK_CHAIN_STATUS Sub_Task::Over_Chain_Status()
{
	return Over_Status_;
}

void Sub_Task::Set_Sub_Task_Status(SUB_TASK_STATUS status)
{
	sub_task_status_ = status;
}

SUB_TASK_STATUS Sub_Task::Get_Sub_Task_Status()
{
	return sub_task_status_;
}