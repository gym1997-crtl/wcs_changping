#include <Mode_Manage.h>
/**
 * 任务管理类
 */
Mode_Manage::Mode_Manage()
{
}

Mode_Manage::~Mode_Manage()
{
}

/**
 * 初始化：加载数据库，获取任务列表
 */
void Mode_Manage::Initial()
{
	wcs_db_ = DATABASE_MANAGE.Get_WCS_DB();
	wcs_db_->loadListFromDB(taskNameList, tableName, listName);
}

/**
 * 获取所有任务名
 */
std::vector<std::string>  Mode_Manage::getAllTaskName() {
	return taskNameList;
}
