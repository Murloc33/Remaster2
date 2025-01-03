#include "intropage.h"
#include "ui_intropage.h"
#include "datahandler.h"
#include "dbmanager.h"
#include "custommodel.h"

#include <QMessageBox>
#include <QComboBox>
#include <QVariant>
#include <QMap>

IntroPage::IntroPage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::IntroPage)
{
	ui->setupUi(this);
	setTitle(tr("Основная информация"));

}

IntroPage::~IntroPage()
{
	delete ui;
}

void IntroPage::fillCompetitionStatus()
{
	QVector<DBManager::Item> data = DBManager::instance()->getData(COMPETITION_STATUSES_REQUEST);
	for (int i = 0; i < data.size(); ++i) {
		QListWidgetItem *item = new QListWidgetItem();
		item->setData(Qt::DisplayRole, data[i].name);
		item->setData(Qt::WhatsThisRole, QVariant::fromValue(data[i].id));
		ui->lw_copetitionStatus->addItem(item);
	}
}

void IntroPage::fillAgeGroup()
{
	QVector<DBManager::Item> data = DBManager::instance()->getData(AGE_GROUP_REQUEST);
	for (int i = 0; i < data.size(); ++i) {
		ui->cb_ageGroup->addItem(data[i].name, QVariant::fromValue(data[i].id));
	}
	ui->cb_ageGroup->setCurrentIndex(-1);
}

bool IntroPage::validatePage()
{
	if (ui->cb_ageGroup->currentIndex() == -1) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Выберети возрастную группу!"));
		return false;
	}

	if (!(ui->rb_m->isChecked() || ui->rb_w->isChecked())) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Выберети пол!"));
		return false;
	}

	if (ui->lw_copetitionStatus->selectedItems().size() == 0) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Выберети статус соревнований!"));
		return false;
	}

	DataHandler *handler = DataHandler::Instance();

	bool isAG = handler->setGroupAgeId(ui->cb_ageGroup->currentData().toInt());
	if (!isAG) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Для получения КМС или МС возраст учатника должен быть не ниже 14!"));
		return false;
	}

	bool isCS = handler->setCompetitionStatusId(ui->lw_copetitionStatus->currentItem()->data(Qt::WhatsThisRole).toInt());
	if (!isCS) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Для получения КМС или МС cтатус соревнований должен быть не ниже \"Другие соревнования субъекта Российской Федерации\""));
		return false;
	}


	return true;
}

int IntroPage::nextId() const
{
	return 1;
}

void IntroPage::initializePage()
{
	QWizardPage().initializePage();
	fillCompetitionStatus();
	fillAgeGroup();
}
