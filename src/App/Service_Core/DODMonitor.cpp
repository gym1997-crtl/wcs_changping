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
#include "DODMonitor.h"
#include "DataModel.h"

#include "Manage/Order_Manage.h"
#include <map>
#include <string>
#include <QDesktopWidget>
#include <QAction>
#include <QMenu>



DOD_Monitor::DOD_Monitor(QWidget *parent) :QTableView(parent)
{
	int screenWidth = QApplication::desktop()->screenGeometry().width();
	int screenHeight = QApplication::desktop()->screenGeometry().height();
	float factorx = screenWidth/1000;
	float factory = screenHeight/760;

	this->setAlternatingRowColors(true);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setObjectName("DOD_Monitor");

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

DOD_Monitor::~DOD_Monitor()
{
	delete m_model;
}


void DOD_Monitor::iniData()
{
	m_model = new DataModel();
	QSortFilterProxyModel *proxymodel = new QSortFilterProxyModel(this);
	proxymodel->setSourceModel(m_model);
	this->setModel(proxymodel);   //绑定数据模型;

	QVariantList headers;
	headers << tr("Order ID")<<tr("Start")<<tr("Target")<<tr("Priority")<<tr("Status")<<tr("Mode")<<tr("Type")<<tr("Enter Date");
	m_model->setHorizontalHeader(headers);

	this->setSortingEnabled(true);
}

void DOD_Monitor::initTimer()
{
	timer = new QTimer(this);
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressValue()));

	timer->start();
}

void DOD_Monitor::translatorUI()
{
	QVariantList headers;
	/*headers << tr("ORDER_ID") << tr("START") << tr("TARGETED") << tr("PRIORITY") << tr("STATUS") << tr("MODE") << tr("TYPE") << tr("ENTER DATE");*/
	headers << "ORDER_ID" << "START" <<"TARGETED" << "PRIORITY" << "STATUS"<< "MODE" << "TYPE" << "ENTER DATE";
	m_model->setHorizontalHeader(headers);


}

void DOD_Monitor::updateProgressValue()
{
	try
	{
		QVector<QVariantList> data = m_model->DataVector();
		data.clear();

		std::map<std::string, Order> DOD_List;
		DOD_List = ORDER_MANAGE.getNewOrder();

		std::map<std::string, Order>::iterator it = DOD_List.begin();

		
		for (; it != DOD_List.end(); ++it)
		{
			Order current_order = it->second;
			QVariantList rowset;
			rowset.push_back(QString::fromStdString(current_order.ORDER_ID_));
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
	catch (_com_error &e) {

		std::stringstream ss;
		ss << e.ErrorMessage() << "updateProgressValue" << e.Description();
	}
	
}

void DOD_Monitor::popMenu(const QPoint&)
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

void DOD_Monitor::Revoke_Order()
{
	std::string order_id = "";
	QModelIndexList list = this->selectedIndexes();

	if(list.count()>1)
	{
		QModelIndex test = list[0];
		order_id = test.data().toString().toStdString();
	}
	if(order_id != "")
	{
		ORDER_MANAGE.Revoke_Order(order_id);
	}
}

void DOD_Monitor::changeEvent(QEvent *event)
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
