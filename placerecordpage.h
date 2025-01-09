#ifndef PLACERECORDPAGE_H
#define PLACERECORDPAGE_H

#include <QWizardPage>

#include "datahandler.h"

namespace Ui {
class PlaceRecordPage;
}

class PlaceRecordPage : public QWizardPage
{
	Q_OBJECT

public:
	explicit PlaceRecordPage(QWidget *parent = nullptr);
	~PlaceRecordPage();

	void initializePage();
	bool validatePage();
	int nextId() const;
	void clearError();
	QVector<Error> getErrors();

private:
	void addError(Error error);

private:
	Ui::PlaceRecordPage *ui;
	bool				m_isModified;
	QVector<Error>		m_errors = {};
};

#endif // PLACERECORDPAGE_H
