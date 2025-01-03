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
		currentItem.name = query.value("name").toString();

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

//QVector<DBManager::itemInfo> DBManager::getDataWhere(QString request, QMap<QString, QVector<int>> args)
//{
//	QVector<DBManager::itemInfo> result;
//	request += " WHERE ";

//	for (auto arg = args.constBegin(); arg != args.constEnd(); ++arg) {
//		if (arg.value().size() > 1) {
//			request += arg.key() + " IN (";
//			for (int i = 0; i < arg.value().size(); ++i) {
//				request += QString::number(arg.value()[i]);
//				if ((i + 1) == arg.value().size()) {
//					request += ")";
//				} else {
//					request += ",";
//				}
//			}
//			request += ";";
//		} else {
//			request += arg.key() + " = :" + arg.key();

//			if (std::next(arg) == args.constEnd()) {
//				request += ";";
//			} else {
//				request += " AND ";
//			}
//		}
//	}

//	QSqlQuery query;
//	query.prepare(request);
//	qDebug() << request;

//	for (auto arg = args.constBegin(); arg != args.constEnd(); ++arg) {
//		if (arg.value().size() == 1) {
//			query.bindValue(":" + arg.key(), arg.value()[0]);
//		}

//		qDebug() << arg.key() << " " << arg.value();
//	}


//	query.exec();
//	QSqlRecord rec = query.record();

//	bool isDescription = checkDescription(rec);

//	while(query.next()) {
//		DBManager::itemInfo currentStruct;

//		currentStruct.name = query.value("name").toString();

//		if (isDescription) {
//			currentStruct.description = query.value("description").toString();
//		}

//		for (int i = 0; i < rec.count(); ++i) {
//			QString key = rec.fieldName(i);
//			if (key == "name" || key == "description") {
//				continue;
//			}

//			int value = query.value(key).toInt();
//			currentStruct.otherInfo.insert(key, value);
//		}

//		result.push_back(currentStruct);
//	}

//	return result;
//}

bool DBManager::checkDescription(QSqlRecord &rec)
{
	for (int i = 0; i < rec.count(); ++i) {
		if (rec.fieldName(i) == "description") {
			return true;
		}
	}

	return false;
}
