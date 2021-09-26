#include <QtGui>
#include <QMainWindow>
#include <QStringList>
#include <QVector>
#include <QTimer>
#include <QDebug>
#include "iostream"
#include <vector>
#include <QHeaderView>

#include <QtGui/QApplication> 
#include "iostream"

#include "progressbardelegate.h"
#include "AssignMonitor.h"
#include "DataModel.h"

#include "Manage/Order_Manage.h"
#include <map>
#include <string>



Assign_Monitor::Assign_Monitor(QWidget *parent) :QTableView(parent)
{
	int screenWidth = QApplication::desktop()->screenGeometry().width();
	int screenHeight = QApplication::desktop()->screenGeometry().height();
	float factorx = screenWidth/1000;
	float factory = screenHeight/760;

	this->setAlternatingRowColors(true);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setObjectName("Assign_Monitor");

	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");

	this->horizontalHeader()->setStretchLastSection(true);
	this->verticalHeader()->hide();

	iniData();
	initTimer();
	this->setFont( QFont( "Times", 8, QFont::Black ) );

	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(popMenu(const QPoint&)));
}

Assign_Monitor::~Assign_Monitor()
{
	delete m_model;
}


void Assign_Monitor::iniData()
{
	m_model = new DataModel();
	QSortFilterProxyModel *proxymodel = new QSortFilterProxyModel(this);
	proxymodel->setSourceModel(m_model);
	this->setModel(proxymodel);   

	QStringList headers;
	headers << tr("ORDER_ID")<<tr("START")<<tr("TARGETED")<<tr("PRIORITY")<<tr("STATUS")<<tr("MODE")<<tr("TYPE")<<tr("ENTER DATE");
	m_model->setHorizontalHeader(headers);

	this->setSortingEnabled(true);
}

void Assign_Monitor::initTimer()
{
	timer = new QTimer(this);
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressValue()));

	timer->start();
}

void Assign_Monitor::translatorUI()
{
	QStringList headers;
	headers << tr("ORDER_ID") << tr("START") << tr("TARGETED") << tr("PRIORITY") << tr("STATUS") << tr("MODE") << tr("TYPE") << tr("ENTER DATE");
	m_model->setHorizontalHeader(headers);


}

void Assign_Monitor::updateProgressValue()
{
	QVector<QStringList> data= m_model->DataVector();
	data.clear();

	std::map<int, Order> Assign_List;
	Assign_List =ORDER_MANAGE.getAssignOrder();

	std::map<int, Order>::iterator it= Assign_List.begin();

	for( ; it!= Assign_List.end(); ++it)
	{  
		Order current_order=it->second;
		QStringList rowset;
		rowset.push_back(QString::number(current_order.ORDER_ID_));
		rowset.push_back(QString::fromStdString(current_order.START_));
		rowset.push_back(QString::fromStdString(current_order.TARGETED_));
		rowset.push_back(QString::number(current_order.PRIORITY_));
		rowset.push_back(QString::fromStdString(current_order.STATUS_));	
		rowset.push_back(QString::fromStdString(current_order.MODE_));
		rowset.push_back(QString::fromStdString(current_order.TYPE_));
		rowset.push_back(QString::fromStdString(current_order.ENTERDATE_));
		data.append(rowset);
	}
	m_model->setData(data);
}

void Assign_Monitor::popMenu(const QPoint&)
{
	QModelIndexList list = this->selectedIndexes();
	if(list.count()>1)
	{
		QAction SetRevoke(tr("Revoke Order"),this);
		
		connect(&SetRevoke,SIGNAL(triggered()),this,SLOT(Revoke_Order()));

		QPoint pos;
		QMenu menu(this);
		menu.addAction(&SetRevoke);
		menu.exec(QCursor::pos());
	}
}

void Assign_Monitor::Revoke_Order()
{
	int order_id = -1;
	QModelIndexList list = this->selectedIndexes();

	if(list.count()>1)
	{
		QModelIndex test = list[0];
		order_id = test.data().toInt();
	}
	if(order_id != -1)
	{
		ORDER_MANAGE.revokeAssignOrder(order_id);
	}
}

void Assign_Monitor::changeEvent(QEvent *event)
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
