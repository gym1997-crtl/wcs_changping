#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>

class DataModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit DataModel(QObject *parent = 0);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void setHorizontalHeader(const QVariantList& headers);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	void setData(const QVector<QVariantList>& data);
	void setDodData(const QVector<QVariantList>& data);
	QVector<QVariantList> DataVector();
	~DataModel(void);
	QVariantList m_HorizontalHeader;
	QVector<QVariantList> m_data;
signals:

public slots:

private:


};
class SpecialDataModel : public DataModel
{
	Q_OBJECT
public:
	explicit SpecialDataModel(QObject *parent = 0);
	~SpecialDataModel(void);
	QVariant data(const QModelIndex &index, int role) const;
	void setDataColor(Qt::GlobalColor data);
	void sort(int column, Qt::SortOrder order);
	bool lessThan(const QVariant & left, const QVariant & right) const;
	Qt::GlobalColor QCdata_;
signals:

public slots:

private:
};
#endif 