#include "Core/ModelStationConfirm.h"

ModelStationConfirm::ModelStationConfirm()
{
}

ModelStationConfirm::ModelStationConfirm(std::string name, std::string status)
{
	station_name = name;
	station_status = status;
}

ModelStationConfirm::~ModelStationConfirm()
{
}

std::string ModelStationConfirm::getName() {
	return station_name;
}

std::string ModelStationConfirm::getStatus() {
	return station_status;
}
