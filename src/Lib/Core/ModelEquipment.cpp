#include "Core/ModelEquipment.h"
#include <iostream>

ModelEquipment::ModelEquipment()
{
}

ModelEquipment::ModelEquipment(std::string id, std::string e_status, std::string s_status)
{
	equipment_id = id;
	equipment_status = e_status;
	station_status = s_status;
}

ModelEquipment::~ModelEquipment()
{
}

std::string ModelEquipment::getId() {
	return equipment_id;
}

std::string ModelEquipment::getEquipmentStatus() {
	return equipment_status;
}

std::string ModelEquipment::getStatus() {
	return station_status;
}

void ModelEquipment::setEquipmentStatus(std::string status) {
	equipment_status = status;
}
void ModelEquipment::setStationStatus(std::string status) {
	station_status = status;
}