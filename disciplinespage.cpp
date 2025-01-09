#include "disciplinespage.h"
#include "ui_disciplinespage.h"

#include <QMessageBox>

#include "datahandler.h"

#include <QDebug>

DisciplinesPage::DisciplinesPage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::DisciplinesPage)
{
	ui->setupUi(this);
	setTitle(tr("Дисциплина"));
	connect(ui->lw_disciplines, &QListWidget::currentItemChanged,
			[this] {
				m_isModified = true;
	});
}

DisciplinesPage::~DisciplinesPage()
{
	delete ui;
}

void DisciplinesPage::initializePage()
{
	DataHandler *handler = DataHandler::Instance();
	handler->setIsPlace(true);
	handler->setIsResult(true);
	fillDisciplines();
}

bool DisciplinesPage::validatePage()
{
	DataHandler *handler = DataHandler::Instance();
	if (ui->lw_disciplines->selectedItems().size() == 0) {
		QMessageBox::critical(this, "Ошибка", "Выберите дисциплину!");
		return false;
	}

	handler->setDisciplineId(ui->lw_disciplines->currentItem()->data(Qt::WhatsThisRole).toInt());

	if (m_isModified) {
		handler->clearNextPages(DISCIPLINE_PAGE);
		m_isModified = false;
	}
	return true;
}

int DisciplinesPage::nextId() const
{
	DataHandler *handler = DataHandler::Instance();
	if (handler->getIsResult()) {
		return RESULT_RECORD_PAGE;
	} else {
		return PLACE_RECORD_PAGE;
	}
}

void DisciplinesPage::fillDisciplines()
{
	QVector<DBManager::Item> resultData = DBManager::instance()->getData(DISCIPLINE_RESULT_REQUEST);
	resultData = filterResult(resultData);
	QVector<DBManager::Item> placeData = DBManager::instance()->getData(DISCIPLINE_PLACE_REQUEST);
	placeData = filterPlace(placeData);

	QVector<DBManager::Item> data = resultData;
	for (auto item : placeData) {
		if (!data.contains(item)) {
			data.push_back(item);
		}
	}
	ui->lw_disciplines->clear();
	for (int i = 0; i < data.size(); ++i) {
		QListWidgetItem *item = new QListWidgetItem();
		item->setData(Qt::DisplayRole, data[i].name);
		item->setData(Qt::WhatsThisRole, QVariant::fromValue(data[i].id));
		ui->lw_disciplines->addItem(item);
	}
	ui->lw_disciplines->clearSelection();
}

QVector<DBManager::Item> DisciplinesPage::filterResult(QVector<DBManager::Item> data)
{
	DataHandler *handler = DataHandler::Instance();
	QVector<int> sexId = handler->getSexId();
	int disciplineTypeId = handler->getDisciplineTypeId();
	QVector<int> ageGroupId = handler->getGroupAgeId();
	QVector<DBManager::Item> result;
	for (auto item : data) {

		if (!(item.baseItemsId["sex_id"] == sexId[0] || item.baseItemsId["sex_id"] == sexId[1])) {
			continue;
		}

		if (item.baseItemsId["discipline_type_id"] != disciplineTypeId) {
			continue;
		}

		if (!(item.baseItemsId["age_group_id"] == ageGroupId[0] || item.baseItemsId["age_group_id"] == ageGroupId[1])){
			continue;
		}

		if (result.contains(item)) {
			continue;
		}

		result.push_back(item);
	}

	if (result.size() == 0) {
		handler->setIsResult(false);
	}
	return result;
}

QVector<DBManager::Item> DisciplinesPage::filterPlace(QVector<DBManager::Item> data)
{
	DataHandler *handler = DataHandler::Instance();
	QVector<int> sexId = handler->getSexId();
	int disciplineTypeId = handler->getDisciplineTypeId();
	int competitionStatusId = handler->getCompetitionStatusId();
	QVector<int> ageGroupId = handler->getGroupAgeId();
	QVector<DBManager::Item> result;
	for (auto item : data) {

		if (!(item.baseItemsId["sex_id"] == sexId[0] || item.baseItemsId["sex_id"] == sexId[1])) {
			continue;
		}

		if (item.baseItemsId["discipline_type_id"] != disciplineTypeId) {
			continue;
		}

		if (!(item.baseItemsId["age_group_id"] == ageGroupId[0] || item.baseItemsId["age_group_id"] == ageGroupId[1])){
			continue;
		}

		if (item.baseItemsId["competition_status_id"] <= competitionStatusId) {
			continue;
		}

		if (result.contains(item)) {
			continue;
		}

		result.push_back(item);
	}

	if (result.size() == 0) {
		handler->setIsPlace(false);
	}
	return result;
}
