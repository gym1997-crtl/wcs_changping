//#include "stdafx.h"  
#include <stdio.h>

#include "iostream"
#include <sstream>
#include <fstream>

#include "ADODatabase/ADODatabase.h"
#include "Manage/Config_Manage.h"

ADOcon::ADOcon(void)
{
	_AGV_Management_DSN = "Local";
	_AGV_Managemnet_ServerIP = "127.0.0.1";
	_AGV_Managemnet_Database_Name = "task_managementdb";
	_AGV_Managemnet_User_Name = "root";
	_AGV_Managemnet_Password = "123456^";

	_WCS_DSN = "Local";
	_WCS_ServerIP = "127.0.0.1";
	_WCS_Database_Name = "wcs_cspg";
	_WCS_User_Name = "root";
	_WCS_Password = "123456^";

	_Oracle_DSN = "Oracle";
	_Oracle_ServerIP = "127.0.0.1";
	_Oracle_Database_Name = "test";
	_Oracle_User_Name = "root";
	_Oracle_Password = "123456^";


	if (Config_.FileExist("config.txt"))
	{
		Config_.ReadFile("config.txt");
		read_AMS_config();
		read_WCS_config();
		read_Oracle_cofig();
		readMapConfig();
	}

	Set_AMS_Connection_info(_AGV_Management_DSN, _AGV_Managemnet_ServerIP, _AGV_Managemnet_Database_Name, _AGV_Managemnet_User_Name, _AGV_Managemnet_Password);
	
	Set_WCS_Connection_Info(_WCS_DSN, _WCS_ServerIP, _WCS_Database_Name, _WCS_User_Name, _WCS_Password);

	Set_Oracle_Connection_Info(_Oracle_DSN, _Oracle_ServerIP, _Oracle_Database_Name, _Oracle_User_Name, _Oracle_Password);
}

ADOcon::~ADOcon(void)
{

}

void ADOcon::read_AMS_config()
{
	if (Config_.KeyExists("AGV_Management_DSN"))
	{
		_AGV_Management_DSN = Config_.Read<std::string>("AGV_Management_DSN");
		//std::cout<<"Read AMS DSN:"<<_AGV_Management_DSN<<std::endl;  
	}
	if (Config_.KeyExists("AGV_Managemnet_ServerIP"))
	{
		_AGV_Managemnet_ServerIP = Config_.Read<std::string>("AGV_Managemnet_ServerIP");
		//std::cout<<"Read AMS IP:"<<_AGV_Managemnet_ServerIP<<std::endl;  
	}
	if (Config_.KeyExists("AGV_Managemnet_Database_Name"))
	{
		_AGV_Managemnet_Database_Name = Config_.Read<std::string>("AGV_Managemnet_Database_Name");
		//std::cout<<"Read AMS Database Name:"<<_AGV_Managemnet_Database_Name<<std::endl;  
	}
	if (Config_.KeyExists("AGV_Managemnet_User_Name"))
	{
		_AGV_Managemnet_User_Name = Config_.Read<std::string>("AGV_Managemnet_User_Name");
		//std::cout<<"Read AMS User Name:"<<_AGV_Managemnet_User_Name<<std::endl;  
	}
	if (Config_.KeyExists("AGV_Managemnet_Password"))
	{
		_AGV_Managemnet_Password = Config_.Read<std::string>("AGV_Managemnet_Password");
		//std::cout<<"Read AMS Password:"<<_AGV_Managemnet_Password<<std::endl;  
	}
}

void ADOcon::read_WCS_config()
{
	if (Config_.KeyExists("WCS_DSN"))
	{
		_WCS_DSN = Config_.Read<std::string>("WCS_DSN");
		//std::cout<<"Read WCS DSN:"<<_WCS_DSN<<std::endl;  
	}
	if (Config_.KeyExists("WCS_ServerIP"))
	{
		_WCS_ServerIP = Config_.Read<std::string>("WCS_ServerIP");
		//std::cout<<"Read WCS IP:"<<_WCS_ServerIP<<std::endl;  
	}
	if (Config_.KeyExists("WCS_Database_Name"))
	{
		_WCS_Database_Name = Config_.Read<std::string>("WCS_Database_Name");
		//std::cout<<"Read WCS Database Name:"<<_WCS_Database_Name<<std::endl;  
	}
	if (Config_.KeyExists("WCS_User_Name"))
	{
		_WCS_User_Name = Config_.Read<std::string>("WCS_User_Name");
		//std::cout<<"Read WCS User Name:"<<_WCS_User_Name<<std::endl;  
	}
	if (Config_.KeyExists("WCS_Password"))
	{
		_WCS_Password = Config_.Read<std::string>("WCS_Password");
		//std::cout<<"Read WCS Password:"<<_WCS_Password<<std::endl;  
	}
}

void ADOcon::readMapConfig()
{
	CONFIG_MANAGE.readConfig("MAP_DSN", &_Map_DSN);
	CONFIG_MANAGE.readConfig("MAP_ServerIP", &_Map_ServerIP);
	CONFIG_MANAGE.readConfig("MAP_Database_Name", &_Map_Database_Name);
	CONFIG_MANAGE.readConfig("MAP_User_Name", &_Map_User_Name);
	CONFIG_MANAGE.readConfig("MAP_Password", &_Map_Password);
}


void ADOcon::read_Oracle_cofig()
{
	if (Config_.KeyExists("Oracle_DSN"))
	{
		_Oracle_DSN = Config_.Read<std::string>("Oracle_DSN");
		//std::cout<<"Read WMS DSN:"<<_WMS_DSN<<std::endl;  
	}
	if (Config_.KeyExists("Oracle_ServerIP"))
	{
		_Oracle_ServerIP = Config_.Read<std::string>("Oracle_ServerIP");
		//std::cout<<"Read WMS IP:"<<_WMS_ServerIP<<std::endl;  
	}
	if (Config_.KeyExists("Oracle_Database_Name"))
	{
		_Oracle_Database_Name = Config_.Read<std::string>("Oracle_Database_Name");
		//std::cout<<"Read WMS Database Name:"<<_WMS_Database_Name<<std::endl;  
	}
	if (Config_.KeyExists("Oracle_User_Name"))
	{
		_Oracle_User_Name = Config_.Read<std::string>("Oracle_User_Name");
		//std::cout<<"Read WMS User Name:"<<_WMS_User_Name<<std::endl;  
	}
	if (Config_.KeyExists("Oracle_Password"))
	{
		_Oracle_Password = Config_.Read<std::string>("Oracle_Password");
		//std::cout<<"Read WMS Password:"<<_WMS_Password<<std::endl;  
	}
}

bool  ADOcon::OnInitADOConn(ADO_Database Database_Type)
{
	//  
	Current_Con_ = Database_Type;
	::CoInitialize(NULL);

	std::stringstream AGV_Managemnet_Connection_Info;
	std::stringstream WMS_Connection_Info;
	std::stringstream WCS_Connection_Info;

	std::stringstream Oracle_Connection_Info;
	std::stringstream Map_Connection_Info;

	std::stringstream PROJECT_Connection_Info;


	AGV_Managemnet_Connection_Info << "DSN=" << _AGV_Management_DSN << ";Server=" << _AGV_Managemnet_ServerIP << ";Database=" << _AGV_Managemnet_Database_Name;
	WCS_Connection_Info << "DSN=" << _WCS_DSN << ";Server=" << _WCS_ServerIP << ";Database=" << _WCS_Database_Name;
	Oracle_Connection_Info << "DSN=" << _Oracle_DSN << ";Server=" << _Oracle_ServerIP << ";Database=" << _Oracle_Database_Name;
	Map_Connection_Info << "DSN=" << _Map_DSN << ";Server=" << _Map_ServerIP << ";Database=" << _Map_Database_Name;
	HRESULT hr;

	try
	{
		//  
		hr = m_pConnection.CreateInstance("ADODB.Connection");
		HRESULT connection_result = false;
		if (SUCCEEDED(hr))
		{

			m_pConnection->ConnectionTimeout = 600;// 
			m_pConnection->CommandTimeout = 120;// 

			if (Database_Type == ADO_Database::ACS_DB)
			{
				connection_result = m_pConnection->Open((_bstr_t)AGV_Managemnet_Connection_Info.str().c_str(), (_bstr_t)_AGV_Managemnet_User_Name.c_str(), (_bstr_t)_AGV_Managemnet_Password.c_str(), adModeUnknown);

			}
			else if (Database_Type == ADO_Database::WCS_DB)
			{
				connection_result = m_pConnection->Open((_bstr_t)WCS_Connection_Info.str().c_str(), (_bstr_t)_WCS_User_Name.c_str(), (_bstr_t)_WCS_Password.c_str(), adModeUnknown);
			}

			else if (Database_Type == ADO_Database::Oracle_DB)
			{
				connection_result = m_pConnection->Open((_bstr_t)Oracle_Connection_Info.str().c_str(), (_bstr_t)_Oracle_User_Name.c_str(), (_bstr_t)_Oracle_Password.c_str(), adModeUnknown);
			}
			else if (Database_Type == ADO_Database::Map_DB)
			{
				connection_result = m_pConnection->Open((_bstr_t)Map_Connection_Info.str().c_str(), (_bstr_t)_Map_User_Name.c_str(), (_bstr_t)_Map_Password.c_str(), adModeUnknown);
			}
			else {
				std::cout << "wrong Database ID!" << std::endl;
				return false;
			}

			if (SUCCEEDED(connection_result))
			{
				//std::cout<<"Connected!"<<std::endl;
				return true;
			}
			else {
				std::cout << "Fail to connect!" << std::endl;
				return false;
			}

		}
	}
	catch (_com_error e)
	{
		std::cout << "Connect Error:" << e.Description() << std::endl;
		return false;
	}
}

_RecordsetPtr& ADOcon::GetRecordSet(_bstr_t bstrSQL, int type)
{
	try
	{
		//   
		if (m_pConnection == NULL)
			OnInitADOConn(Current_Con_);
		//   
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		// 
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	// 
	catch (_com_error e)
	{
		std::cout << "GetRecordSet Error:" << e.ErrorMessage() << e.Description() << std::endl;

		std::stringstream Error_description;
		std::string Error_message = "Unknown error 0x800A0E7D";
		//Error_info << (std::string)e.Description();
		Error_description << "[Oracle][ODBC][Ora]ORA-03114: not connected to ORACLE" << std::endl;

		if ((std::string)e.Description() == Error_description.str() || (std::string)e.ErrorMessage() == Error_message)
		{
			OnInitADOConn(ADO_Database::Oracle_DB);
		}
	}
	//   
	return m_pRecordset;
}

_RecordsetPtr& ADOcon::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		//   
		if (m_pConnection == NULL)
			OnInitADOConn(Current_Con_);
		//   
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		// 
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	// 
	catch (_com_error e)
	{
		std::cout << "GetRecordSet Error:" << e.ErrorMessage() << e.Description() << std::endl;
	}
	//   
	return m_pRecordset;
}

BOOL ADOcon::ExecuteSQL(_bstr_t bstrSQL)
{
	// _variant_t RecordsAffected;  
	try
	{
		if (m_pConnection == NULL)
			OnInitADOConn(Current_Con_);

		m_pConnection->Execute(bstrSQL, NULL, adCmdText);

		return true;
	}
	catch (_com_error e)
	{
		std::cout << "ExecuteSQL Error:" << e.Description() << std::endl;
		return false;
	}
}

void ADOcon::ExitConnect()
{
	// 
	if (m_pRecordset != NULL)
	{
		m_pRecordset->Close();
		//m_pRecordset->Release();  
	}
	m_pConnection->Close();
	//m_pConnection->Release();  
	//   
	::CoUninitialize();
}

void ADOcon::Set_AMS_Connection_info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password)
{
	_AGV_Management_DSN = DSN;
	_AGV_Managemnet_ServerIP = ServerIP;
	_AGV_Managemnet_Database_Name = Database_Name;

	_AGV_Managemnet_User_Name = User_Name;
	_AGV_Managemnet_Password = Password;


}

void ADOcon::Set_WCS_Connection_Info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password)
{
	_WCS_DSN = DSN;
	_WCS_ServerIP = ServerIP;
	_WCS_Database_Name = Database_Name;

	_WCS_User_Name = User_Name;
	_WCS_Password = Password;

}


void ADOcon::Set_Oracle_Connection_Info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password)
{
	_Oracle_DSN = DSN;
	_Oracle_ServerIP = ServerIP;
	_Oracle_Database_Name = Database_Name;

	_Oracle_User_Name = User_Name;
	_Oracle_Password = Password;

}


