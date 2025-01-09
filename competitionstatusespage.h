#ifndef COMPETITIONSTATUSESPAGE_H
#define COMPETITIONSTATUSESPAGE_H

#include <QWizardPage>

#include "datahandler.h"

namespace Ui {
class CompetitionStatusesPage;
}

class CompetitionStatusesPage : public QWizardPage
{
	Q_OBJECT

public:
	explicit CompetitionStatusesPage(QWidget *parent = nullptr);
	~CompetitionStatusesPage();
	void initializePage();
	bool validatePage();
	int nextId() const;
	QVector<Error> getErrors();

private:
	void fillCompetitionStatus();
	void addError(Error error);
	void clearError();

private:
	Ui::CompetitionStatusesPage	*ui;
	bool						m_isModified = false;
	QVector<Error>				m_errors = {};
};

#endif // COMPETITIONSTATUSESPAGE_H
