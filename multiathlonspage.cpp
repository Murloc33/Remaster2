#include "multiathlonspage.h"
#include "ui_multiathlonspage.h"

MultiathlonsPage::MultiathlonsPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MultiathlonsPage)
{
	ui->setupUi(this);
}

MultiathlonsPage::~MultiathlonsPage()
{
	delete ui;
}
