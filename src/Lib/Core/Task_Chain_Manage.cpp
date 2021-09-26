#include <iostream>
#include <sstream>
#include "ADODatabase/WCS_Database.h"
#include "Core/Task_Chain_Manage.h"  
#include "Core/Event_Handler.h"
#include "comm/simplelog.h"
#include "time.h"


Task_Chain_Manage::Task_Chain_Manage()
{

}

Task_Chain_Manage::~Task_Chain_Manage()
{

}

void Task_Chain_Manage::Initial()
{
	Task_ID_ = 1;

	now_parking_ = 0;

	WCS_DB_ = DATABASE_MANAGE.Get_WCS_DB();

	Task_ID_ = WCS_DB_->getMaxTaskId();
}

int Task_Chain_Manage::Generate_New_Sub_Task_ID()
{
	Task_ID_++;
	return Task_ID_;
}

bool Task_Chain_Manage::Create_Task_Chain(std::string order_id, std::string start, std::string target, std::string mode, std::string type, AGV* associate_AGV, std::string palletno)
{
	Order_ID_ = order_id;

	int index = Full_Task_List_.size();

	Task_Chain* New_Task = new Task_Chain();

	TASK_CHAIN_STATUS result = New_Task->Task_Chain_Initial(index, Order_ID_, start, target, mode, type, associate_AGV, Task_ID_,palletno);

	switch (result)
	{
	case TASK_CHAIN_STATUS::BEGIN:
		Add_to_active_task_list(New_Task);
		//	Add_to_full_task_list(New_Task);

		return true;
		break;
	case TASK_CHAIN_STATUS::ERR:
		//	Add_to_inactive_task_list(New_Task);
		//	Add_to_full_task_list(New_Task);

		return false;
		break;
	case TASK_CHAIN_STATUS::BLOCKED:
		delete(New_Task);

		return false;
		break;
	}

	return false;
}

bool Task_Chain_Manage::Create_Parking_Task_Chain(AGV* associate_AGV)
{
	std::string enter_time = getStartTime();

	WCS_DB_->addParkingChargingOrder(associate_AGV->AGV_In_Station_, associate_AGV->Parking_Station_, "PARKING", associate_AGV->AGV_ID_);

	int index = Full_Task_List_.size();

	Task_Chain* New_Task = new Task_Chain();

	TASK_CHAIN_STATUS result = New_Task->Parking_Initial(index, associate_AGV);

	switch (result)
	{
	case TASK_CHAIN_STATUS::BEGIN:
		Add_to_active_task_list(New_Task);
		//Add_to_full_task_list(New_Task);
		return true;
		break;
	case TASK_CHAIN_STATUS::ERR:
		//	Add_to_inactive_task_list(New_Task);
		//	Add_to_full_task_list(New_Task);
		return false;
		break;
	case TASK_CHAIN_STATUS::BLOCKED:
		delete(New_Task);
		return false;
		break;
	}

	return false;
}

bool Task_Chain_Manage::createForceParkingTaskChain(AGV* associate_AGV)
{
	std::string enter_time = getStartTime();

	WCS_DB_->addParkingChargingOrder(associate_AGV->AGV_In_Station_, associate_AGV->Parking_Station_, "PARKING", associate_AGV->AGV_ID_);

	int index = Full_Task_List_.size();

	Task_Chain* New_Task = new Task_Chain();

	TASK_CHAIN_STATUS result = New_Task->forceParkingInitial(index, associate_AGV);

	switch (result)
	{
	case TASK_CHAIN_STATUS::BEGIN:
		Add_to_active_task_list(New_Task);
		//	Add_to_full_task_list(New_Task);
		return true;
		break;
	case TASK_CHAIN_STATUS::ERR:
		//	Add_to_inactive_task_list(New_Task);
		//	Add_to_full_task_list(New_Task);
		return false;
		break;
	case TASK_CHAIN_STATUS::BLOCKED:
		delete(New_Task);
		return false;
		break;
	}

	return false;
}

bool Task_Chain_Manage::Create_Charging_Task_Chain(AGV* associate_AGV)
{
	std::string enter_time = getStartTime();
	WCS_DB_->addParkingChargingOrder(associate_AGV->AGV_In_Station_, associate_AGV->Parking_Station_, "CHARGING", associate_AGV->AGV_ID_);

	int index = Full_Task_List_.size();

	Task_Chain* New_Task = new Task_Chain();

	TASK_CHAIN_STATUS result = New_Task->Charging_Initial(index, associate_AGV);

	switch (result)
	{
	case TASK_CHAIN_STATUS::BEGIN:
		Add_to_active_task_list(New_Task);
		//Add_to_full_task_list(New_Task);
		return true;
		break;
	case TASK_CHAIN_STATUS::ERR:
		//Add_to_inactive_task_list(New_Task);
		//Add_to_full_task_list(New_Task);
		return false;
		break;
	case TASK_CHAIN_STATUS::BLOCKED:
		delete(New_Task);
		return false;
		break;
	}

	return false;
}

void Task_Chain_Manage::Add_to_full_task_list(Task_Chain* the_task)
{
	Full_Task_List_.push_back(the_task);
}

void Task_Chain_Manage::Add_to_active_task_list(Task_Chain* the_task)
{
	Active_Task_List_.push_back(the_task);
}

void Task_Chain_Manage::Add_to_inactive_task_list(Task_Chain* the_task)
{
	Inactive_Task_List_.push_back(the_task);
}

void Task_Chain_Manage::Task_Status_Check_Event()
{
	std::vector<Task_Chain*>::iterator it;
	for (it = Active_Task_List_.begin(); it != Active_Task_List_.end(); )
	{
		Task_Chain* current_task = *it;

		AGV* current_agv = current_task->Associate_AGV_;

		Sub_Task *Current_Sub_Task;

		if (!current_task->Sub_Task_Chain_.empty())
		{
			Current_Sub_Task = current_task->Sub_Task_Chain_.front();
		}
		else
		{
			//std::cout<<"Sub_Task_Chain_ IS Empty!!!"<<std::endl;
			break;
		}
		//状态判断;
		//把begin变成to_get,to_put,parking,is_charging;
		//把     变成mid;
		//把     变成over;
		switch (current_task->Get_Status())
		{

		case TASK_CHAIN_STATUS::BEGIN:
		{
			current_task->Check_Feedback(Current_Sub_Task);

			if (Current_Sub_Task->task_mode_ == "CHARGING")
			{
				EVENT_HANDLER.Sub_Task_Dispatch_Event(Current_Sub_Task, current_task);

				current_task->Set_Status(TASK_CHAIN_STATUS::IS_CHARGING);
			}
			else if (Current_Sub_Task->task_mode_ == "PARKING")
			{
				current_task->Set_Status(TASK_CHAIN_STATUS::PARKING);
			}
			else if (Current_Sub_Task->task_mode_ == "FOCE_PARKING")
			{
				ORDER_MANAGE.releaseParkingStation(current_agv->AGV_In_Station_);
				current_task->Set_Status(TASK_CHAIN_STATUS::PARKING);
			}
			else if (Current_Sub_Task->task_mode_ == "GOODS")
			{
				current_task->Set_Status(EQUIP_GET_CONFIRM);//前往输送线取满轮的确认点
			}
			else if (Current_Sub_Task->task_mode_ == "TRAY")
			{
				current_task->Set_Status(BUFFER_GET);//前往缓存区取空轮
			}

			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_GET_CONFIRM://前往输送线取满轮的确认点
		{
			Current_Sub_Task = current_task->Move_To_Next_Sub_Task(Current_Sub_Task, "EQUIP_GET_CONFIRM");
			if (Current_Sub_Task->carry_type_ == "EQUIP_GET_CONFIRM")
			{
				EVENT_HANDLER.Sub_Task_Dispatch_Event(Current_Sub_Task, current_task);
				current_task->Set_Status(TASK_CHAIN_STATUS::EQUIP_GET_CONFIRM_CHECK);

				if (current_agv->AGV_In_Station_ == "P1" || current_agv->AGV_In_Station_ == "P2" || current_agv->AGV_In_Station_ == "P3" || current_agv->AGV_In_Station_ == "P4")
				{
					ORDER_MANAGE.releaseParkingStation(current_agv->AGV_In_Station_);   //释放停车点
					current_agv->Parking_Is_Charging_ = "";
					current_agv->Parking_Station_ = "";
					std::stringstream ss;
					ss << "release Parking Station: " << current_agv->AGV_In_Station_;
					log_info_color(log_color::red, ss.str().c_str());
				}
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_GET_CONFIRM_CHECK:
		{
			//在START里面判断子任务的状态;		
			current_task->Check_Feedback(Current_Sub_Task);

			if (Current_Sub_Task->sub_task_status_ == DONE)
			{
#if 1
				if (RABBITMQ_SERVICE.ApplyGetGoods(current_task->getGoodsGet(), current_task->Order_ID_))
				{
					current_task->Set_Status(EQUIP_GET);
				}
#endif
				std::stringstream ss;
				ss << "RABBITMQ_SERVICE:ApplyGetGoods," << "EQUIP ID:" << current_task->getGoodsGet() << ",ORDER_ID:" << current_task->Order_ID_;
				log_info_color(log_color::purple, ss.str().c_str());
				
			}
			else if (Current_Sub_Task->sub_task_status_ == REJECTED || Current_Sub_Task->sub_task_status_ == FAILED)
			{
				current_task->Set_Status(ERR);
			}
			else if (Current_Sub_Task->sub_task_status_ == ABORTED)
			{
				current_task->Set_Status(ABORT);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::BUFFER_GET://前往缓存区取空轮
		{
			Current_Sub_Task = current_task->Move_To_Next_Sub_Task(Current_Sub_Task, "BUFFER_GET");
			if (Current_Sub_Task->carry_type_ == "BUFFER_GET")
			{
				std::string storage_group;
				std::string tray_get;
				if (WCS_DB_->getCurrentEquipToStorage(storage_group, current_task->getStart()))//获取到当前水箱距离较近的缓存区
				{
					if (WCS_DB_->getCurrentTableStorageName("s_storage_station_status", "FULL", tray_get, "TRAY", storage_group))//就近找一个空轮
					{
						Current_Sub_Task->task_to_ = tray_get;
						current_task->setTrayGet(tray_get);
						EVENT_HANDLER.Sub_Task_Dispatch_Event(Current_Sub_Task, current_task);
						current_task->Set_Status(TASK_CHAIN_STATUS::BUFFER_GET_CHECK);
						WCS_DB_->setCurrentTableStorageStatus("s_storage_station_status", "RESERVE", tray_get);
						WCS_DB_->updateOrderTargetStorageInfo(current_task, "CARRY", "kh_report_order_info");//更新当前取空轮位置
#if 1
						RABBITMQ_SERVICE.ReportAgvAction(current_task->getTrayGet(), CageType::TRAY, WorkType::OUT_STORAGE, " ", current_agv->AGV_ID_);//取空托盘时给的信号
#endif
						std::stringstream ss;
						ss << "RABBITMQ_SERVICE:ReportAgvAction" << "CageName:" << current_task->getTrayGet() << ",CageType:" << CageType::TRAY << ",WorkType:" << WorkType::OUT_STORAGE
							<< ",AGV_ID:" << current_agv->AGV_ID_;
						log_info_color(log_color::purple, ss.str().c_str());

						if (current_agv->AGV_In_Station_ == "P1" || current_agv->AGV_In_Station_ == "P2" || current_agv->AGV_In_Station_ == "P3" || current_agv->AGV_In_Station_ == "P4")
						{
							ORDER_MANAGE.releaseParkingStation(current_agv->AGV_In_Station_);   //释放停车点
							current_agv->Parking_Is_Charging_ = "";
							current_agv->Parking_Station_ = "";
							std::stringstream ss;
							ss << "release Parking Station: " << current_agv->AGV_In_Station_;
							log_info_color(log_color::red, ss.str().c_str());
						}
					}
				}
				
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::BUFFER_GET_CHECK:
		{
			//在START里面判断子任务的状态;		
			current_task->Check_Feedback(Current_Sub_Task);

			if (Current_Sub_Task->sub_task_status_ == DONE)
			{
				current_task->Set_Status(EQUIP_PUT_CONFIRM);
			}
			else if (Current_Sub_Task->sub_task_status_ == REJECTED || Current_Sub_Task->sub_task_status_ == FAILED)
			{
				current_task->Set_Status(ERR);
			}
			else if (Current_Sub_Task->sub_task_status_ == ABORTED)
			{
				current_task->Set_Status(ABORT);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_PUT_CONFIRM://前往输送线放空轮的确认点
		{
			Current_Sub_Task = current_task->Move_To_Next_Sub_Task(Current_Sub_Task, "EQUIP_PUT_CONFIRM");
			if (Current_Sub_Task->carry_type_ == "EQUIP_PUT_CONFIRM")
			{
				EVENT_HANDLER.Sub_Task_Dispatch_Event(Current_Sub_Task, current_task);
				current_task->Set_Status(TASK_CHAIN_STATUS::EQUIP_PUT_CONFIRM_CHECK);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_PUT_CONFIRM_CHECK:
		{
			//在START里面判断子任务的状态;		
			current_task->Check_Feedback(Current_Sub_Task);

			if (Current_Sub_Task->sub_task_status_ == DONE)
			{
#if 1
				if (RABBITMQ_SERVICE.ApplyUnit(current_task->getTrayPut(), current_task->Order_ID_))//判断当前滚筒线上是否有尚未取走的空轮)
				{
					WCS_DB_->setCurrentTableStorageStatus("s_storage_station_status", "IDLE", current_task->getTrayGet());
						current_task->Set_Status(EQUIP_PUT);
						std::stringstream ss;
						ss << "RABBITMQ_SERVICE:ApplyUnit," << "EQUIP ID:" << current_task->getTrayPut() << ",ORDER_ID:" << current_task->Order_ID_;
						log_info_color(log_color::purple, ss.str().c_str());
				}
				
#endif

				/*WCS_DB_->setCurrentTableStorageStatus("s_storage_station_status", "IDLE", current_task->getTrayGet());
				current_task->Set_Status(EQUIP_PUT);*/
			}
			else if (Current_Sub_Task->sub_task_status_ == REJECTED || Current_Sub_Task->sub_task_status_ == FAILED)
			{
				current_task->Set_Status(ERR);
			}
			else if (Current_Sub_Task->sub_task_status_ == ABORTED)
			{
				current_task->Set_Status(ABORT);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_PUT://前往输送线放空轮
		{
			Current_Sub_Task = current_task->Move_To_Next_Sub_Task(Current_Sub_Task, "EQUIP_PUT");
			if (Current_Sub_Task->carry_type_ == "EQUIP_PUT")
			{
				EVENT_HANDLER.Sub_Task_Dispatch_Event(Current_Sub_Task, current_task);
				current_task->Set_Status(TASK_CHAIN_STATUS::EQUIP_PUT_CHECK);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_PUT_CHECK:
		{
			//在START里面判断子任务的状态;		
			current_task->Check_Feedback(Current_Sub_Task);

			if (Current_Sub_Task->sub_task_status_ == DONE)
			{
				current_task->Set_Status(EQUIP_PUT_RELEASE);
			}
			else if (Current_Sub_Task->sub_task_status_ == REJECTED || Current_Sub_Task->sub_task_status_ == FAILED)
			{
				current_task->Set_Status(ERR);
			}
			else if (Current_Sub_Task->sub_task_status_ == ABORTED)
			{
				current_task->Set_Status(ABORT);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_PUT_RELEASE://退出到输送线放空轮的安全位置
		{
			Current_Sub_Task = current_task->Move_To_Next_Sub_Task(Current_Sub_Task, "EQUIP_PUT_RELEASE");
			if (Current_Sub_Task->carry_type_ == "EQUIP_PUT_RELEASE")
			{
				EVENT_HANDLER.Sub_Task_Dispatch_Event(Current_Sub_Task, current_task);
				current_task->Set_Status(TASK_CHAIN_STATUS::EQUIP_PUT_RELEASE_CHECK);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_PUT_RELEASE_CHECK:
		{
			//在START里面判断子任务的状态;		
			current_task->Check_Feedback(Current_Sub_Task);

			if (Current_Sub_Task->sub_task_status_ == DONE)
			{
				current_task->Set_Status(OVER);
#if 1
				RABBITMQ_SERVICE.ReportOrderStatus(current_task->Order_ID_, AGV_RESPONSE_WC::AGV_RESPONSE_SUCC, current_agv->AGV_ID_, " ", current_task->getTrayGet());//空轮放到产线，并回到安全位置，上报MES
#endif
				std::stringstream ss;
				ss << "RABBITMQ_SERVICE:ReportOrderStatus," << "Task ID:" << current_task->Order_ID_ << ",STAUTS:" << AGV_RESPONSE_WC::AGV_RESPONSE_SUCC << ",AGV_ID:" << current_agv->AGV_ID_
					<< ",PALLETNO:" <<" " << "Location:" << current_task->getTrayGet();
				log_info_color(log_color::purple, ss.str().c_str());
			}
			else if (Current_Sub_Task->sub_task_status_ == REJECTED || Current_Sub_Task->sub_task_status_ == FAILED)
			{
				current_task->Set_Status(ERR);
			}
			else if (Current_Sub_Task->sub_task_status_ == ABORTED)
			{
				current_task->Set_Status(ABORT);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_GET://前往输送线取满轮
		{
			Current_Sub_Task = current_task->Move_To_Next_Sub_Task(Current_Sub_Task, "EQUIP_GET");
			if (Current_Sub_Task->carry_type_ == "EQUIP_GET")
			{
				EVENT_HANDLER.Sub_Task_Dispatch_Event(Current_Sub_Task, current_task);
				current_task->Set_Status(TASK_CHAIN_STATUS::EQUIP_GET_CHECK);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::EQUIP_GET_CHECK:
		{
			//在START里面判断子任务的状态;		
			current_task->Check_Feedback(Current_Sub_Task);
#if 1
			if (!RABBITMQ_SERVICE.FeedbackUnitStatus(current_task->getGoodsGet(), current_task->Order_ID_))
			{
				current_task->Set_Status(ERR);
				std::stringstream ss;
				ss << "RABBITMQ_SERVICE:FeedbackUnitStatus," << "EQUIP_ID:" << current_task->getGoodsGet() << ",ORDER_ID:" << current_task->Order_ID_<<"Failed!!!";
				log_info_color(log_color::red, ss.str().c_str());
			}
#endif
			
			if (Current_Sub_Task->sub_task_status_ == DONE)
			{
				current_task->Set_Status(BUFFER_PUT);
#if 1
				RABBITMQ_SERVICE.ReportStopGetGoods(current_task->getGoodsGet(),current_task->Order_ID_);//空轮放到产线，并回到安全位置，上报MES
#endif
				std::stringstream ss;
				ss << "RABBITMQ_SERVICE:ReportStopGetGoods," << "EQUIP_ID:" << current_task->getGoodsGet() << ",ORDER_ID:" << current_task->Order_ID_; 
				log_info_color(log_color::purple, ss.str().c_str());
			}
			else if (Current_Sub_Task->sub_task_status_ == REJECTED || Current_Sub_Task->sub_task_status_ == FAILED)
			{
				current_task->Set_Status(ERR);
			}
			else if (Current_Sub_Task->sub_task_status_ == ABORTED)
			{
				current_task->Set_Status(ABORT);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::BUFFER_PUT://前往缓存区放满轮
		{
			Current_Sub_Task = current_task->Move_To_Next_Sub_Task(Current_Sub_Task, "BUFFER_PUT");
			if (Current_Sub_Task->carry_type_ == "BUFFER_PUT")
			{
				std::string storage_group;
				std::string goods_put;
				if (WCS_DB_->getCurrentEquipToStorage(storage_group, current_task->getStart()))//获取到当前水箱距离较近的缓存区
				{
					if (WCS_DB_->getCurrentTableStorageName("s_storage_station_status", "EMPTY", goods_put, "AREA", storage_group))//就近找一个空地
					{
						WCS_DB_->setCurrentTableStorageStatus("s_storage_station_status", "RESERVE", goods_put);

						WCS_DB_->updateOrderTargetStorageInfo(current_task, "CARRY", "kh_report_order_info");//更新当前放满轮位置

						Current_Sub_Task->task_to_ = goods_put;
						current_task->setGoodsPut(goods_put);
						EVENT_HANDLER.Sub_Task_Dispatch_Event(Current_Sub_Task, current_task);
						current_task->Set_Status(TASK_CHAIN_STATUS::BUFFER_PUT_CHECK);
					}
				}
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::BUFFER_PUT_CHECK://满轮放到缓存区
		{
			//在START里面判断子任务的状态;		
			current_task->Check_Feedback(Current_Sub_Task);

			if (Current_Sub_Task->sub_task_status_ == DONE)
			{
				current_task->Set_Status(OVER);
				WCS_DB_->setCurrentTableStorageStatus("s_storage_station_status", "IDLE", current_task->getGoodsPut());

#if 1
				RABBITMQ_SERVICE.ReportAgvAction(current_task->getTrayGet(), CageType::GOODS, WorkType::IN_STORAGE, current_task->getPalletno(), current_agv->AGV_ID_);//放满轮时给的信号
#endif
				std::stringstream ss;
				ss << "RABBITMQ_SERVICE:ReportAgvAction," << "CageName:" << current_task->getTrayGet() << ",CageType:" << CageType::GOODS << ",WorkType:" << WorkType::IN_STORAGE
					<<",PalletNo:"<< current_task->getPalletno() <<",AGV_ID:" << current_agv->AGV_ID_;
				log_info_color(log_color::purple, ss.str().c_str());

#if 1
				RABBITMQ_SERVICE.ReportOrderStatus(current_task->Order_ID_, AGV_RESPONSE_WC::AGV_RESPONSE_SUCC, current_agv->AGV_ID_, current_task->getPalletno(), current_task->getGoodsPut());//满轮放到储位后，并回到安全位置，上报MES
#endif
				std::stringstream ss2;
				ss2 << "RABBITMQ_SERVICE:ReportOrderStatus" <<",Task ID:"<<current_task->Order_ID_<<",STAUTS:"<<AGV_RESPONSE_WC::AGV_RESPONSE_SUCC <<",AGV_ID:"<<current_agv->AGV_ID_
				   <<",PALLETNO:"<<current_task->getPalletno()<<",Location:"<<current_task->getGoodsPut();
				log_info_color(log_color::purple, ss2.str().c_str());
			}
			else if (Current_Sub_Task->sub_task_status_ == REJECTED || Current_Sub_Task->sub_task_status_ == FAILED)
			{
				current_task->Set_Status(ERR);
			}
			else if (Current_Sub_Task->sub_task_status_ == ABORTED)
			{
				current_task->Set_Status(ABORT);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::PARKING:
		{
			Current_Sub_Task = current_task->Move_To_Next_Sub_Task(Current_Sub_Task, "PARKING");

			if (Current_Sub_Task->carry_type_ == "PARKING")
			{
				std::stringstream ss;
				ss << "task_chain_manager:Now parking=" << BATTERY_MANAGE.Now_Parking_;
				log_info_color(log_color::green, ss.str().c_str());
				EVENT_HANDLER.Sub_Task_Dispatch_Event(Current_Sub_Task, current_task);
				current_task->Set_Status(TASK_CHAIN_STATUS::PARKING_CHECK);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::PARKING_CHECK:
		{
			//在PARKING里面判断子任务的状态;
			current_task->Check_Feedback(Current_Sub_Task);

			if (Current_Sub_Task->sub_task_status_ == DONE)
			{
				current_task->Set_Status(OVER);
				current_agv->Invoke_AGV_Parking_ = INVOKE_STATUS::STOP_INVOKE;
			}
			else if (Current_Sub_Task->sub_task_status_ == REJECTED || Current_Sub_Task->sub_task_status_ == FAILED)
			{
				current_task->Set_Status(ERR);
			}
			else if (Current_Sub_Task->sub_task_status_ == ABORTED)
			{
				current_task->Set_Status(ABORT);
			}
			it++;
			break;
		}

		case TASK_CHAIN_STATUS::IS_CHARGING:
		{
			//在Charging里面判断子任务的状态;
			current_task->Check_Feedback(Current_Sub_Task);
			if (Current_Sub_Task->sub_task_status_ == DONE)
			{
				current_task->Set_Status(OVER);
			}
			else if (Current_Sub_Task->sub_task_status_ == CHARGING)
			{
				if (current_agv->Is_Charging_ != CHARGING_STATUS::CHARGING_PAUSE)
				{
					current_agv->Is_Charging_ = CHARGING_STATUS::CHANRING_CHARGING;
				}
			}
			else if (Current_Sub_Task->sub_task_status_ == REJECTED || Current_Sub_Task->sub_task_status_ == FAILED)
			{
				current_task->Set_Status(ERR);
			}
			else if (Current_Sub_Task->sub_task_status_ == ABORTED)
			{
				current_agv->Is_Charging_ = CHARGING_STATUS::CHANRING_STOP;
				current_task->Set_Status(ABORT);
			}
			it++;
			break;
		}

		case  TASK_CHAIN_STATUS::OVER:
		{
			if (current_task->getType() == "CHARGING")
			{
				current_task->Set_Over_Time_And_Duration();
				current_agv->Is_Charging_ = CHARGING_STATUS::CHANRING_STOP;

				std::stringstream ss;
				ss << current_task->Task_ID_ << ":Charging task completed !";
				log_info_color(log_color::purple, ss.str().c_str());
				delete current_task;
				delete Current_Sub_Task;
				it = Active_Task_List_.erase(it);
			}
			else if (current_task->getType() == "CARRY")
			{
				current_task->Set_Over_Time_And_Duration();
				WCS_DB_->updateOrderStatusToDone(current_task, "CARRY", "kh_report_order_info");
				ORDER_MANAGE.Delete_DONE_From_Full_Order_List(current_task->Order_ID_);
				AGV_MANAGE.setIdel(Current_Sub_Task->agv_id_);
				AGV_MANAGE.Set_Unlock(Current_Sub_Task->agv_id_);

				std::stringstream ss;
				ss << "Carry order ID:" << current_task->Order_ID_ << ",is from:" << current_task->getStart() << ",to:" << current_task->getTargeted() << " completed !";
				log_info_color(log_color::purple, ss.str().c_str());
				delete current_task;
				delete Current_Sub_Task;
				it = Active_Task_List_.erase(it);
			}
			else if (current_task->getType() == "PARKING")
			{
				AGV_MANAGE.setIdel(Current_Sub_Task->agv_id_);
				AGV_MANAGE.Set_Unlock(Current_Sub_Task->agv_id_);

				std::stringstream ss;
				ss << "Parking task completed !";
				log_info_color(log_color::purple, ss.str().c_str());
				delete current_task;
				delete Current_Sub_Task;
				it = Active_Task_List_.erase(it);
			}
			else
			{
				std::stringstream ss;
				ss << Current_Sub_Task->task_id_ << ":Abnormal  task finish !";
				log_info_color(log_color::red, ss.str().c_str());
				delete current_task;
				delete Current_Sub_Task;
				it = Active_Task_List_.erase(it);
			}
			break;
		}

		case  TASK_CHAIN_STATUS::ABORT:
		{

			AGV_MANAGE.setIdel(Current_Sub_Task->agv_id_);
			if (current_task->getType() == "CARRY")
			{
				WCS_DB_->updateOrderStatusToErr(current_task, current_task->getType(), "kh_report_order_info");
#if 1
				if (current_task->getMode() == "GOODS")
				{
					RABBITMQ_SERVICE.ReportOrderStatus(current_task->Order_ID_, AGV_RESPONSE_WC::AGV_RESPONSE_FAILED, current_agv->AGV_ID_, current_task->getPalletno(), current_task->getGoodsPut());//满轮任务失败，上报MES
				}
				else if (current_task->getMode() == "TRAY")
				{
					RABBITMQ_SERVICE.ReportOrderStatus(current_task->Order_ID_, AGV_RESPONSE_WC::AGV_RESPONSE_FAILED, current_agv->AGV_ID_, "", current_task->getTrayGet());//空轮任务失败，上报MES
				}

#endif
				std::stringstream ss2;
				ss2 << "RABBITMQ_SERVICE:ReportOrderStatus" << ",Task ID:" << current_task->Order_ID_ << ",STAUTS:" << AGV_RESPONSE_WC::AGV_RESPONSE_FAILED << ",AGV_ID:" << current_agv->AGV_ID_
					<< ",PALLETNO:" << current_task->getPalletno() << ",Location:" << current_task->getGoodsPut();
				log_info_color(log_color::purple, ss2.str().c_str());

			}
			std::stringstream ss;
			ss << current_task->Task_ID_ << ":ABORTED Task !!!";
			log_info_color(log_color::blue, ss.str().c_str());



			delete current_task;
			delete Current_Sub_Task;
			it = Active_Task_List_.erase(it);
			break;
		}

		case  TASK_CHAIN_STATUS::ERR:
		{
			if (current_agv->Is_Charging_ == CHARGING_STATUS::CHANRING_CHARGING)
			{
				current_agv->Is_Charging_ = CHARGING_STATUS::CHANRING_STOP;              //当充电任务异常时，会恢复未充电状态;
			}
			if (current_task->getType() == "CARRY")
			{
				WCS_DB_->updateOrderStatusToErr(current_task, current_task->getType(), "kh_report_order_info");
#if 1
				if (current_task->getMode() == "GOODS")
				{
					RABBITMQ_SERVICE.ReportOrderStatus(current_task->Order_ID_, AGV_RESPONSE_WC::AGV_RESPONSE_FAILED, current_agv->AGV_ID_, current_task->getPalletno(), current_task->getGoodsPut());//满轮任务失败，上报MES
				}
				else if (current_task->getMode() == "TRAY")
				{
					RABBITMQ_SERVICE.ReportOrderStatus(current_task->Order_ID_, AGV_RESPONSE_WC::AGV_RESPONSE_FAILED, current_agv->AGV_ID_, "", current_task->getTrayGet());//空轮任务失败，上报MES
				}

#endif
				std::stringstream ss2;
				ss2 << "RABBITMQ_SERVICE:ReportOrderStatus" << ",Task ID:" << current_task->Order_ID_ << ",STAUTS:" << AGV_RESPONSE_WC::AGV_RESPONSE_FAILED << ",AGV_ID:" << current_agv->AGV_ID_
					<< ",PALLETNO:" << current_task->getPalletno() << ",Location:" << current_task->getGoodsPut();
				log_info_color(log_color::purple, ss2.str().c_str());

			}
			
			AGV_MANAGE.setIdel(Current_Sub_Task->agv_id_);

			std::stringstream ss;
			ss << current_task->Task_ID_ << ":ERR Task !!!";
			log_info_color(log_color::red, ss.str().c_str());
			delete current_task;
			delete Current_Sub_Task;
			it = Active_Task_List_.erase(it);
			break;
		}

		default:
			std::stringstream ss;
			ss << Current_Sub_Task->task_id_ << ":TASK_CHAIN_STATUS Default !!!";
			log_info_color(log_color::blue, ss.str().c_str());
			delete current_task;
			delete Current_Sub_Task;
			it = Active_Task_List_.erase(it);
			break;
		}
	}

}

std::vector<Task_Chain*>  Task_Chain_Manage::Get_Full_Task_List()
{
	return Full_Task_List_;
}

std::vector<Task_Chain*>  Task_Chain_Manage::Get_Active_Task_List()
{
	return Active_Task_List_;
}

std::vector<Task_Chain*>  Task_Chain_Manage::Get_Inactive_Task_List()
{
	return Inactive_Task_List_;
}

void Task_Chain_Manage::Add_to_full_list_if_not_exist(int id, int state)
{
	Full_Sub_Task_List_[id] = state;
}

std::string Task_Chain_Manage::getReportPoint(std::string target_point)
{
	std::string result = "";
	std::map<std::string, std::string> ::iterator it = Report_Point_Map_.find(target_point);
	if (it != Report_Point_Map_.end())
	{
		return it->second;
	}
	else {
		return result;
	}
}

float Task_Chain_Manage::ReadNum(std::string s)
{
	int i = 0, n = 0;
	int point_index = s.find('.');
	float result = 0, under_0 = 0;//under_0存储小数部分  
	if (count(s.begin(), s.end(), '.') > 1)
	{
		return 0;//字符串里只能有1个或0个小数点，不然出错退出; 
	}
	if (s.find('.') != -1)//字符串里有小数点;
	{
		if ((point_index == 0) || (point_index == s.size() - 1))//小数点位置合理，不能在字符串第1位,且不能在最后一位;  
		{
			return 0;
		}
		for (i = 0; i <= point_index - 1; i++)//计算整数部分;  
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				result = result * 10 + s[i] - 48;
			}
		}
		for (i = s.size() - 1; i >= point_index - 1; i--)//计算小数部分;  
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				if (i == point_index - 1)
				{
					under_0 = under_0 * 0.1 + 0;//i=小数点前一位，under_0+0; 
				}
				else
				{
					under_0 = under_0 * 0.1 + s[i] - 48;
				}
			}
		}
		result = result + under_0;//把整数部分和小数部分相加;  
	}
	else//字符串只有整数部分;  
	{
		for (i = 0; i <= s.size() - 1; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				result = result * 10 + s[i] - 48;
			}
		}
	}

	return result;

}

void Task_Chain_Manage::splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c)
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

bool Task_Chain_Manage::Is_AGV_In_Parking_Station(AGV* current_agv)
{
	if (current_agv->AGV_In_Station_ == "P1" || current_agv->AGV_In_Station_ == "P2" || current_agv->AGV_In_Station_ == "P3" ||
		current_agv->AGV_In_Station_ == "P4" || current_agv->AGV_In_Station_ == "P5")
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string Task_Chain_Manage::getStartTime()
{
	std::string order_start_time;
	struct tm *tm_now;
	time_t start_time;
	time(&start_time);
	tm_now = localtime(&start_time);
	std::stringstream ss;
	ss << tm_now->tm_year + 1900 << "-" << tm_now->tm_mon + 1 << "-" << tm_now->tm_mday << " " << tm_now->tm_hour << ":" << tm_now->tm_min << ":" << tm_now->tm_sec;
	order_start_time = ss.str();
	return order_start_time;
}

void Task_Chain_Manage::cancelTaskChain(std::string order_id, int task_id)
{
	WCS_DB_->abortTask(task_id);
	std::vector<Task_Chain*>::iterator it;
	for (it = Active_Task_List_.begin(); it != Active_Task_List_.end(); ++it)
	{
		Task_Chain* current_task = *it;

		if (current_task->Task_ID_ == task_id)
		{
			current_task->Set_Status(ABORT);
		}
	}

	std::stringstream ss;
	ss << "Order ID:" << order_id << "Cancel Order Successful!";
	log_info_color(log_color::blue, ss.str().c_str());
}
