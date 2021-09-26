#ifndef _Order_Monitor_
#define _Order_Monitor_
#include <QTableView>
#include <QAbstractItemModel>
#include <QTimer>

class ProgressBarDelegate;
class DataModel;
class QAbstractItemModel;

class Order_Monitor : public QTableView
{
	Q_OBJECT
public:
	explicit Order_Monitor(QWidget *parent = 0);
	DataModel* dataModel() {return m_model;}

	~Order_Monitor();

//signals:

	public slots:
		void updateProgressValue();

protected:
	void changeEvent(QEvent *evnet);

private:
	void iniData();
	void initTimer();
	void translatorUI();

private:
	DataModel *m_model;

	QTimer *timer;

	ProgressBarDelegate *m_progressBarDelegate;
};

#endif 