#ifndef SendOrderComfirmLabel_H_
#define SendOrderComfirmLabel_H_

#include "SendOrderLabelWidget.h"

/**
 *
 */
class SendOrderConfirmLabel :public SendOrderLabelWidget
{
	Q_OBJECT
public:

	explicit SendOrderConfirmLabel(QWidget *parent = 0);
	explicit SendOrderConfirmLabel(const QString &text, QWidget *parent = 0);
	~SendOrderConfirmLabel();

	//bool set_background_color_of_label(std::string status, bool scaling = false);

signals:

public slots:

protected:

private:

};

#endif

