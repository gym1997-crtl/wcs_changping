#ifndef _COMM_WANGHONGTAO_20120607_
#define _COMM_WANGHONGTAO_20120607_

#include <sstream>
#include <boost/lexical_cast.hpp>
#include <QtGui>

template<typename T>
QString NumtoQString(T value){
	std::stringstream ss;
	ss<<value;
	return QString(ss.str().c_str());
}
template<typename T>
void SetLineEdit(QLineEdit * line_edit,T value){
	QString qs = NumtoQString<T>(value);
	line_edit->setText(qs);
}
template<typename T>
T GetLineEdit(T &value,QLineEdit * line_edit){
	std::string str = line_edit->text().toStdString();
	value = boost::lexical_cast<T>(str.c_str());
	return value;
}

#endif //_COMM_WANGHONGTAO_20120607_

