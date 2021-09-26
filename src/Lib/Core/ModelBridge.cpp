#include "Core/ModelBridge.h"
#include <iostream>

ModelBridge::ModelBridge():ModelEquipment()
{
}

ModelBridge::ModelBridge(std::string id, std::string e_status, std::string s_status) :ModelEquipment(id, e_status, s_status)
{
}

ModelBridge::~ModelBridge()
{
}