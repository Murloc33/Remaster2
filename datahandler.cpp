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

void DataHandler::setSexId(int sexId)
{
	m_sexId[0] =  sexId;
}

bool DataHandler::setCompetitionStatusId(int сompetitionStatusId)
{
	if (сompetitionStatusValidate(сompetitionStatusId)) {
		m_сompetitionStatusId = сompetitionStatusId;
		return true;
	}
	return false;
}

bool DataHandler::ageGroupValidate(int ageGroupId)
{
	return ageGroupId >= 2;
}

bool DataHandler::сompetitionStatusValidate(int сompetitionStatusId)
{
	return сompetitionStatusId <= 16;
}
