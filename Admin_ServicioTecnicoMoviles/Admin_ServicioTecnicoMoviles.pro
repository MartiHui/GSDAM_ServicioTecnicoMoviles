#-------------------------------------------------
#
# Project created by QtCreator 2019-01-18T13:35:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Admin_ServicioTecnicoMoviles
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT += websockets
QT += xmlpatterns

INCLUDEPATH += ./source \
               ./header \
               ./ui

SOURCES += \
        source/main.cpp \
        source/mainwindow.cpp \
    source/serverconnection.cpp \
    source/action.cpp

HEADERS += \
        header/mainwindow.h \
    header/serverconnection.h \
    header/action.h \
    header/datainfo.h

FORMS += \
        ui/mainwindow.ui

copydata.commands = $(COPY_DIR) $$PWD/XML $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
