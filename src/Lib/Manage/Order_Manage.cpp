#include "Common/Common.h"
#include "ADODatabase/DatabaseManage.h"
#include "Manage/Order_Manage.h"  
#include "Manage/Storage_Manage.h"
#include "comm/simplelog.h"

Order_Manage::Order_Manage()
{

}

Order_Manage::~Order_Manage()
{

}

void Order_Manage::Initial()
{
	WCS_Con_=DATABASE_MANAGE.Get_WCS_DB();
}

void Order_Manage::Download_Order_Info_From_Database_Event()
{
	WCS_Con_->updateOrderInfo();
	WCS_Con_->updateNewOrderInfo();
}

bool Order_Manage::Add_to_full_list_if_not_exist(Order current_order)
{
	std::map<std::string, Order>::iterator it=Full_Order_List_.find(current_order.ORDER_ID_);
	if(it!=Full_Order_List_.end())
	{
		it->second = current_order;
		return false;
	}
	else{
		Full_Order_List_[current_order.ORDER_ID_]=current_order;
		return true;
	}
}

bool Order_Manage::QueryOrderInfo(std::string order_id, Order *order_in) {
	if (Full_Order_List_.find(order_id) != Full_Order_List_.end())
	{
		*order_in = Full_Order_List_[order_id];
		return true;
	}
	else
	{
		return false;
	}
}

bool Order_Manage::Get_All_NEW_Order(Order current_order)
{	
	std::map<std::string, Order>::iterator it= New_Order_List_.find(current_order.ORDER_ID_);
	if(it!= New_Order_List_.end())
	{
		it->second = current_order;
		return false;
	}
	else
	{
		New_Order_List_[current_order.ORDER_ID_]=current_order;
		return true;
	}
}

bool Order_Manage::Delete_DONE_From_Full_Order_List(std::string order_id)
{
	Full_Order_List_.erase(order_id);
	return true;
}

std::map<std::string, Order> Order_Manage::Get_All_Order()
{
	return Full_Order_List_;
}
 
std::map<std::string, Order> Order_Manage::getNewOrder()
{
	return New_Order_List_;
}

void Order_Manage::setNewOrder(std::map<std::string, Order> order_map)
{
	New_Order_List_ = order_map;
}

bool Order_Manage::checkOrderList(AGV* associate_AGV)
{
	return WCS_Con_->checkNewOrderList(associate_AGV);
}

bool Order_Manage::Revoke_Order(std::string order_id)
{
	if (WCS_Con_->revokeDodOrder(order_id))
	{
		std::stringstream ss;
		ss << order_id << ":Revoke DOD order successful " << std::endl;
		log_info_color(log_color::green, ss.str().c_str());
		return true;
	}
	else
	{
		std::stringstream ss;
		ss << order_id << ":Revoke DOD order failed " << std::endl;
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool Order_Manage::Update_Priority(std::string order_id, std::string priority)
{
	if (WCS_Con_->updateDodOrderPriority(order_id,priority))
	{
		std::stringstream ss;
		ss << order_id << ":Revoke DOD order successful " << std::endl;
		log_info_color(log_color::green, ss.str().c_str());
		return true;
	}
	else
	{
		std::stringstream ss;
		ss << order_id << ":Revoke DOD order failed " << std::endl;
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool Order_Manage::getParkingStation(std::string &parking_station, std::string &is_charging, int agv_type)
{
	if (WCS_Con_->getCurrentParkingStation(parking_station, is_charging, agv_type))
	{
		std::stringstream ss;
		ss << "get Current Parking Station successful " << parking_station;
		log_info_color(log_color::green, ss.str().c_str());
		return true;
	}
	else
	{
		return false;
	}
}

void Order_Manage::reserveParkingStation(std::string parking_station)
{
	WCS_Con_->reserveCurrentParkingStation(parking_station);
}

void Order_Manage::releaseParkingStation(std::string parking_station)
{
	WCS_Con_->releaseCurrentParkingStation(parking_station);
}

bool Order_Manage::getStationIsCharging(std::string parking_station)     //true：当前停车点没有充电桩;
{
	if (WCS_Con_->getCurrentStationIsCharging(parking_station))
	{
		/*std::stringstream ss;
		ss << "get Current Station Is Charging successful " << parking_station;
		log_info_color(log_color::green, ss.str().c_str());*/
		return true;
	}
	else
	{
		/*std::stringstream ss;
		ss << "get Current Station Is Charging failed ";
		log_info_color(log_color::red, ss.str().c_str());*/
		return false;
	}
}


bool Order_Manage::getMustChargingStation(std::string &parking_station)
{
	if (WCS_Con_->getCurrentMustChargingStation(parking_station))
	{
		std::stringstream ss;
		ss << "get Current Must Charging Station successful " << parking_station;
		log_info_color(log_color::green, ss.str().c_str());
		return true;
	}
	else
	{
		/*std::stringstream ss;
		ss << "get Current Must Charging Station failed ";
		log_info_color(log_color::red, ss.str().c_str());*/
		return false;
	}
}