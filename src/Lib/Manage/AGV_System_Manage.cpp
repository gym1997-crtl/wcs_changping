#include<windows.h> 
#include<string>
#include <boost/thread.hpp>
#include "ADODatabase/DatabaseManage.h"
#include "Manage/AGV_System_Manage.h"


AgvSystemManage::AgvSystemManage()
{
	ACS_CON_ = DATABASE_MANAGE.Get_ACS_DB();
	WCS_CON_ = DATABASE_MANAGE.Get_WCS_DB();
	
}

AgvSystemManage::~AgvSystemManage()
{

}
