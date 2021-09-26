#include "Manage/Storage_Manage.h"  
#include "ADODatabase/DatabaseManage.h"


Storage_Manage::Storage_Manage()
{
	mainwindow_delegate_ = nullptr;
}

Storage_Manage::~Storage_Manage()
{

}

void Storage_Manage::setStorageStatusNotifier(Storage_Status_Notifier *notifier)
{
	storage_status_notifier_ = notifier;
}

void Storage_Manage::Set_MainWindow_Delegate(MainWindowDelegate* mw)
{
	mainwindow_delegate_ = mw;
}

void Storage_Manage::Initial()
{
	WCS_CON_=DATABASE_MANAGE.Get_WCS_DB();
	WCS_CON_->loadWcsTableListFromDB(sql_table_list_);
	storage_list_map_ = loadStorageMapList();
}

bool Storage_Manage::Get_Full_Storage(std::vector<Storage*> &full_storage_list)
{
	return true;
}

bool Storage_Manage::Set_Lock_Storage(std::string storage_name)
{
	return true;
}

bool Storage_Manage::Set_Empty_Storage(std::string storage_name)
{
	return true;
}

bool Storage_Manage::Set_Full_Storage(std::string storage_name)
{
	return true;
}

bool Storage_Manage::Insert_Order(std::string start, std::string target, int priority, std::string status, std::string mode, std::string type)
{
	return WCS_CON_->insertOrderToDb(start, target, priority, status, mode, type);
}

bool Storage_Manage::Insert_Order(std::string order_id, std::string start, std::string target, int priority, std::string status, std::string mode, std::string type)
{
	return WCS_CON_->insertOrderToDb(order_id, start, target, priority, status, mode, type);
}


bool Storage_Manage::Insert_Order(std::string order_id, std::string start, std::string target, int priority, std::string status, std::string mode, std::string type, int agvID)
{
	return WCS_CON_->insertOrderToDb(order_id, start, target, priority, status, mode, type, agvID);
}

bool Storage_Manage::Insert_Order(std::string order_id, std::string start, std::string target, int priority, std::string status, std::string mode, std::string type, int agvID, std::string palletNo)
{
	return WCS_CON_->insertOrderToDb(order_id, start, target, priority, status, mode, type, agvID, palletNo);
}

bool Storage_Manage::Insert_Order_XML(std::string uuid, Order order_in)
{
	//return XML_Database::Instance()->InsertOrderToDb(uuid, order_in);
	return true;
}

int Storage_Manage::GetAgvExeGoodsTask(std::string palletNo) {
	int agv_id = WCS_CON_->GetAgvExeGoodsTask(palletNo, "DOING", "GOODS");// TODO
	if (agv_id == 0)
	{
		WCS_CON_->GetAgvExeGoodsTask(palletNo, "NEW", "GOODS");
	}
	if (agv_id == 0)
	{
		WCS_CON_->GetAgvExeGoodsTask(palletNo, "DONE", "GOODS");
	}
	if (agv_id == 0)
	{
		WCS_CON_->GetAgvExeGoodsTask(palletNo, "DOING", "GOODS");
	}
	return agv_id;
}

int Storage_Manage::getMaxTaskId()
{
	int max_order_id = 1;
	if (!WCS_CON_->checkOrderInfoCount(max_order_id))
	{
		max_order_id = WCS_CON_->getMaxWcsTaskId();
	}
	else
	{
		int report_max_id = WCS_CON_->getMaxWcsTaskId();

		if (max_order_id < report_max_id)
		{
			max_order_id = report_max_id;
		}
	}
	return max_order_id;
}


bool Storage_Manage::setCurrentStorageStatus(std::string table_name, std::string resource_status, std::string storage_name)
{
	if (WCS_CON_->setCurrentTableStorageStatus(table_name, resource_status, storage_name))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//bool Storage_Manage::setConfirmMyLabel(int confirm, int status)
//{
//	if (mainwindow_delegate_)
//	{
//		//return mainwindow_delegate_->ChangeConfirmLableStatus(confirm, status);
//	}
//	return false;
//}

void Storage_Manage::changeConfirmStatus(std::string current_confirm, std::string status)
{
	WCS_CON_->setDatabaseCurrentComfirmStatus(current_confirm, status);
}

void Storage_Manage::changeParkingStatus(std::string current_parking, std::string status)
{

	WCS_CON_->setDatabaseCurrentParkingStatus(current_parking, status);
}

void Storage_Manage::changeEquipmentStatus(std::string equipment_id_, std::string status)
{

	WCS_CON_->setDatabaseEquipmentStatus(equipment_id_, status);
}


bool Storage_Manage::getCurrentComfirmStatus(std::string current_confirm)
{
	if (WCS_CON_->getDatabaseCurrentComfirmStatus(current_confirm))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Storage_Manage::setCurrentComfirmStatus(std::string current_confirm, std::string status)
{
	WCS_CON_->setDatabaseCurrentComfirmStatus(current_confirm, status);
}

std::vector<Sql_Table_Attri> Storage_Manage::getSqlableList() const
{
	return sql_table_list_;
}

std::map<std::string, std::map<int, Storage>> Storage_Manage::getStorageListMap()
{
	//boost::mutex::scoped_lock(mu_sql_storage_table_);
	return storage_list_map_;
}

void Storage_Manage::checkChange()
{
	boost::mutex::scoped_lock(mu_change_storage_status_);
	std::map<std::string, std::map<int, Storage>> tmp_storage_list_map_ = loadStorageMapList();
	for each (auto var in storage_list_map_)
	{// 哪张表
		std::string tableName = var.first;
		std::map<int, Storage> storageList = var.second;
		for each (auto var2 in storageList)
		{// 表的哪个Storage
			if (var2.second.Storage_Status_.compare(tmp_storage_list_map_[tableName][var2.first].Storage_Status_) != 0 || var2.second.Resource_status_.compare(tmp_storage_list_map_[tableName][var2.first].Resource_status_) != 0)
			{// Storage 的 Storage_Status_ 与之前的是否相同， 如果不同，发送改变的信号
				storage_status_notifier_->OnstorageStatusChanged(tmp_storage_list_map_[tableName][var2.first]);
				storage_list_map_[tableName][var2.first].Storage_Status_ = tmp_storage_list_map_[tableName][var2.first].Storage_Status_;
				storage_list_map_[tableName][var2.first].Resource_status_ = tmp_storage_list_map_[tableName][var2.first].Resource_status_;
			}
		}
	}
}

// 给出 storage 名，要更改的字段，要更改成为哪种类型
// 在数据库中更改对应字段
void Storage_Manage::changeStorageStatus(std::string storage_name, std::string status_name, std::string status)
{

	std::string sql_table_name;

	// 遍历 表 ，找到存在 storage_name 的表名
	std::map<std::string, std::map<int, Storage>>::iterator it = storage_list_map_.begin();

	for (; it != storage_list_map_.end(); it++) {
		std::map<std::string, std::map<int, Storage>>::iterator selectStorageMap = it;

		std::map<int, Storage> selectSql = it->second;
		std::map<int, Storage>::iterator it2 = selectSql.begin();

		for (; it2 != selectSql.end(); it2++)
		{
			if (!it2->second.Storage_Name_.compare(storage_name))
			{
				sql_table_name = it->first;
				break;
			}
		}
	}

	if (sql_table_name.compare("")) {
		// 更改对应 数据库 的信息
		WCS_CON_->updateWcsStorageStatus(sql_table_name, storage_name, status_name, status);
	}
	else {
		// 没找到库位名对应的表名
	}

}

std::map<std::string, std::map<int, Storage>> Storage_Manage::loadStorageMapList()
{
	std::map<std::string, std::map<int, Storage>> result;
	std::vector<Sql_Table_Attri>::iterator it = sql_table_list_.begin();

	for (; it != sql_table_list_.end(); it++) {
		if (it->sql_table_type.compare("storage") == 0) {
			// 如果是"storage"表
			std::map<int, Storage> storage_map;
			WCS_CON_->getStorageList(storage_map, it->sql_table_name);
			result[it->sql_table_name] = storage_map;
		}
	}
	return result;
}

/**
 * 从数据库加载所有站点名
 */
std::vector<std::string>  Storage_Manage::getAllStationName() {
	std::vector<std::string> result;
	for each (auto currentTable in storage_list_map_)
	{
		for each (auto currentStation in currentTable.second)
		{
			result.push_back(currentStation.second.Storage_Name_);
		}
	}
	return result;
}

/// <summary>
/// Gets the standard storage which status is like type.
/// </summary>
/// <param name="storage">The storage.</param>
/// <param name="status">The status.</param>
/// <returns>get storage success</returns>
/// Creator:MeiXu
/// CreateDate:2021/1/21
/// 
std::vector<std::string> Storage_Manage::getStandardStorage(const std::string& status) {
	std::vector<std::string> result;

	for each (auto var in storage_list_map_)
	{// 哪张表
		std::string tableName = var.first;
		std::map<int, Storage> table = var.second;
		for each (auto var2 in table)
		{// 表的哪个Storage
			Storage this_storage = var2.second;
			if (this_storage.Storage_Status_ == status)
			{// 
				result.push_back(this_storage.Storage_Name_);
			}
		}
	}
	return result;
}

/// <summary>
/// Gets the storage status.
/// </summary>
/// <param name="storage_name">Name of the storage.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/1/22
/// 
std::string Storage_Manage::getStorageStatus(const std::string& storage_name) {
	std::string result = "";
	for each (auto var in storage_list_map_)
	{// 哪张表
		std::string tableName = var.first;
		std::map<int, Storage> table = var.second;
		for each (auto var2 in table)
		{// 表的哪个Storage
			Storage this_storage = var2.second;
			if (this_storage.Storage_Name_ == storage_name)
			{// 
				result = this_storage.Storage_Status_;
				return result;
			}
		}
	}
	return result;
}