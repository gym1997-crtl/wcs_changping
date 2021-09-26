#include <QtGui>
#include <QMainWindow>
#include <QStringList>
#include <QVector>
#include <QTimer>
#include <QDebug>
#include "iostream"
#include <vector>
#include <QHeaderView>

#include <QApplication> 
#include "iostream"

#include "progressbardelegate.h"
#include "OrderMonitor.h"
#include "DataModel.h"

#include "Manage/Order_Manage.h"
#include <map>
#include <string>
#include <QDesktopWidget>



Order_Monitor::Order_Monitor(QWidget *parent) :QTableView(parent)
{
	int screenWidth = QApplication::desktop()->screenGeometry().width();
	int screenHeight = QApplication::desktop()->screenGeometry().height();
	float factorx = screenWidth/1000;
	float factory = screenHeight/760;

	this->setAlternatingRowColors(true);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setObjectName("Order_Monitor");

	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");

	this->horizontalHeader()->setStretchLastSection(true);
	//this->horizontalHeader()->setBaseSize(30,20);
	this->verticalHeader()->hide();

	iniData();
	initTimer();
	this->setFont( QFont( "Times", 8, QFont::Black ) );
//	Database_Reader_=DATABASE_MANAGE.Get_DatabaseReader();
}

Order_Monitor::~Order_Monitor()
{
	delete m_model;
}


void Order_Monitor::iniData()
{
	//set data model
	m_model = new SpecialDataModel(this);
	// 这里必须先绑定数据模型，再设置表头，否则导致字体设置无效
	QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(m_model);
	this->setModel(proxyModel);   //绑定数据模型
	
	//this->setModel(m_model);

	//set table header
	QVariantList headers;
	headers << tr("ID")<<tr("Equip")<<tr("Storage")<<tr("Priority")<<tr("Status")<<tr("AGV ID")<<tr("Mode")<<tr("Type")<<tr("Enter Date")<<tr("Finish Date");
	m_model->setHorizontalHeader(headers);

	this->setSortingEnabled(true);

	//this->sortByColumn(0,Qt::AscendingOrder);
      
	/*m_progressBarDelegate = new ProgressBarDelegate(this);
	this->setItemDelegate(m_progressBarDelegate);*/

}

void Order_Monitor::initTimer()
{
	timer = new QTimer(this);
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressValue()));

	timer->start();
}

void Order_Monitor::translatorUI()
{
	QVariantList headers;
	headers << tr("ID") << tr("EQUIP") << tr("STORAGE") << tr("PRIORITY") << tr("STATUS") << tr("AGV_ID") << tr("MODE") << tr("TYPE") << tr("ENTER DATE") << tr("FINISH DATE");
	m_model->setHorizontalHeader(headers);


}

void Order_Monitor::updateProgressValue()
{
	QVector<QVariantList> data= m_model->DataVector();
	data.clear();

	std::map<std::string, Order> order_list=ORDER_MANAGE.Get_All_Order();

	std::map<std::string, Order>::iterator it=order_list.begin();

	for( ; it!=order_list.end(); ++it)
	{  
		Order current_order=it->second;
		QVariantList rowset;
		rowset.push_back(QString::fromStdString(current_order.ORDER_ID_));
		rowset.push_back(QString::fromStdString(current_order.START_));
		rowset.push_back(QString::fromStdString(current_order.TARGETED_));
		rowset.push_back(QString::number(current_order.PRIORITY_));
		rowset.push_back(QString::fromStdString(current_order.STATUS_));	
		rowset.push_back(QString::number(current_order.AGV_ID_)); 
		rowset.push_back(QString::fromStdString(current_order.MODE_));
		rowset.push_back(QString::fromStdString(current_order.TYPE_));
		QDateTime enterdate = QDateTime::fromString(current_order.ENTERDATE_.c_str(), "yyyy/M/dd hh:mm:ss");
		if (enterdate.isNull())
		{
			enterdate = QDateTime::fromString(current_order.ENTERDATE_.c_str(), "yyyy/MM/dd hh:mm:ss");
		}
		rowset.push_back(enterdate);
		QDateTime finishdate = QDateTime::fromString(current_order.FINISHDATE_.c_str(), "yyyy/M/dd hh:mm:ss");
		if (finishdate.isNull())
		{
			finishdate = QDateTime::fromString(current_order.FINISHDATE_.c_str(), "yyyy/MM/dd hh:mm:ss");
		}
		rowset.push_back(finishdate);
		data.append(rowset);
	}
	m_model->setData(data);
}

void Order_Monitor::changeEvent(QEvent *event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange:
	{
		translatorUI();
	}
	break;
	default:
		QTableView::changeEvent(event);
		break;
	}
}
