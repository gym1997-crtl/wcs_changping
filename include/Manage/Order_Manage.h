
#ifndef _Order_Manage_ED_H
#define _Order_Manage_ED_H
#include <string>  
#include <map> 
#include <vector>
#include <iostream>  
#include <boost/serialization/singleton.hpp>
#include <boost/thread.hpp>
#include "Manage/Manage_Define.h"
#include "ADODatabase/WCS_Database.h"

class Order_Manage 
{  
public:  

	Order_Manage();  

	~Order_Manage();  

	void Initial();

	void Download_Order_Info_From_Database_Event();

	void Quantity_Change_Confirm(Order* curretn_order);

	bool Order_Dispatchable(Order* order);

	bool Add_to_full_list_if_not_exist(Order order);

	bool Get_All_NEW_Order(Order order);

	std::vector<Order*> Sort_Active_Order_By_Priority();

	bool Delete_DONE_From_Full_Order_List(std::string order_id);

	std::map<std::string, Order> Get_All_Order();

	std::map<std::string, Order> getNewOrder();

	void Order_Manage::setNewOrder(std::map<std::string, Order> order_map);

	bool checkOrderList(AGV* associate_AGV);

	bool Revoke_Order(std::string order_id);

	bool Update_Priority(std::string order_id, std::string priority);

	bool Add_to_full_list_if_not_exist(Task_Chain_Info order);

	void reserveParkingStation(std::string parking_station);

	void releaseParkingStation(std::string parking_station);

	bool getParkingStation(std::string &parking_station, std::string &is_charging, int agv_type);

	bool getStationIsCharging(std::string current_shataion);

	bool getMustChargingStation(std::string &parking_station);

	bool QueryOrderInfo(std::string order_id, Order *order_in);

protected:  


private:
	std::map<std::string, Order> New_Order_List_;
	std::map<std::string, Order> Full_Order_List_;   //KH_REPORT_TASK_INFO全部信息;
	std::map<std::string, Order*> All_Order_List_;
	std::map<std::string, Order*> Active_Order_List_;
	std::map<std::string, Order*> Inactive_Order_List_;

	WCS_Database * WCS_Con_;

}; 

typedef boost::serialization::singleton<Order_Manage> Singleton_Order_Manage;
#define ORDER_MANAGE Singleton_Order_Manage::get_mutable_instance()

#endif //_Order_Manage_ED_H