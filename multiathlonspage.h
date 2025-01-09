#ifndef MULTIATHLONSPAGE_H
#define MULTIATHLONSPAGE_H

#include <QWidget>

namespace Ui {
class MultiathlonsPage;
}

class MultiathlonsPage : public QWidget
{
	Q_OBJECT

public:
	explicit MultiathlonsPage(QWidget *parent = nullptr);
	~MultiathlonsPage();

private:
	Ui::MultiathlonsPage *ui;
};

#endif // MULTIATHLONSPAGE_H
