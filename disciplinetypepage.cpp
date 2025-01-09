#include "disciplinetypepage.h"
#include "ui_disciplinetypepage.h"

#include <QMessageBox>

#include "shared_defs.h"
#include "datahandler.h"

DisciplineTypePage::DisciplineTypePage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::DisciplineTypePage)
{
	ui->setupUi(this);
	setTitle(tr("Вид дисциплины"));
	connect(ui->lw_discipilneType, &QListWidget::currentItemChanged,
			[this] {
				m_isModified = true;
	});
}

DisciplineTypePage::~DisciplineTypePage()
{
	delete ui;
}

void DisciplineTypePage::initializePage()
{
	QWizardPage().initializePage();
	fillDisciplinesType();
}

bool DisciplineTypePage::validatePage()
{
	DataHandler *handler = DataHandler::Instance();
	if (ui->lw_discipilneType->selectedItems().size() == 0) {
		QMessageBox::critical(this, "Ошибка", "Выберите вид дисциплины!");
		return false;
	}

	handler->setDisciplineTypeId(ui->lw_discipilneType->selectedItems()[0]->data(Qt::WhatsThisRole).toInt());

	if (m_isModified) {
		handler->clearNextPages(DISCIPLINE_TYPE_PAGE);
		m_isModified = false;
	}

	return true;
}

int DisciplineTypePage::nextId() const
{
	return DISCIPLINE_PAGE;
}

void DisciplineTypePage::fillDisciplinesType()
{
	QVector<DBManager::Item> resultData = DBManager::instance()->getData(DISCIPLINE_TYPES_RESULT_REQUEST);
	resultData = filterResult(resultData);
	QVector<DBManager::Item> placeData = DBManager::instance()->getData(DISCIPLINE_TYPES_PLACE_REQUEST);
	placeData = filterPlace(placeData);

	QVector<DBManager::Item> data = resultData;
	for (auto item : placeData) {
		if (!data.contains(item)) {
			data.push_back(item);
		}
	}


	ui->lw_discipilneType->clear();
	for (int i = 0; i < data.size(); ++i) {
		QListWidgetItem *item = new QListWidgetItem();
		item->setData(Qt::DisplayRole, data[i].name);
		item->setData(Qt::WhatsThisRole, QVariant::fromValue(data[i].id));
		ui->lw_discipilneType->addItem(item);
	}
	ui->lw_discipilneType->clearSelection();
}

QVector<DBManager::Item> DisciplineTypePage::filterResult(QVector<DBManager::Item> data)
{
	DataHandler *handler = DataHandler::Instance();
	QVector<int> sexId = handler->getSexId();
	QVector<int> ageGroupId = handler->getGroupAgeId();
	QVector<DBManager::Item> result;
	for (auto item : data) {

		if (!(item.baseItemsId["sex_id"] == sexId[0] || item.baseItemsId["sex_id"] == sexId[1])) {
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
	return result;
}

QVector<DBManager::Item> DisciplineTypePage::filterPlace(QVector<DBManager::Item> data)
{
	DataHandler *handler = DataHandler::Instance();
	QVector<int> sexId = handler->getSexId();
	QVector<int> ageGroupId = handler->getGroupAgeId();
	int competitionStatusId = handler->getCompetitionStatusId();
	QVector<DBManager::Item> result;
	for (auto item : data) {

		if (!(item.baseItemsId["sex_id"] == sexId[0] || item.baseItemsId["sex_id"] == sexId[1])) {
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
	return result;
}
