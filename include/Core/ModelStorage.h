#ifndef ModelStorage_H_
#define ModelStorage_H_
#include <string>

class ModelStorage
{
public:
	ModelStorage();
	ModelStorage(int id, std::string storage_name, int storage_row, int storage_column, std::string storage_type = "GOODS", std::string storagr_status = "EMPTY", std::string resource_status = "IDLE");
	~ModelStorage();

	std::string ModelStorage::getName();

private:

	int id;

	std::string storage_name;

	std::string storage_type;

	std::string storage_row;

	std::string storage_column;

	std::string storagr_status;

	std::string resource_status;
};

#endif