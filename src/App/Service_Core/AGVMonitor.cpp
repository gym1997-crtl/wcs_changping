#include <QtGui>
#include <QMainWindow>
#include <QStringList>
#include <QVector>
#include <QTimer>
#include <QDebug>
#include "iostream"
#include <sstream>
#include <vector>
#include <QHeaderView>
#include <QApplication> 
#include "comm/simplelog.h"
#include "AGVMonitor.h"
#include "DataModel.h"

#include "Manage/AGV_Manage.h"
#include <map>
#include <string>
#include <QDesktopWidget>
#include <QAction>
#include <QMenu>
#include <QMessageBox>



AGV_Monitor::AGV_Monitor(QWidget *parent) :QTableView(parent)
{
	int screenWidth = QApplication::desktop()->screenGeometry().width();
	int screenHeight = QApplication::desktop()->screenGeometry().height();
	float factorx = screenWidth/1000;
	float factory = screenHeight/760;

	this->setAlternatingRowColors(true);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);

	
	this->setObjectName("AGV_Monitor");
	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");
	
	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");
	vHeader->setMinimumWidth((int)55*factorx);
	this->horizontalHeader()->setStretchLastSection(true);
	this->verticalHeader()->hide();
	iniData();
	initTimer();
	this->setFont( QFont( "Times", 8, QFont::Black ) );

	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(popMenu(const QPoint&)));
//	Database_Reader_=DATABASE_MANAGE.Get_DatabaseReader();
}

AGV_Monitor::~AGV_Monitor()
{
	delete m_model;
}


void AGV_Monitor::iniData()
{
	//set data model
	m_model = new DataModel();
	QSortFilterProxyModel *proxymodel = new QSortFilterProxyModel(this);
	proxymodel->setSourceModel(m_model);
	this->setModel(proxymodel);   //绑定数据模型

	//set table header
	QVariantList headers;
	headers << tr("ID")<<tr("Type")<<tr("Status")<<tr("Error Code")<<tr("Resource Status")<<tr("Network")<<tr("Dispatched")<<tr("Battery")<<tr("In Station");
	m_model->setHorizontalHeader(headers);

	this->setSortingEnabled(true);
                                           

}

void AGV_Monitor::initTimer()
{
	timer = new QTimer(this);
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressValue()));

	timer->start();
}

void AGV_Monitor::translatorUI()
{
	QVariantList headers;
	headers << tr("ID") << tr("Type") << tr("Status") << tr("Error Code") << tr("Resource Status") << tr("Network") << tr("Dispatched") << tr("Battery") << tr("In Station");
	m_model->setHorizontalHeader(headers);
}

void AGV_Monitor::updateProgressValue()
{
	QVector<QVariantList> data= m_model->DataVector();
	data.clear();

	std::map<int, AGV*> AGV_list=AGV_MANAGE.Get_All_AGV();

	std::map<int, AGV*>::iterator it=AGV_list.begin();


	for( ; it!=AGV_list.end(); ++it)
	{  
		AGV* current_agv=it->second;
		QVariantList rowset;


		std::string agv_type;
		switch(current_agv->AGV_Type_)
		{
		case 1: agv_type="T20";break;
		case 2: agv_type="L16";break;
		}

		QString agv_status;
		switch(current_agv->AGV_Status_)
		{
		case 0: agv_status=tr("IDLE");break;
		case 1: agv_status=tr("Ready");break;
		case 2: agv_status=tr("RUNNING");break;
		case 4: agv_status=tr("ERROR");break;
		}



		QString resource_status;
		switch((RESOURCE_STATUS)current_agv->Resource_Status_)
		{
		case RESOURCE_STATUS::LOCKED: resource_status=tr("Locked");break;
		case RESOURCE_STATUS::UNLOCKED: resource_status=tr("Free");break;
		}

		QString online;
		switch(current_agv->Is_Online_)
		{
		case 0: online=tr("Offline");break;
		case 1: online=tr("Online");break;
		}

		QString assigned;
		switch(current_agv->Is_Assign_)
		{
		case 0: assigned=tr("Free");break;
		case 1: assigned=tr("Dispatched");break;
		}

		rowset.push_back(QString::number(current_agv->ID_));
		rowset.push_back(QString::fromStdString(agv_type));
		rowset.push_back(agv_status);
		rowset.push_back(QString::number(current_agv->Error_Code_));
		rowset.push_back(resource_status);
		rowset.push_back(online);
		rowset.push_back(assigned);
		rowset.push_back(QString::number(current_agv->Battery_Level_));
		rowset.push_back(QString::fromStdString(current_agv->AGV_In_Station_));	
		data.append(rowset);
	
	}
	m_model->setData(data);
}

void AGV_Monitor::popMenu(const QPoint&)
{
	QModelIndexList list = this->selectedIndexes();
	if(list.count()>1)
	{
		QAction SetLock(tr("Lock AGV"),this);
		QAction SetUnlock(tr("Unlock AGV"),this);
		QAction invokeParking(tr("AGV Parking"), this);
		connect(&SetLock,SIGNAL(triggered()),this,SLOT(Lock_AGV()));
		connect(&SetUnlock,SIGNAL(triggered()),this,SLOT(Unlock_AGV()));
		connect(&invokeParking, SIGNAL(triggered()), this, SLOT(invokeAGVParking()));

		QPoint pos;
		QMenu menu(this);
		menu.addAction(&SetLock);
		menu.addAction(&SetUnlock);
		menu.addAction(&invokeParking);

		menu.exec(QCursor::pos());
	}
}

void AGV_Monitor::Lock_AGV()
{
	int agv_id = -1;
	QModelIndexList list = this->selectedIndexes();
	
	if(list.count()>1)
	{
		QModelIndex test = list[0];
		agv_id = test.data().toInt();
	}
	if(agv_id != -1)
	{
		AGV_MANAGE.Set_Lock(agv_id);
	}
}

void AGV_Monitor::Unlock_AGV()
{
	int agv_id = -1;
	QModelIndexList list = this->selectedIndexes();
	if(list.count()>1)
	{
		QModelIndex test = list[0];
		agv_id = test.data().toInt();
	}
	if(agv_id != -1)
	{
		std::stringstream ss;
		switch( QMessageBox::information( this, tr("Confirm Unlock AGV?"),
			tr("Confirm Unlock AGV? (Please confirm AGV has no task assigned!)"),
			tr("Yes"), tr("No"),
			0, 1 ) ) 
		{
		case 0:
			AGV_MANAGE.setManualUnlock(agv_id);
			ss << "Unlocked AGV In GUI!";
			log_info_color(log_color::blue, ss.str().c_str());
			
			break;
		case 1:
		default: 
			break; 
		}
	}
}

void AGV_Monitor::invokeAGVParking()
{
	int agv_id = -1;
	QModelIndexList list = this->selectedIndexes();
	if (list.count() > 1)
	{
		QModelIndex test = list[0];
		agv_id = test.data().toInt();
	}
	if (agv_id != -1)
	{
		std::stringstream ss;
		switch (QMessageBox::information(this, tr("Confirm Unlock AGV?"),
			tr("Confirm invoke AGV? (Please confirm AGV has no task assigned!)"),
			tr("Yes"), tr("No"),
			0, 1))
		{
		case 0:
			AGV_MANAGE.invokeParking(agv_id);

			ss << "Invoke parking AGV in GUI!";
			log_info_color(log_color::blue, ss.str().c_str());

			break;
		case 1:
		default:
			break;
		}
	}
}

void AGV_Monitor::changeEvent(QEvent *event)
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
