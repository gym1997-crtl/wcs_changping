#ifndef MYLABEL_H_
#define MYLABEL_H_
#include <QtGui>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>

#include <stdio.h>
#include<iostream>
#include<sstream>
//#include "MainWnd.h"

enum ResizeRegion
{
	Default,
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest
};

class MyLabel : public QLabel
{
	Q_OBJECT
public:

	explicit MyLabel(QWidget *parent = 0);
	explicit MyLabel(const QString &text, QWidget *parent = 0);

	~MyLabel();
signals:
	void clicked();
	void changeStorageSignal( std::string storage_name_, std::string signal_type_);
	void changeStorageBusySignal(int aaaa);
	void changeStorageEmptySignal1(int aaaa);
	void selectedAsStartPointSignal(std::string storage_name);
	void selectedAsTargetPointSignal(std::string storage_name);

public slots:
	void slotClicked();
	virtual void popMenu(const QPoint&);
	void sendChangeFullSignal(bool flag);
	void sendChangeEmptySignal(bool flag);
	void sendChangeTraySignal(bool flag);
	void sendChangeIdleSignal(bool flag);
	void sendChangeBusySignal(bool flag);
	void sendselectedAsStartPointSignal(bool flag);
	void sendselectedAsTargetPointSignal(bool flag);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	bool click_click;
	bool Selected_;
	std::string storage_name_;
	std::string storage_status_;
	std::string belong_column_;
	std::string storage_type_;
	std::string resource_status_;
	std::string current_sql_table_name_;

	int number_;

public:
	ResizeRegion getResizeRegion(QPoint clientPos);
	void handleMove(QPoint pt);
	void handleResize();


	void set_click(bool flag);
	bool get_click();
	bool set_label_select_status(bool flag);
	virtual bool set_background_color_of_label(std::string status, bool selected = false, bool scaling = false);
	bool set_storage_label_name(std::string name);
	std::string get_storage_label_name();
	bool set_storage_label_status(std::string status);
	std::string get_storage_label_status();
	bool set_storage_label_belong_column(std::string belong_column);
	std::string get_storage_label_belong_column();
	bool set_storage_type(std::string belong_column);
	std::string get_storage_type();
	bool set_storage_resource_status(std::string resource_status);
	std::string get_storage_resource_status();
	void setnumber(int aa);

private:
	void setResizeCursor(ResizeRegion region);


};

#endif 