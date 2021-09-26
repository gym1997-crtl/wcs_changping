#include <tchar.h>
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <Windows.h>
#include <DbgHelp.h> 
#include <boost/serialization/singleton.hpp>
#include <boost/thread.hpp>
#include <boost/signals2/signal.hpp>
#include "MainWnd.h"
#include "ADODatabase/DatabaseManage.h"
#include "Common/Common.h"
#include "comm/Comm.h"
#include "comm/simplelog.h"


MainWindow* m_main = NULL;
void InitSystemLog(const QString& appPath)
{
	QString logsDir = appPath + "/logs/";
	QDir dir(logsDir);
	if (!dir.exists())
	{
		dir.mkpath(logsDir);
	}
	//init log
	QString strLogName = "WCS_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".log";
	QString logfile = logsDir + strLogName;
	init_log(logfile.toStdString().c_str(), 10);
}
int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
{
	// 定义函数指针
	typedef BOOL(WINAPI * MiniDumpWriteDumpT)(
		HANDLE,
		DWORD,
		HANDLE,
		MINIDUMP_TYPE,
		PMINIDUMP_EXCEPTION_INFORMATION,
		PMINIDUMP_USER_STREAM_INFORMATION,
		PMINIDUMP_CALLBACK_INFORMATION
		);
	// 从 "DbgHelp.dll" 库中获取 "MiniDumpWriteDump" 函数
	MiniDumpWriteDumpT pfnMiniDumpWriteDump = NULL;
	HMODULE hDbgHelp = LoadLibrary(_T("DbgHelp.dll"));
	if (NULL == hDbgHelp)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");

	if (NULL == pfnMiniDumpWriteDump)
	{
		FreeLibrary(hDbgHelp);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	// 创建 dmp 文件件
	TCHAR szFileName[MAX_PATH] = { 0 };
	TCHAR* szVersion = _T("WCS_Dump");
	SYSTEMTIME stLocalTime;
	GetLocalTime(&stLocalTime);
	wsprintf(szFileName, "%s-%04d%02d%02d-%02d%02d%02d.dmp",
		szVersion, stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);
	HANDLE hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
	if (INVALID_HANDLE_VALUE == hDumpFile)
	{
		FreeLibrary(hDbgHelp);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	// 写入 dmp 文件
	MINIDUMP_EXCEPTION_INFORMATION expParam;
	expParam.ThreadId = GetCurrentThreadId();
	expParam.ExceptionPointers = pExceptionPointers;
	expParam.ClientPointers = FALSE;
	pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
		hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &expParam : NULL), NULL, NULL);
	// 释放文件
	CloseHandle(hDumpFile);
	FreeLibrary(hDbgHelp);
	return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
	// 这里做一些异常的过滤或提示
	if (IsDebuggerPresent())
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}
	return GenerateMiniDump(lpExceptionInfo);
}

int main(int argc,char *argv[])  
{  	
	//加入崩溃dump文件功能
	SetUnhandledExceptionFilter(ExceptionFilter);

	QApplication a(argc,argv);

	InitSystemLog(a.applicationDirPath());

	QTranslator *translator = new QTranslator;
	bool flaggg = translator->load("wcs_sdjd_zh.qm");
	int language = 0;
	Config_File config_file;
	if (config_file.FileExist("config.txt"))
	{
		config_file.ReadFile("config.txt");
		if (config_file.KeyExists("LANGUAGE"))
		{
			std::stringstream second_agv(config_file.Read<std::string>("LANGUAGE"));
			second_agv >> language;
		}
	}
	if (language == 0) {
		std::cout << "config: do not load translator\n";
	}
	else {
		a.installTranslator(translator);
	}

	//MainWindow m;
	//m.show();
	m_main = new MainWindow();
	m_main->setTranslator(translator);
	std::string nm;
	nm = argv[0];
	nm = cComm::Get_FileName(nm);
	HANDLE hMutex = CreateMutex(NULL, FALSE, nm.c_str());
	if (GetLastError() == ERROR_ALREADY_EXISTS){ //如果已经存在同名的Mutex会得到这个错误.
		QMessageBox::about(NULL, "Error", "Already Open This App");
		CloseHandle(hMutex);
		return FALSE;
	}
	
	
	//将log输出到主窗口的print_info方法中。
	auto slot = boost::bind(&MainWindow::print_info, m_main, _1, _2);
	log_bind_sink(slot);
	m_main->show();
	//如果有命令行参数，从命令行自动加载工程

	return a.exec();  
}
