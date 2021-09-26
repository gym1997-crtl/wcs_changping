#include <QAction>
#include <QMenu>

#include "SendOrderEquipmentLabel.h"

SendOrderEquipmentLabel::SendOrderEquipmentLabel(const QString &text1, QWidget *parent) :SendOrderLabelWidget::SendOrderLabelWidget(text1, parent) {

}

SendOrderEquipmentLabel::~SendOrderEquipmentLabel() {

}

void SendOrderEquipmentLabel::popMenu(const QPoint&)
{
	QAction pick_up_action("Pick Up", this);
	QAction put_down_action("Put Down", this);
	connect(&pick_up_action, SIGNAL(triggered(bool)), this, SLOT(sendChangePickUpSignal(bool)));
	connect(&put_down_action, SIGNAL(triggered(bool)), this, SLOT(sendChangePutDownSignal(bool)));

	QPoint pos;
	QMenu menu(this);
	menu.addAction(&pick_up_action);
	menu.addAction(&put_down_action);
	menu.exec(QCursor::pos());
}

void SendOrderEquipmentLabel::sendChangePickUpSignal(bool flag)
{
	emit changeStorageSignal(equipment->getId(), "PICKUP");
}
void SendOrderEquipmentLabel::sendChangePutDownSignal(bool flag)
{
	emit changeStorageSignal(equipment->getId(), "PUTDOWN");
}

bool SendOrderEquipmentLabel::set_equipment(ModelEquipment *eq) {
	equipment = eq;
	return true;
}