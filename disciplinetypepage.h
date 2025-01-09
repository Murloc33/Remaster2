#ifndef DISCIPLINETYPEPAGE_H
#define DISCIPLINETYPEPAGE_H

#include <QWizardPage>

#include "dbmanager.h"

namespace Ui {
class DisciplineTypePage;
}

class DisciplineTypePage : public QWizardPage
{
	Q_OBJECT

public:
	explicit DisciplineTypePage(QWidget *parent = nullptr);
	~DisciplineTypePage();

	void initializePage();
	bool validatePage();
	int nextId() const;

private:
	void fillDisciplinesType();
	QVector<DBManager::Item> filterResult(QVector<DBManager::Item> data);
	QVector<DBManager::Item> filterPlace(QVector<DBManager::Item> data);

private:
	Ui::DisciplineTypePage	*ui;
	bool					m_isModified = false;
};

#endif // DISCIPLINETYPEPAGE_H
