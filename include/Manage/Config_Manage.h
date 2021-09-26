#ifndef CONFIG_MANAGE_H_
#define CONFIG_MANAGE_H_
#include <string>
#include <map>

#include <boost/serialization/singleton.hpp>
#include "Common/Config.h"

class Config_Manage
{
public:
	Config_Manage::Config_Manage() {};
	Config_Manage::~Config_Manage() {};
	bool readConfig(std::string key, std::string *value, std::string filename = "config.txt");
	inline bool readConfig(std::string key, int *value, std::string filename = "config.txt") {
		std::string tmp;
		if (readConfig(key, &tmp, filename))
		{
			*value = std::atoi(tmp.c_str());
			return true;
		}
		return false;
	};
	inline bool readConfig(std::string key, double *value, std::string filename = "config.txt") {
		std::string tmp;
		if (readConfig(key, &tmp, filename))
		{
			*value = std::atof(tmp.c_str());
			return true;
		}
		return false;
	};
private:
	std::map<std::string, Config_File> all_config_files;
};

typedef boost::serialization::singleton<Config_Manage> Singleton_Config_Manage;
#define CONFIG_MANAGE Singleton_Config_Manage::get_mutable_instance()

#endif // #ifndef API_CLIENT_H_