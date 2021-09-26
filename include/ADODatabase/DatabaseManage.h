#ifndef _DATABASE_MANAGE_EDWARD_
#define _DATABASE_MANAGE_EDWARD_

#include <boost/serialization/singleton.hpp>
#include "ADODatabase/ADODatabase.h"
#include "ADODatabase/WCS_Database.h"
#include "ADODatabase//ACS_Database.h"
#include "ADODatabase/MAP_Database.h"

#include <vector>

static const char thread_name_[] = "main";

class Database_Manage
{
public:
	Database_Manage();
	~Database_Manage();

	void setWcsAdo(ADOcon* WCS_Con, std::string thread_name = thread_name_);
	void set_ACS_ADO(ADOcon* ACS_Con, std::string thread_name = thread_name_);

	void setMapADO(ADOcon * MAP_Con, std::string thread_name = thread_name_);
	
	void Initial(std::string thread_name = thread_name_);

	WCS_Database* Get_WCS_DB(std::string thread_name = thread_name_);
	ACS_Database* Get_ACS_DB(std::string thread_name = thread_name_);

	MAP_Database * Get_MAP_DB(std::string thread_name = thread_name_);
	
	int Task_Log_ID;
private:

	std::map<std::string, ADOcon> WCS_ADO_MAP_;
	std::map<std::string, ADOcon> ACS_ADO_MAP_;
	std::map<std::string, ADOcon> MAP_ADO_MAP_;


	_RecordsetPtr recordPtr_;

	std::map<std::string, std::vector<WCS_Database*>> WCS_Map_;
	std::map<std::string, std::vector<ACS_Database*>> ACS_Map_;
	std::map<std::string, std::vector<MAP_Database*>> MAP_Map_;

};

typedef boost::serialization::singleton<Database_Manage> Singleton_DB_Manage;

#define DATABASE_MANAGE Singleton_DB_Manage::get_mutable_instance()
#endif