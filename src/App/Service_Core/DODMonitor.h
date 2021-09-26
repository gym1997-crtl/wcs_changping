#ifndef _DOD_Monitor_
#define _DOD_Monitor_

#include <QTableView>
#include <QAbstractItemModel>
#include <QTimer>

class ProgressBarDelegate;
class DataModel;
class QAbstractItemModel;

class DOD_Monitor : public QTableView
{
	Q_OBJECT
public:
	explicit DOD_Monitor(QWidget *parent = 0);
	DataModel* dataModel() {return m_model;}

	~DOD_Monitor();

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