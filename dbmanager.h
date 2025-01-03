#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QMetaType>
#include <QMap>

#define AGE_GROUP_REQUEST "SELECT * FROM age_groups"
#define COMPETITION_STATUSES_REQUEST "SELECT * FROM competition_statuses"
#define SEX_REQUEST "SELECT * FROM sex WHERE id IN (1,2)"
#define DISCIPLINE_TYPES_REQUEST "SELECT * FROM discipline_types"
#define DISCIPLINE_REQUEST "SELECT * FROM disciplines"
#define DISCIPLINE_CONTENTS_REQUEST "SELECT discipline_contents.id, discipline_contents.name, based_on_result_records.sex_id, based_on_result_records.age_group_id, based_on_result_records.discipline_id FROM based_on_result_records INNER JOIN discipline_contents ON discipline_contents.id = based_on_result_records.discipline_content_id;"
#define PLACE_REQUEST "select * from based_on_place_records inner join adapter_disciplines on adapter_disciplines.based_on_place_discipline_id = based_on_place_records.based_on_place_discipline_id inner join sport_categories on based_on_place_records.sport_category_id = sport_categories.id"
#define RESULT_REQUEST "SELECT * FROM based_on_result_records INNER JOIN sport_categories ON based_on_result_records.sport_category_id = sport_categories.id;"

class DBManager
{

public:
	struct Item
	{
		int64_t id;
		QString name;
		QString description = "";
		QMap<QString, int> baseItemsId;
		QMap<QString, int> otherInformation;

		bool operator==(const Item& other) const {
			return (id == other.id);
		}
	};

public:
	static DBManager *instance();

	QVector<Item> getData(QString request);

	bool checkDescription(QSqlRecord &rec);

private:
	DBManager();

private:
	template<typename data>
	QVariant fillStruct(QSqlQuery &query);

private:
	QSqlDatabase m_db;
};

Q_DECLARE_METATYPE(DBManager::Item)


#endif // DBMANAGER_H
