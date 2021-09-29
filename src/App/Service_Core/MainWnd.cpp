#define WIN32_LEAN_AND_MEAN 

#define TIMESPE 3
#include "iostream"
#include "math.h"
#include <vector>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include "boost/bind.hpp"

#include <QFileDialog>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QInputDialog>
#include <QTextCodec>

#include "comm/Comm.h"
#include "comm/TimerDiff.h"
#include "comm/simplelog.h"
#include "transferdevice/TransferDevice.h"
#include "ADODatabase/DatabaseManage.h"
#include "ADODatabase/RabbitMQService.h"

#include "MainWnd.h"
#include "Core/Event_Handler.h"

#include "Manage/AGV_System_Manage.h"
#include "Manage/Storage_Manage.h"
#include "Manage/PLC_Manage.h"
//#include "StorageManage.h"
#include <QComboBox>
#include <QPushButton>
#include <QDockWidget>
#include <QScrollArea>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QApplication>
//#include "StorageManage.h"
#include "Mode_Manage.h"
#include "Parking_Manage.h"
#include "Core/ModelStationParking.h"
#include "Core/ModelStationConfirm.h"
#include "Core/ModelEquipment.h"
#include "Core/ModelBridge.h"
#include "SendOrderConfirmLabel.h"
#include "SendOrderLabelWidget.h"
#include "SendOrderParkingLabel.h"
#include "SendOrderEquipmentLabel.h"
#include "MyLabel.h"
#include "ADODatabase/ApiClient.h"
#include "ADODatabase/ApiServer.h"
//#include "ApiServer.h"

MainWindow::MainWindow() 
{
	current_Seleted_Mylabel_ = NULL;
	qRegisterMetaType<std::string>("std::string");
	setAttribute(Qt::WA_DeleteOnClose);
	setting_Config_ = new QSettings("config.txt", QSettings::IniFormat);
	language_ = 0;
	getAGVConfig();
	current_label_widget_ = NULL;
	log_lines_ = 0;
	connect(this, SIGNAL(signal_print_log(const QString&)), this, SLOT(slot_print_log(const QString&)));
	/*关于release的发布之后需要屏蔽的部分测试代码;*/
	number_count_ = 1;//关于模仿DOD生成任务的wcs_id的初始化;
	//QWidget *dock_AA = new QWidget;
	//QVBoxLayout *dock_layout = new QVBoxLayout;
	//dock_layout->setMargin(0);
	//dock_layout->setSpacing(0);

	linde_storage_name_ = new QLabel;
	QLabel *storage_namem_label_ = new QLabel("Storage_Name :");
	QLabel *Name1 = new QLabel("START:");
	QLabel *Name2 = new QLabel("Target:");
	Start_Storgae_Name_ = new QLabel;
	Target_Storgae_Name_ = new QLabel;
	
	combobox_start = new QComboBox;
	combobox_target = new QComboBox;
	combobox_mode_ = new QComboBox;

	call_pushb_ = new QPushButton("Create Order");
	call_pushb_->setStyleSheet("color: red");
	call_pushb_->setEnabled(false);
	revoke_pushb_ = new QPushButton;
	change_pushb_ = new QPushButton;

	linde_storage_name_->setAlignment(Qt::AlignCenter);
	Start_Storgae_Name_->setAlignment(Qt::AlignCenter);
	Target_Storgae_Name_->setAlignment(Qt::AlignCenter); 


	connect(call_pushb_,SIGNAL(clicked(bool)),this,SLOT(createOrder(bool))); 

	fun_dock_ = new QDockWidget(this);
	fun_dock_->setFixedWidth(200);
	fun_dock_->setAllowedAreas( Qt::RightDockWidgetArea);
	/*关于release的发布之后需要屏蔽的部分测试代码;*/

	this->setMinimumWidth(1420);
	this->setMinimumHeight(800);

	QMainWindow *mainwindow_dock2 = new QMainWindow;//存在于dock2中的窗口

	Log_Browser_ = new QTextBrowser;//存在于dock2中的窗口

	Order_Monitor_ = new Order_Monitor(this);
	AGV_Monitor_ = new AGV_Monitor(this);
	Task_Monitor_ = new Task_Monitor(this);
	DOD_Monitor_ = new DOD_Monitor(this);
	//Station_Monitor_ = new Station_Monitor(this);
	Station_Monitor_NEW_ = new Station_Monitor_NEW(this);

	QScrollArea *Storage_ScrollArea = new QScrollArea;
	Storage_ScrollArea->setWidget(Station_Monitor_NEW_);
	Storage_ScrollArea->setWidgetResizable(true);
	Storage_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	Storage_ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	

	right_exit_=new QPushButton(tr("YES"));
	error_exit_=new QPushButton(tr("NO"));
	
	QGridLayout *layout = new QGridLayout;
	
	layout->addWidget(right_exit_,2,0,1,1,Qt::AlignHCenter | Qt::AlignRight);
	layout->addWidget(error_exit_,2,1,1,1,Qt::AlignHCenter | Qt::AlignRight);

	Open_Selection_=new QDialog(this);
	Open_Selection_->setLayout(layout);
	Open_Selection_->setWindowTitle("Message");


	AGV_dock = new QDockWidget(tr(" AGV Monitor"), mainwindow_dock2);
	AGV_dock->setWidget(AGV_Monitor_);

	Order_dock = new QDockWidget(tr(" Order Monitor"), mainwindow_dock2);
	Order_dock->setWidget(Order_Monitor_);

	Task_dock = new QDockWidget(tr("Task Monitor"), mainwindow_dock2);
	Task_dock->setWidget(Task_Monitor_);
	
	DOD_dock = new QDockWidget(tr("DOD Monitor"), mainwindow_dock2);
	DOD_dock->setWidget(DOD_Monitor_);

	station_dock = new QDockWidget(tr(" Station Status "), this);
	station_dock->setWidget(Storage_ScrollArea);

	/*dock1 包含关于库位可视化的界面station_monitor_;
	  dock2 包含agv_monitor、order_monitor、dod_monitor、task_monitor*/

	Log_Browser_ = new QTextBrowser();

	dock_widget1 = new QDockWidget(tr("Monitor Info"));
	dock_widget1->setWidget(mainwindow_dock2);

	dock_console = new QDockWidget(tr("Console Info"));
	//dock_console->setWidget(mainwindow_dock3);
	dock_console->setWidget(Log_Browser_);
	//QDockWidget *dock_widget2 = new QDockWidget;
	//dock_widget2->setWidget(mainwindow_dock2);

	mainwindow_dock2->addDockWidget(Qt::RightDockWidgetArea,Task_dock);
	mainwindow_dock2->addDockWidget(Qt::LeftDockWidgetArea,Order_dock);
	mainwindow_dock2->addDockWidget(Qt::LeftDockWidgetArea,AGV_dock);
	mainwindow_dock2->addDockWidget(Qt::RightDockWidgetArea,DOD_dock);

	addDockWidget(Qt::LeftDockWidgetArea,dock_widget1);
	addDockWidget(Qt::LeftDockWidgetArea, dock_console);
	addDockWidget(Qt::RightDockWidgetArea,station_dock);
	addDockWidget(Qt::RightDockWidgetArea,fun_dock_);

	dock_widget1->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dock_console->setFeatures(QDockWidget::NoDockWidgetFeatures);
	station_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	fun_dock_->setFeatures(QDockWidget::NoDockWidgetFeatures);
	splitDockWidget(station_dock,fun_dock_,Qt::Horizontal);
	//fun_dock_->hide();
	
	mainwindow_dock2->splitDockWidget(AGV_dock,DOD_dock,Qt::Vertical);
	mainwindow_dock2->tabifyDockWidget(Order_dock,Task_dock);
	mainwindow_dock2->tabifyDockWidget(Task_dock,DOD_dock);
	
	AGV_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	Task_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	DOD_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

	this->tabifyDockWidget(station_dock,dock_widget1);
	this->tabifyDockWidget(dock_widget1,dock_console);

	station_dock->raise();
	Order_dock->raise();
	//AGV_dock->raise();

	CreateActions();
	CreateMenu();
	CreateStatusBar();
	createChangeStorageStatusDialog();

	timerId_ = 0;
	//times = 0;
	Selected_Label_ = "";
	//connect(this, SIGNAL(signal_change_lable_status(MyLabel *label, std::string status)), this, SLOT(slot_change_lable_status(MyLabel *label, std::string status)));
	connect(this, SIGNAL(signal_change_mylabel_status(MyLabel*, std::string, std::string, bool, bool)), this, SLOT(slot_change_mylabel_status(MyLabel*, std::string, std::string, bool, bool)));
	
	STORAGE_MANAGE.setStorageStatusNotifier(this);
	Parking_Manage::Instance()->setStationStatusNotifier(this);
	STORAGE_MANAGE.Set_MainWindow_Delegate(this);
	
	//accessManager = new QNetworkAccessManager(this);
	//connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_reply_finished(QNetworkReply*)));
	
	RABBITMQ_SERVICE.setRabbitMQServiceNotifier(this);
	connect(this, SIGNAL(signal_rabbitmq_insert_order(std::string , int , int , std::string , std::string )), this, SLOT(slot_rabbitmq_insert_order(std::string , int , int , std::string , std::string )));
	
	translatorUI();

}

MainWindow::~MainWindow(){
	//StorageManage::Instance()->stopStorageCheck();
}

void MainWindow::CreateMenu()
{
	StartMenu = menuBar()->addMenu(tr("&Start"));
	StartMenu->addAction(start_run_);


	Setting_Menu_ = menuBar()->addMenu(tr("Setting"));
	Setting_Menu_->addAction(Language_Action_);
	Setting_Menu_->addAction(Skin_Action_);
	//Setting_Menu_->addAction(Server_IP_Action_);
	//Setting_Menu_->addAction(Recon_PLC_Action_);
}

void MainWindow::CreateActions()
{
	start_run_ = new QAction(QIcon("images/import.png"),
		tr("Start &Run"), this);
	start_run_->setShortcut(tr("Ctrl+R"));
	start_run_->setStatusTip(tr("Start Run Core"));
	connect(start_run_, SIGNAL(triggered()),
		this, SLOT(start_system()));

	Language_Action_ = new QAction(tr("Change Language"),this);
	Language_Action_->setStatusTip(tr("Change Language"));
	connect(Language_Action_, SIGNAL(triggered()), this, SLOT(changeLanguage()));

	Skin_Action_ = new QAction(tr("Change Skin"), this);
	Skin_Action_->setStatusTip(tr("Change Skin"));
	connect(Skin_Action_, SIGNAL(triggered()), this, SLOT(changeLanguage()));

	Server_IP_Action_ = new QAction(tr("Change Server IP"), this);
	Server_IP_Action_->setStatusTip(tr("Change Server IP"));
	connect(Server_IP_Action_, SIGNAL(triggered()), this, SLOT(changeServerIP()));

	Recon_PLC_Action_ = new QAction(tr("Reconnect PLC"), this);
	Recon_PLC_Action_->setStatusTip(tr("Reconnect PLC"));
	connect(Recon_PLC_Action_, SIGNAL(triggered()), this, SLOT(ReconnectPLC()));
}

void MainWindow::select_close_status()
{
	Open_Selection_->show();
}

void MainWindow::CreateStatusBar()
{
	msgLabel = new QLabel; 
	msgLabel->setObjectName("WhiteFont");
	msgLabel->setMinimumSize(msgLabel->sizeHint()); 
	msgLabel->setAlignment(Qt::AlignHCenter); 
	msgLabel->setFixedWidth(400);
	statusBar()->addWidget(msgLabel);

	system_status=new QLabel;
	system_status->setMinimumSize(system_status->sizeHint()); 
	system_status->setAlignment(Qt::AlignHCenter); 
	system_status->setFixedWidth(400);
	statusBar()->addWidget(system_status);
	QPalette status_palette;
	status_palette.setColor(QPalette::WindowText,Qt::red);
	system_status->setPalette(status_palette);
	system_status->setText(tr("Stopped"));
}

void MainWindow::right_exit()
{
	EVENT_HANDLER.Initial();
	Is_Open_Data_Transfer_ = true;

	startTimer(1000/10);
	Open_Selection_->hide();
}

void MainWindow::error_exit()
{
	Is_Open_Data_Transfer_=true;
	start_run();
	Open_Selection_->hide();
}

void MainWindow::start_run()
{
	// 开启监听端口
	//API_SERVER.Initial();
	EVENT_HANDLER.Initial();
	//if (PLC_MANAGE.Initial() == false)
	//{
	//	// 弹窗提示PLC连接失败
	//	QMessageBox msgBox;
	//	msgBox.setText(tr("PLC Connect Failed!"));
	//	msgBox.setStandardButtons(QMessageBox::Ok);
	//	msgBox.exec();
	//}
	
	//Station_Monitor_->iniData();
	initialParkingStatus();

	/* 初始化库位界面 */
	// Station_Monitor_NEW_->initDate();
	/* 福沙定制 ，获取下拉框用于展示界面 by meixu */
	combo = Station_Monitor_NEW_->initDate(false);
	/* 加载“SendOrder”界面*/
	loadSendOrderInterface();
	
	std::map<std::string, std::map<std::string, MyLabel*>> tableList = Station_Monitor_NEW_->getMylabelList();
	for each (auto var in tableList)
	{
		storageLabelList.insert(var.second.begin(), var.second.end());
	}
	connectMylabelSlots();
	/* 弹窗提示 系统启动 */
	if (!timerId_)
	{
		API_SERVER.Initial();
		//RABBITMQ_SERVICE.Init();
		//XML_Database::Instance()->Initial();
		timerId_ = startTimer(1000 / TIMESPE);
		QString string_start_ = tr("System Start!");
		QMessageBox::information(this, tr("Info"), string_start_);
		QPalette status_palette;
		status_palette.setColor(QPalette::WindowText, Qt::green);
		system_status->setPalette(status_palette);
		system_status->setText(tr("Running"));
	}
	else
	{
		//PLC_MANAGE.StopScan();
		//RABBITMQ_SERVICE.StopScan();
		//XML_Database::Instance()->SaveData();
		killTimer(timerId_);
		timerId_ = 0;
		QString string_stop_ = tr("System Stopped!");
		QMessageBox::information(this, tr("Info"), string_stop_);
		QPalette status_palette;
		status_palette.setColor(QPalette::WindowText, Qt::red);
		system_status->setPalette(status_palette);
		system_status->setText(tr("Stopped"));
	}
}

void MainWindow::changeLanguage()
{
	if (language_ == 0) {
		setting_Config_->setValue("LANGUAGE", "1");
		APP_->installTranslator(translator_);
		language_ = 1;
	}
	else if (language_ == 1) {
		setting_Config_->setValue("LANGUAGE", "0");
		language_ = 0;
		APP_->removeTranslator(translator_);
	}
}

void MainWindow::changeServerIP()
{
	bool bOk = false;
	// 当前 ip
	QString ip = API_CLIENT.get_server_ip();

	QInputDialog *getip = new QInputDialog(this);
	getip->setOkButtonText(tr("OK"));
	ip = getip->getText(this, tr("Set IP"), tr("Input Server IP:"), QLineEdit::Normal, ip, &bOk);
	QHostAddress _Address;//借助QHostAddress判断输入的内容的格式是不是IP
	bool _isAddr = _Address.setAddress(ip.trimmed()); //timmed是去掉空格

	if (bOk && _isAddr)
	{
		API_CLIENT.set_server_ip(ip);
	}
	else if (bOk)
	{
		QMessageBox::information(this, tr("Info"), tr("Not legal IP"));
	}
}

void MainWindow::ReconnectPLC()
{
	//if (PLC_MANAGE.TestCononect() == false)
	//{
	//	// 弹窗提示PLC连接失败
	//	QMessageBox msgBox;
	//	msgBox.setText(tr("PLC Connect Failed!"));
	//	msgBox.setStandardButtons(QMessageBox::Ok);
	//	msgBox.exec();
	//}
	//else
	//{
	//	// 弹窗提示PLC连接成功
	//	QMessageBox msgBox;
	//	msgBox.setText(tr("Reconnect Success!"));
	//	msgBox.setStandardButtons(QMessageBox::Ok);
	//	msgBox.exec();
	//}
}

void MainWindow::start_system()
{
	ADOcon* default_ACS_Con = new ADOcon();
	ADOcon* default_WCS_Con = new ADOcon();
	ADOcon* default_MAP_Con = new ADOcon();

	default_ACS_Con->OnInitADOConn(ADO_Database::ACS_DB);
	default_WCS_Con->OnInitADOConn(ADO_Database::WCS_DB);
	default_MAP_Con->OnInitADOConn(ADO_Database::Map_DB);

	DATABASE_MANAGE.set_ACS_ADO(default_ACS_Con);
	DATABASE_MANAGE.setWcsAdo(default_WCS_Con);
	DATABASE_MANAGE.setMapADO(default_MAP_Con);
	call_pushb_->setEnabled(true);
	//StartMenu->setEnabled(false);
	start_run();
}

void MainWindow::timerEvent( QTimerEvent *event )
{
	//轮询 - 初始化停车点与确认点信息
	//Parking_Manage::Instance()->checkStationStatus();
	cTimerDiff dt;
	F64 Event_Time=0;

	AGV_MANAGE.nearestFreeAgv("F9WC-1-2-P");
	//API_CLIENT.EquipmentStatusChangeNotification();

	/*dt.Begin();
	PLC_MANAGE.DatabaseIO();
	Event_Time = dt.GetTime() / 1e3;
	if (Event_Time > 1500)
	{
		std::cout << "PLC_MANAGE.DatabaseIO(): " << Event_Time << std::endl;
	}*/
	
	//dt.Begin();
	//API_CLIENT.SendMsgToRemote();
	//Event_Time = dt.GetTime() / 1e3;
	//if (Event_Time > 1500)
	//{
	//	std::cout << "API_CLIENT.SendMsgToRemote: " << Event_Time << std::endl;
	//}

	dt.Begin();	
	STORAGE_MANAGE.checkChange();
	Parking_Manage::Instance()->checkStationStatus();
	Event_Time= dt.GetTime()/1e3;
	if (Event_Time > 1500)
	{
		std::cout << "Update_Storages_Data_From_ACS_Event: " << Event_Time << std::endl;
	}

	dt.Begin();
	AGV_MANAGE.Update_AGV_Data_From_ACS_Event();
	Event_Time= dt.GetTime()/1e3;
	if (Event_Time>1500)
	{
		std::cout<<"Update_AGV_Data_From_ACS_Event: "<<Event_Time<<std::endl;
	}
	
	dt.Begin();
	EVENT_HANDLER.High_Priority_Battery_Event();
	Event_Time= dt.GetTime()/1e3;
	if (Event_Time>1500)
	{
		std::cout<<"High_Priority_Battery_Event: "<<Event_Time<<std::endl;
	}

	dt.Begin();
	EVENT_HANDLER.Data_Update_Event();
	Event_Time= dt.GetTime()/1e3;
	if (Event_Time>1500)
	{
		std::cout<<"Data_Update_Event: "<<Event_Time<<std::endl;
	}

	dt.Begin();
	EVENT_HANDLER.Task_Dispatch_Event();
	Event_Time= dt.GetTime()/1e3;
	if (Event_Time>1500)
	{
		std::cout<<"Task_Dispatch_Event: "<<Event_Time<<std::endl;
	}

	dt.Begin();
	EVENT_HANDLER.Parking_Event();
	Event_Time= dt.GetTime()/1e3;
	if (Event_Time>1500)
	{
		std::cout<<"Parking_Event: "<<Event_Time<<std::endl;
	}

	dt.Begin();
	EVENT_HANDLER.Low_Priority_Battery_Event();
	Event_Time= dt.GetTime()/1e3;
	if (Event_Time>1500)
	{
		std::cout<<"Low_Priority_Battery_Event: "<<Event_Time<<std::endl;
	}
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	switch (QMessageBox::information(this, tr("Exit Core Service?"),
		tr("Do you really want to exit Core Service?"),
		tr("Yes"), tr("No"),
		0, 1))
	{
	case 0:
		//XML_Database::Instance()->SaveData();
		//PLC_MANAGE.StopScan();
		//RABBITMQ_SERVICE.StopScan();
		event->accept();
		break;
	case 1:
	default:
		event->ignore();
		break;
	}
}

//void MainWindow::InStorageOrder( bool flag)
//{
//	number_count_ = STORAGE_MANAGE.getMaxTaskId();
//	std::string START = "1001";
//	std::string TARGET = "01-001-001";
//	int PRIORITY = 1;
//	std::string STATUS = "NEW";
//	std::string MODE = "IN";
//	std::string TYPE = "CARRY";
//	
//	STORAGE_MANAGE.Insert_Order(START, TARGET, PRIORITY, STATUS, MODE, TYPE);
//}
//
//void MainWindow::OutStorageOrder( bool flag)
//
//{
//	std::string START = "02-010-001";
//	std::string TARGET = "1002";
//	int PRIORITY = 1;
//	std::string STATUS = "NEW";
//	std::string MODE = "OUT";
//	std::string TYPE = "CARRY";
//
//	STORAGE_MANAGE.Insert_Order( START, TARGET, PRIORITY, STATUS, MODE, TYPE);
//	
//}

// 创建任务
void MainWindow::createOrder(bool flag)
{
	//模拟调用API接口
	API_CLIENT.TaskFinishReport("orderId","-1","123","1","2");

	//if (!storageList.contains(combobox_start->currentText()) )
	//{// 如果输入的 出发点 不存在
	//	combobox_start->setEditText(storageList.at(0));
	//	combobox_start->setFocus();
	//}
	//else if (!storageList.contains(combobox_target->currentText()) )
	//{// 如果输入的 目的地 不存在
	//	combobox_target->setEditText(storageList.at(0));
	//	combobox_target->setFocus();
	//}
	//else
	//{
	//	QString GUID = QUuid::createUuid().toString();
	//	GUID.remove("{").remove("}").remove("-"); // 一般习惯去掉左右花括号和连字符

	//	// 创建从 start 到 target 的 mode 类型命令
	//	std::string START = combobox_start->currentText().toStdString();
	//	//std::string TARGET = combobox_target->currentText().toStdString();
	//	std::string TARGET = "HP-01";
	//	int PRIORITY = 1;
	//	std::string STATUS = "NEW";
	//	std::string MODE = combobox_mode_->currentText().toStdString();
	//	std::string TYPE = "CARRY";
	//	STORAGE_MANAGE.Insert_Order(GUID.toStdString(), START, TARGET, PRIORITY, STATUS, MODE, TYPE);
	//	//RABBITMQ_SERVICE.ReportAgvAction("1", 1, 1, "1", 1);
	//}
}

void MainWindow::revokeOrder( bool flag)
{	
	number_count_ = STORAGE_MANAGE.getMaxTaskId();
	std::string START = "";
	std::string TARGET = "";
	int PRIORITY = 1;
	std::string STATUS = "REVOKE";
	std::string MODE = "";
	std::string TYPE = "CARRY";

}

void MainWindow::changeCurrentStorageStatus(bool flag)
{
	copy_linde_storage_name_->setText(QString::fromStdString(Selected_Label_));
	change_current_storage_status_dialog->show();
}

void MainWindow::createChangeStorageStatusDialog()
{
	change_current_storage_status_dialog = new QDialog;
	change_current_storage_status_dialog->setWindowFlags(Qt::Tool|Qt::WindowStaysOnTopHint);
	//change_current_storage_status_dialog->setWindowModality(Qt::ApplicationModal);
	change_current_storage_status_dialog->setModal(true);
	change_current_storage_status_dialog->setFixedSize(500,200);
	QPushButton *change_to_empty = new QPushButton(tr("Empty"));
	QPushButton *change_to_full = new QPushButton(tr("Full"));
	QPushButton *change_to_reserve = new QPushButton(tr("Reserve"));
	QLabel *storage_name_laebl = new QLabel(tr("current storage name : "));
	copy_linde_storage_name_ = new QLabel;

	
	QHBoxLayout *vboxlayout = new QHBoxLayout;
	vboxlayout->addWidget(storage_name_laebl);
	vboxlayout->addWidget(copy_linde_storage_name_);

	QHBoxLayout *hboxlayout = new QHBoxLayout;
	hboxlayout->addWidget(change_to_empty);
	hboxlayout->addWidget(change_to_full);

	QVBoxLayout *vboxlayout1 = new QVBoxLayout;
	vboxlayout1->addLayout(vboxlayout);
	vboxlayout1->addLayout(hboxlayout);

	change_current_storage_status_dialog->setLayout(vboxlayout1);
	
}

void MainWindow::slot_print_log(const QString& str)
{
	//每500行清一次记录。
	if (log_lines_++ > 500)
	{
		Log_Browser_->document()->clear();
		log_lines_ = 0;
	}

	Log_Browser_->append(str);
	Log_Browser_->moveCursor(QTextCursor::End);
}

void MainWindow::print_info(std::string info, int color)
{
	QColor clr;
	switch (color)
	{
	case 0:
		clr = Qt::black;
		break;
	case 1:
		clr = Qt::red;
		break;
	case 2:
		clr = Qt::green;
		break;
	case 3:
		clr = Qt::blue;
		break;
	case 4:
		clr = Qt::yellow;
		break;
	case 5:
		clr = Qt::white;
		break;
	case 6:
		clr = QColor(0xFF, 0x00, 0xFF);	//purple color
		break;
	default:
		clr = Qt::black;
		break;
	}
	QString strText = QDateTime::currentDateTime().toString("[yyyy-MM-dd-hh:mm:ss:zzz]:");
	strText += QString::fromStdString(info);
	stringToHtml(strText, clr);
	emit signal_print_log(strText);
}

void MainWindow::stringToHtml(QString &str, QColor clr)
{
	QByteArray array;
	array.append(clr.red());
	array.append(clr.green());
	array.append(clr.blue());
	QString strC(array.toHex());
	str = QString("<span style=\" color:#%1;font-size:24px;\">%2</span>").arg(strC).arg(str);
}

void MainWindow::setTranslator(QTranslator *translator)
{
	this->translator_ = translator;
}

void MainWindow::setApplication(QApplication *appa)
{
	this->APP_ = appa;
}

void MainWindow::translatorUI()
{
	this->setWindowTitle(tr("WCS_XD9C"));
	call_pushb_->setText(tr("Create Order"));
	revoke_pushb_->setText(tr("Revoke Order"));
	change_pushb_->setText(tr("Change Storage Status"));
	fun_dock_->setWindowTitle(tr(" Send Order"));
	AGV_dock->setWindowTitle(tr(" AGV Monitor"));
	Order_dock->setWindowTitle(tr(" Order Monitor"));
	Task_dock->setWindowTitle(tr("Task Monitor"));
	DOD_dock->setWindowTitle(tr("DOD Monitor"));
	station_dock->setWindowTitle(tr(" Station Status "));
	dock_widget1->setWindowTitle(tr("Monitor Info"));
	dock_console->setWindowTitle(tr("Console Info"));
	StartMenu->setTitle(tr("&Start"));
	Setting_Menu_->setTitle(tr("Setting"));
	start_run_->setText(tr("Start &run"));
	start_run_->setStatusTip(tr("Start Run Core"));
	Language_Action_->setText(tr("Change Language"));
	Language_Action_->setStatusTip(tr("Change Language"));
	Skin_Action_->setText(tr("Change Skin"));
	Skin_Action_->setStatusTip(tr("Change Skin"));
	Server_IP_Action_->setText(tr("Change Server IP"));
	Server_IP_Action_->setStatusTip(tr("Change Server IP"));
	Recon_PLC_Action_->setText(tr("Reconnect PLC"));
	Recon_PLC_Action_->setStatusTip(tr("Reconnect PLC"));
	if (timerId_ == 0) {
		system_status->setText(tr("Stopped"));
	}
	else {
		system_status->setText(tr("Running"));
	}
	
	
}

void MainWindow::initialParkingStatus()
{
	AGV_MANAGE.updateParkingManage();
}

 /// <summary>
 /// Loads the send order interface.
 /// </summary>
 /// Creator:MeiXu
 /// CreateDate:2021/1/28
 /// 
void MainWindow::loadSendOrderInterface()
{
	QVBoxLayout *dock_layout = new QVBoxLayout;
	dock_layout->setMargin(0);
	dock_layout->setSpacing(0);

	if (combo != nullptr)
	{/* 福沙定制 */
		dock_layout->addWidget(combo);
	}

	// 从数据库加载停车点与确认点数据
	Parking_Manage::Instance()->Initial();
	// 获取所有停车点
	std::map<std::string, ModelStationConfirm*>  allConfirmStation = Parking_Manage::Instance()->getAllConfirmStation();
	std::vector<ModelStationParking*>  allParkingStation = Parking_Manage::Instance()->getAllParkingStation();
	std::map<std::string, ModelEquipment*> allEquipment = Parking_Manage::Instance()->getAllEquipment();
	//std::vector<ModelBridge *> allBridge = Parking_Manage::Instance()->getAllBridge();
	if (allConfirmStation.begin()!= allConfirmStation.end())
	{ // Confirm Station
		// 提示信息
		QLabel *tipConfirmStation = new QLabel(tr("Confirm Station:"));
		dock_layout->addWidget(tipConfirmStation, 0, Qt::AlignHCenter);
		// 根据获取到的数据加载按钮
		for each (auto iter in allConfirmStation)
		{
			ModelStationConfirm* station = iter.second;
			SendOrderConfirmLabel* comfirm = new SendOrderConfirmLabel(station->getName().c_str());
			comfirm->set_background_color_of_label(station->getStatus());
			comfirm->setFixedSize(QSize(100, 25));
			comfirm->setEnabled(true);
			// 连接槽
			connect(comfirm, SIGNAL(changeStorageSignal(std::string, std::string)), this, SLOT(slot_change_confirm_station_status(std::string, std::string)));
			// 界面添加按钮
			dock_layout->addWidget(comfirm, 0, Qt::AlignHCenter);
			confirmLabelList[station->getName()] = comfirm;
		}
	}
	
	if (allParkingStation.begin()!=allParkingStation.end())
	{ // Parking Station，存在至少一个停车点，展示提示信息
		// 提示信息
		QLabel *tipParkingStation = new QLabel(tr("Parking Station:"));
		dock_layout->addWidget(tipParkingStation, 0, Qt::AlignHCenter);
		for each (auto iter in allParkingStation)
		{
			ModelStationParking* station = iter;
			SendOrderParkingLabel * parking = new SendOrderParkingLabel(station->getName().c_str());
			parking->set_background_color_of_label(station->getStatus());
			parking->setFixedSize(QSize(100, 25));
			parking->setEnabled(true);
			connect(parking, SIGNAL(changeStorageSignal(std::string, std::string)), this, SLOT(slot_change_parking_station_status(std::string, std::string)));
			dock_layout->addWidget(parking, 0, Qt::AlignHCenter);
			parkingLabelList[station->getName()] = parking;
		}
	}
	
	if (allEquipment.begin()!=allEquipment.end())
	{ // Equipment
		// 提示信息
		QLabel *tipInteraction = new QLabel(tr("Equipment:"));
		dock_layout->addWidget(tipInteraction, 0, Qt::AlignHCenter);
		for each (auto iter in allEquipment)
		{
			ModelEquipment* equipment = iter.second;
			SendOrderEquipmentLabel* equipment_label = new SendOrderEquipmentLabel(equipment->getId().c_str());
			equipment_label->set_background_color_of_label(equipment->getStatus());
			equipment_label->setFixedSize(QSize(100, 25));
			equipment_label->setEnabled(true);
			equipment_label->set_equipment(equipment);
			// 连接槽
			connect(equipment_label, SIGNAL(changeStorageSignal(std::string, std::string)), this, SLOT(slot_change_equipment_status(std::string, std::string)));
			// 界面添加按钮
			dock_layout->addWidget(equipment_label, 0, Qt::AlignHCenter);
			equipmentLabelList[equipment->getId()] = equipment_label;
		}
	}
	// TO-DO
	//if (allEquipment.begin() != allEquipment.end())
	//{ // Equipment
	//	// 提示信息
	//	QLabel *tipInteraction = new QLabel(tr("Equipment:"));
	//	dock_layout->addWidget(tipInteraction, 0, Qt::AlignHCenter);
	//	for each (auto iter in allEquipment)
	//	{
	//		ModelEquipment* equipment = iter.second;
	//		SendOrderEquipmentLabel* equipment_label = new SendOrderEquipmentLabel(equipment->getId().c_str());
	//		equipment_label->set_background_color_of_label(equipment->getStatus());
	//		equipment_label->setFixedSize(QSize(100, 25));
	//		equipment_label->setEnabled(true);
	//		equipment_label->set_equipment(equipment);
	//		// 连接槽
	//		connect(equipment_label, SIGNAL(changeStorageSignal(std::string, std::string)), this, SLOT(slot_change_equipment_status(std::string, std::string)));
	//		// 界面添加按钮
	//		dock_layout->addWidget(equipment_label, 0, Qt::AlignHCenter);
	//		equipmentLabelList[equipment->getId()] = equipment_label;
	//	}
	//}

	//STORAGE_MANAGE.Initial();
	// 从 数据库 读取 出发点与目的地 站点名
	std::vector<std::string>  allStationName = STORAGE_MANAGE.getAllStationName();
	Mode_Manage::Instance()->Initial();
	// 从 数据库 读取 modeName
	std::vector<std::string>  allModeName = Mode_Manage::Instance()->getAllTaskName();
	if (allStationName.begin()!=allStationName.end()&&allModeName.begin()!=allModeName.end())
	{ // Create Order
		// 提示信息
		QLabel *tipCreateOrder = new QLabel(tr("Create Order:"));
		dock_layout->addWidget(tipCreateOrder, 0, Qt::AlignHCenter);
		for each (std::string stationName in allStationName)
		{
			storageList << stationName.c_str();
		}
		combobox_start->addItems(storageList);
		combobox_start->setEditable(true);
		combobox_target->addItems(storageList);
		combobox_target->setEditable(true);

		for each (std::string modeName in allModeName)
		{
			combobox_mode_->addItem(modeName.c_str());
		}
		dock_layout->addWidget(combobox_start);
		//dock_layout->addWidget(combobox_target);
		dock_layout->addWidget(combobox_mode_);

		dock_layout->addSpacing(80);
		dock_layout->addWidget(call_pushb_);
		dock_layout->addSpacing(40);
	}
	

	QWidget *dock_AA = new QWidget;
	dock_AA->setLayout(dock_layout);

	QScrollArea *scroll_station;
	scroll_station = new QScrollArea;
	scroll_station->setWidget(dock_AA);
	scroll_station->setWidgetResizable(true);
	scroll_station->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scroll_station->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	fun_dock_->setWidget(scroll_station);
}


void MainWindow::changeEvent(QEvent *event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange :
		{
		translatorUI();
		}
		break;
	default:
		QMainWindow::changeEvent(event);
		break;
	}
}

void MainWindow::connectMylabelSlots()
{
	std::map<std::string, std::map<std::string, MyLabel*>> mylabel_map_list = Station_Monitor_NEW_->getMylabelList();
	for each (std::pair<std::string , std::map<std::string , MyLabel*>> var in mylabel_map_list)
	{
		for each (std::pair<std::string , MyLabel*> var1 in var.second)
		{
			//添加三个可以接收Mylabel的槽函数;
			connect(var1.second, SIGNAL(clicked()), this, SLOT(changeSelectedStatus()));
			connect(var1.second, SIGNAL(changeStorageSignal(std::string , std::string )), this, SLOT(changeStorageStatusSlot( std::string , std::string)));
		}
	}
}

void MainWindow::selectedAsTargetPointButton(std::string storage_name)
{
	Target_Storgae_Name_->setText(QString::fromStdString(storage_name));
}

//void MainWindow::slot_change_lable_status(MyLabel * label, std::string status)
//{
//	label->set_background_color_of_label(status);
//}

void MainWindow::slot_change_parking_station_status(std::string storage_name_, std::string signal_type_)
{
	STORAGE_MANAGE.changeParkingStatus(storage_name_, signal_type_);
}

void MainWindow::slot_change_confirm_station_status(std::string storage_name_, std::string signal_type_)
{
	STORAGE_MANAGE.changeConfirmStatus(storage_name_, signal_type_);
}

void MainWindow::slot_change_equipment_status(std::string equipment_id_, std::string signal_type_)
{
	STORAGE_MANAGE.changeEquipmentStatus(equipment_id_, signal_type_);
}


void MainWindow::slot_change_confirm_status(std::string storage_name_, std::string signal_type_)
{
	//STORAGE_MANAGE.changeConfirmStatus("6015-CONFIRM", "");
	//STORAGE_MANAGE.changeParkingStatus("P2", "FREE");

	/*if (label_number == 1)
	{
		STORAGE_MANAGE.changeConfirmStatus("6015-CONFIRM", 1);
	}
	else if (label_number == 2)
	{
		STORAGE_MANAGE.changeConfirmStatus("STORAGE-CONFIRM", 1);
	}
	else if (label_number == 3)
	{
		STORAGE_MANAGE.changeConfirmStatus("IN-CONFIRM", 1);
	}
	else if (label_number == 4)
	{
		STORAGE_MANAGE.changeConfirmStatus("OUT-CONFIRM", 1);
	}
	else if (label_number == 11)
	{
		STORAGE_MANAGE.changeConfirmStatus("P-CONFIRM", 1);
	}
	else if (label_number == 5)
	{
		STORAGE_MANAGE.changeParkingStatus("P1", "FREE");
	}
	else if (label_number == 6)
	{
		STORAGE_MANAGE.changeParkingStatus("P2", "FREE");
	}*/
}

void MainWindow::slot_change_confirm_status_Busy(int label_number)
{
	if (label_number == 1)
	{
		STORAGE_MANAGE.changeConfirmStatus("3008-CONFIRM", 0);
	}
	else if (label_number == 5)
	{
		STORAGE_MANAGE.changeParkingStatus("P1", "BUSY");
	}
	else if (label_number == 6)
	{
		STORAGE_MANAGE.changeParkingStatus("P2", "BUSY");
	}
	
}


//************************************
// Method:    OnstorageStatusChanged
// FullName:  MainWindow::OnstorageStatusChanged
// Access:    private 
// Returns:   void
// Qualifier: 发送改变Storage的信号
// Parameter: const std::map<std::string，std::map<int，Storage>> & sql_storage_map_list
//************************************
//void MainWindow::OnstorageStatusChanged(const std::map<std::string, std::map<int, Storage>> &sql_storage_map_list)
void MainWindow::OnstorageStatusChanged(Storage storage)
{
	storageLabelList[storage.Storage_Name_]->set_storage_label_status(storage.Storage_Status_);
	storageLabelList[storage.Storage_Name_]->set_storage_resource_status(storage.Resource_status_);
	emit signal_change_mylabel_status(storageLabelList[storage.Storage_Name_], storage.Storage_Status_, storage.Resource_status_, false, false);
	//
	////std::map<int, Storage>::const_iterator itor = sql_storage_map_list.begin();
	//for each (const std::pair<std::string, std::map<int, Storage>> &var in sql_storage_map_list)
	//{
	//	std::map<std::string, MyLabel*>aa = mylabel_map_list[var.first];

	//	for each (const std::pair<int, Storage> &var1 in var.second)
	//	{
	//		if (current_Seleted_Mylabel_ == NULL)
	//		{
	//			emit signal_change_mylabel_status(aa[var1.second.Storage_Name_], var1.second.Storage_Status_, false, false);
	//		}
	//		else
	//		{
	//			if (current_Seleted_Mylabel_ == aa[var1.second.Storage_Name_]) {
	//				emit signal_change_mylabel_status(aa[var1.second.Storage_Name_], var1.second.Storage_Status_, true, false);
	//			}
	//			else
	//			{
	//				emit signal_change_mylabel_status(aa[var1.second.Storage_Name_], var1.second.Storage_Status_, false, false);
	//			}
	//		}
	//	}
	//}
}

void MainWindow::OnStationStatusChanged( ModelStationConfirm* station) {
	// 发送更改信号
	emit signal_change_mylabel_status(confirmLabelList[station->getName()], station->getStatus());

}

void MainWindow::OnStationStatusChanged(ModelStationParking* station) {
	emit signal_change_mylabel_status(parkingLabelList[station->getName()],station->getStatus());
}

void MainWindow::OnStationStatusChanged(ModelEquipment* equipment) {
	emit signal_change_mylabel_status(equipmentLabelList[equipment->getId()], equipment->getStatus());
}

void MainWindow::selectedAsStartPointButton(std::string storage_name)
{
	Start_Storgae_Name_->setText(QString::fromStdString(storage_name));
}

void MainWindow::getAGVConfig()
{
	if (Config_.FileExist("config.txt"))
	{
		Config_.ReadFile("config.txt");
	}
	if (Config_.KeyExists("LANGUAGE"))
	{
		std::stringstream second_agv(Config_.Read<std::string>("LANGUAGE"));
		second_agv >> language_;
	}
}

void MainWindow::splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

//************************************
// Method:    slot_change_mylabel_status
// FullName:  MainWindow::slot_change_mylabel_status
// Access:    private 
// Returns:   void
// Qualifier: change current label status . auto trigger
// Parameter: MyLabel * label
// Parameter: std::string resource_status
// Parameter: std::string storage_type
// Parameter: std::string storage_status
// Parameter: bool flag1
// Parameter: bool flag2
//************************************
void MainWindow::slot_change_mylabel_status(MyLabel* label , std::string storage_status, std::string resource_status_, bool flag1, bool flag2)
{
	if (label != nullptr)
	{
		if (resource_status_ != "IDLE" && resource_status_ != "")
		{
			label->set_background_color_of_label(resource_status_, flag1, flag2);
		}
		else
		{
			int status = 1;
			if (storage_status == "EMPTY")
			{
				status = 0;
			}
			//TODO ????λ????????
			if (label->get_storage_label_name()[0] != 'P')
			{
				RABBITMQ_SERVICE.ReportStorageStatus(label->get_storage_label_name(), 0, status);
			}
			label->set_background_color_of_label(storage_status, flag1, flag2);
		}
	}
}

//************************************
// Method:    changeSelectedStatus
// FullName:  MainWindow::changeSelectedStatus
// Access:    private 
// Returns:   void
// Qualifier:change selected label status
//************************************
void MainWindow::changeSelectedStatus()
{
	//QMessageBox::information(NULL, "AAA", "AAA");
	MyLabel* current_mylabel = qobject_cast<MyLabel*>(sender());

	if (current_Seleted_Mylabel_ != current_mylabel&& current_Seleted_Mylabel_ !=nullptr) {
		current_Seleted_Mylabel_->set_label_select_status(false);
	}
	current_mylabel->set_label_select_status(true);
	current_Seleted_Mylabel_ = current_mylabel;
}

//************************************
// Method:    changeStorageStatusSlot
// FullName:  MainWindow::changeStorageStatusSlot
// Access:    private 
// Returns:   void
// Qualifier: 槽函数 接收到界面上的单击时触发
// Parameter: std::string storage_name 要修改的库位名
// Parameter: std::string status_name 以后可添加
// Parameter: std::string status 要修改为哪种状态
//************************************
void MainWindow::changeStorageStatusSlot(std::string storage_name, std::string status)
{
	if (status != "IDLE")
	{
		STORAGE_MANAGE.changeStorageStatus(storage_name, "storage_status", status);
	}
	else
	{
		STORAGE_MANAGE.changeStorageStatus(storage_name, "resource_status", status);
	}
}

//void MainWindow::SendApply(QNetworkRequest request, QByteArray postData) {
//	//accessManager->post(request, postData);
//}

//void MainWindow::slot_reply_finished(QNetworkReply* reply) {
//	API_CLIENT.ReplyFinished(reply);
//}


void MainWindow::RabbitMQInsertOrder(std::string taskId, int taskType, int taskStatus, std::string unitId, std::string palletNo)
{
	emit signal_rabbitmq_insert_order(taskId, taskType, taskStatus, unitId, palletNo);
}
void MainWindow::slot_rabbitmq_insert_order(std::string taskId, int taskType, int taskStatus, std::string unitId, std::string palletNo)
{

	//if (taskStatus == 0)
	//{
	//	return;
	//}
	int PRIORITY = 10;//优先级倒序
	std::string MODE = "";
	int agv_id = -1;

	if (taskType == 3)
	{
		// 3:水箱空轮搬运
		PRIORITY = 2;
		MODE = "TRAY";
		agv_id = STORAGE_MANAGE.GetAgvExeGoodsTask(palletNo);
	}
	else if (taskType == 2) {
		// 2:水箱满轮搬运
		PRIORITY = 1;
		MODE = "GOODS";
	}

	STORAGE_MANAGE.Insert_Order(taskId, unitId, "", PRIORITY, "NEW", MODE, "CARRY", agv_id, palletNo);
}