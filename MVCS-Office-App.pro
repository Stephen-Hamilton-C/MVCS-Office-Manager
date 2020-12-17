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
    datamanager.cpp \
    inspectioncard.cpp \
    inspectioneditor.cpp \
    itemeditor.cpp \
    main.cpp \
    mainwindow.cpp \
    supplyitem.cpp \
    verticallabel.cpp

HEADERS += \
    cadet.h \
    cadeteditor.h \
    constants.h \
    datamanager.h \
    inspectioncard.h \
    inspectioneditor.h \
    itemeditor.h \
    mainwindow.h \
    supplyitem.h \
    verticallabel.h

FORMS += \
    cadeteditor.ui \
    inspectioneditor.ui \
    itemeditor.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	Resources.qrc
