#ifndef PARKING_MANAGE_H
#define PARKING_MANAGE_H
#include <string>  
#include <map> 
#include <vector>
#include <iostream>  
#include <boost/serialization/singleton.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "Manage/Manage_Define.h"

#include "DatabaseManage.h"
#include "ADODatabase/WCS_Database.h"
#include "Manage/Manage_Define.h"
#include "ADODatabase/ACS_Database.h"
#include "WCS_Database.h"
#include "Core/ModelStationConfirm.h"
#include "Core/ModelStationParking.h"
#include "Core/ModelEquipment.h"
#include "Core/ModelBridge.h"


class Station_Status_Notifier
{
public:
	virtual void OnStationStatusChanged(ModelStationConfirm*) = 0;
	virtual void OnStationStatusChanged(ModelStationParking*) = 0;
	virtual void OnStationStatusChanged(ModelEquipment*) = 0;
};

class Parking_Manage:private boost::noncopyable
{

public:
	
	Parking_Manage();
	~Parking_Manage();

	void Initial();

	void setStationStatusNotifier(Station_Status_Notifier * notifier);

	std::vector< ModelStationParking*> getAllParkingStation();//获取所有停车点名，加载界面时调用

	std::map<std::string, ModelStationConfirm*> getAllConfirmStation();//获取所有确认点名，加载界面时调用

	std::map<std::string, ModelEquipment*> getAllEquipment();

	std::vector<ModelBridge *> getAllBridge();

	void checkStationStatus();

	static Parking_Manage* Instance()
	{
		static Parking_Manage manage_;
		return &manage_;
	}

	void Auto_Parking_Monitor();

private:

	WCS_Database *wcs_db_;
	//停车点数据库信息
	std::string parking_TableName_ = "parking_manage";

	std::string parking_NameListName_ = "STATION_NAME";

	std::string parking_ChargingListName_ = "IS_CHARGING";

	std::string parking_StatusListNAme_ = "STATUS";
	//确认点数据库信息
	std::string ModelStationConfirm_TableName_ = "s_confirm_station_status";

	std::string ModelStationConfirm_NameListName_ = "STATION_NAME";

	std::string ModelStationConfirm_StatusListName_ = "STATUS";

	std::string ModelEquipment_TableName_ = "kh_equipment_info";

	std::string ModelEquipment_IdListName_ = "EQUIP_ID";

	std::string ModelEquipment_EquipStatusListName_ = "EQUIP_STATUS";

	std::string ModelEquipment_StationStatusListName_ = "STATUS";

	std::vector< ModelStationParking*> ModelStationParkingList;

	std::map<std::string, ModelStationConfirm*> ModelStationConfirmList;

	std::map<std::string, ModelEquipment*> ModelEquipmentList;

	std::vector<ModelBridge *> ModelBridgeList;

	std::vector< ModelStationParking*> loadParkingStation();// 从数据库更新停车点信息

	std::map<std::string, ModelStationConfirm*> loadConfirmStation();//从数据库更新确认点信息

	std::map<std::string, ModelEquipment*> loadEquipment();

	void Parking_Manage::freeConfirmList(std::map<std::string, ModelStationConfirm*>);

	void Parking_Manage::freeParkingList(std::map<std::string, ModelStationParking*>);

	//接口类实例，用作更新界面显示的站点状态
	Station_Status_Notifier *station_status_notifier_;

	//用来开线程进行实时刷新数据库的库位状态的智能指针
	boost::shared_ptr<boost::thread> station_status_check_;

	void changeStationStatus();

	bool Generate_Parking_Task(AGV* associate_AGV);

	bool generateForceParkingChargingTask(AGV* associate_AGV);

	void Auto_Parking_System(AGV* current_AGV);

//	void autoParkingFakeChargingSystem(AGV* current_AGV);

};

typedef boost::serialization::singleton<Parking_Manage> Singleton_Parking_Manage;
#define PARKING_MANAGE Singleton_Parking_Manage::get_mutable_instance()

#endif