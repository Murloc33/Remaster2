#ifndef CBMODEL_H
#define CBMODEL_H

#include <QAbstractItemModel>

#include "dbmanager.h"

class CustomModel : public QAbstractListModel
{
public:
	CustomModel();
	QVariant data(const QModelIndex &index, int role) const;
	void updateData(QVector<DBManager::Item> items);
	int rowCount(const QModelIndex &parent) const;
	void addItems(QVector<DBManager::Item> items);
	DBManager::Item getItem(int index) const;
	size_t count();
	void clear();

private:
	QVector<DBManager::Item> m_items;
};

#endif // CBMODEL_H
