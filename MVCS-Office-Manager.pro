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
    src/item/cadet.cpp \
    src/widgets/editor/cadeteditor.cpp \
    src/changesmanager.cpp \
    src/dataconverter.cpp \
    src/datamanager.cpp \
    src/item/inspectioncard.cpp \
    src/widgets/editorinspectioneditor.cpp \
    src/itemsnapshot.cpp \
    src/main.cpp \
    src/widgets/mainwindow.cpp \
    src/widgets/editor/supplyeditor.cpp \
    src/item/supplyitem.cpp \
    src/uuidgenerator.cpp \
    src/widgets/verticallabel.cpp

HEADERS += \
    src/item/cadet.h \
    src/widgets/editor/cadeteditor.h \
    src/changesmanager.h \
    src/constants.h \
    src/dataconverter.h \
    src/datamanager.h \
    src/item/inspectioncard.h \
    src/widgets/editor/inspectioneditor.h \
    src/item/item.h \
    src/itemsnapshot.h \
    src/widgets/mainwindow.h \
    src/serializable.h \
    src/widgets/editor/supplyeditor.h \
    src/item/supplyitem.h \
    src/uuidgenerator.h \
    src/widgets/verticallabel.h

FORMS += \
    src/widgets/editor/cadeteditor.ui \
    src/widgets/editor/inspectioneditor.ui \
    src/widgets/mainwindow.ui \
    src/widgets/editor/supplyeditor.ui

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
