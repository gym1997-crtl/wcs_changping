#ifndef _MODLE_STATION_CCONFIRM_H_
#define _MODLE_STATION_CCONFIRM_H_
#include <string>

class ModelStationConfirm
{
public:
	ModelStationConfirm();
	ModelStationConfirm(std::string name, std::string status);
	~ModelStationConfirm();

	std::string ModelStationConfirm::getName();
	std::string ModelStationConfirm::getStatus();

private:

	int station_id_;

	std::string station_name;

	std::string station_status;
};

#endif