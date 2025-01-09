#ifndef DISCIPLINESPAGE_H
#define DISCIPLINESPAGE_H

#include <QWizardPage>

#include "dbmanager.h"

namespace Ui {
class DisciplinesPage;
}

class DisciplinesPage : public QWizardPage
{
	Q_OBJECT

public:
	explicit DisciplinesPage(QWidget *parent = nullptr);
	~DisciplinesPage();

	void initializePage();
	bool validatePage();
	int nextId() const;

private:
	void fillDisciplines();
	QVector<DBManager::Item> filterResult(QVector<DBManager::Item> data);
	QVector<DBManager::Item> filterPlace(QVector<DBManager::Item> data);

private:
	Ui::DisciplinesPage	*ui;
	bool				m_isModified = false;
};

#endif // DISCIPLINESPAGE_H
