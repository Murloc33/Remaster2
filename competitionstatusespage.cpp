#include "competitionstatusespage.h"
#include "ui_competitionstatusespage.h"

#include <QMessageBox>

#include "dbmanager.h"

CompetitionStatusesPage::CompetitionStatusesPage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::CompetitionStatusesPage)
{
	ui->setupUi(this);
	setTitle(tr("Статус сревнования"));
	connect(ui->lw_competitionStatus, &QListWidget::currentItemChanged,
			[this] {
				m_isModified = true;
				clearError();
	});
}

CompetitionStatusesPage::~CompetitionStatusesPage()
{
	delete ui;
}

void CompetitionStatusesPage::fillCompetitionStatus()
{
	QVector<DBManager::Item> data = DBManager::instance()->getData(COMPETITION_STATUSES_REQUEST);
	ui->lw_competitionStatus->clear();
	for (int i = 0; i < data.size(); ++i) {
		QListWidgetItem *item = new QListWidgetItem();
		item->setData(Qt::DisplayRole, data[i].name);
		item->setData(Qt::WhatsThisRole, QVariant::fromValue(data[i].id));
		ui->lw_competitionStatus->addItem(item);
	}
	ui->lw_competitionStatus->clearSelection();
}

void CompetitionStatusesPage::addError(Error error)
{
	m_errors.push_back(error);
}

void CompetitionStatusesPage::clearError()
{
	DataHandler *handler = DataHandler::Instance();
	handler->deleteErrors(m_errors.size());
	m_errors.clear();
}

void CompetitionStatusesPage::initializePage()
{
	QWizardPage().initializePage();
	fillCompetitionStatus();
	clearError();
}

bool CompetitionStatusesPage::validatePage()
{
	if (ui->lw_competitionStatus->selectedItems().size() == 0) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Выберите статус соревнования!"));
		return false;
	}

	DataHandler *handler = DataHandler::Instance();
	bool isCS = handler->setCompetitionStatusId(ui->lw_competitionStatus->selectedItems()[0]->data(Qt::WhatsThisRole).toInt());
	if (!isCS) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Для получения КМС и МС cтатус соревнования должен быть не ниже \"Другие соревнования субъекта Российской Федерации\""));
		return false;
	}

	if (handler->getCompetitionStatusId() >= 10) {
		m_errors.push_back({"Слижком низкий статус соревнования", ErrorType::MS});
	}

	if (m_isModified) {
		handler->clearNextPages(COMPETITION_STATUS_PAGE);
		m_isModified = false;
	}

	handler->addErrors(m_errors);
	return true;
}

int CompetitionStatusesPage::nextId() const
{
	return DISCIPLINE_TYPE_PAGE;
}

QVector<Error> CompetitionStatusesPage::getErrors()
{
	return m_errors;
}
