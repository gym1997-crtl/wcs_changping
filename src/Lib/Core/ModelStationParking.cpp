#include "Core/ModelStationParking.h"

ModelStationParking::ModelStationParking()
{
}

ModelStationParking::ModelStationParking(std::string name, std::string charging, std::string status)
{
	station_name = name;
	is_charging_ = charging;
	station_status = status;
}

ModelStationParking::~ModelStationParking()
{
}

std::string ModelStationParking::getName()
{
	return station_name;
}

std::string ModelStationParking::getCharging() {
	return is_charging_;
}

std::string ModelStationParking::getStatus() {
	return station_status;
}

void ModelStationParking::setStatus(std::string status) {
	station_status = status;
}