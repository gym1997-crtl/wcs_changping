#ifndef _Assign_Monitor_
#define _Assign_Monitor_

#include <QTableView>
#include <QAbstractItemModel>
#include <QTimer>

class ProgressBarDelegate;
class DataModel;
class QAbstractItemModel;

class Assign_Monitor : public QTableView
{
	Q_OBJECT
public:
	explicit Assign_Monitor(QWidget *parent = 0);
	DataModel* dataModel() {return m_model;}

	~Assign_Monitor();

public slots:
	
	void updateProgressValue();
	void popMenu(const QPoint&);
	void Revoke_Order();

protected:
	void changeEvent(QEvent *event);

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