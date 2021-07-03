# This file is a part of {{ dc045.manager }}.

# Developed for MVCS Office Manager.
# See the LICENSE file at the top-level directory of this distribution for license details.
# Licensed under the GNU General Public License V3
# C/2Lt Stephen Hamilton, Civil Air Patrol

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cadet.cpp \
    cadeteditor.cpp \
    changesmanager.cpp \
    dataconverter.cpp \
    datamanager.cpp \
    inspectioncard.cpp \
    inspectioneditor.cpp \
    itemsnapshot.cpp \
    main.cpp \
    mainwindow.cpp \
    supplyeditor.cpp \
    supplyitem.cpp \
    uuidgenerator.cpp \
    verticallabel.cpp

HEADERS += \
    cadet.h \
    cadeteditor.h \
    changesmanager.h \
    constants.h \
    dataconverter.h \
    datamanager.h \
    inspectioncard.h \
    inspectioneditor.h \
    item.h \
    itemsnapshot.h \
    mainwindow.h \
    serializable.h \
    supplyeditor.h \
    supplyitem.h \
    uuidgenerator.h \
    verticallabel.h

FORMS += \
    cadeteditor.ui \
    inspectioneditor.ui \
    mainwindow.ui \
    supplyeditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	Resources.qrc

DISTFILES += \
	CHANGELOG.md \
	TODO.md

RC_ICONS = imgs/MVCS-Office-Manager.ico
