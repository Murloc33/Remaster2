#include "placerecordpage.h"
#include "ui_placerecordpage.h"

#include <QRegularExpressionValidator>
#include <QMessageBox>

PlaceRecordPage::PlaceRecordPage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::PlaceRecordPage)
{
	ui->setupUi(this);
	setTitle(tr("Результат"));
	QRegularExpressionValidator *validatorPlace = new QRegularExpressionValidator(QRegularExpression("[0-9]*"), ui->le_place);
	ui->le_place->setValidator(validatorPlace);
	QRegularExpressionValidator *validatorPlaceCount = new QRegularExpressionValidator(QRegularExpression("[0-9]*"), ui->le_place);
	ui->le_placeCount->setValidator(validatorPlaceCount);

	connect(ui->le_place, &QLineEdit::textEdited,
			[this] {
				m_isModified = true;
	});

	connect(ui->le_placeCount, &QLineEdit::textEdited,
			[this] {
				m_isModified = true;
	});

	connect(ui->rb_cms_5, &QRadioButton::clicked,
			[this] {
				m_isModified = true;
	});


	connect(ui->rb_ms_5, &QRadioButton::clicked,
			[this] {
				m_isModified = true;
	});
}

PlaceRecordPage::~PlaceRecordPage()
{
	delete ui;
}

void PlaceRecordPage::initializePage()
{
	clearError();
	DataHandler *handler = DataHandler::Instance();
	ui->le_place->clear();
	ui->le_placeCount->clear();
	ui->l_add->setVisible(false);
	ui->rb_cms_5->setVisible(false);
	ui->rb_ms_5->setVisible(false);
	ui->rb_cms_5->setChecked(false);
	ui->rb_ms_5->setChecked(false);

	if (handler->getDisciplineId() == 65 || handler->getDisciplineId() == 66 || handler->getDisciplineTypeId() == 6) {
		ui->l_add->setVisible(true);
		ui->rb_cms_5->setVisible(true);
		ui->rb_ms_5->setVisible(true);
	}
}

bool PlaceRecordPage::validatePage()
{
	DataHandler *handler = DataHandler::Instance();
	clearError();

	if (ui->le_placeCount->text().size() == 0) {
			QMessageBox::critical(this, tr("Ошибка"), tr("Введите количество участников"));
			return false;
	}

	if (ui->le_place->text().size() == 0) {
		QMessageBox::critical(this, tr("Ошибка"), tr("Введите место"));
		return false;
	}

	if (ui->l_add->isVisible()) {
		if (!(ui->rb_cms_5->isChecked() || ui->rb_ms_5->isChecked())) {
			QMessageBox::critical(this, tr("Ошибка"), tr("Чтобы получить МС или КМС нужно выбрать одно из дополнительных условий"));
			return false;
		}

		if (ui->rb_cms_5->isChecked()) {
			m_errors.push_back({"Недостаточно участников с МС", ErrorType::MS});
		}
	}


	handler->setPlace(ui->le_place->text().toInt());
	handler->setPlaceCount(ui->le_placeCount->text().toInt());


	handler->addErrors(m_errors);

	if (m_isModified) {
		handler->clearNextPages(PLACE_RECORD_PAGE);
		m_isModified = false;
	}
	return true;
}

int PlaceRecordPage::nextId() const
{
	return FINAL_PAGE;;
}

void PlaceRecordPage::clearError()
{
	DataHandler *handler = DataHandler::Instance();
	handler->deleteErrors(m_errors.size());
	qDebug() << "Place apge clearError error size" << m_errors.size();
	m_errors.clear();
}

QVector<Error> PlaceRecordPage::getErrors()
{
	return m_errors;
}

void PlaceRecordPage::addError(Error error)
{
	m_errors.push_back(error);
}
