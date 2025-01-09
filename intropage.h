#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QWizardPage>

#include "datahandler.h"
#include "shared_defs.h"

namespace Ui {
	class IntroPage;
}

class CustomModel;

class IntroPage : public QWizardPage
{
	Q_OBJECT

public:
	explicit IntroPage(QWidget *parent = nullptr);
	void initializePage();
	bool validatePage();
	int nextId() const;;
	~IntroPage();

private:
	void fillAgeGroup();
	void clearErros();
	void slotUpdate(int in);

private:
	Ui::IntroPage	*ui;
	bool			m_isModified = false;
	QVector<Error>	m_errors;
};

#endif // INTROPAGE_H
