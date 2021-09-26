#include "Config_Manage.h"

bool Config_Manage::readConfig(std::string key, std::string *value, std::string filename /*= "config.txt"*/) {
	bool result = false;

	if (all_config_files.find(filename) == all_config_files.end())
	{
		// û�ж������ļ�
		Config_File config;
		if (config.FileExist(filename))
		{
			config.ReadFile(filename);
			all_config_files[filename] = config;
		}
		else
		{
			// �����ڸ��ļ�
		}
	}

	if (all_config_files[filename].KeyExists(key))
	{
		result = true;
		*value = all_config_files[filename].Read<std::string>(key);
	}
	else
	{
		// �����ڸ�����
	}
	return result;
}