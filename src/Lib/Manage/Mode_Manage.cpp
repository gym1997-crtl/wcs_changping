#include <Mode_Manage.h>
/**
 * ���������
 */
Mode_Manage::Mode_Manage()
{
}

Mode_Manage::~Mode_Manage()
{
}

/**
 * ��ʼ�����������ݿ⣬��ȡ�����б�
 */
void Mode_Manage::Initial()
{
	wcs_db_ = DATABASE_MANAGE.Get_WCS_DB();
	wcs_db_->loadListFromDB(taskNameList, tableName, listName);
}

/**
 * ��ȡ����������
 */
std::vector<std::string>  Mode_Manage::getAllTaskName() {
	return taskNameList;
}
