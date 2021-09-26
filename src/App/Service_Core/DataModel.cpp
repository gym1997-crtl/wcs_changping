#include "DataModel.h"
#include <QAbstractTableModel>
#include <QBrush>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <sstream>
#include "iostream"
#include "comdef.h"
DataModel::DataModel(QObject *parent) :QAbstractTableModel(parent)
{

}

DataModel::~DataModel()
{

}


int DataModel::rowCount(const QModelIndex &parent) const
{
	return m_data.size();
}

int DataModel::columnCount(const QModelIndex &parent) const
{
	return m_HorizontalHeader.count();
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (role == Qt::TextAlignmentRole)
	{
		return int(Qt::AlignHCenter | Qt::AlignVCenter);
	}
	if (role == Qt::DisplayRole) {
		int ncol = index.column();
		int nrow = index.row();
		QVariantList values = m_data.at(nrow);

		if (values.size() > ncol)
			return values.at(ncol);
		else
			return QVariant();
	}
	if (role == Qt::BackgroundRole)
	{

	}
	return QVariant();
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	Qt::ItemFlags flag = QAbstractItemModel::flags(index);

	// flag|=Qt::ItemIsEditable // ���õ�Ԫ��ɱ༭,�˴�ע��,��Ԫ���޷����༭
	return flag;
}

void DataModel::setHorizontalHeader(const QVariantList &headers)
{
	m_HorizontalHeader = headers;
}


QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		return m_HorizontalHeader.at(section);
	}
	return QAbstractTableModel::headerData(section, orientation, role);
}

void DataModel::setData(const QVector<QVariantList> &data)
{
	try
	{
		m_data = data;
		emit layoutAboutToBeChanged();
		emit layoutChanged();
	}
	catch (_com_error &e) {

		std::stringstream ss;
		ss << e.ErrorMessage() << "setData" << e.Description();
	}
}

QVector<QVariantList> DataModel::DataVector()
{
	return m_data;

}

SpecialDataModel::SpecialDataModel(QObject *parent) :DataModel(parent)
{

}

SpecialDataModel::~SpecialDataModel()
{

}

QVariant SpecialDataModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (role == Qt::TextAlignmentRole)
	{
		return int(Qt::AlignHCenter | Qt::AlignVCenter);
	}
	if (role == Qt::DisplayRole) {
		int ncol = index.column();
		int nrow = index.row();
		QVariantList values = m_data.at(nrow);

		if (values.size() > ncol)
			return values.at(ncol);
		else
			return QVariant();
	}
	if (role == Qt::BackgroundRole)
	{
		
		if (index.column() == 4 && m_data.at(index.row()).at(4).toString() == "ERR")
		{
			return QColor(Qt::red);
		}
		else if (index.column() == 4 && m_data.at(index.row()).at(4).toString() == "DOING")
		{
			return QColor(Qt::yellow);
		}
		else if (index.column() == 4 && m_data.at(index.row()).at(4).toString() == "DONE")
		{
			return QColor(Qt::green);
		}
		else if (index.column() == 4 && m_data.at(index.row()).at(4).toString() == "NEW")
		{
			return QColor(Qt::cyan);
		}
	}
	return QVariant();
}

void SpecialDataModel::setDataColor(Qt::GlobalColor data)
{
	QCdata_ = data;
}

void SpecialDataModel::sort(int column, Qt::SortOrder order)
{
	if (m_data.isEmpty() || column < 0 || column >= columnCount())
		return;
	//�ж�������order
	const bool is_asc = (order == Qt::AscendingOrder);
	//����
	std::sort(m_data.begin(), m_data.end(),
		[column, is_asc, this](const QVariantList &left, const QVariantList &right) {
		//����QVariantֻ������ǰ�Ļ����ϸĵģ��Զ������Ϳ��Բ������
		//������赥Ԫ�����ݶ����������͵�
		const QVariant left_val = left.at(column);
		const QVariant right_val = right.at(column);

		//�����ӿڣ�a<b����true
		return is_asc
			? lessThan(left_val, right_val)
			: lessThan(right_val, left_val);
	});
	//����view
	dataChanged(index(0, 0), index(m_data.count() - 1, columnCount() - 1));
	return;
}

bool SpecialDataModel::lessThan(const QVariant &left, const QVariant &right) const
{
	//����QAbstractItemModelPrivate::isVariantLessThan��ʵ��
	//��Щ����ͨ���͵��������һ�����ǻ����Զ�������󣬱�������ַ����е���������
	//��Щ������Ҫ����ͷ�ļ�����ʹ�ã���datetime
	if (left.userType() == QMetaType::UnknownType)
		return false;
	if (right.userType() == QMetaType::UnknownType)
		return true;
	switch (left.userType()) {
	case QMetaType::Int:
		return left.toInt() < right.toInt();
	case QMetaType::UInt:
		return left.toUInt() < right.toUInt();
	case QMetaType::LongLong:
		return left.toLongLong() < right.toLongLong();
	case QMetaType::ULongLong:
		return left.toULongLong() < right.toULongLong();
	case QMetaType::Float:
		return left.toFloat() < right.toFloat();
	case QMetaType::Double:
		return left.toDouble() < right.toDouble();
	case QMetaType::QChar:
		return left.toChar() < right.toChar();
	case QMetaType::QDate:
		return left.toDate() < right.toDate();
	case QMetaType::QTime:
		return left.toTime() < right.toTime();
	case QMetaType::QDateTime:
		return left.toDateTime() < right.toDateTime();
	case QMetaType::QString: break;
	default: printf("%d", left.userType());
	}
	//Locale��ʾ֧�ֱ����ַ���
	//if (isLocaleAware)
	return left.toString().localeAwareCompare(right.toString()) < 0;
	//else
	//   return left.toString().compare(right.toString(), cs) < 0;
}