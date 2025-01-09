QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	competitionstatusespage.cpp \
    datahandler.cpp \
	dbmanager.cpp \
	custommodel.cpp \
	disciplinespage.cpp \
	disciplinetypepage.cpp \
	finalpage.cpp \
    intropage.cpp \
    main.cpp \
    mainwindow.cpp \
	multiathlonspage.cpp \
	placerecordpage.cpp \
	resultrecordpage.cpp

HEADERS += \
	competitionstatusespage.h \
    datahandler.h \
	dbmanager.h \
	custommodel.h \
	disciplinespage.h \
	disciplinetypepage.h \
	finalpage.h \
    intropage.h \
    mainwindow.h \
	multiathlonspage.h \
	placerecordpage.h \
	resultrecordpage.h \
    shared_defs.h

FORMS += \
    competitionstatusespage.ui \
    disciplinespage.ui \
    disciplinetypepage.ui \
    finalpage.ui \
    intropage.ui \
    mainwindow.ui \
    multiathlonspage.ui \
    placerecordpage.ui \
    resultrecordpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	remasterResources.qrc
