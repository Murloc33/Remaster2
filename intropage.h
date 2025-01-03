#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QWizardPage>

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
	~IntroPage();

private:
	void fillCompetitionStatus();
	void fillAgeGroup();

private:
	Ui::IntroPage *ui;


public:
	bool validatePage();
	int nextId() const;
};

#endif // INTROPAGE_H
