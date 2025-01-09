#include "intropage.h"
#include "ui_intropage.h"
#include "dbmanager.h"
#include "custommodel.h"

#include <QMessageBox>
#include <QComboBox>
#include <QVariant>
#include <QMap>
#include <QObject>

IntroPage::IntroPage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::IntroPage)
{
	ui->setupUi(this);
	setTitle(tr("Личная инфрмация"));
	ui->chb_year->setVisible(false);
	ui->l_add->setVisible(false);
	connect(ui->cb_ageGroup, &QComboBox::currentIndexChanged,
			this, &IntroPage::slotUpdate); /*{
		m_isModified = true;
		ui->chb_year->setChecked(false);
		if (ui->cb_ageGroup->currentIndex() == 1) {
			ui->chb_year->setVisible(true);
			ui->l_add->setVisible(true);
		} else {
			ui->chb_year->setVisible(false);
			ui->l_add->setVisible(false);
		}
	});*/

	connect(ui->rb_m, &QRadioButton::clicked,
			[this] {
		m_isModified = true;
	});

	connect(ui->rb_w, &QRadioButton::clicked,
			[this] {
		m_isModified = true;
	});

	connect(ui->chb_year, &QCheckBox::stateChanged,
			[this] {
				m_isModified = true;
	});

}

IntroPage::~IntroPage()
{
	delete ui;
}

void IntroPage::fillAgeGroup()
{
	QVector<DBManager::Item> data = DBManager::instance()->getData(AGE_GROUP_REQUEST);
	for (int i = 0; i < data.size(); ++i) {
		ui->cb_ageGroup->addItem(data[i].name, QVariant::fromValue(data[i].id));
	}
	ui->cb_ageGroup->setCurrentIndex(-1);
}

void IntroPage::clearErros()
{
	DataHandler *handler = DataHandler::Instance();
	handler->deleteErrors(m_errors.size());
	m_errors.clear();
}

void IntroPage::slotUpdate(int in)
{
	m_isModified = true;
	ui->chb_year->setChecked(false);
	if (ui->cb_ageGroup->currentIndex() == 1) {
		ui->chb_year->setVisible(true);
		ui->l_add->setVisible(true);
	} else {
		ui->chb_year->setVisible(false);
		ui->l_add->setVisible(false);
	}
}

bool IntroPage::validatePage()
{
	clearErros();
	if (ui->cb_ageGroup->currentIndex() == -1) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Выберети возрастную группу!"));
		return false;
	}

	if (!(ui->rb_m->isChecked() || ui->rb_w->isChecked())) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Выберети пол!"));
		return false;
	}


	DataHandler *handler = DataHandler::Instance();

	bool isAG = handler->setGroupAgeId(ui->cb_ageGroup->currentData().toInt());
	if (!isAG) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Для получения КМС и МС возраст учатника должен быть не ниже 14!"));
		return false;
	}

	if (ui->rb_m->isChecked()) {
		handler->setSexId(1);
	} else {
		handler->setSexId(2);
	}

	if (ui->chb_year->isVisible() && !ui->chb_year->isChecked()) {
		m_errors.push_back({"Слишком маленький возраст для МС", ErrorType::MS});
	}

	handler->addErrors(m_errors);

	if (m_isModified) {
		handler->clearNextPages(INTRO_PAGE);
		m_isModified = false;
	}

	return true;
}

int IntroPage::nextId() const
{
	return COMPETITION_STATUS_PAGE;
}

void IntroPage::initializePage()
{
	QWizardPage().initializePage();
	fillAgeGroup();
}
