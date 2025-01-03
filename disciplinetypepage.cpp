#include "disciplinetypepage.h"
#include "ui_disciplinetypepage.h"

DisciplineTypePage::DisciplineTypePage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::DisciplineTypePage)
{
	ui->setupUi(this);
}

DisciplineTypePage::~DisciplineTypePage()
{
	delete ui;
}
