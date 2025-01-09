#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "intropage.h"
#include "disciplinetypepage.h"
#include "competitionstatusespage.h"
#include "disciplinespage.h"
#include "shared_defs.h"
#include "datahandler.h"
#include "resultrecordpage.h"
#include "placerecordpage.h"
#include "finalpage.h"
#include <QObject>
#include <QApplication>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QVector<QWizardPage *> pages;
	m_wizard = new QWizard(this);
	m_wizard->setOptions(QWizard::IndependentPages);

	m_wizard->setPage(INTRO_PAGE , new IntroPage);
	pages.push_back(m_wizard->page(INTRO_PAGE));

	m_wizard->setPage(COMPETITION_STATUS_PAGE , new CompetitionStatusesPage);
	pages.push_back(m_wizard->page(COMPETITION_STATUS_PAGE));

	m_wizard->setPage(DISCIPLINE_TYPE_PAGE, new DisciplineTypePage);
	pages.push_back(m_wizard->page(DISCIPLINE_TYPE_PAGE));

	m_wizard->setPage(DISCIPLINE_PAGE, new DisciplinesPage);
	pages.push_back(m_wizard->page(DISCIPLINE_PAGE));

	m_wizard->setPage(RESULT_RECORD_PAGE, new ResultRecordPage);
	pages.push_back(m_wizard->page(RESULT_RECORD_PAGE));

	m_wizard->setPage(PLACE_RECORD_PAGE, new PlaceRecordPage);
	pages.push_back(m_wizard->page(PLACE_RECORD_PAGE));

	m_wizard->setPage(FINAL_PAGE, new FinalPage);
	pages.push_back(m_wizard->page(FINAL_PAGE));


	DataHandler::Instance()->setWizardpages(pages);
	layout()->addWidget(m_wizard);

}

MainWindow::~MainWindow()
{
	delete ui;
}

