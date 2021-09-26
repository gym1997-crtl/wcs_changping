#include <QAction>
#include <QMenu>

#include "SendOrderLabelWidget.h"

SendOrderLabelWidget::SendOrderLabelWidget(const QString &text1, QWidget *parent) :MyLabel::MyLabel(text1, parent){

}

/**
 * 站点状态，是否需要放缩，默认为false
 */
//bool SendOrderLabelWidget::set_background_color_of_label(std::string status, bool scaling)
//{
//	if (scaling)
//	{
//		if (status.compare("IDLE") == 0)
//			this->setStyleSheet("border:2px solid #FFFFFF;border-radius:10px;background-color:#7FFF00;font-size:10px");
//		else if (status.compare("RESERVE") == 0)
//			this->setStyleSheet("border:2px solid #FFFFFF;border-radius:10px;background-color:#FF7F50;font-size:10px");
//	}
//	else
//	{
//		if (status.compare("IDLE") == 0)
//			this->setStyleSheet("border:2px solid #FFFFFF;border-radius:10px;background-color:#7FFF00;color:#000000");
//		else if (status.compare("RESERVE") == 0)
//			this->setStyleSheet("border:2px solid #FFFFFF;border-radius:10px;background-color:#FF7F50");
//	}
//	return false;
//}

SendOrderLabelWidget::~SendOrderLabelWidget() {

}

void SendOrderLabelWidget::sendChangeIdleSignal(bool flag)
{
	//storage_status_ = "IDLE";
	emit changeStorageSignal(get_storage_label_name(), "IDLE");
}

void SendOrderLabelWidget::popMenu(const QPoint&)
{
	QAction IdleAction("Change To IDLE", this);
	connect(&IdleAction, SIGNAL(triggered(bool)), this, SLOT(sendChangeIdleSignal(bool)));
	QPoint pos;
	QMenu menu(this);
	menu.addAction(&IdleAction);
	menu.exec(QCursor::pos());
}