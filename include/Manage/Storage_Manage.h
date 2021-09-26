#ifndef _STORAGE_MANAGE_HSQ
#define _STORAGE_MANAGE_HSQ
#include <string>  
#include <map> 
#include <vector>
#include <iostream>  
#ifndef Q_MOC_RUN
#include <boost/serialization/singleton.hpp>
#include <boost/thread.hpp>
#endif
#include "Manage/Manage_Define.h"
#include "ADODatabase/WCS_Database.h"
#include "ADODatabase/ACS_Database.h"
//#include "ADODatabase/XML_Database.h"

class Storage_Status_Notifier
{
public:
	//virtual void OnstorageStatusChanged(const std::map<std::string, std::map<int, Storage>> &map_list) = 0;
	virtual void OnstorageStatusChanged(Storage) = 0;
};

enum {
	//AUTOMATIC_LOGISTIC_WAREHOUSE,//立体库
	//IN_BUFFER_STORAGE,//入库缓冲区
	//WAITING_IN_STORAGE,//待检、待入库区
	CHECK_OVER_STORAGE = 3,//已检区
	CHECK_WAITING_STORAGE = 4,//待检区
	OUT_BUFFER_STORAGE = 5,//立库理货、发货区
	CHECK_STATION = 6//实训工位
};

class MainWindowDelegate
{
public:
	//virtual bool ChangeConfirmLableStatus(int id, int status) = 0;
};

class Storage_Manage 
{  
public:  

	Storage_Manage();  

	~Storage_Manage();  

	void Set_MainWindow_Delegate(MainWindowDelegate* mw);

	void Initial();

	//void Initial_All_Storage_Event();                                                      //初始化所有库位;   
	
	bool Get_Full_Storage(std::vector<Storage*> &full_storage_list);					   //获取有货库位;

	bool Set_Lock_Storage(std::string storage_name);									  //下发任务后预定某库位;

	bool Set_Empty_Storage(std::string storage_name);									  //下发取货任务后，某库位被释放;

	bool Set_Full_Storage(std::string storage_name);									 //下发放任务后，某库位被占用;

	//bool setConfirmMyLabel(int confirm, int status);

	bool setCurrentStorageStatus(std::string table_name, std::string resource_status, std::string storage_name);

	bool Insert_Order(std::string start, std::string target, int priority, std::string status, std::string mode, std::string type);

	bool Insert_Order(std::string order_id, std::string start, std::string target, int priority, std::string status, std::string mode, std::string type);

	bool Insert_Order(std::string order_id, std::string start, std::string target, int priority, std::string status, std::string mode, std::string type, int agvID);

	bool Insert_Order(std::string order_id, std::string start, std::string target, int priority, std::string status, std::string mode, std::string type, int agvID, std::string palletNo);

	bool Insert_Order_XML(std::string uuid, Order order_in);

	int GetAgvExeGoodsTask(std::string palletNo);

	int getMaxTaskId();

	bool changeStorageStatusToEmpty(std::string Storage,int storage_type);

	bool changeStorageStatusToFull(std::string Storage,int storage_type);

	void changeConfirmStatus(std::string current_confirm, std::string status);

	void changeParkingStatus(std::string current_parking, std::string status);

	void changeEquipmentStatus(std::string equipment_id_, std::string signal_type_);

	bool getCurrentComfirmStatus(std::string current_confirm);

	void setCurrentComfirmStatus(std::string current_confirm, std::string status);

	std::vector<Sql_Table_Attri> getSqlableList() const;

	std::map<std::string, std::map<int, Storage>> getStorageListMap();

	void setStorageStatusNotifier(Storage_Status_Notifier *notifier);

	void checkChange();
	
	//从界面修改数据库的数据;
	void changeStorageStatus(std::string storage_name, std::string status_name, std::string status);

	std::vector<std::string> getAllStationName();//获取所有站点名，加载界面时调用

	std::vector<std::string> getStandardStorage(const std::string & status);

	std::string getStorageStatus(const std::string & storage_name);

protected:  


private:

	MainWindowDelegate* mainwindow_delegate_;

	bool Is_Locked(int agv_id);

	std::map<int, AGV*> AGV_List_;

	WCS_Database* WCS_CON_;
	ACS_Database* ACS_CON_;
	//XML_Database* XML_CON_;

	//接口类实例，用作更新界面显示的库位状态
	Storage_Status_Notifier *storage_status_notifier_;

	//从数据库加载的需要从数据库加载的表的结构体;
	std::vector<Sql_Table_Attri> sql_table_list_;

	//用来盛装创建用来盛装Storage结构体的map表的map
	std::map<std::string, std::map<int, Storage>> storage_list_map_;

	std::map<std::string, std::map<int, Storage>> loadStorageMapList();

}; 

typedef boost::serialization::singleton<Storage_Manage> Singleton_Storage_Manage;
#define STORAGE_MANAGE Singleton_Storage_Manage::get_mutable_instance()

#endif //_AGV_MANAGE_ED_H