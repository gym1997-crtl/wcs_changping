#ifndef _TASK_MONITOR_ED_ZHANG_
#define _TASK_MONITOR_ED_ZHANG_

#include <QTableView>
#include <QAbstractItemModel>
#include <QTimer>


class DataModel;
class QAbstractItemModel;

class Task_Monitor : public QTableView
{
	Q_OBJECT
public:
	explicit Task_Monitor(QWidget *parent = 0);
	DataModel* dataModel() {return m_model;}

	~Task_Monitor();

//signals:

	public slots:
		void updateProgressValue();
		void popMenu(const QPoint&);
		void cancelOrder();
protected:
	void changeEvent(QEvent *event);
private:
	void iniData();
	void initTimer();
	void translatorUI();
private:
	DataModel *m_model;

	QTimer *timer;

};

#endif 