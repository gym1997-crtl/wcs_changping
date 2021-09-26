#include "Manage/Parking_Manage.h"
#include "Manage/AGV_Manage.h"
#include "Manage/Battery_Manage.h"
#include "Core/Task_Chain_Manage.h"
#include "Manage/Order_Manage.h"
#include "comm//simplelog.h"
#include "Core/ModelStationConfirm.h"
#include "Core/ModelStationConfirm.h"

Parking_Manage::Parking_Manage()
{

}

Parking_Manage::~Parking_Manage()
{

}

void Parking_Manage::setStationStatusNotifier(Station_Status_Notifier *notifier)
{
	station_status_notifier_ = notifier;
}

/**
 * ��ʼ�����������ݿ⣬��ȡվ�����б�
 */
void Parking_Manage::Initial()
{
	wcs_db_ = DATABASE_MANAGE.Get_WCS_DB();
	ModelStationParkingList = loadParkingStation();
	ModelStationConfirmList = loadConfirmStation();
	ModelEquipmentList = loadEquipment();
	
	// �½��̣߳��������ݿ���վ����Ϣ
	//station_status_check_.reset(new boost::thread(boost::bind(&Parking_Manage::checkStationStatus, this)));
}

std::vector< ModelStationParking*>  Parking_Manage::getAllParkingStation()//��ȡ����ͣ�����������ؽ���ʱ����
{
	return ModelStationParkingList;
}
std::map<std::string, ModelStationConfirm*>  Parking_Manage::getAllConfirmStation()//��ȡ����ͣ��ȷ�ϵ��������ؽ���ʱ����
{
	return ModelStationConfirmList;
}

std::map<std::string, ModelEquipment*>  Parking_Manage::getAllEquipment()//��ȡ����ͣ��ȷ�ϵ��������ؽ���ʱ����
{
	return ModelEquipmentList;
}

/// <summary>
/// Gets all bridge.
/// </summary>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/3
/// 
std::vector<ModelBridge *>  Parking_Manage::getAllBridge()//��ȡ����ͣ��ȷ�ϵ��������ؽ���ʱ����
{
	return ModelBridgeList;
}

void Parking_Manage::freeParkingList(std::map<std::string, ModelStationParking*> parkingList) {
	auto iter = parkingList.begin();
	while (iter != parkingList.end())
	{
		iter = parkingList.erase(iter);
	}
}

void Parking_Manage::freeConfirmList(std::map<std::string, ModelStationConfirm*> confirmList) {
	auto iter = confirmList.begin();
	while (iter != confirmList.end())
	{
		iter = confirmList.erase(iter);
	}
}

/**
 * ��������ͣ����
 */
std::vector< ModelStationParking*>  Parking_Manage::loadParkingStation() {
	std::vector<ModelStationParking*> allParkingStation;
	wcs_db_->getParkingStorage(&allParkingStation);
	return allParkingStation;
}

/**
 * ��������ȷ�ϵ�
 */
std::map<std::string, ModelStationConfirm*>  Parking_Manage::loadConfirmStation() {
	std::map<std::string, ModelStationConfirm*>  allConfirmStation;
	
	std::vector<std::string> nameList;
	std::vector<std::string> statusList;
	wcs_db_->loadListFromDB(nameList, ModelStationConfirm_TableName_, ModelStationConfirm_NameListName_);
	wcs_db_->loadListFromDB(statusList, ModelStationConfirm_TableName_, ModelStationConfirm_StatusListName_);

	for (int i = 0; i < nameList.size() && i < statusList.size(); i++)
	{
		ModelStationConfirm *tmp = new ModelStationConfirm(nameList.at(i), statusList.at(i));
		delete allConfirmStation[tmp->getName()];
		allConfirmStation[tmp->getName()] = tmp;
	}
	return allConfirmStation;
}

/**
 * ���������豸
 */
std::map<std::string, ModelEquipment*>  Parking_Manage::loadEquipment() {
	std::map<std::string, ModelEquipment*>  allEquipment;

	std::vector<std::string> id_list;
	std::vector<std::string> e_status_list;
	std::vector<std::string> s_status_list;
	do {
		wcs_db_->loadListFromDB(id_list, ModelEquipment_TableName_, ModelEquipment_IdListName_);
		wcs_db_->loadListFromDB(e_status_list, ModelEquipment_TableName_, ModelEquipment_EquipStatusListName_);
		wcs_db_->loadListFromDB(s_status_list, ModelEquipment_TableName_, ModelEquipment_StationStatusListName_);
	} while (id_list.size() != e_status_list.size() || id_list.size() != s_status_list.size());

	for (int i = 0; i < id_list.size() && i < e_status_list.size() && i < s_status_list.size(); i++)
	{
		ModelEquipment *tmp = new ModelEquipment(id_list.at(i), e_status_list.at(i), s_status_list.at(i));
		delete allEquipment[tmp->getId()];
		allEquipment[tmp->getId()] = tmp;
	}
	return allEquipment;
}


void Parking_Manage::checkStationStatus()
{
	
	// ��������ͣ������Ϣ
	std::vector<ModelStationParking*> allParkingStation = loadParkingStation();
	// �����������ź�
	for (unsigned int i = 0; i < ModelStationParkingList.size(); i++)
	{// ����֮ǰ��ͣ���㣬����¼��벻�ᵼ���쳣
		if (ModelStationParkingList.at(i)->getStatus() != allParkingStation.at(i)->getStatus())
		{// ״̬���ı��ˣ������źţ����ļ�¼��״̬
			ModelStationParkingList.at(i)->setStatus(allParkingStation.at(i)->getStatus());
			station_status_notifier_->OnStationStatusChanged(ModelStationParkingList.at(i));
		}
	}
	for each (auto var in allParkingStation)
	{
		delete var;
	}

	std::map<std::string, ModelStationConfirm*> allConfirmStation = loadConfirmStation();
	for each (auto var in allConfirmStation)
	{
		ModelStationConfirm *station = var.second;
		std::string stationName = var.first;
		if (station->getStatus() != ModelStationConfirmList[stationName]->getStatus())
		{// ״̬���ı���
			delete ModelStationConfirmList[stationName];
			ModelStationConfirmList[stationName] = station;
			station_status_notifier_->OnStationStatusChanged(ModelStationConfirmList[stationName]);
		}
		else {
			delete station;
		}
	}

	std::map<std::string, ModelEquipment*> allEquipment = loadEquipment();
	for each (auto var in allEquipment)
	{
		ModelEquipment *equipment = var.second;
		std::string equipment_name = var.first;
		if (equipment->getStatus() != ModelEquipmentList[equipment_name]->getStatus())
		{// ״̬���ı���
			ModelEquipmentList[equipment_name]->setStationStatus(equipment->getStatus());
			station_status_notifier_->OnStationStatusChanged(ModelEquipmentList[equipment_name]);
		}
		delete equipment;
	}
}

void Parking_Manage::Auto_Parking_Monitor()
{

	std::vector<AGV*> Free_AGV_List;
	AGV_MANAGE.Get_Free_AGV(Free_AGV_List);

	for (int i = 0; i < Free_AGV_List.size(); i++)
	{
		for (int j = i+1; j < Free_AGV_List.size(); j++)
		{
			if (Free_AGV_List[j]->Battery_Level_ < Free_AGV_List[i]->Battery_Level_)
			{
				AGV* temp = Free_AGV_List[i];
				Free_AGV_List[i] = Free_AGV_List[j];
				Free_AGV_List[j] = temp;
			}
		}
	}
	
	for (std::vector<AGV*>::iterator it = Free_AGV_List.begin(); it != Free_AGV_List.end(); ++it)
	{
		AGV* current_AGV = *it;
		if ( BATTERY_MANAGE.Check_Low_Power(current_AGV) || current_AGV->Invoke_AGV_Parking_ == INVOKE_STATUS::BEGING_INVOKE)
		{
			Auto_Parking_System(current_AGV);
		}
	}
}

void Parking_Manage::Auto_Parking_System(AGV* current_AGV)
{
	if (!AGV_MANAGE.Is_Parking(current_AGV) && current_AGV->Is_Serving_ == 1)                  //���ж�AGV�Ƿ��ڳ���λ��
	{
		if (ORDER_MANAGE.getParkingStation(current_AGV->Parking_Station_, current_AGV->Parking_Is_Charging_, current_AGV->AGV_Type_))
		{
			ORDER_MANAGE.reserveParkingStation(current_AGV->Parking_Station_);
			AGV_MANAGE.Set_Lock(current_AGV->ID_);
			AGV_MANAGE.setBusy(current_AGV->ID_);
			Generate_Parking_Task(current_AGV);
		}
		else if (current_AGV->Parking_Is_Charging_.size() == 0)
		{
			ORDER_MANAGE.getParkingStation(current_AGV->AGV_In_Station_, current_AGV->Parking_Is_Charging_, current_AGV->AGV_Type_);
		}
	}
	else if (AGV_MANAGE.Is_Parking(current_AGV) && ORDER_MANAGE.getStationIsCharging(current_AGV->AGV_In_Station_) && current_AGV->Battery_Level_ < 50)
	{
		if (ORDER_MANAGE.getMustChargingStation(current_AGV->Parking_Station_))
		{
			ORDER_MANAGE.reserveParkingStation(current_AGV->Parking_Station_);
			AGV_MANAGE.Set_Lock(current_AGV->ID_);
			AGV_MANAGE.setBusy(current_AGV->ID_);
			generateForceParkingChargingTask(current_AGV);
		}
	}
}

bool Parking_Manage::Generate_Parking_Task(AGV* associate_AGV)
{
	if (TASK_CHAIN_MANAGE.Create_Parking_Task_Chain(associate_AGV))
	{
		std::stringstream ss;
		ss << "AGV:" << associate_AGV->AGV_ID_ << "  Go To Parking~~~ ";
		log_info_color(log_color::green, ss.str().c_str());
		return true;
	}
	else
	{
		std::stringstream ss;
		ss << "AGV:" << associate_AGV->AGV_ID_ << "  Parking failed~~~ ";
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool Parking_Manage::generateForceParkingChargingTask(AGV* associate_AGV)
{
	if (TASK_CHAIN_MANAGE.createForceParkingTaskChain(associate_AGV))
	{
		std::stringstream ss;
		ss << "AGV:" << associate_AGV->AGV_ID_ << "  Parking~~~Rush";
		log_info_color(log_color::green, ss.str().c_str());
		return true;
	}
	else
	{
		std::stringstream ss;
		ss << "AGV:" << associate_AGV->AGV_ID_ << "  Parking failed ";
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}