#include <iostream>
#include <sstream>
#include <ctime>
#include "ADODatabase/DatabaseManage.h"


Database_Manage::Database_Manage()
{
	
}

Database_Manage::~Database_Manage()
{

}

void Database_Manage::setWcsAdo(ADOcon* WCS_Con, std::string thread_name /*= std::string("main")*/)
{
	WCS_ADO_MAP_[thread_name]=*WCS_Con;
	for each (auto var in WCS_Map_[thread_name])
	{
		var->setWcsAdo(WCS_ADO_MAP_[thread_name]);
	}
}

void Database_Manage::set_ACS_ADO(ADOcon* ACS_Con, std::string thread_name /*= std::string("main")*/)
{
	ACS_ADO_MAP_[thread_name] = *ACS_Con;
	for each (auto var in ACS_Map_[thread_name])
	{
		var->set_ACS_ADO(ACS_ADO_MAP_[thread_name]);
	}
}

void Database_Manage::setMapADO(ADOcon* MAP_Con, std::string thread_name /*= std::string("main")*/)
{
	MAP_ADO_MAP_[thread_name] = *MAP_Con;
	for each (auto var in MAP_Map_[thread_name])
	{
		var->setMapAdo(MAP_ADO_MAP_[thread_name]);
	}
}

void Database_Manage::Initial(std::string thread_name /*= std::string("main")*/)
{
	Task_Log_ID = 1;

	DATABASE_MANAGE.Get_WCS_DB();
	_bstr_t SQL = "truncate task_feedback_table";
	try
	{
		DATABASE_MANAGE.WCS_ADO_MAP_[thread_name].ExecuteSQL(SQL);
	}
	catch(_com_error &e){
		std::cout<< " Database_Manage Initial " <<e.ErrorMessage()<<std::endl;
	}

	SQL = "truncate task_in_history";
	try
	{
		DATABASE_MANAGE.WCS_ADO_MAP_[thread_name].ExecuteSQL(SQL);
	}
	catch(_com_error &e){
		std::cout<< " Database_Manage Initial " <<e.ErrorMessage()<<std::endl;
	}
	SQL = "UPDATE s_confirm_station_status SET STATUS = 'IDLE'";
	try
	{
		DATABASE_MANAGE.WCS_ADO_MAP_[thread_name].ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << " Database_Manage Initial " << e.ErrorMessage() << std::endl;
	}
	SQL = "UPDATE parking_manage SET Status = 'IDLE'";
	try
	{
		DATABASE_MANAGE.WCS_ADO_MAP_[thread_name].ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << " Database_Manage Initial " << e.ErrorMessage() << std::endl;
	}
}


//************************************
// Method:    Get_WCS_DB
// FullName:  Database_Manage::Get_WCS_DB
// Access:    public 
// Returns:   WCS_Database*
// Parameter: std::string thread_name : default "main"
// Author:    Meixu
// Date:	  2021/07/05
// Usage: use "Get_WCS_DB()" in main thread; use "Get_WCS_DB([thread_name])" in sub thread
// eg:
// 	WCS_CON_ = DATABASE_MANAGE.Get_WCS_DB();
//	WCS_CON_2 = DATABASE_MANAGE.Get_WCS_DB("sub_thread");
//************************************
WCS_Database* Database_Manage::Get_WCS_DB(std::string thread_name /*= std::string("main")*/)
{
	WCS_Database* new_WCS_database=new WCS_Database();
	if (WCS_ADO_MAP_.find(thread_name) == WCS_ADO_MAP_.end())
	{
		ADOcon* default_WCS_Con = new ADOcon();

		default_WCS_Con->OnInitADOConn(ADO_Database::WCS_DB);

		DATABASE_MANAGE.setWcsAdo(default_WCS_Con, thread_name);
	}
	new_WCS_database->setWcsAdo(WCS_ADO_MAP_[thread_name]);    

	WCS_Map_[thread_name].push_back(new_WCS_database);
	return new_WCS_database;
}

//************************************
// Method:    Get_ACS_DB
// FullName:  Database_Manage::Get_ACS_DB
// Access:    public 
// Returns:   ACS_Database*
// Parameter: std::string thread_name : default "main"
// Author:    Meixu
// Date:	  2021/07/05
// Usage: use "Get_ACS_DB()" in main thread; use "Get_ACS_DB([thread_name])" in sub thread
// eg:
// 	WCS_CON_ = DATABASE_MANAGE.Get_ACS_DB();
//	WCS_CON_2 = DATABASE_MANAGE.Get_ACS_DB("sub_thread");
//************************************
ACS_Database* Database_Manage::Get_ACS_DB(std::string thread_name /*= std::string("main")*/)
{
	ACS_Database* new_ACS_database=new ACS_Database();
	if (ACS_ADO_MAP_.find(thread_name) == ACS_ADO_MAP_.end())
	{
		ADOcon* default_ACS_Con = new ADOcon();

		default_ACS_Con->OnInitADOConn(ADO_Database::ACS_DB);

		DATABASE_MANAGE.set_ACS_ADO(default_ACS_Con, thread_name);
	}
	new_ACS_database->set_ACS_ADO(ACS_ADO_MAP_[thread_name]);

	ACS_Map_[thread_name].push_back(new_ACS_database);
	return new_ACS_database;
}

MAP_Database* Database_Manage::Get_MAP_DB(std::string thread_name /*= std::string("main")*/)
{
	MAP_Database* new_map_database = new MAP_Database();
	if (MAP_ADO_MAP_.find(thread_name) == MAP_ADO_MAP_.end())
	{
		ADOcon* default_map_con = new ADOcon();

		default_map_con->OnInitADOConn(ADO_Database::Map_DB);

		DATABASE_MANAGE.setMapADO(default_map_con, thread_name);
	}
	new_map_database->setMapAdo(MAP_ADO_MAP_[thread_name]);

	MAP_Map_[thread_name].push_back(new_map_database);
	return new_map_database;
}