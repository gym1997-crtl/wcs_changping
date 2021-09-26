#ifndef _MODLE_EQUIPMENT_H_
#define _MODLE_EQUIPMENT_H_
#include <string>

class ModelEquipment
{
public:
	ModelEquipment();
	ModelEquipment(std::string id, std::string e_status, std::string status);
	~ModelEquipment();

	std::string ModelEquipment::getId();
	std::string ModelEquipment::getEquipmentStatus();
	std::string ModelEquipment::getStatus();

	void setEquipmentStatus(std::string status);

	void setStationStatus(std::string status);

private:

	std::string equipment_id;

	std::string equipment_status;

	std::string station_status;
};

#endif