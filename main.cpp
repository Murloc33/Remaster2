#include "mainwindow.h"
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
#include <QWizard>
#include <QObject>
#include <QPushButton>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
//	MainWindow w;
//	w.show();
	QVector<QWizardPage *> pages;
	QWizard wizard;
	wizard.setOptions(QWizard::IndependentPages);
	wizard.setOptions(QWizard::NoCancelButtonOnLastPage);
	wizard.setOption(QWizard::CancelButtonOnLeft);
	wizard.setStartId(INTRO_PAGE);

	wizard.setPage(INTRO_PAGE , new IntroPage);
	pages.push_back(wizard.page(INTRO_PAGE));
	wizard.page(INTRO_PAGE)->setButtonText(QWizard::NextButton, "Далее");
	wizard.page(INTRO_PAGE)->setButtonText(QWizard::BackButton, "Назад");
	wizard.page(INTRO_PAGE)->setButtonText(QWizard::CancelButton, "Отмена");

	wizard.setPage(COMPETITION_STATUS_PAGE , new CompetitionStatusesPage);
	pages.push_back(wizard.page(COMPETITION_STATUS_PAGE));
	wizard.page(COMPETITION_STATUS_PAGE)->setButtonText(QWizard::NextButton, "Далее");
	wizard.page(COMPETITION_STATUS_PAGE)->setButtonText(QWizard::BackButton, "Назад");
	wizard.page(COMPETITION_STATUS_PAGE)->setButtonText(QWizard::CancelButton, "Отмена");

	wizard.setPage(DISCIPLINE_TYPE_PAGE, new DisciplineTypePage);
	pages.push_back(wizard.page(DISCIPLINE_TYPE_PAGE));
	wizard.page(DISCIPLINE_TYPE_PAGE)->setButtonText(QWizard::NextButton, "Далее");
	wizard.page(DISCIPLINE_TYPE_PAGE)->setButtonText(QWizard::BackButton, "Назад");
	wizard.page(DISCIPLINE_TYPE_PAGE)->setButtonText(QWizard::CancelButton, "Отмена");

	wizard.setPage(DISCIPLINE_PAGE, new DisciplinesPage);
	pages.push_back(wizard.page(DISCIPLINE_PAGE));
	wizard.page(DISCIPLINE_PAGE)->setButtonText(QWizard::NextButton, "Далее");
	wizard.page(DISCIPLINE_PAGE)->setButtonText(QWizard::BackButton, "Назад");
	wizard.page(DISCIPLINE_PAGE)->setButtonText(QWizard::CancelButton, "Отмена");

	wizard.setPage(RESULT_RECORD_PAGE, new ResultRecordPage);
	pages.push_back(wizard.page(RESULT_RECORD_PAGE));
	wizard.page(RESULT_RECORD_PAGE)->setButtonText(QWizard::NextButton, "Далее");
	wizard.page(RESULT_RECORD_PAGE)->setButtonText(QWizard::BackButton, "Назад");
	wizard.page(RESULT_RECORD_PAGE)->setButtonText(QWizard::CancelButton, "Отмена");

	wizard.setPage(PLACE_RECORD_PAGE, new PlaceRecordPage);
	pages.push_back(wizard.page(PLACE_RECORD_PAGE));
	wizard.page(PLACE_RECORD_PAGE)->setButtonText(QWizard::NextButton, "Далее");
	wizard.page(PLACE_RECORD_PAGE)->setButtonText(QWizard::BackButton, "Назад");
	wizard.page(PLACE_RECORD_PAGE)->setButtonText(QWizard::CancelButton, "Отмена");


//	QObject::connect(wizard.button(QWizard::NextButton), &QPushButton::clicked,
//					 [&wizard] {
//						if (wizard.currentId() == FINAL_PAGE + 1) {
//							wizard.restart();
//						}

//	});

	wizard.setPage(FINAL_PAGE, new FinalPage);
	pages.push_back(wizard.page(FINAL_PAGE));
	wizard.page(FINAL_PAGE)->setButtonText(QWizard::FinishButton, "Завершить");
	wizard.page(FINAL_PAGE)->setButtonText(QWizard::BackButton, "Назад");
	wizard.page(FINAL_PAGE)->setButtonText(QWizard::CancelButton, "Отмена");



	DataHandler::Instance()->setWizardpages(pages);

	wizard.show();
	return a.exec();
}
