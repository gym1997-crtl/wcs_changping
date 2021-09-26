#ifndef SendOrderLabelWidget_H_
#define SendOrderLabelWidget_H_

#include <MyLabel.h>

/**
 * 
 */
class SendOrderLabelWidget :public MyLabel
{
	Q_OBJECT
public:

	explicit SendOrderLabelWidget(QWidget *parent = 0);
	explicit SendOrderLabelWidget(const QString &text, QWidget *parent = 0);
	//bool set_background_color_of_label(std::string status, bool scaling = false);
	~SendOrderLabelWidget();

signals:

public slots:
	void popMenu(const QPoint&);
	void sendChangeIdleSignal(bool flag);

protected:

private:
	//std::string storage_status_;

};

#endif

