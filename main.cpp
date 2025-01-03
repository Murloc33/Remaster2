#include "mainwindow.h"
#include "intropage.h"
#include "shared_defs.h"

#include <QApplication>
#include <QWizard>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
//	MainWindow w;
//	w.show();
	QWizard wizard;
	wizard.setOptions(QWizard::IndependentPages);
	wizard.setPage( INTRO_PAGE , new IntroPage);
	wizard.show();
	return a.exec();
}
