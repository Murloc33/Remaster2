#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QMetaType>
#include <QMap>

#define AGE_GROUP_REQUEST "SELECT * FROM age_groups"
#define COMPETITION_STATUSES_REQUEST "SELECT * FROM competition_statuses"
#define SEX_REQUEST "SELECT * FROM sex WHERE id IN (1,2)"
#define DISCIPLINE_TYPES_RESULT_REQUEST "select discipline_types.id, discipline_types.name, based_on_result_records.sex_id, age_group_id from based_on_result_records inner join disciplines on disciplines.id = based_on_result_records.discipline_id inner join discipline_types on disciplines.discipline_type_id = discipline_types.id;"
#define DISCIPLINE_TYPES_PLACE_REQUEST "select discipline_types.id, discipline_types.name, sex_id, age_group_id, competition_status_id from based_on_place_records inner join based_on_place_disciplines on based_on_place_records.based_on_place_discipline_id = based_on_place_disciplines.id inner join adapter_disciplines on adapter_disciplines.based_on_place_discipline_id = based_on_place_disciplines.id inner join disciplines on disciplines.id = adapter_disciplines.discipline_id  inner join discipline_types on disciplines.discipline_type_id = discipline_types.id;"
#define DISCIPLINE_PLACE_REQUEST "select disciplines.id, disciplines.name, disciplines.discipline_type_id, sex_id, age_group_id, competition_status_id from based_on_place_records inner join based_on_place_disciplines on based_on_place_records.based_on_place_discipline_id = based_on_place_disciplines.id inner join adapter_disciplines on adapter_disciplines.based_on_place_discipline_id = based_on_place_disciplines.id inner join disciplines on disciplines.id = adapter_disciplines.discipline_id;"
#define DISCIPLINE_RESULT_REQUEST "select disciplines.id, disciplines.name, disciplines.discipline_type_id, based_on_result_records.sex_id, age_group_id from based_on_result_records inner join disciplines on disciplines.id = based_on_result_records.discipline_id;"
#define DISCIPLINE_CONTENTS_REQUEST "select discipline_contents.id, discipline_contents.name, discipline_id, based_on_result_records.sex_id, age_group_id from based_on_result_records left join discipline_contents on based_on_result_records.discipline_content_id = discipline_contents.id;"
#define RESULT_RECORD_REQUEST "select * from based_on_result_records;"
#define PLACE_RECORD_REQUEST "select id, competition_status_id, age_group_id, based_on_place_records.sport_category_id, place_from, place_by, min_count_participants, discipline_id from based_on_place_records inner join adapter_disciplines on based_on_place_records.based_on_place_discipline_id = adapter_disciplines.based_on_place_discipline_id;"

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
