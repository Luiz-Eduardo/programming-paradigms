QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Estoque
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    conexao.cpp \
    caixa.cpp \
    gerente.cpp \
    adicionar.cpp \
    cadastrar.cpp

HEADERS  += mainwindow.h \
    conexao.h \
    caixa.h \
    gerente.h \
    adicionar.h \
    cadastrar.h

FORMS    += mainwindow.ui \
    caixa.ui \
    gerente.ui \
    adicionar.ui \
    cadastrar.ui

LIBS += -lmysqlclient

RESOURCES += \
    resources.qrc
