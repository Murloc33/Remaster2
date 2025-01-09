#include "datahandler.h"

DataHandler::DataHandler()
{
}

DataHandler *DataHandler::Instance()
{
	static DataHandler dataHandler;
	return &dataHandler;
}

bool DataHandler::setGroupAgeId(int groupAgeId)
{
	if (ageGroupValidate(groupAgeId)) {
		m_groupAgeId[0] = groupAgeId;
		return true;
	}
	return false;
}

QVector<int>DataHandler::getGroupAgeId()
{
	return m_groupAgeId;
}

void DataHandler::setSexId(int sexId)
{
	m_sexId[0] =  sexId;
}

QVector<int> DataHandler::getSexId()
{
	return m_sexId;
}

void DataHandler::setDisciplineTypeId(int disciplineTypeId)
{
	m_disciplineTypeId = disciplineTypeId;
}

int DataHandler::getDisciplineTypeId()
{
	return m_disciplineTypeId;
}

bool DataHandler::setCompetitionStatusId(int сompetitionStatusId)
{
	if (сompetitionStatusValidate(сompetitionStatusId)) {
		m_сompetitionStatusId = сompetitionStatusId;
		return true;
	}
	return false;
}

int DataHandler::getCompetitionStatusId()
{
	return m_сompetitionStatusId;
}

void DataHandler::setDisciplineId(int disciplineId)
{
	m_disciplineId = disciplineId;
}

int DataHandler::getDisciplineId()
{
	return m_disciplineId;
}

void DataHandler::setIsPlace(bool isPlace)
{
	m_isPlace = isPlace;
}

bool DataHandler::getIsPlace()
{
	return m_isPlace;
}

void DataHandler::setIsResult(bool isResult)
{
	m_isResult = isResult;
}

bool DataHandler::getIsResult()
{
	return m_isResult;
}

void DataHandler::setDisciplineContentId(int disciplineContentId)
{
	m_disciplineContentId = disciplineContentId;
}

int DataHandler::getDisciplineContentId()
{
	return m_disciplineContentId;
}

void DataHandler::setResult(double result)
{
	m_result = result;
}

double DataHandler::getResult()
{
	return m_result;
}

void DataHandler::setPlace(int place)
{
	m_place = place;
}

int DataHandler::getPlace()
{
	return m_place;
}

void DataHandler::setPlaceCount(int placeCount)
{
	m_placeCount = placeCount;
}

int DataHandler::getPlaceCount()
{
	return m_placeCount;
}

void DataHandler::setYear(bool isYear)
{
	m_isYear = isYear;
}

bool DataHandler::getYear()
{
	return m_isYear;
}


QVector<int> DataHandler::getUM()
{
	return m_UM;
}

void DataHandler::addErrors(QVector<Error> errors)
{
	for (auto error : errors) {
		m_errors.push_back(error);
	}
}

void DataHandler::deleteErrors(int count)
{
	for (int i = 0; i < count; ++i) {
		m_errors.pop_back();
	}
}

QVector<Error> DataHandler::getErrors()
{
	return m_errors;
}

void DataHandler::clearNextPages(pageId from)
{
	for (int i = from + 1; i <= pageId::FINAL_PAGE; ++i) {
		m_wizardPages[i]->initializePage();
	}
}

void DataHandler::setWizardpages(QVector<QWizardPage *> pages)
{
	m_wizardPages = pages;
}

bool DataHandler::ageGroupValidate(int ageGroupId)
{
	return ageGroupId >= 2;
}

bool DataHandler::сompetitionStatusValidate(int сompetitionStatusId)
{
	return сompetitionStatusId <= 16;
}
