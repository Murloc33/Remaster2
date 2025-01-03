#ifndef DISCIPLINETYPEPAGE_H
#define DISCIPLINETYPEPAGE_H

#include <QWizardPage>

namespace Ui {
class DisciplineTypePage;
}

class DisciplineTypePage : public QWizardPage
{
	Q_OBJECT

public:
	explicit DisciplineTypePage(QWidget *parent = nullptr);
	~DisciplineTypePage();

private:
	Ui::DisciplineTypePage *ui;


public:
	void initializePage();
	bool validatePage();
	int nextId() const;
};

#endif // DISCIPLINETYPEPAGE_H
