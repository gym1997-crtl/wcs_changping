#ifndef _WCS_Database_EDWARD_
#define _WCS_Database_EDWARD_

#include <map>
#include <deque>
#include <vector>
#include "ADODatabase/ADODatabase.h"
#include "Manage/Manage_Define.h"
#include "Core/Task_Define.h"
#include "Core/ModelStationParking.h" 
#include "Core/ModelBridge.h"

class Task_Chain;

class WCS_Database
{

public:
		//void insert_sql_data();
	WCS_Database();

	~WCS_Database();

	void setWcsAdo(ADOcon ADO);

	int getMaxTaskId();

	int getMaxWcsTaskId();//得到WCS中最大的ID;

	bool checkOrderInfoCount(int &max_id);

	std::vector<Oreder_Task*> updateTaskOrderInfo(std::vector<Oreder_Task*>Executing_List);

	bool updateOrderInfo();

	bool updateNewOrderInfo();

	void setCurrentStorageStatus(std::string table_name, std::string state, std::string storage_name);

	bool updateOrderStatusToDoing(std::string order_id,int agv_id);

	void updateOrderStatusToDone(Task_Chain* the_task, std::string order_type, std::string sql_table_name);

	void updateOrderStatusToErr(Task_Chain* the_task, std::string order_type, std::string sql_table_name);

	void updateOrderTargetStorageInfo(Task_Chain* the_task, std::string order_type, std::string sql_table_name);

	bool copyOrderInfo(Task_Chain_Info &order_in);

	void deleteCurrentOrder(std::string order_id);

	void splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c);

	int timestamp;

	int readTaskStatus(int taskid);

	bool stopCurrentCharging(AGV* agv);

	void abortTask(int id);

	bool insertTask(int task_id_, std::string task_from_, std::string task_to_, int priority_, int agv_type_, int task_type_, int auto_dispatch_, int agv_id_, int task_extra_param_type, std::string task_extra_param);

	bool addOrder(std::string ORDER_ID, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, int AGV_ID);

	bool addParkingChargingOrder(std::string START, std::string TARGET, std::string TYPE, int AGV_ID);

	bool insertOrderToDb(std::string START,std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE,std::string TYPE);
	
	bool insertOrderToDb(std::string ORDER_ID, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE);
	
	bool insertOrderToDb(std::string ORDER_ID, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, int agvID);
	
	bool insertOrderToDb(std::string ORDER_ID, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, int agvID, std::string palletNo);

	bool checkNewOrderList(AGV* associate_AGV);

	bool revokeDodOrder(std::string wcs_id);

	bool updateDodOrderPriority(std::string wcs_id,std::string priority);

	void setErrStorageOrder(int wcs_task_id);

	bool setCurrentTableStorageStatus(std::string table_name, std::string resource_status, std::string storage_name);

	void setCurrentStationStatus();

	bool getCurrentParkingStation(std::string &station_name, std::string &is_charging, int agv_type);

	void reserveCurrentParkingStation(std::string station_name);

	float getDatabaseCurrentWeightInfo();

	void updateCurrentWeightInfo(double weight,std::string status);

	void releaseCurrentParkingStation(std::string station_name);

	void setDatabaseCurrentComfirmStatus(std::string current_confirm, std::string status);

	void setDatabaseCurrentBridgeStatus(std::string current_confirm, std::string status);

	void setDatabaseCurrentParkingStatus(std::string current_parking, std::string status);

	void setDatabaseEquipmentStatus(std::string equipment_id_, std::string status);

	bool getDatabaseCurrentComfirmStatus(std::string current_confirm);

	bool getDatabaseCurrentBridgeStatus(std::string current_bridge);

	void getConfirmStorage();

	bool getParkingStorage(std::vector<ModelStationParking*> *parkings );

	bool getCurrentStationIsCharging(std::string current_station);

	bool getCurrentMustChargingStation(std::string &station_name);

	void setDatabaseCurrentEquipmentInfoStatus(std::string current_equipment, std::string equip_status);

	void setDatabaseCurrentEquipmentAppleyStatus(std::string current_equipment, std::string status);

	std::string getDatabaseCurrentEquipmentInfoStatus(std::string current_equipment);

	std::string getCurrentAGVIsBack(int agv_id);

	bool getDatabaseCurrentNextNewOrder(std::string statioin,std::string agv_type);
	// PLC 相关流程
	bool LoadPLCMap(std::map<std::string, std::map<int, std::string>>* plc_map_, std::string table_name, std::vector<std::string> table_fields_);

	bool updatePLCStatus(std::string dev_name, std::string plc_status);

	bool updatePLCMsgStatus(std::string plc_status);

	bool updatePLCReadStatus(std::string plc_status);

	bool updatePLCMsgStatus(std::string dev_name, std::string plc_status);
	
	bool updatePLCReadStatus(std::string plc_name, std::string plc_status);

	bool loadFromDB(std::string table_name, std::vector<std::string> table_fields, std::vector<std::vector<std::string>>* result_list);
	// END-PLC

	bool getCurrentEquipToStorage(std::string &storage_group, std::string equip_name);

	bool getCurrentTableStorageName(std::string table_name, std::string storage_status, std::string &storage_name, std::string storage_type, std::string storage_group);
	
	int GetAgvExeGoodsTask(std::string palletNo, std::string status, std::string mode);
	
	bool plcForbidAllStorage();
	bool readAreaInfo(std::map<int, std::vector<Pos_Info>> *all_area);
	bool loadWcsTableListFromDB(std::vector<Sql_Table_Attri> &sql_table_list_);
	bool getStorageList(std::map<int, Storage> &storage_map, std::string sql_table_name);
	void updateWcsStorageStatus(std::string sql_table_name,std::string storage_name,std::string status_name ,std::string status);
	bool loadParkingStationNameListFromDB(std::vector<std::string> &parkingStationNameList);
	bool loadListFromDB(std::vector<std::string> &nameList, std::string tableName, std::string listName);
	std::string WCS_Database::getStorageStatus(std::string &storage_name);
	//小保当盘点接口
	bool changeAgvMode(std::string equip_mode);
	bool agvBackSignal(int agv_id, std::string mode);
private:
	std::vector<int>WCS_TASK_ID_;
	std::vector<std::string>storage_up_list;
	std::vector<std::string>storage_down_list;


private:

	ADOcon WCS_ADO_;
	_RecordsetPtr recordPtr_;
	_RecordsetPtr recordPtr2_;
	_RecordsetPtr recordPtr3_;
	_RecordsetPtr recordPtr4_;

	int confirm1;
	int confirm2;
	int confirm3;
	int confirm4;
	int confirm5;

private:
	std::vector<Sql_Table_Attri> sql_table_list_;

};

#endif