#ifndef _Oracle_Database_
#define _Oracle_Database_

#include <map>
#include "ADODatabase/ADODatabase.h"
#include "Manage/Manage_Define.h"
#include <vector>
#include "Core/Task_Define.h"

class Task_Chain;

class Oracle_Database
{

public:
		//void insert_sql_data();
	Oracle_Database();

	~Oracle_Database();

	void set_Oracle_ADO(ADOcon ADO);

	bool copyOracleOrderInfo();

	bool addOracleOrder(int WCS_TASK_ID, std::string START_CONFIRM, std::string TARGETED_CONFIRM, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, int AGV_ID);
	
	bool updateOrderStatusToDoing(int order_id, int agv_id);

	void updateOrderStatusToDone(Task_Chain* the_task);

	void updateOrderStatusToErr(Task_Chain* the_task);

	bool insertOrderToOracle(std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, std::string SYSTEM, int AGV_ID);



private:

	ADOcon Oracle_ADO_;
	_RecordsetPtr recordPtr_;
};

#endif