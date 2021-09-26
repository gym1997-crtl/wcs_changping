#include "Core/Event_Handler.h" 
#include "Core/Task_Chain.h"
#include "Manage/AGV_Manage.h"
#include "Manage/Storage_Manage.h"
#include <Windows.h>
#include "comm/simplelog.h"
#include <sstream>
#include <fstream>
#include <iostream>
//#include "XML_Database.h"

Event_Handler::Event_Handler()
{	
	if (!Executing_List_.empty())
	{
		Executing_List_.erase(Executing_List_.begin(), Executing_List_.end());
	}
}

Event_Handler::~Event_Handler()
{

}

void Event_Handler::Initial(){
	
	WCS_CON_ = DATABASE_MANAGE.Get_WCS_DB();    //数据库连接初始化;
	AGV_MANAGE.Initial();						//AGV初始化;
	ORDER_MANAGE.Initial();
	TASK_CHAIN_MANAGE.Initial();
	DATABASE_MANAGE.Initial(); 
	STORAGE_MANAGE.Initial();
	PARKING_MANAGE.Initial();
	existstorages = new std::map<std::string, int>;
}

void Event_Handler::Data_Update_Event()
{
	EVENT_HANDLER.Task_Fetcher_Event();
	
	ORDER_MANAGE.Download_Order_Info_From_Database_Event();
	
	TASK_CHAIN_MANAGE.Task_Status_Check_Event();

	Feedback_Event();
}

void Event_Handler::High_Priority_Battery_Event()
{
	BATTERY_MANAGE.High_Priority_Battery_Monitor_System();
}

void Event_Handler::Low_Priority_Battery_Event()
{
	BATTERY_MANAGE.Low_Priority_Battery_Monitor_Subsystem();
	
	BATTERY_MANAGE.Charging_AGV_Monitor();
}

void Event_Handler::Parking_Event()
{
	PARKING_MANAGE.Auto_Parking_Monitor();
}

void Event_Handler::Feedback_Event(){

	for(int j=0; j < TASK_CHAIN_MANAGE.Active_Task_List_.size(); j++)
	{
		TASK_CHAIN_MANAGE.Active_Task_List_[j]->Set_Status(WCS_CON_->readTaskStatus(TASK_CHAIN_MANAGE.Active_Task_List_[j]->Task_ID_));
	}

}

void Event_Handler::Task_Dispatch_Event()
{
	std::vector<AGV*> All_AGV_List;

	AGV_MANAGE.Get_All_AGV(All_AGV_List);

	for (std::vector<AGV*>::iterator it = All_AGV_List.begin(); it != All_AGV_List.end(); ++it)
	{
		AGV* current_AGV=*it;
					
		if(Task_Dispatcher_AGV(current_AGV))
		{		
			AGV_MANAGE.Set_Lock(current_AGV->ID_);
			AGV_MANAGE.setBusy(current_AGV->ID_);
		}			
	}
}

bool Event_Handler::Task_Dispatcher_AGV(AGV* current_AGV)  //AGV任务派发
{
	std::vector<Oreder_Task*>::iterator it;
	
	for (it = Executing_List_.begin(); it != Executing_List_.end();)
	{
		Oreder_Task *order_task = *it;
		
		if (current_AGV->AGV_ID_ == order_task->AGV_ID)
		{ 
			if (TASK_CHAIN_MANAGE.Create_Task_Chain(order_task->ORDER_ID, order_task->START_POINT, order_task->TARGET_POINT, order_task->MODE, order_task->TYPE, current_AGV,order_task->PALLETNO))
			{
				WCS_CON_->updateOrderStatusToDoing(order_task->ORDER_ID, order_task->AGV_ID);
			
				delete(order_task);
				it = Executing_List_.erase(it);
				return true;
			}
			else
			{
				it++;
			}
		}
		else
		{
			it++;
		}
	}
	return false;
}

void Event_Handler::Sub_Task_Dispatch_Event(Sub_Task* current_sub_task,Task_Chain* task)
{
		Task_Chain* current_task = task;
		Sub_Task *Current_Sub_Task=current_sub_task;
		std::string task_from = current_sub_task->task_from_;
		std::string task_to = current_sub_task->task_to_;

		Task_Dispatch_ = Current_Sub_Task->Dispatch(task_from,task_to);
		
		current_task->Task_ID_ = Task_Dispatch_.task_id_;

		if(Task_Dispatch_.dispatched == false)
		{
			Task_Dispatch_.dispatched = WCS_CON_->insertTask(Task_Dispatch_.task_id_,Task_Dispatch_.task_from_,Task_Dispatch_.task_to_,Task_Dispatch_.priority_,Task_Dispatch_.agv_type_,Task_Dispatch_.task_type_,Task_Dispatch_.auto_dispatch_,Task_Dispatch_.agv_id_, Task_Dispatch_.task_extra_param_type_, Task_Dispatch_.task_extra_param_);
		}
}

void Event_Handler::Task_Fetcher_Event()         //订单分配 ：kh_order_info ==> kh_report_order_info
{ 
	Task_Chain_Info new_task_in;

	std::vector<AGV*> Free_AGV_List;

	int priority = 1;
	int agv_type = 1;
	int agv_id = 1;
	std::string parking_station;

	if (WCS_CON_->copyOrderInfo(new_task_in))
	{
		agv_id = new_task_in.AGV_ID_;
		if (AGV_MANAGE.getCurrentAgvFreeStatus(agv_id))
		{
			AGV_MANAGE.Set_Lock(agv_id);   //分配任务后锁定车辆;
			AGV_MANAGE.setBusy(agv_id);

			std::stringstream ss;
			ss << "AGV_" << agv_id << "Assign AGV Order Locked";
			log_info(ss.str().c_str());

			WCS_CON_->deleteCurrentOrder(new_task_in.ORDER_ID_);
			WCS_CON_->addOrder(new_task_in.ORDER_ID_, new_task_in.START_, new_task_in.TARGET_, new_task_in.PRIORITY_, "NEW",
				new_task_in.MODE_, new_task_in.TYPE_, agv_id);

			Oreder_Task* order_task = new Oreder_Task;

			order_task->ORDER_ID = new_task_in.ORDER_ID_;
			order_task->AGV_ID = new_task_in.AGV_ID_;
			order_task->START_POINT = new_task_in.START_;
			order_task->TARGET_POINT = new_task_in.TARGET_;
			order_task->MODE = new_task_in.MODE_;
			order_task->TYPE = new_task_in.TYPE_;
			order_task->PALLETNO = new_task_in.PALLETNO_;
			Executing_List_.push_back(order_task);
		}
		return;
	}
}

bool Event_Handler::Assign_AGV_Current_Order(int &agv_id)
{
	std::vector<AGV*> Free_AGV_List;
	if (AGV_MANAGE.Get_Free_AGV(Free_AGV_List))
	{
		for (int i = 0; i < Free_AGV_List.size(); i++)
		{
			for (int j = i; j < Free_AGV_List.size(); j++)
			{
				if (Free_AGV_List[j]->Battery_Level_ > Free_AGV_List[i]->Battery_Level_)
				{
					AGV* temp = Free_AGV_List[i];
					Free_AGV_List[i] = Free_AGV_List[j];
					Free_AGV_List[j] = temp;
				}
			}
		}
		std::vector<AGV*>::iterator it = Free_AGV_List.begin();
		AGV* current_AGV = *it;
		agv_id = current_AGV->AGV_ID_;
		return true;
	}
	else
	{
		agv_id = -1;
		return false;
	}
}

void Event_Handler::splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c)
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


/// <summary>
/// Gets the standard storage.
/// </summary>
/// <param name="storage">The storage.</param>
/// <param name="status">The status.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/1/21
/// 
bool Event_Handler::getStandardStorage(std::string &storage, const std::string& status) {
	storage = "";
	// 库位长宽

	const int row = 13, col = 19;
	int storages[row + 1][col + 1] = { {0} };
	// 标记库位
	// 获取所有符合状态的库位
	std::vector<std::string> standard_storages = STORAGE_MANAGE.getStandardStorage(status);
	for each (std::string var in standard_storages)
	{
		// 库位名获取库位位置
		long storage_name;
		std::istringstream is(var);
		is >> storage_name;
		if ((storage_name) %1000000000 / 10000  == 20501)
		{// 是二楼的托盘库位
			int s_row = (storage_name % 10000) / 100;
			int s_col = storage_name % 100;
			// 标记
			storages[s_row][s_col] ++;
		}
	}

	if (status == "EMPTY")
	{// 找EMPTY代表入库放货
		// 找到最深的EMPTY库位（左上角）
		int c_row[col + 1] = {};
		for (int i = 1; i <= col; i++)
		{// 从第一列开始查
			for (int j = 1; j <= row; j++)
			{ // 第一行
				if (storages[j][i] != 0)
				{// 从下往上找符合条件的库位
					c_row[i] = j;
					//break;
				}
				else
				{// 有货，以上的不能放
					break;
				}
			}
		}
		// 深度
		int max = 0;
		// 最深库位的列
		int dep_col = 1;
		for (int i = 1; i <= col; i++)
		{
			if (max < c_row[i])
			{
				max = c_row[i];
				dep_col = i;
			}			
		}
		if (max != 0)
		{
			storage = createFloor2StorageName(max, dep_col);
		}
	}
	else if (status == "TRAY")
	{// 找托盘代表出库
		// 找到最浅的标记（右下角）
		for (int i = 1; i <= row; i++)
		{
			for (int j = col; j >= 1; j--)
			{
				if (storages[i][j] != 0)
				{
					storage = createFloor2StorageName(i, j);
					break;
				}
			}
			if (storage != "")
			{
				break;
			}
		}
	}
	return storage == "" ? false : true;
}

/// <summary>
/// Creates the name of the floor2 storage.
/// </summary>
/// <param name="row">The row.</param>
/// <param name="col">The col.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/1/21
/// 
std::string Event_Handler::createFloor2StorageName(int row, int col) {
	return "0" + std::to_string(205010000 + row * 100 + col);
}