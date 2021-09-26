//#include "comm/Comm.h"
#include "comm/Log.h"
#include <assert.h>

//map<string,cLog*> cLog::log_p_map;
map<string,cLog*>  cLog::name_log_map;

cLog::cLog()
:m_bEnabled(false),m_print_(true)
{
}

cLog::~cLog()
{
}

bool cLog::Open(string sFileName)
{
	m_tOLogFile.open(sFileName.c_str(), ios_base::out | ios_base::app);

	if( !m_tOLogFile )
		{
			return false;
		}

		return true;
}

void cLog::Close()
{
	if(m_tOLogFile.is_open())
		{
			m_tOLogFile.close();
		}
	
}

bool cLog::Close( string str_name )
{
	mlog::iterator cit = name_log_map.find(str_name);
	if (cit != name_log_map.end())
	{
		cit->second->Close();
		delete cit->second;
		name_log_map.erase(cit);
		return true;
	}
	else
	{
		return false;
	}
}

bool cLog::NewWithTime(string str)
{
	log_name_ = str;

	time_t tNowTime;
	time(&tNowTime);

	tm* tLocalTime = localtime(&tNowTime);

	string sDateStr = ValueToStr(tLocalTime->tm_year+1900) + "-" +
		ValueToStr(tLocalTime->tm_mon+1) + "-" +
		ValueToStr(tLocalTime->tm_mday) + "-" +
		ValueToStr(tLocalTime->tm_hour) + 
		ValueToStr(tLocalTime->tm_min)  +
		ValueToStr(tLocalTime->tm_sec);
	std::string path ;
	//path = cComm::GetRunPath();
	path += "./Log/" + str + "_" + sDateStr + ".log";
	//std::cout<<path<<std::endl;
	return Open(path);
}

void cLog::Enable()
{
	m_bEnabled = true;
}
void cLog::Print(bool b){
	m_print_ = b;
}
void cLog::Disable()
{
	m_bEnabled = false;
}


string cLog::GetTimeStr()
{
	time_t tNowTime;
	time(&tNowTime);

	tm* tLocalTime = localtime(&tNowTime);


	string strDateTime = ValueToStr(tLocalTime->tm_year+1900) + "-" +
		ValueToStr(tLocalTime->tm_mon+1)     + "-" +
		ValueToStr(tLocalTime->tm_mday)      + " " +
		ValueToStr(tLocalTime->tm_hour)      + ":" +
		ValueToStr(tLocalTime->tm_min)       + ":" +
		ValueToStr(tLocalTime->tm_sec)       + " ";
	return strDateTime;
}

cLog* cLog::GetInstance( string str_name )
{
	mlog::const_iterator cit = name_log_map.find(str_name);
	if (cit == name_log_map.end())
	{
	
		typedef mlog::value_type vtype;
		cLog* plog = new cLog();
		plog->NewWithTime(str_name);
		name_log_map.insert(vtype(str_name,plog));
		return plog;
	}
	else
	{
		return cit->second;
	}
}

