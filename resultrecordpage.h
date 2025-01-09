#ifndef RESULTRECORDPAGE_H
#define RESULTRECORDPAGE_H

#include "dbmanager.h"

#include <QWizardPage>

namespace Ui {
class ResultRecordPage;
}

class ResultRecordPage : public QWizardPage
{
	Q_OBJECT

public:
	explicit ResultRecordPage(QWidget *parent = nullptr);
	~ResultRecordPage();

	void initializePage();
	bool validatePage();
	int nextId() const;

private:
	void fillDisciplineContents();
	void fillResult();
	QVector<DBManager::Item> filterDisciplineContents(QVector<DBManager::Item> data);


private:
	Ui::ResultRecordPage	*ui;
	bool					m_isModified;


};

#endif // RESULTRECORDPAGE_H
