#include <iostream>
#include <sstream>
#include "stdlib.h"
#include "ADODatabase/DatabaseManage.h"
#include "ADODatabase/Oracle_Database.h"
#include "Manage/Order_Manage.h"
#include "Manage/Storage_Manage.h"
#include "Core/Task_Chain_Manage.h"
#include "Core/Task_Chain.h"
#include "comm/simplelog.h"
#include <Windows.h>

Oracle_Database::Oracle_Database()
{
	
}

Oracle_Database::~Oracle_Database()
{

}

void Oracle_Database::set_Oracle_ADO(ADOcon ADO)
{
	Oracle_ADO_ = ADO;
}

bool Oracle_Database::copyOracleOrderInfo()
{
	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;
	char szSq1[10240] = { 0 };
	char szSq12[10240] = { 0 };
	Task_Chain_Info current_order;
	try
	{
		ss << "SELECT COUNT(*) FROM \"KH_ORDER_INFO\" WHERE STATUS = 'NEW'";
		sprintf(szSq1, "%s", ss.str().c_str());
		recordPtr_ = Oracle_ADO_.GetRecordSet((_bstr_t)szSq1);
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
			ss2 << "SELECT * FROM \"KH_ORDER_INFO\" WHERE STATUS = 'NEW'";
			sprintf(szSq12, "%s", ss2.str().c_str());
			recordPtr_ = Oracle_ADO_.GetRecordSet((_bstr_t)szSq12);

			recordPtr_->MoveFirst();
			while (recordPtr_->adoEOF == VARIANT_FALSE)
			{
				current_order.ORDER_ID_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ORDER_ID")))->Value);
				current_order.START_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
				current_order.TARGET_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
				current_order.STATUS_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATUS"))->Value);
				current_order.PRIORITY_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("PRIORITY"))->Value));
				current_order.MODE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);
				current_order.TYPE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TYPE"))->Value);
				current_order.SYSTEM_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("SYSTEM"))->Value);
				current_order.AGV_ID_ = atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("AGV_ID"))->Value));
				current_order.Timestamp_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ENTERDATE"))->Value);
				recordPtr_->Delete(adAffectCurrent);
				recordPtr_->MoveNext();
				ORDER_MANAGE.Add_to_full_list_if_not_exist(current_order);
			}
		}
		return true;
	}
	catch (_com_error &e) {

		std::stringstream ss;
		ss << e.ErrorMessage() << "copyOracleOrderInfo" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool Oracle_Database::addOracleOrder(int ORDER_ID, std::string START_CONFIRM, std::string TARGET_CONFIRM, std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, int AGV_ID)

{
	try
	{
		std::stringstream ssOrder;

		ssOrder << "INSERT INTO KH_REPORT_ORDER_INFO (\"ORDER_ID\",\"AGV_ID\",\"START_CONFIRM\",\"TARGET_CONFIRM\",\"PRIORITY\",\"STATUS\",\"MODE\",\"TYPE\",\"START\",\"TARGET\")VALUES(" 
			<< ORDER_ID << "," << AGV_ID << ",'" << START_CONFIRM << "','" << TARGET_CONFIRM << "','"
			<< PRIORITY << "','" << STATUS << "','" << MODE << "','" << TYPE << "','" << START << "','" << TARGET << "')";
		_bstr_t SQL = ssOrder.str().c_str();
		Oracle_ADO_.ExecuteSQL(SQL);
		return true;
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << e.ErrorMessage() << "addOracleOrder" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool Oracle_Database::updateOrderStatusToDoing(int order_id, int agv_id)
{
	try {
		int row_count = 0;
		std::stringstream ss;
		std::stringstream ss2;
		std::stringstream ss3;

		ss << "SELECT COUNT(*) FROM \"KH_REPORT_ORDER_INFO\" WHERE ORDER_ID = " << order_id << "";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = Oracle_ADO_.GetRecordSet(SQL);

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		if (row_count != 0)
		{
			ss2 << "SELECT * FROM \"KH_REPORT_ORDER_INFO\" WHERE ORDER_ID = " << order_id << "";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = Oracle_ADO_.GetRecordSet(SQL2);

			int ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ID"))->Value));
			int ORDER_ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ORDER_ID"))->Value));
			std::string START = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
			std::string TARGET = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
			std::string MODE = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);

			ss3 << "UPDATE KH_REPORT_ORDER_INFO SET STATUS = 'DOING' WHERE ORDER_ID = " << order_id << "";
			_bstr_t SQL5 = ss3.str().c_str();
			Oracle_ADO_.ExecuteSQL(SQL5);
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
void Oracle_Database::updateOrderStatusToDone(Task_Chain* the_task) {

	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;
	std::stringstream ss3;

	ss << "SELECT COUNT(*) FROM \"KH_REPORT_ORDER_INFO\" WHERE STATUS = 'DOING' AND ORDER_ID = " << the_task->Order_ID_ << "";
	_bstr_t SQL = ss.str().c_str();
	recordPtr_ = Oracle_ADO_.GetRecordSet(SQL);

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
			ss2 << "SELECT * FROM \"KH_REPORT_ORDER_INFO\" WHERE STATUS = 'DOING' AND ORDER_ID = " << the_task->Order_ID_ << "";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = Oracle_ADO_.GetRecordSet(SQL2);

			int ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ID"))->Value));
			int ORDER_ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ORDER_ID"))->Value));
			std::string START = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
			std::string TARGET = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
			std::string MODE = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);
			std::string TYPE = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TYPE"))->Value);

			ss3 << "UPDATE KH_REPORT_ORDER_INFO SET STATUS = 'DONE',FINISHDATE = '" << the_task->Get_Over_Time() << "' WHERE ORDER_ID = " << ORDER_ID << "";
			_bstr_t SQL4 = ss3.str().c_str();
			Oracle_ADO_.ExecuteSQL(SQL4);

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
void Oracle_Database::updateOrderStatusToErr(Task_Chain* the_task) {

	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;

	ss << "SELECT COUNT(*) FROM \"KH_REPORT_ORDER_INFO\" WHERE STATUS = 'DOING' AND ORDER_ID = " << the_task->Order_ID_ << "";
	_bstr_t SQL = ss.str().c_str();
	recordPtr_ = Oracle_ADO_.GetRecordSet(SQL);

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
		if (row_count == 1)
		{
			ss2 << "UPDATE KH_REPORT_ORDER_INFO SET STATUS = 'ERR',FINISHDATE = 'null' WHERE ORDER_ID = " << the_task->Order_ID_ << "";
			_bstr_t SQL2 = ss2.str().c_str();
			Oracle_ADO_.ExecuteSQL(SQL2);
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "updateOrderStatusToErr" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}

bool Oracle_Database::insertOrderToOracle(std::string START, std::string TARGET, int PRIORITY, std::string STATUS, std::string MODE, std::string TYPE, std::string SYSTEM, int AGV_ID)
{
	try
	{
		std::stringstream ssOrder;
		ssOrder << "INSERT INTO KH_ORDER_INFO (\"START\",\"TARGET\",\"PRIORITY\",\"STATUS\",\"MODE\",\"TYPE\",\"SYSTEM\",\"AGV_ID\")VALUES('" 
				<< START << "','" << TARGET << "'," << PRIORITY << ",'" << STATUS << "','" << MODE << "','" << TYPE << "','" << SYSTEM << "','" << AGV_ID << "')";
		_bstr_t SQL = ssOrder.str().c_str();
		Oracle_ADO_.ExecuteSQL(SQL);

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