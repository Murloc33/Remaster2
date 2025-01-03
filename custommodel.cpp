#include "custommodel.h"

CustomModel::CustomModel()
{

}

int CustomModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return m_items.size();
}

QVariant CustomModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	int row = index.row();

	if (role == Qt::DisplayRole) {
		return QVariant(m_items[row].name);
	}

	if (role == Qt::WhatsThisRole) {
		return  QVariant(m_items[row].description);
	}

	return QVariant();
}

void CustomModel::addItems(QVector<DBManager::Item> items)
{
	beginResetModel();
	m_items = items;
	endResetModel();
}

void CustomModel::updateData(QVector<DBManager::Item> items)
{
	beginResetModel();
	m_items.clear();
	addItems(items);
	endResetModel();
}

size_t CustomModel::count()
{
	return m_items.size();
}

void CustomModel::clear()
{
	beginResetModel();
	m_items.clear();
	endResetModel();
}

DBManager::Item CustomModel::getItem(int index) const
{
	return m_items[index];
}
