#ifndef SendOrderEquipmentLabel_H_
#define SendOrderEquipmentLabel_H_

#include "SendOrderLabelWidget.h"
#include "Core/ModelEquipment.h"

/**
 *
 */
class SendOrderEquipmentLabel :public SendOrderLabelWidget
{
	Q_OBJECT
public:

	explicit SendOrderEquipmentLabel(QWidget *parent = 0);
	explicit SendOrderEquipmentLabel(const QString &text, QWidget *parent = 0);
	~SendOrderEquipmentLabel();

	//bool set_background_color_of_label(std::string status, bool scaling = false);

signals:

public slots:

	void popMenu(const QPoint&);

	void sendChangePickUpSignal(bool flag);

	void sendChangePutDownSignal(bool flag);

	bool set_equipment(ModelEquipment *eq);

protected:

private:

	ModelEquipment *equipment;

};

#endif

