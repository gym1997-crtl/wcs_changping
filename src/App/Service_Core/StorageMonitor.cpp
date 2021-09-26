#include "StorageMonitor.h"

Cell_Station::Cell_Station(QWidget *parent) {
	storage_label_numver_ = 0;
}
Cell_Station::~Cell_Station() {}

std::map<std::string, MyLabel*> Cell_Station::setStorageLayout(std::map <int, Storage>storage_list)
{
	std::map<std::string, MyLabel*> result;
	std::map<int, Storage>::iterator it = storage_list.begin();
	Storage current_storage;
	QGridLayout *storage_widget_gridlayout = new QGridLayout;

	for (; it != storage_list.end(); it++)
	{
		current_storage = it->second;
		std::map<std::string, MyLabel *>storage_label_;
		storage_label_[current_storage.Storage_Name_] = new MyLabel(current_storage.Storage_Name_.c_str());
		if (current_storage.Resource_status_ != "IDLE")
		{
			storage_label_[current_storage.Storage_Name_]->set_background_color_of_label(current_storage.Resource_status_, false, false);
		}
		else {
			storage_label_[current_storage.Storage_Name_]->set_background_color_of_label(current_storage.Storage_Status_, false, false);
		}
		storage_label_[current_storage.Storage_Name_]->set_storage_label_name(current_storage.Storage_Name_);
		storage_label_[current_storage.Storage_Name_]->set_storage_label_status(current_storage.Storage_Status_);
		storage_label_[current_storage.Storage_Name_]->set_storage_label_belong_column(current_storage.Belong_Column_);
		storage_label_[current_storage.Storage_Name_]->set_storage_resource_status(current_storage.Resource_status_);
		storage_label_[current_storage.Storage_Name_]->set_storage_type(current_storage.Storage_Type_);

		storage_widget_gridlayout->addWidget(storage_label_[current_storage.Storage_Name_], current_storage.Storage_Row_, current_storage.Storage_Column_, 1, 1);
		result[current_storage.Storage_Name_] = storage_label_[current_storage.Storage_Name_];
	}
	this->setLayout(storage_widget_gridlayout);
	return result;
}

std::map<std::string, MyLabel*> Cell_Station::setStorageLayout(std::map <int, Storage>storage_list, bool custom)
{
	std::map<std::string, MyLabel*> result;
	std::map<int, Storage>::iterator it = storage_list.begin();
	Storage current_storage;
	QGridLayout *storage_widget_gridlayout = new QGridLayout;

	/* 福沙定制 界面布局 */
	int max_col = 4;
	int tmp_row = 0;
	int tmp_col = 0;

	for (; it != storage_list.end(); it++)
	{
		current_storage = it->second;
		std::map<std::string, MyLabel *>storage_label_;
		storage_label_[current_storage.Storage_Name_] = new MyLabel(current_storage.Storage_Name_.c_str());
		if (current_storage.Resource_status_ != "IDLE")
		{
			storage_label_[current_storage.Storage_Name_]->set_background_color_of_label(current_storage.Resource_status_, false, false);
		}
		else {
			storage_label_[current_storage.Storage_Name_]->set_background_color_of_label(current_storage.Storage_Status_, false, false);
		}
		storage_label_[current_storage.Storage_Name_]->set_storage_label_name(current_storage.Storage_Name_);
		storage_label_[current_storage.Storage_Name_]->set_storage_label_status(current_storage.Storage_Status_);
		storage_label_[current_storage.Storage_Name_]->set_storage_label_belong_column(current_storage.Belong_Column_);
		storage_label_[current_storage.Storage_Name_]->set_storage_resource_status(current_storage.Resource_status_);
		storage_label_[current_storage.Storage_Name_]->set_storage_type(current_storage.Storage_Type_);

		if (custom)
		{
			/* 福沙定制 界面布局 */
			if (tmp_col > max_col)
			{
				tmp_col = 0;
				tmp_row++;
			}
			tmp_col++;
			current_storage.Storage_Row_ = tmp_row;
			current_storage.Storage_Column_ = tmp_col;
		}

		storage_widget_gridlayout->addWidget(storage_label_[current_storage.Storage_Name_], current_storage.Storage_Row_, current_storage.Storage_Column_, 1, 1);
		result[current_storage.Storage_Name_] = storage_label_[current_storage.Storage_Name_];
	}
	this->setLayout(storage_widget_gridlayout);
	return result;
}
Station_Monitor_NEW::Station_Monitor_NEW(QWidget *parent /* = 0 */) {}
Station_Monitor_NEW::~Station_Monitor_NEW() {}

void Station_Monitor_NEW::initDate()
{
	QGridLayout *gridlayout = new QGridLayout;
	std::vector<Sql_Table_Attri> sql_table_list = STORAGE_MANAGE.getSqlableList();
	std::map<std::string, std::map<int, Storage>> storage_list = STORAGE_MANAGE.getStorageListMap();

	int i = 0;
	for each (auto var in sql_table_list)
	{
		int column = var.widget_column;
		int row = var.widget_row;
		int columnSpan = var.columnSpan;
		int rowSpan = var.rowSpan;
		std::string group_name = var.group_name;
		std::string table_name = var.sql_table_name;
		// int i = 0;
		QGroupBox * groupbox_ = new QGroupBox;
		Cell_Station * cell_station_ = new Cell_Station;
		QVBoxLayout *layout = new QVBoxLayout;
		groupbox_->setTitle(QString::fromLocal8Bit(group_name.c_str()));
		std::map<std::string, std::map<int, Storage>>::iterator itor = (storage_list.find(table_name));

		if (itor != storage_list.end()) {
			mylabel_map_list_[table_name] = cell_station_->setStorageLayout(itor->second);
			layout->addWidget(cell_station_);
			// groupbox_[i]->setLayout(layout);
		}
		//initDate((storage_list.find(table_name))->second);
		groupbox_->setLayout(layout);
		gridlayout->addWidget(groupbox_, column, row, columnSpan, rowSpan);

		i++;
	}
	setLayout(gridlayout);
}


std::map<std::string, std::map<std::string, MyLabel*>> Station_Monitor_NEW::getMylabelList()
{
	return mylabel_map_list_;
}

/// <summary>
/// Initializes the date.福沙库位显示定制
/// </summary>
/// <param name="custom">if set to <c>true</c> 代表为定制界面 </param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/1/28
/// 
QComboBox * Station_Monitor_NEW::initDate(bool custom)
{
	if (custom)
	{
		/* 下拉菜单，给外部使用 */
		combo = new QComboBox(this);
		/* 界面 */
		stacked_layout = new QStackedLayout(this);
		/* 加载数据 */
		std::vector<Sql_Table_Attri> sql_table_list = STORAGE_MANAGE.getSqlableList();
		std::map<std::string, std::map<int, Storage>> storage_list = STORAGE_MANAGE.getStorageListMap();
		/* 表名， 行， 库位号， 库位 */
		std::map<std::string, std::map<int, std::map <int, Storage>>> sort_by_row;
		for each (auto var in sql_table_list)
		{
			for each (auto var2 in storage_list[var.sql_table_name])
			{
				sort_by_row[var.sql_table_name][atoi(var2.second.Storage_Name_.c_str()) / 100][var2.second.ID_] = var2.second;
			}
		}
		QGroupBox * groupbox_ = new QGroupBox;
		QVBoxLayout *layout = new QVBoxLayout;
		for each (auto var in sort_by_row)
		{
			std::string table_name = var.first;
			// 遍历表
			for each (auto var2 in var.second)
			{
				// 遍历行
				Cell_Station * cell_station_ = new Cell_Station;
				std::map<std::string, MyLabel*> tmp;
				tmp = cell_station_->setStorageLayout(var2.second, custom);
				for each (auto var in tmp)
				{
					mylabel_map_list_[table_name][var.first] = var.second;
				}
				stacked_layout->addWidget(cell_station_);
				//std::string tmp = var2.first;
				int cal_type = var2.first / 10000 % 10;
				QString type;
				switch (cal_type)
				{
				case 1:
					type = tr("Platform");
					break;
				case 2:
					type = tr("In");
					break;
				case 3:
					type = tr("Out");
					break;
				case 4:
					type = tr("Hoist");
					break;
				case 5:
					type = tr("Tray");
					break;
				case 6:
					type = tr("Trestle");
					break;
				case 7:
					type = tr("Parking");
					break;
				default:
					type = tr("ERROR");
					break;
				}
				combo->addItem(QString(tr("%1:F%2-R%3")).arg(type).arg(var2.first / 1000000, 2, 10, QChar('0')).arg(var2.first % 100, 2, 10, QChar('0')));
			}
		}
		//stacked_layout->addWidget(groupbox_);
		//combo->addItem(QString("A"));

		stacked_layout->setEnabled(true);
		setLayout(stacked_layout);
		connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboValueChanged(int)));
		return combo;
	}
	else
	{
		initDate();
		return nullptr;
	}
}

/// <summary>
/// Comboes the value changed.
/// </summary>
/// <param name="index">The index.</param>
/// Creator:MeiXu
/// CreateDate:2021/1/28
/// 
void Station_Monitor_NEW::ComboValueChanged(int index)
{// 选择下拉框，更换显示界面
	//stacked_layout.size
	stacked_layout->setCurrentIndex(index);
	return;
}