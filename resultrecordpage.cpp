#include "resultrecordpage.h"
#include "ui_resultrecordpage.h"

#include "datahandler.h"

#include <QMessageBox>
#include <QRegularExpressionValidator>

ResultRecordPage::ResultRecordPage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::ResultRecordPage)
{
	ui->setupUi(this);
	setTitle(tr("Результат"));
	QDoubleValidator *validator_1 = new QDoubleValidator(ui->le_result_1);
	validator_1->setNotation(QDoubleValidator::StandardNotation);
	ui->le_result_1->setValidator(validator_1);

	QDoubleValidator *validator_2 = new QDoubleValidator(ui->le_result_1);
	validator_2->setNotation(QDoubleValidator::StandardNotation);
	ui->le_result_1->setValidator(validator_2);

	QObject::connect(ui->cb_disciplineContents, &QComboBox::currentIndexChanged,
			[this] {
					m_isModified = true;
	});

	connect(ui->le_result_1, &QLineEdit::textChanged,
			[this] {
					m_isModified = true;
	});


	connect(ui->le_result_2, &QLineEdit::textChanged,
			[this] {
					m_isModified = true;
	});

}

ResultRecordPage::~ResultRecordPage()
{
	delete ui;
}

void ResultRecordPage::initializePage()
{
	ui->cb_disciplineContents->setEnabled(true);
	ui->l_disciplineContents->setEnabled(true);
	fillDisciplineContents();
	fillResult();
}

bool ResultRecordPage::validatePage()
{
	DataHandler *handler = DataHandler::Instance();
	if (ui->cb_disciplineContents->isEnabled()) {
		if (ui->cb_disciplineContents->currentIndex() == -1) {
			QMessageBox::critical(this, tr("Ошибка"), tr("Выберите уточнение дисциплины"));
			return false;
		}
	}

	if (ui->le_result_1->text().size() == 0 && ui->le_result_2->text().size() == 0) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Введите результат"));
		return false;
	}

	if (ui->cb_disciplineContents->isEnabled()) {
		handler->setDisciplineContentId(ui->cb_disciplineContents->currentData().toInt());
	}

	QVector<int> UM = handler->getUM();
	if (UM.contains(handler->getDisciplineId())) {
		handler->setResult(ui->le_result_1->text().toDouble() * 1000 +  ui->le_result_2->text().toDouble());
	} else {
		handler->setResult(ui->le_result_1->text().toDouble() * 60 +  ui->le_result_2->text().toDouble());
	}


	if (m_isModified) {
		handler->clearNextPages(RESULT_RECORD_PAGE);
		m_isModified = false;
	}

	return true;
}

int ResultRecordPage::nextId() const
{
	DataHandler *handler = DataHandler::Instance();
	if (handler->getIsPlace()) {
		return PLACE_RECORD_PAGE;
	} else {
		return FINAL_PAGE;
	}
}

void ResultRecordPage::fillDisciplineContents()
{
	QVector<DBManager::Item> data = DBManager::instance()->getData(DISCIPLINE_CONTENTS_REQUEST);
	data = filterDisciplineContents(data);
	ui->cb_disciplineContents->clear();
	for (int i = 0; i < data.size(); ++i) {
		ui->cb_disciplineContents->addItem(data[i].name, QVariant::fromValue(data[i].id));

	}

	ui->cb_disciplineContents->setCurrentIndex(-1);
}

void ResultRecordPage::fillResult()
{
	DataHandler *handler = DataHandler::Instance();
	QVector<int> UM = handler->getUM();
	if (UM.contains(handler->getDisciplineId())) {
		ui->le_result_1->setPlaceholderText("Километры");
		ui->le_result_2->setPlaceholderText("Метры");
	} else {
		ui->le_result_1->setPlaceholderText("Минуты");
		ui->le_result_2->setPlaceholderText("Секунды");
	}

	ui->le_result_1->clear();
	ui->le_result_2->clear();
}

QVector<DBManager::Item> ResultRecordPage::filterDisciplineContents(QVector<DBManager::Item> data)
{
	DataHandler *handler = DataHandler::Instance();
	QVector<int> sexId = handler->getSexId();
	QVector<int> ageGroupId = handler->getGroupAgeId();
	int disciplineId = handler->getDisciplineId();
	QVector<DBManager::Item> result;
	for (auto item : data) {

		if (!(item.baseItemsId["sex_id"] == sexId[0] || item.baseItemsId["sex_id"] == sexId[1])) {
			continue;
		}

		if (!(item.baseItemsId["age_group_id"] == ageGroupId[0] || item.baseItemsId["age_group_id"] == ageGroupId[1])){
			continue;
		}

		if (item.baseItemsId["discipline_id"] != disciplineId) {
			continue;
		}

		if (result.contains(item)) {
			continue;
		}

		result.push_back(item);

	}

	if (result.size() == 0 || (result.size() == 1 && result[0].id == 0)) {
		ui->cb_disciplineContents->setEnabled(false);
		ui->l_disciplineContents->setEnabled(false);
	}
	return result;
}
