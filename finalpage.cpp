#include "finalpage.h"
#include "ui_finalpage.h"

#include <QPushButton>

FinalPage::FinalPage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::FinalPage)
{
	ui->setupUi(this);
	setTitle("КМС и МС");
}

FinalPage::~FinalPage()
{
	delete ui;
}

void FinalPage::setPlacePage(PlaceRecordPage *placePage)
{
	m_placePage = placePage;
}

void FinalPage::setStatusPage(CompetitionStatusesPage *statusPage)
{
	m_statusPage = statusPage;
}

void FinalPage::initializePage()
{
	QWizardPage().initializePage();
	DataHandler *handler = DataHandler::Instance();
	fillIcon();
	m_isCMS = true;
	m_isMS = true;
	m_errors.clear();
	ui->l_cmsW->clear();
	ui->l_msW->clear();
	m_isPlace = handler->getIsPlace();
	m_isResult = handler->getIsResult();

	checkSportCategory();

	auto otherErrors = handler->getErrors();

	for (auto item : otherErrors) {
		m_errors.push_back(item);
	}

	QString messageCMS = "КМC не получен, потому что: ";
	QString messageMS = "МC не получен, потому что: ";
	for (auto item : m_errors) {


		if (item.type == ErrorType::MS) {
			messageMS += "\n    -" + item.message;
			ui->l_msW->setText(messageMS);
			m_isMS = false;
		}
	}

	for (auto item : m_errors) {
		if (m_isMS) {
			break;
		}
		if (item.type == ErrorType::CMS) {
			messageCMS += "\n    -" + item.message;
			ui->l_cmsW->setText(messageCMS);
			m_isCMS = false;
		}

	}

	if (!m_isMS) {
		ui->l_ms_i->setPixmap(QPixmap(":/resources/icons/close.svg"));
	}

	if (!m_isCMS) {
		ui->l_cms_i->setPixmap(QPixmap(":/resources/icons/close.svg"));
	}
 }

bool FinalPage::validatePage()
{
	return true;
}

int FinalPage::nextId() const
{

	return -1;
}

void FinalPage::fillIcon()
{
	ui->l_cms_i->setPixmap(QPixmap(":/resources/icons/done.svg"));
	ui->l_ms_i->setPixmap(QPixmap(":/resources/icons/done.svg"));
}

void FinalPage::addError(Error error)
{
	m_errors.push_back(error);
}

void FinalPage::checkSportCategory()
{
	QVector<DBManager::Item> data;
	DataHandler *handler = DataHandler::Instance();
	if (m_isResult) {
		QVector<DBManager::Item> data = DBManager::instance()->getData(RESULT_RECORD_REQUEST);
		data = filterResult(data);
		if (data.size() == 1) {
			if (data[0].baseItemsId["sport_category_id"] == 2) {
				addError({"На основании результатов нелзя получить МС в данной дисциплине", ErrorType::MS});
			} else {
				addError({"На основании результатов нелзя получить КМС в данной дисциплине", ErrorType::CMS});
			}
		}
		double result = handler->getResult();
		for (auto item : data) {
			if (handler->getUM().contains(handler->getDisciplineId())) {
				if (item.otherInformation["min_result"] <= result) {
//					if (item.baseItemsId["sport_category_id"] == 2) {
//						m_isCMS = true;
//					} else {
//						m_isMS = true;
//					}
				} else {
					if (item.baseItemsId["sport_category_id"] == 2) {
						addError({"Слишком маленький результат для КМС", ErrorType::CMS});
					} else {
						addError({"Слишком маленький результат для МС", ErrorType::MS});
					}
				}
			} else {
				if (item.otherInformation["min_result"] >= result) {
//					if (item.baseItemsId["sport_category_id"] == 2) {
//						m_isCMS = true;
//					} else {
//						m_isMS = true;
//					}
				} else {
					if (item.baseItemsId["sport_category_id"] == 2) {
						addError({"Слишком маленький результат для КМС", ErrorType::CMS});
					} else {
						addError({"Слишком маленький результат для МС", ErrorType::MS});
					}
				}
			}
		}
	}
	if (m_isPlace) {
		QVector<DBManager::Item> placeData = DBManager::instance()->getData(PLACE_RECORD_REQUEST);
		placeData = filterPlace(placeData);

		if (placeData.size() == 0) {
			addError({"Слишком маленькое количество участников для КМС", ErrorType::CMS});
			addError({"Слишком маленькое количество участников для МС", ErrorType::MS});
			return;
		}

//		if (placeData.size() == 1) {
//			if (placeData[0].baseItemsId["sport_category_id"] == 2) {
//				addError({"На основании места нелзя получить МС в данной дисциплине", ErrorType::MS});
//			} else {
//				addError({"На основании места нелзя получить КМС в данной дисциплине", ErrorType::CMS});
//			}
//		}

		int place = handler->getPlace();
		for (auto item : placeData) {
			if (item.otherInformation["place_from"] > place || item.otherInformation["place_by"] < place) {
				if (item.baseItemsId["sport_category_id"] == 2) {
					addError({"Неподходящее место для КМС", ErrorType::CMS});
				} else {
					addError({"Неподходящее место для МС", ErrorType::MS});
				}
			}
		}
	}
}

QVector<DBManager::Item> FinalPage::filterResult(QVector<DBManager::Item> data)
{

	DataHandler *handler = DataHandler::Instance();
	QVector<DBManager::Item> result;
	int discipline_id = handler->getDisciplineId();
	QVector<int> sex_id = handler->getSexId();
	QVector<int> age_group_id = handler->getGroupAgeId();
	int discipline_content_id = handler->getDisciplineContentId();
	for (auto item : data) {
		if (item.baseItemsId["discipline_id"] != discipline_id) {
			continue;
		}

		if (!(item.baseItemsId["sex_id"] == sex_id[0] || item.baseItemsId["sex_id"] == sex_id[1])) {
			continue;
		}

		if (!(item.baseItemsId["age_group_id"] == age_group_id[0] || item.baseItemsId["age_group_id"] == age_group_id[1])) {
			continue;
		}

		if (item.baseItemsId["discipline_id"] != discipline_id) {
			continue;
		}

		if (item.baseItemsId["discipline_content_id"] != discipline_content_id) {
			continue;
		}

		result.push_back(item);
	}

	return result;
}

QVector<DBManager::Item> FinalPage::filterPlace(QVector<DBManager::Item> data)
{
	DataHandler *handler = DataHandler::Instance();
	QVector<DBManager::Item> result;
	int discipline_id = handler->getDisciplineId();
	QVector<int> age_group_id = handler->getGroupAgeId();
	int competition_status_id = handler->getCompetitionStatusId();
	int min_count_participants = handler->getPlaceCount();
	for (auto item : data) {
		if (item.baseItemsId["discipline_id"] != discipline_id) {
			continue;
		}

		if (!(item.baseItemsId["age_group_id"] == age_group_id[0] || item.baseItemsId["age_group_id"] == age_group_id[1])) {
			continue;
		}

		result.push_back(item);
	}

	for (int i = 0;  i < result.size(); ++i) {
		if (result[i].baseItemsId["competition_status_id"] > competition_status_id) {
			if (i == 0) {
				competition_status_id = result[i].baseItemsId["competition_status_id"];
				break;
			}
			competition_status_id = result[i - 1].baseItemsId["competition_status_id"];
			break;
		}
	}

	QVector<DBManager::Item> newResult;

	bool isCMS = false;
	bool isMS = false;

	for (auto item : result) {
		if (item.baseItemsId["competition_status_id"] != competition_status_id) {
			continue;
		}

		if (item.baseItemsId["sport_category_id"] == 1) {
			isMS = true;
		} else {
			isCMS = true;
		}

		if (item.otherInformation["min_count_participants"] > min_count_participants) {
			continue;
		}

		newResult.push_back(item);
	}

	if (!isMS) {
		addError({"На основании результата нельзя получить МС в данной дисциплине", ErrorType::MS});
	}

	if (!isCMS) {
		addError({"На основании результата нельзя получить КМС в данной дисциплине", ErrorType::CMS});
	}

	result = newResult;
	if (result.size() == 0) {
		return {};
	}


	QVector<DBManager::Item> CMS;
	QVector<DBManager::Item> MS;

	for (auto item : result) {
		if (item.baseItemsId["sport_category_id"] == 1) {
			MS.push_back(item);
		} else {
			CMS.push_back(item);
		}
	}

	result.clear();


	DBManager::Item maxCMS;
	if (CMS.size() != 0) {
		maxCMS = CMS[0];
		for (auto item : CMS) {
			if (item.otherInformation["min_count_participants"] > maxCMS.otherInformation["min_count_participants"]) {
				maxCMS = item;
			}
		}

		result.push_back(maxCMS);
	} else if (isCMS){
		addError({"Неподходящее количество участников для КМС в данной дисциплине", ErrorType::CMS});
	}

	DBManager::Item maxMS;
	if (MS.size() != 0) {
		maxMS = MS[0];
		for (auto item : MS) {
			if (item.otherInformation["min_count_participants"] > maxMS.otherInformation["min_count_participants"]) {
				maxMS = item;
			}
		}
		result.push_back(maxMS);
	} else if (isMS){
		addError({"Неподходящее количество участников для МС в данной дисциплине", ErrorType::MS});
	}

	return result;
}
