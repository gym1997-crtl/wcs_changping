#ifndef _AGV_MONITOR_ED_ZHANG_
#define _AGV_MONITOR_ED_ZHANG_

#include <QTableView>
#include <QAbstractItemModel>
#include <QTimer>

class DataModel;
class QAbstractItemModel;

class AGV_Monitor : public QTableView
{
	Q_OBJECT
public:
	explicit AGV_Monitor(QWidget *parent = 0);
	DataModel* dataModel() {return m_model;}

	~AGV_Monitor();

//signals:

	public slots:
		void updateProgressValue();
		void popMenu(const QPoint&);
		void Lock_AGV();
		void Unlock_AGV();
		void invokeAGVParking();
	
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