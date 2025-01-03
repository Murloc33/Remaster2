#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QVector>

class DataHandler
{
public:
	static DataHandler *Instance();

	void setSexId(int sexId);

	bool setGroupAgeId(int groupAgeId);
	bool setCompetitionStatusId(int сompetitionStatusId);

private:
	bool ageGroupValidate(int ageGroupId);
	bool сompetitionStatusValidate(int сompetitionStatusId);

	DataHandler();


private:
	QVector<int> m_groupAgeId = {0,3};
	QVector<int> m_sexId = {0, 7};
	int m_сompetitionStatusId = 0;

};

#endif // DATAHANDLER_H
