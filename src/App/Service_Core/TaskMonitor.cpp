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
#include "TaskMonitor.h"
#include "DataModel.h"

#include "Core/Task_Chain_Manage.h"
#include <map>
#include <string>
#include <QMessageBox>
#include <QAction>
#include <QDesktopWidget>
#include <QMenu>

Task_Monitor::Task_Monitor(QWidget *parent) :QTableView(parent)
{
	int screenWidth = QApplication::desktop()->screenGeometry().width();
	int screenHeight = QApplication::desktop()->screenGeometry().height();
	float factorx = screenWidth / 1000;
	float factory = screenHeight / 760;

	this->setAlternatingRowColors(true);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setObjectName("Task_Monitor");

	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");
	vHeader->setMinimumWidth((int)55 * factorx);

	this->horizontalHeader()->setStretchLastSection(true);
	this->verticalHeader()->hide();
	iniData();
	initTimer();
	this->setFont(QFont("Times", 8, QFont::Black));
	//	Database_Reader_=DATABASE_MANAGE.Get_DatabaseReader();

	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(popMenu(const QPoint&)));
}

Task_Monitor::~Task_Monitor()
{
	delete m_model;
}

void Task_Monitor::iniData()
{
	//set data model
	m_model = new DataModel();
	//QSortFilterProxyModel *proxymodel = new QSortFilterProxyModel(this);
	//proxymodel->setSourceModel(m_model);
	this->setModel(m_model);   //绑定数据模型

	//set table header
	QVariantList headers;
	headers << tr("ID") << tr("Order ID") << tr("AGV ID") << tr("Start") << tr("Target") << tr("Mode") << tr("Status") << tr("Start Time");
	m_model->setHorizontalHeader(headers);

	this->setSortingEnabled(true);
}

void Task_Monitor::initTimer()
{
	timer = new QTimer(this);
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressValue()));

	timer->start();
}

void Task_Monitor::translatorUI()
{
	QVariantList headers;
	headers << tr("ID") << tr("Order ID") << tr("AGV ID") << tr("START") << tr("TARGET") << tr("MODE") << tr("Status") << tr("Start Time") << tr("Over Time") << tr("Duration");
	m_model->setHorizontalHeader(headers);

}

void Task_Monitor::updateProgressValue()
{
	QVector<QVariantList> data = m_model->DataVector();
	data.clear();

	std::vector<Task_Chain*> full_task_list;
	std::vector<Task_Chain*> active_task_list = TASK_CHAIN_MANAGE.Get_Active_Task_List();
	std::vector<Task_Chain*> inactive_task_list = TASK_CHAIN_MANAGE.Get_Inactive_Task_List();


	full_task_list.insert(full_task_list.end(), active_task_list.begin(), active_task_list.end());
	full_task_list.insert(full_task_list.end(), inactive_task_list.begin(), inactive_task_list.end());

	std::vector<Task_Chain*>::iterator it = full_task_list.begin();


	for (; it != full_task_list.end(); ++it)
	{
		Task_Chain* task = *it;
		QVariantList rowset;

		QString status;
		switch (task->Get_Status())
		{
		case TASK_CHAIN_STATUS::BEGIN: status = tr("BEGIN"); break;
		case TASK_CHAIN_STATUS::BLOCKED: status = tr("BLOCKED"); break;
		case TASK_CHAIN_STATUS::EQUIP_GET_CHECK: status = tr("EQUIP_GET"); break;
		case TASK_CHAIN_STATUS::BUFFER_PUT_CHECK: status = tr("BUFFER_PUT"); break;
		case TASK_CHAIN_STATUS::BUFFER_GET_CHECK: status = tr("BUFFER_GET"); break;
		case TASK_CHAIN_STATUS::EQUIP_PUT_CHECK: status = tr("EQUIP_PUT"); break;
		case TASK_CHAIN_STATUS::EQUIP_PUT_CONFIRM_CHECK: status = tr("EQUIP_PUT_CONFIRM"); break;
		case TASK_CHAIN_STATUS::EQUIP_PUT_RELEASE_CHECK: status = tr("EQUIP_PUT_RELEASE"); break;
		case TASK_CHAIN_STATUS::EQUIP_GET_CONFIRM_CHECK: status = tr("EQUIP_GET_CONFIRM"); break;
		case TASK_CHAIN_STATUS::PARKING_TURN_CHECK: status = tr("PARKING_TURN"); break;
		case TASK_CHAIN_STATUS::PARKING_CHECK: status = tr("PARKING"); break;
		case TASK_CHAIN_STATUS::IS_CHARGING: status = tr("IS_CHARGING"); break;
		case TASK_CHAIN_STATUS::ERR: status = tr("ERROR"); break;
		case TASK_CHAIN_STATUS::NONE: status = tr("NONE"); break;
		case TASK_CHAIN_STATUS::OVER: status = tr("OVER"); break;
		}

		rowset.push_back(QString::number(task->Task_ID_));
		rowset.push_back(QString::fromStdString(task->Order_ID_));
		rowset.push_back(QString::number(task->Get_Associate_AGV()->ID_));

		rowset.push_back(QString::fromStdString(task->getStart()));
		rowset.push_back(QString::fromStdString(task->getTargeted()));
		rowset.push_back(QString::fromStdString(task->getMode()));
		rowset.push_back(status);

		rowset.push_back(QString::fromStdString(task->Get_Start_Time()));
		data.append(rowset);
	}
	m_model->setData(data);
}

void Task_Monitor::popMenu(const QPoint&)
{
	QModelIndexList list = this->selectedIndexes();
	if (list.count() > 1)
	{
		QAction Abort(tr("Abort"), this);   //强制取消;
		connect(&Abort, SIGNAL(triggered()), this, SLOT(cancelOrder()));
		QPoint pos;
		QMenu menu(this);
		menu.addAction(&Abort);

		menu.exec(QCursor::pos());
	}
}

void Task_Monitor::cancelOrder()
{
	std::string order_index = "";
	int task_index = -1;
	QModelIndexList task_attribute_list = this->selectedIndexes();
	if (task_attribute_list.count() > 1)
	{
		QString str = tr("Abort Task Successful!");
		QMessageBox::information(this, tr("Info"), str);
		QModelIndex task_index_variant = task_attribute_list[0];
		QModelIndex order_index_variant = task_attribute_list[1];
		task_index = task_index_variant.data().toInt();
		order_index = order_index_variant.data().toString().toStdString();
		TASK_CHAIN_MANAGE.cancelTaskChain(order_index, task_index);
	}
}

void Task_Monitor::changeEvent(QEvent *event)
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
