#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QWizardPage>
#include <QVector>
#include <QString>
#include <QObject>

#include <tuple>

#include "shared_defs.h"

enum ErrorType {
	CMS,
	MS
};

struct Error {
	QString message;
	ErrorType type;
};

class DataHandler : public QObject
{
	Q_OBJECT
public:
	static DataHandler *Instance();

	void setSexId(int sexId);
	QVector<int> getSexId();
	void setDisciplineTypeId(int disciplineTypeId);
	int getDisciplineTypeId();
	bool setGroupAgeId(int groupAgeId);
	QVector<int> getGroupAgeId();
	bool setCompetitionStatusId(int сompetitionStatusId);
	int getCompetitionStatusId();
	void setDisciplineId(int disciplineId);
	int getDisciplineId();
	void setIsPlace(bool isPlace);
	bool getIsPlace();
	void setIsResult(bool isResult);
	bool getIsResult();
	void setDisciplineContentId(int disciplineContentId);
	int getDisciplineContentId();
	void setResult(double result);
	double getResult();
	void setPlace(int place);
	int getPlace();
	void setPlaceCount(int placeCount);
	int getPlaceCount();
	void setYear(bool isYear);
	bool getYear();

	QVector<int> getUM();

	void addErrors(QVector<Error> errors);
	void deleteErrors(int count);
	QVector<Error> getErrors();

	void clearNextPages(pageId from);

	void setWizardpages(QVector<QWizardPage *> pages);

private:
	bool ageGroupValidate(int ageGroupId);
	bool сompetitionStatusValidate(int сompetitionStatusId);

	DataHandler();


private:
	QVector<QWizardPage *>	m_wizardPages;

	QVector<int>		m_groupAgeId = {0,7};
	QVector<int>		m_sexId = {0, 3};
	int					m_сompetitionStatusId = 0;
	int					m_disciplineTypeId = 0;
	int					m_disciplineId = 0;
	int					m_disciplineContentId = 0;
	double				m_result = 0;
	int					m_place = 0;
	int					m_placeCount = 0;

	bool									m_isCMS;
	bool									m_isMS;
	bool									m_isResult;
	bool									m_isPlace;
	bool									m_isYear = false;

	QVector<Error>							m_errors;

	QVector<int>							m_UM = {20, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57};
};

#endif // DATAHANDLER_H
