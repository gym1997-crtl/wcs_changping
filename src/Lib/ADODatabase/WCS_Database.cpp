#include <iostream>
#include <sstream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "stdlib.h"
#include "ADODatabase/DatabaseManage.h"
#include "ADODatabase/WCS_Database.h"
#include "Manage/Order_Manage.h"
#include "Manage/Storage_Manage.h"
#include "Core/Task_Chain_Manage.h"
#include "Core/Task_Chain.h"
#include "comm/simplelog.h"
#include <Windows.h>
#include "Manage/Config_Manage.h"

WCS_Database::WCS_Database()
{

}

WCS_Database::~WCS_Database()
{

}

void WCS_Database::setWcsAdo(ADOcon ADO)
{
	WCS_ADO_ = ADO;
}

//linde_order_info---->kh_report_order_info
bool WCS_Database::copyOrderInfo(Task_Chain_Info &order_in)
{
	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;
	char szSq1[10240] = { 0 };
	char szSq12[10240] = { 0 };
	try
	{
		ss << "SELECT COUNT(*) FROM kh_order_info WHERE STATUS = 'NEW' ORDER BY PRIORITY asc";
		sprintf(szSq1, "%s", ss.str().c_str());
		recordPtr_ = WCS_ADO_.GetRecordSet((_bstr_t)szSq1);
		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			ss2 << "SELECT * FROM kh_order_info WHERE STATUS = 'NEW' ORDER BY PRIORITY asc";
			sprintf(szSq12, "%s", ss2.str().c_str());
			recordPtr_ = WCS_ADO_.GetRecordSet((_bstr_t)szSq12);

			recordPtr_->MoveFirst();
			while (recordPtr_->adoEOF == VARIANT_FALSE)
			{
				order_in.ORDER_ID_ = (std::string)((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ORDER_ID")))->Value);
				order_in.START_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
				order_in.TARGET_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
				order_in.STATUS_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATUS"))->Value);
				order_in.PRIORITY_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("PRIORITY"))->Value));
				order_in.MODE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);
				order_in.TYPE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TYPE"))->Value);
				order_in.PALLETNO_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("PALLETNO"))->Value);
				order_in.AGV_ID_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("AGV_ID"))->Value));
				order_in.Timestamp_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ENTERDATE"))->Value);
				

				std::string start = order_in.START_;
				std::string target = order_in.TARGET_;
				std::vector<AGV*> Free_AGV_List;
				if (order_in.MODE_ == "TRAY" || order_in.MODE_ == "GOODS")   //满轮任务需找一个空闲车
				{
					if (AGV_MANAGE.getFreeHighBatteryAGV(Free_AGV_List,2))
					{
						for (int i = 0; i < Free_AGV_List.size(); i++)
						{
							for (int j = i; j < Free_AGV_List.size(); j++)
							{
								if (Free_AGV_List[j]->Battery_Level_ > Free_AGV_List[i]->Battery_Level_)
								{
									AGV* temp = Free_AGV_List[i];
									Free_AGV_List[i] = Free_AGV_List[j];
									Free_AGV_List[j] = temp;
								}
							}
						}
						std::vector<AGV*>::iterator it = Free_AGV_List.begin();
						AGV* current_AGV = *it;
						order_in.AGV_ID_ = current_AGV->AGV_ID_;
						return true;
					}
					else if (AGV_MANAGE.getFreeHighBatteryAGV(Free_AGV_List,2) && order_in.MODE_ == "TRAY")//空轮任务需找一个指定的空闲车
					{
						for (int i = 0; i < Free_AGV_List.size(); i++)
						{
							if (Free_AGV_List[i]->AGV_ID_ == order_in.AGV_ID_)
							{
								return true;
							}
						}
					}
				}
				recordPtr_->MoveNext();
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {

		std::stringstream ss;
		ss << e.ErrorMessage() << "copyOrderInfo" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

void WCS_Database::deleteCurrentOrder(std::string order_id)
{
	try
	{
		std::stringstream ss;
		ss << "DELETE FROM kh_order_info WHERE ORDER_ID = '" << order_id << "' ";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "deleteCurrentOrder" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

void WCS_Database::setCurrentStorageStatus(std::string table_name, std::string state, std::string storage_name)   //改变当前库位状态;
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE " << table_name << " SET storage_status = '" << state << "' WHERE storage_name = '" << storage_name << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "setCurrentStorageStatus" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}
//NEW->DOING;
bool WCS_Database::updateOrderStatusToDoing(std::string order_id, int agv_id)
{
	try {
		int row_count = 0;
		std::stringstream ss;
		std::stringstream ss2;
		std::stringstream ss3;

		ss << "SELECT COUNT(*) FROM kh_report_order_info WHERE ORDER_ID = '" << order_id << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		if (row_count != 0)
		{
			ss3 << "UPDATE kh_report_order_info SET STATUS = 'DOING' WHERE ORDER_ID = '" << order_id << "'";
			_bstr_t SQL5 = ss3.str().c_str();
			WCS_ADO_.ExecuteSQL(SQL5);
			return true;
		}
		else
		{
			return false;
		}

	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "updateOrderStatusToDoing" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}

}
//DOING->DONE;
void WCS_Database::updateOrderStatusToDone(Task_Chain* the_task, std::string order_type, std::string sql_table_name) {

	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;
	std::stringstream ss3;

	ss << "SELECT COUNT(*) FROM " << sql_table_name << " WHERE ORDER_ID = '" << the_task->Order_ID_ << "' AND TYPE = '" << order_type << "'";
	_bstr_t SQL = ss.str().c_str();
	recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

	try {
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			ss2 << "SELECT * FROM " << sql_table_name << " WHERE ORDER_ID = '" << the_task->Order_ID_ << "' AND TYPE = '" << order_type << "'";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);

			int ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ID"))->Value));
			std::string ORDER_ID = (std::string)(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ORDER_ID"))->Value));
			std::string START = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
			std::string TARGET = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
			std::string MODE = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);
			std::string TYPE = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TYPE"))->Value);

			ss3 << "UPDATE " << sql_table_name << " SET STATUS = 'DONE',FINISHDATE = '" << the_task->Get_Over_Time() << "' WHERE ORDER_ID = '" << ORDER_ID << "' AND TYPE = '" << order_type << "'";
			_bstr_t SQL4 = ss3.str().c_str();
			WCS_ADO_.ExecuteSQL(SQL4);

		}
		else
		{
			return;
		}
	}
	catch (_com_error &e) {

		std::stringstream ss;
		ss << e.ErrorMessage() << "updateOrderStatusToDone" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}

}
//DOING->ERR;
void WCS_Database::updateOrderStatusToErr(Task_Chain* the_task, std::string order_type, std::string sql_table_name)
{

	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;

	ss << "SELECT COUNT(*) FROM " << sql_table_name << " WHERE STATUS = 'DOING' AND TYPE = '" << order_type << "' AND ORDER_ID = '" << the_task->Order_ID_ << "'";
	_bstr_t SQL = ss.str().c_str();
	recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

	try {
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			ss2 << "UPDATE " << sql_table_name << " SET STATUS = 'ERR',FINISHDATE = 'null' WHERE ORDER_ID = '" << the_task->Order_ID_ << "' AND TYPE = '" << order_type << "'";
			_bstr_t SQL2 = ss2.str().c_str();
			WCS_ADO_.ExecuteSQL(SQL2);
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "updateOrderStatusToErr" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}


void WCS_Database::updateOrderTargetStorageInfo(Task_Chain* the_task, std::string order_type, std::string sql_table_name)
{

	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;

	ss << "SELECT COUNT(*) FROM " << sql_table_name << " WHERE  TYPE = '" << order_type << "' AND ORDER_ID = '" << the_task->Order_ID_ << "'";
	_bstr_t SQL = ss.str().c_str();
	recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

	try {
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			if (the_task->getMode()=="GOODS")
			{
				ss2 << "UPDATE " << sql_table_name << " SET TARGET = '" << the_task->getGoodsPut() << "' WHERE ORDER_ID = '" << the_task->Order_ID_ << "' AND TYPE = '" << order_type << "'";
			}
			else if (the_task->getMode() == "TRAY")
			{
				ss2 << "UPDATE " << sql_table_name << " SET TARGET = '" << the_task->getTrayGet() << "' WHERE ORDER_ID = '" << the_task->Order_ID_ << "' AND TYPE = '" << order_type << "'";
			}
			_bstr_t SQL2 = ss2.str().c_str();
			WCS_ADO_.ExecuteSQL(SQL2);
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "updateOrderTargetStorageInfo" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

std::vector<Oreder_Task*> WCS_Database::updateTaskOrderInfo(std::vector<Oreder_Task*>Executing_List) {
	try {

		int row_count = 0;
		_bstr_t SQL = "SELECT COUNT(*) FROM kh_report_order_info WHERE STATUS = 'NEW'";
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		if (row_count != 0)
		{
			std::string sql = "SELECT * FROM kh_report_order_info WHERE STATUS = 'NEW'";
			_bstr_t SQL = sql.c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

			recordPtr_->MoveFirst();
			while (recordPtr_->adoEOF == VARIANT_FALSE) {
				Oreder_Task* order_task = new Oreder_Task;
				order_task->ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ID"))->Value));
				order_task->ORDER_ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ORDER_ID"))->Value));
				order_task->AGV_ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("AGV_ID"))->Value));
				order_task->START_POINT = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
				order_task->TARGET_POINT = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
				order_task->MODE = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);
				order_task->TYPE = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TYPE"))->Value);

				std::vector<Oreder_Task *>::iterator ite;
				bool data = true;
				for (ite = Executing_List.begin(); ite != Executing_List.end(); ite++)       //判断当前executing_list是否有重复;
				{
					Oreder_Task* p = *ite;

					if (p->ID == order_task->ID)
					{
						data = false;
						delete(order_task);
						break;
					}
					else
					{
						data = true;
						continue;
					}
				}
				if (data)
				{
					Executing_List.push_back(order_task);
				}
				recordPtr_->MoveNext();
			}
		}
		return Executing_List;

	}
	catch (_com_error &e) {

		std::stringstream ss;
		ss << e.ErrorMessage() << "updateTaskOrderInfo" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return Executing_List;
	}
}

int WCS_Database::getMaxTaskId()
{

	_bstr_t SQL = "select count(*) from task_in_history";
	try
	{
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			if ((int)recordPtr_->GetCollect("count(*)") == 0)
				return 0;
			else
			{
				SQL = "select task_id from task_in_history";
				recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
				recordPtr_->MoveLast();
				return (int)recordPtr_->GetCollect("task_id");
			}
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "getMaxTaskId" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

int WCS_Database::getMaxWcsTaskId()
{
	_bstr_t SQL = "select count(*) from kh_parking_charging_info";
	try
	{
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			if ((int)recordPtr_->GetCollect("count(*)") == 0)
			{
				return 1;
			}
			else
			{
				SQL = "select ID from kh_parking_charging_info";
				recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
				recordPtr_->MoveLast();
				return (int)recordPtr_->GetCollect("ID");
			}
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "getMaxWcsTaskId" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

bool WCS_Database::checkOrderInfoCount(int &max_id)
{
	_bstr_t SQL = "select count(*) from kh_order_info";
	try
	{
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			if ((int)recordPtr_->GetCollect("count(*)") == 0)
			{
				return false;
			}
			else
			{
				SQL = "select ORDER_ID from kh_order_info";
				recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
				recordPtr_->MoveLast();
				max_id = (int)recordPtr_->GetCollect("ORDER_ID");
				return true;
			}
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "checkOrderInfoCount" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

bool WCS_Database::insertTask(int task_id_, std::string task_from_, std::string task_to_, int priority_, int agv_type_, int task_type_, int auto_dispatch_, int agv_id_, int task_extra_param_type, std::string task_extra_param)
{
	try
	{
		std::stringstream ssTask;
		std::stringstream ssTask_History;

		ssTask << "INSERT INTO task_in_table (task_id,task_from,task_to,priority,agv_type,task_type,auto_dispatch,agv_id,task_extra_param_type,task_extra_param)VALUES(" << task_id_ << ",'" << task_from_ << "','"
			<< task_to_ << "'," << priority_ << "," << agv_type_ << "," << task_type_ << "," << auto_dispatch_ << "," << agv_id_ << "," << task_extra_param_type << ",'" << task_extra_param << "')";
		_bstr_t SQL = ssTask.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);

		ssTask_History << "INSERT INTO task_in_history (task_id,task_from,task_to,priority,agv_type,task_type,task_extra_param)VALUES(" << task_id_ << ",'" << task_from_ << "','" << task_to_ << "'," << priority_ << "," << agv_type_ << "," << task_type_ << ",'" << task_extra_param << "')";
		_bstr_t SQL2 = ssTask_History.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL2);

		std::stringstream ss;
		ss << "Task_ID:" << task_id_ << "," << "From:" << task_from_ << "," << "To:" << task_to_ << "," << "Priority:" << priority_ << "," << "AGV_Type:" << agv_type_ << "," << "task_type:" << task_type_ << "," << "AGV_ID:" << agv_id_ << "," << "TASK_EXTRA_PARAM:" << task_extra_param;
		log_info_color(log_color::blue, ss.str().c_str());
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "insertTask" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
	return true;
}

bool WCS_Database::addOrder(std::string ORDER_ID, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, int AGV_ID)

{
	try
	{
		std::stringstream ssOrder;

		ssOrder << "INSERT INTO kh_report_order_info (ORDER_ID,AGV_ID,PRIORITY,STATUS,MODE,TYPE,START,TARGET)VALUES('" <<
			ORDER_ID << "'," << AGV_ID << ",'" << PRIORITY << "','" << STATUS << "','" 
			<< MODE << "','" << TYPE << "','" << START << "','" << TARGET << "')";
		_bstr_t SQL = ssOrder.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);

		std::stringstream ss;
		ss << "Add_Task_To_Order_List: " << "AGV_ID:" << AGV_ID << "," << "START:" << START << "," << "TARGET:" << TARGET << "," << "PRIORITY:" << PRIORITY << "," << "STATUS:" << STATUS << "," << "MODE:" << MODE << "," << "TYPE:" << TYPE;
		log_info_color(log_color::green, ss.str().c_str());
		return true;
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "addOrder" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool WCS_Database::addParkingChargingOrder(std::string START, std::string TARGET, std::string TYPE, int AGV_ID)

{
	try
	{
		std::stringstream ssOrder;

		ssOrder << "INSERT INTO kh_parking_charging_info (AGV_ID,TYPE,START,TARGET)VALUES(" << AGV_ID << ",'" << TYPE << "','" << START << "','" << TARGET << "')";
		_bstr_t SQL = ssOrder.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);

		std::stringstream ss;
		ss << "Add_Task_To_Order_List: " << "AGV_ID:" << AGV_ID << "," << "START:" << START << "," << "TARGET:" << TARGET << "," << "TYPE:" << TYPE;
		log_info_color(log_color::green, ss.str().c_str());
		return true;
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "addParkingChargingOrder" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool WCS_Database::insertOrderToDb(std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE)
{
	try
	{
		std::stringstream ssOrder;
		ssOrder << "INSERT INTO kh_order_info (START,TARGET,PRIORITY,STATUS,MODE,TYPE)VALUES('" << START << "','" << TARGET << "'," << PRIORITY << ",'" << STATUS << "','" << MODE << "','" << TYPE << "')";
		_bstr_t SQL = ssOrder.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);

		return true;
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "insertOrderToDb" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool WCS_Database::insertOrderToDb(std::string ORDER_ID, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE)
{
	try
	{
		std::stringstream ssOrder;
		ssOrder << "INSERT INTO kh_order_info (ORDER_ID, START,TARGET,PRIORITY,STATUS,MODE,TYPE,PALLETNO)VALUES('" << ORDER_ID <<"','"<< START << "','" << TARGET << "'," << PRIORITY << ",'" << STATUS << "','" << MODE << "','" << TYPE << "','666')";
		_bstr_t SQL = ssOrder.str().c_str();
		
		return WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "insertOrderToDb" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool WCS_Database::insertOrderToDb(std::string ORDER_ID, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, int agvID)
{
	try
	{
		std::stringstream ssOrder;
		ssOrder << "INSERT INTO kh_order_info (ORDER_ID, START,TARGET,PRIORITY,STATUS,MODE,TYPE,AGV_ID)VALUES('" << ORDER_ID << "','" << START << "','" << TARGET << "'," << PRIORITY << ",'" << STATUS << "','" << MODE << "','" << TYPE << "'," << agvID << ")";
		_bstr_t SQL = ssOrder.str().c_str();
		return WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "insertOrderToDb" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool WCS_Database::insertOrderToDb(std::string ORDER_ID, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, int agvID, std::string palletNo)
{
	try
	{
		std::stringstream ssOrder;
		ssOrder << "INSERT INTO kh_order_info (ORDER_ID, START,TARGET,PRIORITY,STATUS,MODE,TYPE,AGV_ID,PALLETNO)VALUES('" << ORDER_ID << "','" << START << "','" << TARGET << "'," << PRIORITY << ",'" << STATUS << "','" << MODE << "','" << TYPE << "'," << agvID << ",'" << palletNo <<"')";
		_bstr_t SQL = ssOrder.str().c_str();
		return WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "insertOrderToDb" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

int WCS_Database::readTaskStatus(int taskid)
{
	int ts = -3;

	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "select count(*) FROM task_feedback_table WHERE task_id=" << taskid << "";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		if (row_count != 0)
		{

			std::stringstream ssTask;
			ssTask << "SELECT task_status FROM task_feedback_table WHERE task_id=" << taskid << "";
			_bstr_t SQL2 = ssTask.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
			recordPtr_->MoveLast();
			ts = (int)recordPtr_->GetCollect("task_status");
		}
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "readTaskStatus" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
	return ts;
}

bool WCS_Database::stopCurrentCharging(AGV* agv)
{
	try
	{
		std::stringstream ssTask;
		ssTask << "INSERT INTO task_op_interface (object,agv_id,task_id,op_code) VALUES('agv'," << agv->AGV_ID_ << ",0,'stop charging')";
		_bstr_t SQL = ssTask.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
		return true;
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "stopCurrentCharging" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool WCS_Database::updateOrderInfo()
{
	try
	{
		int row_count = 0;
		_bstr_t SQL = "SELECT COUNT(*) FROM kh_report_order_info WHERE TYPE = 'CARRY' ORDER BY ENTERDATE desc limit 20";
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		if (row_count != 0)
		{
			std::string sql = "SELECT * FROM kh_report_order_info WHERE TYPE = 'CARRY' ORDER BY ENTERDATE desc limit 20";
			_bstr_t SQL = sql.c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
			recordPtr_->MoveFirst();
			while (recordPtr_->adoEOF == VARIANT_FALSE) {
				Order current_order;
				current_order.ORDER_ID_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ORDER_ID"))->Value);
				current_order.AGV_ID_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("AGV_ID"))->Value));
				current_order.START_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
				current_order.TARGETED_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
				current_order.PRIORITY_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("PRIORITY"))->Value));
				current_order.STATUS_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATUS"))->Value);
				current_order.MODE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);
				current_order.TYPE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TYPE"))->Value);
				std::regex data_regex("/(\\d)(?!\\d)");
				current_order.ENTERDATE_ = std::regex_replace((std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ENTERDATE"))->Value), data_regex, "/0$1");
				current_order.FINISHDATE_ = std::regex_replace((std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("FINISHDATE"))->Value), data_regex, "/0$1");
				ORDER_MANAGE.Add_to_full_list_if_not_exist(current_order);
				recordPtr_->MoveNext();
			}
		}
		else {
			return false;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "updateOrderInfo" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}

	return true;
}

bool WCS_Database::updateNewOrderInfo()
{
	try
	{
		std::map<std::string, Order> order_map = ORDER_MANAGE.getNewOrder();

		order_map.clear();

		ORDER_MANAGE.setNewOrder(order_map);

		int row_count = 0;
		_bstr_t SQL = "SELECT COUNT(*) FROM kh_order_info WHERE STATUS ='NEW'ORDER BY ENTERDATE desc limit 20";
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		if (row_count != 0)
		{

			std::string sql = "SELECT * FROM kh_order_info WHERE STATUS ='NEW' ORDER BY ENTERDATE desc limit 20";
			_bstr_t SQL = sql.c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
			recordPtr_->MoveFirst();
			while (recordPtr_->adoEOF == VARIANT_FALSE) {
				Order current_order;
				current_order.ORDER_ID_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ORDER_ID"))->Value);
				current_order.START_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
				current_order.TARGETED_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
				current_order.PRIORITY_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("PRIORITY"))->Value));
				current_order.STATUS_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATUS"))->Value);
				current_order.MODE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);
				current_order.TYPE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TYPE"))->Value);
				std::regex data_regex("/(\\d)(?!\\d)");
				current_order.ENTERDATE_ = std::regex_replace((std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ENTERDATE"))->Value), data_regex, "/0$1");
				ORDER_MANAGE.Get_All_NEW_Order(current_order);
				recordPtr_->MoveNext();
			}
			return true;
		}
		else {
			return false;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "updateDodInfo" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

void WCS_Database::abortTask(int id)
{
	try
	{
		std::stringstream ssTask;
		ssTask << "INSERT INTO task_op_interface(object,agv_id,task_id,op_code) VALUES('task',0," << id << ",'abort')";
		_bstr_t SQL = ssTask.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "abortTask" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

void WCS_Database::splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

bool WCS_Database::checkNewOrderList(AGV* associate_AGV)
{
	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;
	try
	{
		if (associate_AGV->AGV_Type_ == 21)//测试暂时用1来替代
		{
			ss << "SELECT COUNT(*) FROM kh_order_info WHERE STATUS = 'NEW' AND MODE='J400'";
		}
		else if (associate_AGV->AGV_Type_ == 2)
		{
			ss << "SELECT COUNT(*) FROM kh_order_info WHERE STATUS = 'NEW' AND MODE='L16'";
		}
		else
		{
			return false;
		}
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {

		std::stringstream ss;
		ss << e.ErrorMessage() << "checkNewOrderList" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}

}

bool WCS_Database::revokeDodOrder(std::string order_id)
{
	try {
		int row_count = 0;
		std::stringstream ss;
		char szSq1[10240] = { 0 };
		ss << "SELECT COUNT(*) FROM kh_order_info WHERE ORDER_ID = '" << order_id << "'";
		sprintf(szSq1, "%s", ss.str().c_str());
		recordPtr2_ = WCS_ADO_.GetRecordSet((_bstr_t)szSq1);
		if (recordPtr2_)
		{
			row_count = (int)recordPtr2_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			std::stringstream ss2;
			ss2 << "UPDATE kh_order_info SET STATUS = 'REVOKE' WHERE ORDER_ID = '" << order_id << "'";
			_bstr_t SQL = ss2.str().c_str();
			
			return WCS_ADO_.ExecuteSQL(SQL);
		}
		else
		{
			std::stringstream ss;
			ss << "Revoke DOD Order Error !!!!!! ";
			log_info_color(log_color::red, ss.str().c_str());
			return false;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "revokeDodOrder" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
	return false;
}



bool WCS_Database::updateDodOrderPriority(std::string order_id, std::string priority)
{
	try {
		int row_count = 0;
		std::stringstream ss;
		char szSq1[10240] = { 0 };
		ss << "SELECT COUNT(*) FROM kh_order_info WHERE ORDER_ID = '" << order_id << "'";
		sprintf(szSq1, "%s", ss.str().c_str());
		recordPtr2_ = WCS_ADO_.GetRecordSet((_bstr_t)szSq1);
		if (recordPtr2_)
		{
			row_count = (int)recordPtr2_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			std::stringstream ss2;
			ss2 << "UPDATE kh_order_info SET PRIORITY ="<<priority<<" WHERE ORDER_ID = '" << order_id << "'";
			_bstr_t SQL = ss2.str().c_str();

			return WCS_ADO_.ExecuteSQL(SQL);
		}
		else
		{
			std::stringstream ss;
			ss << "Revoke DOD Order Error !!!!!! ";
			log_info_color(log_color::red, ss.str().c_str());
			return false;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "revokeDodOrder" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
	return false;
}

void WCS_Database::setErrStorageOrder(int wcs_task_id)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE kh_order_info SET STATUS = 'ERR' WHERE ORDER_ID = '" << wcs_task_id << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "setErrStorageOrder" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

bool WCS_Database::setCurrentTableStorageStatus(std::string table_name, std::string resource_status, std::string storage_name)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE " << table_name << " SET resource_status = '" << resource_status << "' WHERE storage_name = '" << storage_name << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
		return true;
	}
	catch (_com_error &e) {
		std::cout << "getCurrentTableStorageStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
}

void WCS_Database::setDatabaseCurrentComfirmStatus(std::string current_confirm, std::string status)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE s_confirm_station_status SET STATUS = '" << status << "' WHERE STATION_NAME = '" << current_confirm << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "setDatabaseCurrentComfirmStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}

/// <summary>
/// 福沙 Sets the database current bridge status.
/// </summary>
/// <param name="current_confirm">The current confirm.</param>
/// <param name="status">The status.</param>
/// Creator:MeiXu
/// CreateDate:2021/2/3
/// 
void WCS_Database::setDatabaseCurrentBridgeStatus(std::string current_confirm, std::string status)
{
	try
	{
		std::stringstream ss;
		ss << "UPDATE kh_bridge_info SET STATUS = '" << status << "' WHERE BRIDGE_ID = '" << current_confirm << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "setDatabaseCurrentBridgeStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}

void WCS_Database::setDatabaseCurrentParkingStatus(std::string current_parking, std::string status)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE parking_manage SET STATUS = '" << status << "' WHERE STATION_NAME = '" << current_parking << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "setDatabaseCurrentComfirmStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}

void WCS_Database::setDatabaseEquipmentStatus(std::string id, std::string status) {
	try
	{
		std::string table_name = "kh_equipment_info";
		std::string equipment_id = "EQUIP_ID";
		std::string equipment_status = "EQUIP_STATUS";
		int row_count = 0;
		std::stringstream ss;
		ss << " UPDATE " << table_name << " SET " << equipment_status << " = '" << status << "' WHERE " << equipment_id << " = '" << id << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "setDatabaseCurrentComfirmStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}

/*————————————————————————————————————分界线————————————————————*/

/********************************************************************
	created:	2020/06/11
	created:	11:6:2020   17:18
	filename: 	E:\work\Project\KunHouSimulator\WMS_Sets\wcs_aimosheng\src\Lib\ADODatabase\WCS_Database.cpp
	file path:	E:\work\Project\KunHouSimulator\WMS_Sets\wcs_aimosheng\src\Lib\ADODatabase
	file base:	WCS_Database
	file ext:	cpp
	author:		HSQ

	purpose:	load all table list from DB
*********************************************************************/
bool WCS_Database::loadWcsTableListFromDB(std::vector<Sql_Table_Attri> &sql_table_list_)
{
	_bstr_t SQL1;
	_bstr_t SQL2;
	_RecordsetPtr recordPtr;

	SQL1 = "select count(*) from A_wcs_table_list ";
	SQL2 = "select * from A_wcs_table_list";

	try {

		int row_count = 0;

		recordPtr = WCS_ADO_.GetRecordSet(SQL1);                               //get the task(RecordSet) with the highest priority

		if (recordPtr)
		{
			row_count = (int)recordPtr->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			std::stringstream ss;
			recordPtr = WCS_ADO_.GetRecordSet(SQL2);                               //get the task(RecordSet) with the highest priority

			recordPtr->MoveFirst();
			while (recordPtr->adoEOF == VARIANT_FALSE) {

				Sql_Table_Attri table_attri;

				table_attri.sql_table_name = (std::string)(_bstr_t)(recordPtr->Fields->GetItem(_variant_t("table_name"))->Value);
				table_attri.sql_table_type = (std::string)(_bstr_t)(recordPtr->Fields->GetItem(_variant_t("table_type"))->Value);
				table_attri.group_name = (std::string)(_bstr_t)(recordPtr->Fields->GetItem(_variant_t("group_name"))->Value);
				table_attri.columnSpan = atoi(_bstr_t(recordPtr->Fields->GetItem(_variant_t("columnSpan"))->Value));
				table_attri.rowSpan = atoi(_bstr_t(recordPtr->Fields->GetItem(_variant_t("rowSpan"))->Value));
				table_attri.widget_column = atoi(_bstr_t(recordPtr->Fields->GetItem(_variant_t("column"))->Value));
				table_attri.widget_row = atoi(_bstr_t(recordPtr->Fields->GetItem(_variant_t("row"))->Value));

				sql_table_list_.push_back(table_attri);
				recordPtr->MoveNext();
			}
			return true;
		}
		else {
			return false;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "loadWcsTableListFromDB" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}

	return true;
}
/********************************************************************
	created:	2020/07/02
	created:	2:7:2020   11:45
	filename: 	E:\work\Project\KunHouSimulator\WMS_Sets\wcs_aimosheng\src\Lib\ADODatabase\WCS_Database.cpp
	file path:	E:\work\Project\KunHouSimulator\WMS_Sets\wcs_aimosheng\src\Lib\ADODatabase
	file base:	WCS_Database
	file ext:	cpp
	author:		HSQ
	
	purpose:	load all storage data from DB 
*********************************************************************/
bool WCS_Database::getStorageList(std::map<int, Storage> &storage_map, std::string sql_table_name)
{
	_bstr_t SQL1;
	_bstr_t SQL2;

	std::stringstream ss, ss2;
	ss << "select count(*) from " << sql_table_name;
	SQL1 = (_bstr_t)(ss.str().c_str());

	ss2 << "select * from " << sql_table_name;
	SQL2 = (_bstr_t)(ss2.str().c_str());

	try {
		/**
		 * 这里为了实现从多张表中读取 Storage ， 取消使用 Current_Storage_List 进行传值
		 * 改为直接取值，然后写入 storage_map
		 */
		//std::map<int, Storage> Current_Storage_List;

		int row_count = 0;
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL1);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			std::stringstream ss;
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);                               //get the task(RecordSet) with the highest priority

			recordPtr_->MoveFirst();
			while (recordPtr_->adoEOF == VARIANT_FALSE) {

				Storage new_storage;
				new_storage.ID_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("id"))->Value));
				new_storage.Storage_Name_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("storage_name"))->Value);
				new_storage.Storage_Row_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("storage_row"))->Value));
				new_storage.Storage_Column_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("storage_column"))->Value));
				new_storage.Storage_Status_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("storage_status"))->Value);
				new_storage.Storage_Type_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("storage_type"))->Value);
				new_storage.Resource_status_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("resource_status"))->Value);
				new_storage.sql_table_name_ = sql_table_name;
				// 这里直接对 storage_map 写入
				storage_map[new_storage.ID_] = new_storage;
				//Current_Storage_List[new_storage.ID_] = new_storage;
				recordPtr_->MoveNext();
			}
			//storage_map = Current_Storage_List;
			return true;
		}
		else {
			return false;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		if (&e == nullptr)
		{
			ss << "getBufferStorageStatus" << e.Description();
		}
		else {
			ss << e.ErrorMessage() << "getBufferStorageStatus";
		}
		log_info_color(log_color::red, ss.str().c_str());
	}

	return true;
}

void WCS_Database::updateWcsStorageStatus(std::string sql_table_name, std::string storage_name,std::string status_name, std::string status)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE " << sql_table_name<<" SET "<<status_name<<" = '"<<status<<"' WHERE storage_name = '" << storage_name << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "updateWcsStorageStatus" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

bool WCS_Database::getCurrentParkingStation(std::string &station_name, std::string &is_charging, int agv_type)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		std::stringstream ss2;
		ss << "SELECT COUNT(*) FROM parking_manage WHERE STATUS='IDLE' AND AGV_TYPE='" << agv_type << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}

		if (row_count != 0)
		{
			ss2 << "select * FROM parking_manage WHERE STATUS = 'IDLE' AND AGV_TYPE='" << agv_type << "'";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);

			station_name = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATION_NAME"))->Value);
			is_charging = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("IS_CHARGING"))->Value);
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {
		std::cout << "getCurrentParkingStation " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
}

void WCS_Database::reserveCurrentParkingStation(std::string station_name)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE parking_manage SET STATUS = 'BUSY' WHERE STATION_NAME = '" << station_name << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);

	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "reserveCurrentParkingStation" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

void WCS_Database::updateCurrentWeightInfo(double weight, std::string status)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE kh_report_weight_info SET WEIGHT = '" << weight << "', STATUS = '" << status << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);

	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "updateCurrentWeightInfo" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

float WCS_Database::getDatabaseCurrentWeightInfo()
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		std::stringstream ss2;
		ss << "SELECT COUNT(*) FROM kh_report_weight_info WHERE `STATUS`='SUCCESS'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}

		if (row_count != 0)
		{
			ss2 << "SELECT * FROM kh_report_weight_info";
			_bstr_t SQL1 = ss2.str().c_str();
			recordPtr2_ = WCS_ADO_.GetRecordSet(SQL1);
			std::string weight = (std::string)(_bstr_t)(recordPtr2_->Fields->GetItem(_variant_t("WEIGHT"))->Value);
			return std::atof(weight.c_str());
		}
		return -1;
		
	}
	catch (_com_error &e) {
		std::cout << "getDatabaseCurrentComfirmStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}

void WCS_Database::releaseCurrentParkingStation(std::string station_name)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE parking_manage SET STATUS = 'IDLE' WHERE STATION_NAME = '" << station_name << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);

	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "releaseCurrentParkingStation" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

bool WCS_Database::getDatabaseCurrentComfirmStatus(std::string current_confirm)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		std::stringstream ss2;
		ss << "SELECT * FROM s_confirm_station_status WHERE STATION_NAME='" << current_confirm << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		std::string status = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATUS"))->Value);
		if (status == "IDLE")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {
		std::cout << "getDatabaseCurrentComfirmStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}

/// <summary>
/// 福沙 Gets the current bridge status from database.
/// </summary>
/// <param name="current_confirm">The current bridge.</param>
/// <returns>Bridge is on the floor</returns>
/// Creator:MeiXu
/// CreateDate:2021/2/3
/// 
bool WCS_Database::getDatabaseCurrentBridgeStatus(std::string current_bridge)
{
	try
	{
		std::stringstream ss;
		ss << "SELECT * FROM kh_bridge_info WHERE BRIDGE_ID='" << current_bridge << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		std::string status = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("BRIDGE_STATUS"))->Value);
		if (status == "DOWN")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {
		std::cout << "getDatabaseCurrentBridgeStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}

bool WCS_Database::getCurrentStationIsCharging(std::string station_name)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;

		ss << "SELECT COUNT(*) FROM parking_manage WHERE STATION_NAME='" << station_name << "' AND IS_CHARGING='FALSE'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}

		if (row_count == 1)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	catch (_com_error &e) {
		std::cout << "getCurrentStationIsCharging " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}

bool WCS_Database::getCurrentMustChargingStation(std::string &station_name)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		std::stringstream ss2;
		ss << "SELECT COUNT(*) FROM parking_manage WHERE Status='IDLE' AND IS_CHARGING='TRUE'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}

		if (row_count != 0)
		{
			ss2 << "SELECT * FROM parking_manage WHERE STATUS='IDLE' AND IS_CHARGING='TRUE'";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
			station_name = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATION_NAME"))->Value);
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {
		std::cout << "getCurrentMustChargingStation " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
}

/**
 * 从数据库获取 tableName 指向的表的 listName 列，并以 std::vector<std::string> 格式返回
 */
bool WCS_Database::loadListFromDB(std::vector<std::string> &valueList, std::string tableName, std::string listName)
{
	try
	{
		// 记录个数
		int row_count = 0;
		// SQL 语句
		std::stringstream ss;
		std::stringstream ss2;
		ss << "SELECT COUNT(*) FROM " << tableName;
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		// 存在可以读取的记录
		if (row_count != 0)
		{
			// 执行查询 SQL
			ss2 << "SELECT * FROM " << tableName;
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
			// 遍历整个表
			while (recordPtr_->adoEOF == VARIANT_FALSE) {
				// 写入 valueList
				valueList.push_back((std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t(listName.c_str()))->Value));
				recordPtr_->MoveNext();
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {
		std::cout << "loadListFromDB " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
	return true;
}

/**
 * 获取库位名对应状态
 */
std::string WCS_Database::getStorageStatus(std::string &storage_name) {
	int count = 0;
	std::stringstream ss;
	std::stringstream ss2;
	std::string status = "";
	try
	{
		ss << "SELECT COUNT(*) FROM s_first_station_status WHERE storage_name ='" << storage_name<<"'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr2_ = WCS_ADO_.GetRecordSet(SQL);

		if (recordPtr2_)
		{
			count = (int)recordPtr2_->GetCollect("COUNT(*)");
		}
		else
		{
			std::stringstream ss3;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (count != 0)
		{
			ss2 << "SELECT * FROM s_first_station_status WHERE storage_name ='" << storage_name << "'";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr2_ = WCS_ADO_.GetRecordSet(SQL2);
			status = (std::string)(_bstr_t)(recordPtr2_->Fields->GetItem(_variant_t("storage_status"))->Value);
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "getStorageStatus" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
	return status;
}

bool WCS_Database::getParkingStorage(std::vector<ModelStationParking*> *parkings) {
	std::string db_name = "parking_manage";
	try
	{
		// 记录个数
		int row_count = 0;
		// SQL 语句
		std::stringstream ss;
		std::stringstream ss2;
		ss << "SELECT COUNT(*) FROM " << db_name;
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		// 存在可以读取的记录
		if (row_count != 0)
		{
			// 执行查询 SQL
			ss2 << "SELECT * FROM "<< db_name <<" ORDER BY ID";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
			// 遍历整个表
			while (recordPtr_->adoEOF == VARIANT_FALSE) {
				// 写入 valueList
				//(std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t(listName.c_str()))->Value)
				//int id = recordPtr_->Fields->GetItem(_variant_t("ID"))->Value;
				std::string name = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATION_NAME"))->Value);
				std::string charging = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("IS_CHARGING"))->Value);
				std::string status = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATUS"))->Value);
				(*parkings).push_back(new ModelStationParking(name, charging, status));
				recordPtr_->MoveNext();
			}
			
		}
	}
	catch (_com_error &e) {
		std::cout << "getParkingStorage" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
	return ((*parkings).begin() == (*parkings).end());
}

/// <summary>
/// Gets the bridge from db.
/// </summary>
/// <param name="parkings">The parkings.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/3
/// 


void WCS_Database::setDatabaseCurrentEquipmentInfoStatus(std::string current_equipment, std::string equip_status)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "UPDATE kh_equipment_info SET EQUIP_STATUS = '" << equip_status << "' WHERE EQUIP_ID = '" << current_equipment << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "setDatabaseCurrentEquipmentInfoStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}


void WCS_Database::setDatabaseCurrentEquipmentAppleyStatus(std::string current_equipment, std::string status)
{
	try
	{
		std::stringstream ss;
		ss << "UPDATE kh_equipment_info SET STATUS = '" << status << "' WHERE EQUIP_ID = '" << current_equipment << "'";
		_bstr_t SQL = ss.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "setDatabaseCurrentEquipmentInfoStatus " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}
}

std::string WCS_Database::getDatabaseCurrentEquipmentInfoStatus(std::string current_equipment)
{
	int count = 0;
	std::stringstream ss;
	std::stringstream ss2;
	std::string EQUIP_STATUS="";
	try
	{
		ss << "SELECT COUNT(*) FROM kh_equipment_info WHERE EQUIP_ID='" << current_equipment << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

		if (recordPtr_)
		{
			count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		else
		{
			std::stringstream ss3;
			ss3 << "Cant get Recordset!";
			log_info_color(log_color::red, ss3.str().c_str());
		}
		if (count != 0)
		{
			ss2 << "SELECT * FROM kh_equipment_info WHERE EQUIP_ID='" << current_equipment << "'";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
			EQUIP_STATUS = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("EQUIP_STATUS"))->Value);
			return EQUIP_STATUS;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "getDatabaseCurrentEquipmentInfoStatus" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return EQUIP_STATUS;
	}
}

std::string WCS_Database::getCurrentAGVIsBack(int agv_id)
{
	int count = 0;
	std::stringstream ss;
	std::stringstream ss2;
	std::string SIGNAL = "";
	try
	{

		ss << "SELECT COUNT(*) FROM agv_back_signal where AGV_ID = " << agv_id << "";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

		if (recordPtr_)
		{
			count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		else
		{
			std::stringstream ss3;
			ss3 << "Cant get Recordset!";
			log_info_color(log_color::red, ss3.str().c_str());
		}
		if (count != 0)
		{
			ss2 << "SELECT * FROM agv_back_signal where AGV_ID = " << agv_id << "";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
			SIGNAL = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("SIGNAL"))->Value);
			return SIGNAL;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "getCurrentAGVIsBack" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		
	}
	return SIGNAL;
}

bool WCS_Database::getDatabaseCurrentNextNewOrder(std::string statioin, std::string agv_type)
{

	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;
	try
	{
		ss << "SELECT COUNT(*) FROM kh_order_info WHERE STATUS = 'NEW' AND MODE='" << agv_type << "' ORDER BY ENTERDATE asc limit 1";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			ss2 << "SELECT * FROM kh_order_info WHERE STATUS = 'NEW' AND MODE='" << agv_type << "' ORDER BY ENTERDATE asc limit 1";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);

			recordPtr_->MoveFirst();
			while (recordPtr_->adoEOF == VARIANT_FALSE)
			{
				std::string  START = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
			
				if (START.substr(0, 6) == statioin.substr(0,6))
				{
					return true;
				}
				else 
				{
					return false;
				}
				recordPtr_->MoveNext();
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {

		std::stringstream ss;
		ss << e.ErrorMessage() << "getDatabaseCurrentNextNewOrder" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool WCS_Database::LoadPLCMap(std::map<std::string, std::map<int, std::string>>* plc_map_, std::string table_name, std::vector<std::string> table_fields_) {
	bool result = false;
	int row_count = 0;
	// 构建SQL语句
	try
	{
		std::stringstream ss;
		std::stringstream ss2;
		ss << "SELECT COUNT(*) FROM " << table_name;
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		else
		{
			std::stringstream ss3;
			ss3 << "Cant get Recordset!";
			log_info_color(log_color::red, ss3.str().c_str());
		}
		if (row_count != 0)
		{
			ss2 << "SELECT * FROM " << table_name;
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
			while (recordPtr_->adoEOF == VARIANT_FALSE) {
				std::string plc_name = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t(table_fields_[1].c_str()))->Value);
				std::map<int, std::string> pld_data;
				for (size_t i = 0; i < table_fields_.size(); i++)
				{
					pld_data[i] = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t(table_fields_[i].c_str()))->Value);
				}
				recordPtr_->MoveNext();
				(*plc_map_)[plc_name] = pld_data;
			}
			
			return true;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "LoadPLCMap " << e.Description();
		log_info_color(log_color::red, ss.str().c_str());

	}

	return result;
}

bool WCS_Database::updatePLCStatus(std::string dev_name, std::string plc_status) {
	bool result = false;
	// 构建SQL语句
	std::stringstream ss;
	ss << "UPDATE " << "kh_plc_data" << " SET " << "PLC_TRIGGER" << " = '" << plc_status << "' WHERE " << "DEV_NAME" << " = '" << dev_name << "'";
	_bstr_t SQL = ss.str().c_str();
	log_error(ss.str().c_str());
	try
	{
		result = WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "setPointField :" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}

	return result;
}
bool WCS_Database::updatePLCMsgStatus(std::string plc_status) {
	bool result = false;
	// 构建SQL语句
	std::stringstream ss;
	ss << "UPDATE " << "kh_plc_data" << " SET " << "MSG_STATUS" << " = '" << plc_status << "'";
	_bstr_t SQL = ss.str().c_str();
	log_error(ss.str().c_str());
	try
	{
		result = WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "WCS_Database::updatePLCMsgStatus :" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}

	return result;
}

bool WCS_Database::updatePLCReadStatus(std::string plc_status) {
	bool result = false;
	// 构建SQL语句
	std::stringstream ss;
	ss << "UPDATE " << "kh_plc_data" << " SET " << "READ_STATUS" << " = '" << plc_status << "' WHERE READ_STATUS!='AUTO'";
	_bstr_t SQL = ss.str().c_str();
	log_error(ss.str().c_str());
	try
	{
		result = WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "WCS_Database::updatePLCReadStatus :" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}

	return result;
}
bool WCS_Database::updatePLCMsgStatus(std::string dev_name, std::string plc_status) {
	bool result = false;
	// 构建SQL语句
	std::stringstream ss;
	ss << "UPDATE " << "kh_plc_data" << " SET " << "MSG_STATUS" << " = '" << plc_status << "' WHERE " << "DEV_NAME" << " = '" << dev_name << "'";
	_bstr_t SQL = ss.str().c_str();
	log_error(ss.str().c_str());
	if (plc_status != "IDLE")
	{
		log_info(ss.str().c_str());
	}
	try
	{
		result = WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "WCS_Database::updatePLCMsgStatus :" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}

	return result;
}

bool WCS_Database::updatePLCReadStatus(std::string dev_name, std::string plc_status) {
	bool result = false;
	// 构建SQL语句
	std::stringstream ss;
	ss << "UPDATE " << "kh_plc_data" << " SET " << "READ_STATUS" << " = '" << plc_status << "' WHERE " << "DEV_NAME" << " = '" << dev_name << "'";
	_bstr_t SQL = ss.str().c_str();
	log_error(ss.str().c_str());
	try
	{
		result = WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "WCS_Database::updatePLCReadStatus :" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}

	return result;
}

bool WCS_Database::changeAgvMode(std::string equip_mode) {
	bool result = false;
	// 构建SQL语句
	std::stringstream ss;
	ss << "UPDATE " << "agv_mode" << " SET " << "EQUIP_MODE" << " = '" << equip_mode << "'";
	_bstr_t SQL = ss.str().c_str();

	try
	{
		result = WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "WCS_Database::changeAgvMode :" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}

	return result;
}

bool WCS_Database::agvBackSignal(int agv_id, std::string mode) {
	bool result = false;
	// 构建SQL语句
	std::stringstream ss;
	ss << "UPDATE " << " agv_back_signal " << " SET " << " BACK_SIGNAL = '" << mode << "' WHERE " << "AGV_ID" << " = " << agv_id;
	_bstr_t SQL = ss.str().c_str();

	try
	{
		result = WCS_ADO_.ExecuteSQL(SQL);
	}
	catch (_com_error &e) {
		std::cout << "WCS_Database::updatePLCReadStatus :" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
	}

	return result;
}
/*
从 table_name 中，获取 table_fields 中的字段， 并放在 result_list 中
返回获取是否成功
*/
bool WCS_Database::loadFromDB(std::string table_name, std::vector<std::string> table_fields, std::vector<std::vector<std::string>>* result_list) {
	bool result = false;
	// 构建SQL语句
	std::stringstream ss1;
	std::stringstream ss2;
	ss1 << "SELECT COUNT(*) FROM " << table_name;
	ss2 << "SELECT * FROM " << table_name;
	_bstr_t SQL1 = ss1.str().c_str();
	_bstr_t SQL2 = ss2.str().c_str();

	try {
		int row_count = 0;
		recordPtr2_ = WCS_ADO_.GetRecordSet(SQL1);
		if (recordPtr2_)
		{
			row_count = (int)recordPtr2_->GetCollect("count(*)");
		}
		else
		{
			std::stringstream ss;
			ss << "Cant get Recordset!";
			log_info_color(log_color::red, ss.str().c_str());
		}
		if (row_count != 0)
		{
			recordPtr2_ = WCS_ADO_.GetRecordSet(SQL2);
			recordPtr2_->MoveFirst();
			while (recordPtr2_->adoEOF == VARIANT_FALSE) {
				std::vector<std::string> record;
				for each (std::string field in table_fields)
				{
					record.push_back((std::string)(_bstr_t)(recordPtr2_->Fields->GetItem(_variant_t(field.c_str()))->Value));
				}
				result_list->push_back(record);
				recordPtr2_->MoveNext();
			}
			result = true;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "loadFromDB :" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
	return result;
}

bool WCS_Database::getCurrentEquipToStorage(std::string &storage_group, std::string equip_name)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "SELECT COUNT(*) FROM s_equip_storage WHERE equip_name='" << equip_name << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		if (row_count != 0)
		{
			std::stringstream ss2;
			ss2 << "SELECT * FROM s_equip_storage WHERE equip_name='" << equip_name << "'";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
			storage_group = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("storage_group"))->Value);
			return true;
		}
		else
		{
			return false;
		}

	}
	catch (_com_error &e) {
		std::cout << "getCurrentEquipToStorage " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
}

bool WCS_Database::getCurrentTableStorageName(std::string table_name, std::string storage_status, std::string &storage_name, std::string storage_type, std::string storage_group)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "SELECT COUNT(*) FROM " << table_name << " WHERE storage_status='" << storage_status << "' AND storage_type='" << storage_type << "' AND storage_group='" << storage_group << "' AND resource_status='IDLE'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		if (row_count != 0)
		{
			std::stringstream ss2;
			ss2 << "SELECT * FROM " << table_name << " WHERE storage_status='" << storage_status << "' AND storage_type='" << storage_type << "' AND storage_group='" << storage_group << "'AND resource_status='IDLE'";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
			storage_name = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("storage_name"))->Value);
			return true;
		}
		else
		{
			return false;
		}

	}
	catch (_com_error &e) {
		std::cout << "getCurrentTableStorageName " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
}

int WCS_Database::GetAgvExeGoodsTask(std::string palletNo, std::string status, std::string mode)
{
	std::stringstream ss;
	ss << "select count(*) from kh_report_order_info WHERE STATUS = '" << status << "' AND MODE = '" << mode << "' ORDER BY ID DESC LIMIT 1";
	_bstr_t SQL = ss.str().c_str();
	try
	{
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			if ((int)recordPtr_->GetCollect("count(*)") == 0)
				return 0;
			else
			{
				std::stringstream ss2;
				ss2 << "select * from kh_report_order_info WHERE STATUS = '" << status << "' AND MODE = '" << mode << "' ORDER BY ID DESC LIMIT 1";
				_bstr_t SQL2 = ss2.str().c_str();

				// SQL = "select task_id from kh_report_order_info";
				recordPtr_ = WCS_ADO_.GetRecordSet(SQL2);
				recordPtr_->MoveLast();
				return (int)recordPtr_->GetCollect("AGV_ID");
			}
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "GetAgvExeGoodsTask" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

bool WCS_Database::plcForbidAllStorage() {
	try
	{
		std::string table_name = "s_storage_station_status";

		int row_count = 0;
		std::stringstream ss;
		std::stringstream ss2;
		ss << "UPDATE " << table_name << " SET storage_status = '" << "EMPTY" << "' WHERE storage_type = '" << "TRAY" << "'";
		ss2 << "UPDATE " << table_name << " SET storage_status = '" << "FULL" << "' WHERE storage_type = '" << "AREA" << "'";
		_bstr_t SQL = ss.str().c_str();
		_bstr_t SQL2 = ss2.str().c_str();
		WCS_ADO_.ExecuteSQL(SQL);
		WCS_ADO_.ExecuteSQL(SQL2);
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "setCurrentStorageStatus" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
	return true;
}


bool WCS_Database::readAreaInfo(std::map<int, std::vector<Pos_Info>> *all_area) {
	bool result = false;

	try
	{
		std::stringstream ss;
		ss << "SELECT COUNT(*) FROM kh_region_info LIMIT 1";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			if ((int)recordPtr_->GetCollect("COUNT(*)") != 0) {
				std::stringstream ss2;
				ss2 << "SELECT * FROM kh_region_info";
				_bstr_t SQL2 = ss2.str().c_str();

				recordPtr2_ = WCS_ADO_.GetRecordSet(SQL2);
				recordPtr2_->MoveFirst();
				result = true;
				while (recordPtr2_->adoEOF == VARIANT_FALSE) {
					std::vector<std::string> record;
					int id = atoi((_bstr_t)(recordPtr2_->Fields->GetItem(_variant_t("ID"))->Value));
					std::string region = (std::string)(_bstr_t)(recordPtr2_->Fields->GetItem(_variant_t("REGION"))->Value);

					// region -> num 个 Pos
					std::vector <std::string> point_row;
					boost::split(point_row, region, boost::is_any_of("("));
					for each (auto var in point_row)
					{
						std::vector <std::string> point_pos;
						boost::split(point_pos, var, boost::is_any_of(","));
						if (point_pos.size() == 2)
						{
							Pos_Info pos;
							pos.x = atof(point_pos.at(0).c_str());
							pos.y = atof(point_pos.at(1).replace(point_pos.at(1).find(")"), 1, "").c_str());
							(*all_area)[id].push_back(pos);
						}
					}

					recordPtr2_->MoveNext();
				}
			}
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "readAreaInfo" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
	return result;
}

//判断出入库的任务终点是否为货位（用于判断任务是出库还是入库）
bool WCS_Database::CheckTargetIsStorage(std::string target)
{
	try {
		int row_count = 0;
		std::stringstream ss;
		
		ss << "SELECT COUNT(*) FROM s_equip_station_status WHERE storage_name = '" << target << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		if (row_count != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "CheckTargetIsStorage" << e.Description();
		log_info_color(log_color::red, "CheckTargetIsStorage expcetion happened in %s %s %d", __FILE__, __FUNCTION__, __LINE__);
		return false;
	}
}