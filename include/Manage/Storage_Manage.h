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
	//AUTOMATIC_LOGISTIC_WAREHOUSE,//�����
	//IN_BUFFER_STORAGE,//��⻺����
	//WAITING_IN_STORAGE,//���졢�������
	CHECK_OVER_STORAGE = 3,//�Ѽ���
	CHECK_WAITING_STORAGE = 4,//������
	OUT_BUFFER_STORAGE = 5,//���������������
	CHECK_STATION = 6//ʵѵ��λ
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

	//void Initial_All_Storage_Event();                                                      //��ʼ�����п�λ;   
	
	bool Get_Full_Storage(std::vector<Storage*> &full_storage_list);					   //��ȡ�л���λ;

	bool Set_Lock_Storage(std::string storage_name);									  //�·������Ԥ��ĳ��λ;

	bool Set_Empty_Storage(std::string storage_name);									  //�·�ȡ�������ĳ��λ���ͷ�;

	bool Set_Full_Storage(std::string storage_name);									 //�·��������ĳ��λ��ռ��;

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
	
	//�ӽ����޸����ݿ������;
	void changeStorageStatus(std::string storage_name, std::string status_name, std::string status);

	std::vector<std::string> getAllStationName();//��ȡ����վ���������ؽ���ʱ����

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

	//�ӿ���ʵ�����������½�����ʾ�Ŀ�λ״̬
	Storage_Status_Notifier *storage_status_notifier_;

	//�����ݿ���ص���Ҫ�����ݿ���صı�Ľṹ��;
	std::vector<Sql_Table_Attri> sql_table_list_;

	//����ʢװ��������ʢװStorage�ṹ���map���map
	std::map<std::string, std::map<int, Storage>> storage_list_map_;

	std::map<std::string, std::map<int, Storage>> loadStorageMapList();

}; 

typedef boost::serialization::singleton<Storage_Manage> Singleton_Storage_Manage;
#define STORAGE_MANAGE Singleton_Storage_Manage::get_mutable_instance()

#endif //_AGV_MANAGE_ED_H