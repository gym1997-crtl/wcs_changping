#ifndef _Station_Monitor_HUANGSHENGQIANG_
#define _Station_Monitor_HUANGSHENGQIANG_

#include <QTableWidget>
#include <QAbstractItemModel>
#include <QTimer>
#include <map>
#include <QGridLayout>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QComboBox>

#include "Manage/Storage_Manage.h"
#include "Manage/Manage_Define.h"
#include "MyLabel.h"

class Station;
class DataModel;
class QAbstractItemModel;
class QPushButton;
class QLabel;
class MyLabel;
class Cell_Station : public QWidget
{
	Q_OBJECT

public:
	Cell_Station(QWidget *parent = 0);
	~Cell_Station();

	std::map<std::string, MyLabel*> setStorageLayout(std::map <int, Storage>storage_list);

	std::map<std::string, MyLabel*> setStorageLayout(std::map <int, Storage>storage_list, bool custom);

private:
	int storage_label_numver_;



	QLabel* station_name_label_;
	QLabel* storage_name_label_;

	Station* bind_station_;
	Storage* bind_storage_;

};


class Station_Monitor_NEW : public QWidget
{
	Q_OBJECT

private:

	std::map<std::string, std::map<std::string, MyLabel*>> mylabel_map_list_;

	QComboBox * combo;

	QStackedLayout * stacked_layout;


	Cell_Station * cell_station_[19];

	std::map<int, QGroupBox *> groupbox_;

public:
	explicit Station_Monitor_NEW(QWidget *parent = 0);

	~Station_Monitor_NEW();

	void initDate();

	QComboBox* initDate(bool custom);

	std::map<std::string, std::map<std::string, MyLabel*>> getMylabelList();

private slots:

	void ComboValueChanged(int index);
};
#endif