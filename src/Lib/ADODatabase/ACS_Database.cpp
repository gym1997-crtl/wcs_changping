#include <iostream>
#include <sstream>
#include "ADODatabase/DatabaseManage.h"
#include "ADODatabase/ACS_Database.h"
#include "Manage/AGV_System_Manage.h"  
#include "Manage/AGV_Manage.h"  
#include "Manage/Order_Manage.h"
#include "comm/simplelog.h"

ACS_Database::ACS_Database()
{

}

ACS_Database::~ACS_Database()
{

}

void ACS_Database::set_ACS_ADO(ADOcon ADO)
{
	ACS_ADO_=ADO;
}

bool ACS_Database::Download_AGV_Info(std::vector<AGV*> &agv_list)
{
	try{
		int row_count=0;
		_bstr_t SQL="select count(*) from agv_data ";

		recordPtr_ = ACS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if(recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		if(row_count!=0)
		{
			std::stringstream ss;
			_bstr_t SQL="select * from agv_data";
			recordPtr_ = ACS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

			recordPtr_->MoveFirst(); 
			while(recordPtr_->adoEOF==VARIANT_FALSE)
			{  
				AGV* new_AGV=new AGV;
				new_AGV->ID_=atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("agv_id"))->Value));
				new_AGV->AGV_ID_=atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("agv_id"))->Value));
				new_AGV->AGV_Type_=atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("agv_type"))->Value)); 
				new_AGV->AGV_Status_=atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("status"))->Value)); 
				new_AGV->Error_Code_=atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("error_code"))->Value)); 
				new_AGV->Is_Assign_= atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("is_assigned"))->Value)); 
				new_AGV->Is_Online_= atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("is_online"))->Value));
				new_AGV->Is_Serving_= atoi((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("is_serving"))->Value));
				new_AGV->AGV_Pos_.x= atof((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("pos_x"))->Value)); 
				new_AGV->AGV_Pos_.y= atof((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("pos_y"))->Value));  
				new_AGV->AGV_Pos_.theta= atof((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("pos_th"))->Value)); 
				new_AGV->AGV_In_Station_=(std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("at_station"))->Value);
				new_AGV->Battery_Level_ = atof((_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("battery_level"))->Value)); 
				
				agv_list.push_back(new_AGV);
				recordPtr_->MoveNext();
			}
		}
		else
		{
			return false;
		}
	}catch(_com_error &e)
	{
		std::stringstream ss;
		ss <<  "Download_AGV_Info " << e.ErrorMessage()<<","<< e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}

	return true;
}

bool ACS_Database::Update_Error_Info_Exist_Status(int ACS_ID,std::string STATUS)
{
	try
	{
		std::stringstream ss;

		ss<<"update agv_error_log set STATUS = '"<<STATUS<<"' where ID = '"<<ACS_ID<<"'";

		ACS_ADO_.ExecuteSQL((_bstr_t)ss.str().c_str());
		return true;

	}
	catch(_com_error &e)
	{
		std::stringstream ss;
		ss << "Update WCS Error Status " << e.ErrorMessage() << "," << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	    return false;
	}
}

bool ACS_Database::getCurrentChargingTask(AGV* agv, int& task_id)
{
	try
	{
		int row_count = 0;
		std::stringstream ss;
		ss << "select count(*) FROM active_task_list WHERE agv_id=" << agv->AGV_ID_ << " AND task_type='1040'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = ACS_ADO_.GetRecordSet(SQL);                               //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		if (row_count != 0)
		{
			std::stringstream ssTask;
			ssTask << "SELECT task_id FROM active_task_list WHERE agv_id=" << agv->AGV_ID_ << " AND task_type='1040'";
			_bstr_t SQL2 = ssTask.str().c_str();
			recordPtr_ = ACS_ADO_.GetRecordSet(SQL2);
			recordPtr_->MoveLast();
			task_id = (int)recordPtr_->GetCollect("task_id");
			return true;
		}
		return false;
	}
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << "getCurrentChargingTask " << e.ErrorMessage() << "," << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}
}

bool ACS_Database::getCurrentAGVIsOnline(int agv_id)
{
	try {
		int row_count = 0;
		std::stringstream ss;

		ss << "SELECT COUNT(*) FROM agv_data WHERE agv_id = '"<< agv_id <<"' AND is_online = '1' AND is_serving='1'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = ACS_ADO_.GetRecordSet(SQL);	                          //get the task(RecordSet) with the highest priority

		if (recordPtr_)
		{
			row_count = (int)recordPtr_->GetCollect("count(*)");
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
	catch (_com_error &e)
	{
		std::stringstream ss;
		ss << "getCurrentAGVIsOnline " << e.ErrorMessage() << "," << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
}