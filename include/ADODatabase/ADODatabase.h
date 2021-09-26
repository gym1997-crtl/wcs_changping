#ifndef ADOBO_H_  
#define ADOBO_H_


#import "c:\Program Files (x86)\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF") rename("BOF","adoBOF")
#include<string>
#include "Common/Config.h"

typedef enum {
	ACS_DB = 1,
	WCS_DB = 2,
	Oracle_DB = 3,
	Map_DB
}ADO_Database;

class ADOcon
{

public:
	ADOcon(void);
	~ADOcon(void);

public:
	//Add a pointer to Connection:
	_ConnectionPtr m_pConnection;
	//add an pointer to Recordset:
	_RecordsetPtr m_pRecordset;
public:
	// initial connection
	bool OnInitADOConn(ADO_Database Database_Type);
	// "get record" query
	_RecordsetPtr& ADOcon::GetRecordSet(_bstr_t bstrSQL, int type);
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	// "execute" query
	BOOL ExecuteSQL(_bstr_t bstrSQL);
	void ExitConnect();

	void Set_AMS_Connection_info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password);

	void Set_WCS_Connection_Info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password);

	void Set_Oracle_Connection_Info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password);

private:

	void read_AMS_config();

	void read_WCS_config();

	void readMapConfig();

	void read_Oracle_cofig();

	std::string _AGV_Management_DSN;
	std::string _AGV_Managemnet_ServerIP;
	std::string _AGV_Managemnet_Database_Name;
	std::string _AGV_Managemnet_User_Name;
	std::string _AGV_Managemnet_Password;

	std::string _WCS_DSN;
	std::string _WCS_ServerIP;
	std::string _WCS_Database_Name;
	std::string _WCS_User_Name;
	std::string _WCS_Password;


	std::string _Oracle_DSN;
	std::string _Oracle_ServerIP;
	std::string _Oracle_Database_Name;
	std::string _Oracle_User_Name;
	std::string _Oracle_Password;

	std::string _Map_DSN;
	std::string _Map_ServerIP;
	std::string _Map_Database_Name;
	std::string _Map_User_Name;
	std::string _Map_Password;

	Config_File Config_;

	ADO_Database Current_Con_;
};

#endif  