#include "Config_Manage.h"

bool Config_Manage::readConfig(std::string key, std::string *value, std::string filename /*= "config.txt"*/) {
	bool result = false;

	if (all_config_files.find(filename) == all_config_files.end())
	{
		// 没有读过该文件
		Config_File config;
		if (config.FileExist(filename))
		{
			config.ReadFile(filename);
			all_config_files[filename] = config;
		}
		else
		{
			// 不存在该文件
		}
	}

	if (all_config_files[filename].KeyExists(key))
	{
		result = true;
		*value = all_config_files[filename].Read<std::string>(key);
	}
	else
	{
		// 不存在该配置
	}
	return result;
}