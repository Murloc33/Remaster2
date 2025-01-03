QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datahandler.cpp \
	dbmanager.cpp \
	custommodel.cpp \
	disciplinetypepage.cpp \
    intropage.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    datahandler.h \
	dbmanager.h \
	custommodel.h \
	disciplinetypepage.h \
    intropage.h \
    mainwindow.h \
    shared_defs.h

FORMS += \
    disciplinetypepage.ui \
    intropage.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	remasterResources.qrc
