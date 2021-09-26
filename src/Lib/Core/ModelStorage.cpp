#include "Core/ModelStorage.h"

ModelStorage::ModelStorage()
{
}

ModelStorage::ModelStorage(int id, std::string storage_name, int storage_row, int storage_column, std::string storage_type, std::string storagr_status, std::string resource_status)
{
	this->id = id;
	this->storage_name = storage_name;
	this->storage_row = storage_row;
	this->storage_column = storage_column;
	this->storage_type = storage_type;
	this->storagr_status = storagr_status;
	this->resource_status = resource_status;
}

ModelStorage::~ModelStorage()
{
}

std::string ModelStorage::getName()
{
	return storage_name;
}