#include "dbmanager.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMap>

DBManager::DBManager()
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName("./remaster.db");
	m_db.open();
}

DBManager *DBManager::instance()
{
	static DBManager manager;
	return &manager;
}


QVector<DBManager::Item> DBManager::getData(QString request)
{
	QVector<DBManager::Item> result;
	QSqlQuery query(request);
	query.exec();



	QSqlRecord records = query.record();
	bool isDescription = checkDescription(records);

	while(query.next()) {
		DBManager::Item currentItem;

		currentItem.id = query.value("id").toInt();
		if (records.fieldName(1) == "name") {
			currentItem.name = query.value("name").toString();
		}


		if (isDescription) {
			currentItem.description = query.value("description").toString();
		}

		for(int i = 0; i < records.count(); ++i) {
			QString recordName = records.fieldName(i);

			if (recordName == "name" || recordName == "id" || recordName == "description") {
				continue;
			}

			if (recordName.contains("id")) {
				currentItem.baseItemsId.insert(recordName, query.value(recordName).toInt());
			} else {
				currentItem.otherInformation.insert(recordName, query.value(recordName).toInt());
			}
		}
		result.push_back(currentItem);
	}
	return result;
}


bool DBManager::checkDescription(QSqlRecord &rec)
{
	for (int i = 0; i < rec.count(); ++i) {
		if (rec.fieldName(i) == "description") {
			return true;
		}
	}

	return false;
}
