#include "SendOrderParkingLabel.h"

SendOrderParkingLabel::SendOrderParkingLabel(const QString &text1, QWidget *parent) :SendOrderLabelWidget::SendOrderLabelWidget(text1, parent) {

}

SendOrderParkingLabel::~SendOrderParkingLabel() {

}

//bool SendOrderParkingLabel::set_background_color_of_label(std::string status, bool scaling)
//{
//	if (scaling)
//	{
//		if (status.compare("IDLE"))
//			this->setStyleSheet("border:2px solid #FFFFFF;border-radius:10px;background-color:#FF7F50;font-size:10px");
//		else
//			this->setStyleSheet("border:2px solid #FFFFFF;border-radius:10px;background-color:#7FFF00;font-size:10px");
//	}
//	else
//	{
//		if (status.compare("IDLE"))
//			this->setStyleSheet("border:2px solid #FFFFFF;border-radius:10px;background-color:#FF7F50");
//		else
//			this->setStyleSheet("border:2px solid #FFFFFF;border-radius:10px;background-color:#7FFF00");
//	}
//	return false;
//}
