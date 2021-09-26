#ifndef AGV_SYSTEM_MANAGE_WHX_
#define AGV_SYSTEM_MANAGE_WHX_

#include <string>  
#include <map> 
#include <vector>
#include <iostream>  
#include <vector>
#include <boost/serialization/singleton.hpp>
#include "ADODatabase.h"
class AgvSystemManage
{

public:

	AgvSystemManage();

	~AgvSystemManage();

public:


private:

	WCS_Database* WCS_CON_;
	ACS_Database* ACS_CON_;

};

typedef boost::serialization::singleton<AgvSystemManage> SingletonAgvSystemManage;
#define AGV_SYSTEM_MANAGE SingletonAgvSystemManage::get_mutable_instance()

#endif
