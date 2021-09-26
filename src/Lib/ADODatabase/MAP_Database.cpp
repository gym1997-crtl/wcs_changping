#include "MAP_Database.h"

#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "stdlib.h"
#include "ADODatabase/DatabaseManage.h"
#include "comm/simplelog.h"
#include <Windows.h>
#include "Manage/Config_Manage.h"

MAP_Database::MAP_Database()
{

}

MAP_Database::~MAP_Database()
{

}

void MAP_Database::setMapAdo(ADOcon ADO)
{
	WCS_ADO_ = ADO;
}

bool MAP_Database::getStationPos(std::string storage_name, Pos_Info *pos)
{
	bool result = false; 
	try
	{
		std::stringstream ss;
		ss << "SELECT COUNT(*) FROM station_info WHERE station_name = '" << storage_name << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = WCS_ADO_.GetRecordSet(SQL);
		if (recordPtr_)
		{
			if ((int)recordPtr_->GetCollect("COUNT(*)") != 0) {
				std::stringstream ss2;
				ss2 << "SELECT * FROM station_info WHERE station_name = '" << storage_name << "'";
				_bstr_t SQL2 = ss2.str().c_str();

				recordPtr2_ = WCS_ADO_.GetRecordSet(SQL2);
				recordPtr2_->MoveFirst();
				result = true;
				pos->x = atof((_bstr_t)(recordPtr2_->Fields->GetItem(_variant_t("pos_x"))->Value));
				pos->y = atof((_bstr_t)(recordPtr2_->Fields->GetItem(_variant_t("pos_y"))->Value));
			}
		}
	}
	catch (_com_error &e) {
		std::stringstream ss;
		ss << e.ErrorMessage() << "getStationPos" << e.Description();
		log_info_color(log_color::red, ss.str().c_str());
	}
	return result;
}