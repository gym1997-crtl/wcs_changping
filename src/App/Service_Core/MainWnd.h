#ifndef CORE_OPERATING_DLG_ED_20180517_
#define CORE_OPERATING_DLG_ED_20180517_

#include <QtGui>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextBrowser>
#include <QTranslator>
#include <QCompleter>
#include <QInputDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <vector>
#ifndef Q_MOC_RUN
#include <boost/signals2.hpp>
#include <boost/thread.hpp>
#endif

#include "comm/MyDefine.h"
#include "ADODatabase.h"
#include "WCS_Database.h"
#include "Common/Config.h"
#include "OrderMonitor.h"
#include "DODMonitor.h"
#include "AGVMonitor.h"
#include "TaskMonitor.h"
#include "StorageMonitor.h"
#include "Manage/Storage_Manage.h"
//#include "Manage/StorageManage.h"
#include "Manage/Parking_Manage.h"
#include "ADODatabase/ApiClient.h"
#include "ADODatabase/RabbitMQService.h"

#include "SendOrderConfirmLabel.h"
#include "SendOrderParkingLabel.h"
#include "SendOrderLabelWidget.h"
#include "SendOrderEquipmentLabel.h"
#include "Core/ModelStationConfirm.h"
#include "Core/ModelStationParking.h"

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class Station_Monitor;
class MyLabel;
class Station_Monitor_NEW;
class RabbitMQ_Service_Notifier;
QT_END_NAMESPACE

class MainWindow: public QMainWindow,public Storage_Status_Notifier, public Station_Status_Notifier, public MainWindowDelegate, public RabbitMQ_Service_Notifier
{
	Q_OBJECT

public:

	MainWindow();

	~MainWindow();

	void print_info(std::string info, int color);

	void createChangeStorageStatusDialog();

	void setTranslator(QTranslator *translator);

	void setApplication(QApplication *appa);

	void translatorUI();

protected:
	void changeEvent(QEvent *event);

private:
	QApplication *APP_;
	QTranslator *translator_;

	int number_count_;

	std::string Selected_Label_;

	int timerId_;
	
	boost::thread check_storage_status;

	boost::thread check_station_status;

	//int times;

	void timerEvent( QTimerEvent *event );

	void closeEvent( QCloseEvent * event);

	bool Is_Open_Data_Transfer_;

	void CreateMenu();

	void CreateActions();
	
	void CreateStatusBar();

	void stringToHtml(QString &str, QColor clr);

	void initialParkingStatus();

	//void loadStationStatusInterface();

	void loadSendOrderInterface(); 

	QMenu *Setting_Menu_;
	QAction *Language_Action_;
	QAction *Skin_Action_;
	QAction *Server_IP_Action_;
	QAction *Recon_PLC_Action_;

	QMenu *StartMenu;
	QAction *start_run_;
	QAction *start_oracle_;
	QAction *done_order_;

	QAction *MysqlAction;
	Order_Monitor* Order_Monitor_;	
	AGV_Monitor* AGV_Monitor_;
	Task_Monitor* Task_Monitor_;
	DOD_Monitor* DOD_Monitor_;
	//Station_Monitor *Station_Monitor_;
	Station_Monitor_NEW *Station_Monitor_NEW_;
	
	QDialog * Open_Selection_;
	QPushButton *right_exit_;
	QPushButton *error_exit_;
	QLabel *show_message_;


	QTextBrowser* Log_Browser_;

	QLabel *copy_linde_storage_name_;
	QLabel *linde_storage_name_ ;
	QLabel *Start_Storgae_Name_;//订单开始位置;
	QLabel *Target_Storgae_Name_;//订单结束位置;
	QComboBox *combobox22_ ;
	QPushButton *IN_STORAGE_;
	QPushButton *OUT_STORAGE_;
	QPushButton *call_pushb_ ;
	QPushButton *revoke_pushb_ ;
	QPushButton *change_pushb_;
	QLineEdit *all_storage_num_text_;
	QDialog *change_current_storage_status_dialog;
	QDockWidget *AGV_dock;
	QDockWidget *Order_dock;
	QDockWidget *Task_dock;
	QDockWidget *DOD_dock;
	QDockWidget *station_dock;
	QDockWidget *dock_widget1;
	QDockWidget *dock_console;
	QDockWidget *fun_dock_;

	QComboBox* combo;

	std::map<std::string , SendOrderConfirmLabel *> confirmLabelList;
	std::map<std::string , SendOrderParkingLabel *> parkingLabelList;
	std::map<std::string, SendOrderEquipmentLabel *> equipmentLabelList;
	std::map<std::string , MyLabel * > storageLabelList;

	QStringList storageList;
	QComboBox *combobox_start;
	QComboBox *combobox_target;
	
	QComboBox *combobox_mode_;

	int language_;
	Config_File Config_;
	QSettings *setting_Config_;
	QInputDialog *Set_Server_IP_DLG;
	
private slots:
	void start_run();

	void changeLanguage();

	void changeServerIP();

	void ReconnectPLC();

	void select_close_status();

	void start_system();

	void right_exit();

	void error_exit();

	//void InStorageOrder( bool flag);

	//void OutStorageOrder( bool flag);
	
	void createOrder( bool flag);

	void revokeOrder( bool flag);

	void changeCurrentStorageStatus(bool flag);

	void slot_print_log(const QString& str);

	void connectMylabelSlots();//链接Mylabels发送过来的信号的槽函数;

	void selectedAsStartPointButton(std::string storage_name);

	void selectedAsTargetPointButton(std::string storage_name);

	//void slot_change_lable_status(MyLabel * label, std::string status);

	void slot_change_parking_station_status(std::string storage_name_, std::string signal_type_);

	void slot_change_confirm_station_status(std::string storage_name_, std::string signal_type_);

	void slot_change_equipment_status(std::string equipment_id_, std::string signal_type_);

	void slot_change_confirm_status(std::string storage_name_, std::string signal_type_);

	void slot_change_confirm_status_Busy(int aaa);

	//void OnstorageStatusChanged(const std::map<std::string, std::map<int, Storage>> &sql_storage_map_list);
	void OnstorageStatusChanged(Storage storage);

	void OnStationStatusChanged(ModelStationParking *);

	void OnStationStatusChanged(ModelEquipment * equipment);

	void OnStationStatusChanged(ModelStationConfirm *);
	// 发送Post请求
	//void SendApply(QNetworkRequest, QByteArray);

	//bool ChangeConfirmLableStatus(int id, int status);

	void getAGVConfig();

	void splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c);

	void slot_change_mylabel_status(MyLabel * mylabel, std::string storage_status, std::string resource_status_ = "", bool flag1 = false, bool flag2 = false);

	void changeSelectedStatus();

	void changeStorageStatusSlot(std::string storage_name, std::string status);

	//void slot_reply_finished(QNetworkReply*);

	void slot_rabbitmq_insert_order(std::string taskId, int taskType, int taskStatus, std::string unitId, std::string palletNo);

signals:
	void signal_print_log(const QString& str);

	//void signal_change_lable_status( MyLabel * , std::string );

	void signal_change_mylabel_status(MyLabel* , std::string, std::string = "", bool flag1 = false, bool flag2 = false);

	void signal_rabbitmq_insert_order(std::string taskId, int taskType, int taskStatus, std::string unitId, std::string palletNo);

private:

	QLabel *msgLabel;
	QLabel *system_status;
	boost::mutex mu_select_label_;
	qulonglong log_lines_;

	MyLabel* current_label_widget_;

	MyLabel* current_Seleted_Mylabel_;

	void RabbitMQInsertOrder(std::string taskId, int taskType, int taskStatus, std::string unitId, std::string palletNo);
};
#endif 