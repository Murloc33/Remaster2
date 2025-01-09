#ifndef FINALPAGE_H
#define FINALPAGE_H

#include <QWizardPage>

#include "datahandler.h"
#include "competitionstatusespage.h"
#include "placerecordpage.h"
#include "dbmanager.h"

namespace Ui {
class FinalPage;
}

class FinalPage : public QWizardPage
{
	Q_OBJECT

public:
	explicit FinalPage(QWidget *parent = nullptr);
	~FinalPage();

	void setPlacePage(PlaceRecordPage *placePage);
	void setStatusPage(CompetitionStatusesPage *statusPage);

	void initializePage();
	bool validatePage();
	int nextId() const;


	QVector<Error> getErrors();

private:
	void fillIcon();
	void fillErrors();
	void addError(Error error);
	void clearError();


	void checkSportCategory();
	QVector<DBManager::Item> filterResult(QVector<DBManager::Item> data);
	QVector<DBManager::Item> filterPlace(QVector<DBManager::Item> data);


private:
	Ui::FinalPage			*ui;
	bool					m_isCMS = true;
	bool					m_isMS = true;
	bool					m_isPlace = true;
	bool					m_isResult = true;
	CompetitionStatusesPage	*m_statusPage;
	PlaceRecordPage			*m_placePage;
	QVector<Error>			m_errors;
};

#endif // FINALPAGE_H
