#ifndef _MODEL_BRIDGE_H_
#define _MODEL_BRIDGE_H_
#include <string>

#include "Core/ModelEquipment.h"

class ModelBridge : public ModelEquipment
{
public:
	ModelBridge();
	ModelBridge(std::string id, std::string e_status, std::string status);
	~ModelBridge();
private:
};

#endif