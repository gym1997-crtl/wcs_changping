#ifndef _MAP_Database_EDWARD_
#define _MAP_Database_EDWARD_

#include <map>
#include <deque>
#include <vector>
#include "ADODatabase/ADODatabase.h"
#include "Manage/Manage_Define.h"
#include "Core/Task_Define.h"
#include "Core/ModelStationParking.h" 
#include "Core/ModelBridge.h"

class Task_Chain;

class MAP_Database
{

public:
		//void insert_sql_data();
	MAP_Database();

	~MAP_Database();

	void setMapAdo(ADOcon ADO);

	bool getStationPos(std::string storage_name, Pos_Info *pos);

private:

	ADOcon WCS_ADO_;
	_RecordsetPtr recordPtr_;
	_RecordsetPtr recordPtr2_;
	_RecordsetPtr recordPtr3_;
	_RecordsetPtr recordPtr4_;

	int confirm1;
	int confirm2;
	int confirm3;
	int confirm4;
	int confirm5;

private:
	std::vector<Sql_Table_Attri> sql_table_list_;

};

#endif // _MAP_Database_EDWARD_