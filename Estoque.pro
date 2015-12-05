QT  += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Estoque
TEMPLATE = app

# Using C++ 11 version
CONFIG += c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    conexao.cpp \
    caixa.cpp \
    gerente.cpp \
    adicionar.cpp \
    cadastrar.cpp \
    alterar.cpp \
    delete.cpp \
    produtos.cpp \
    financas.cpp

HEADERS  += mainwindow.h \
    conexao.h \
    caixa.h \
    gerente.h \
    adicionar.h \
    cadastrar.h \
    alterar.h \
    delete.h \
    produtos.h \
    financas.h

FORMS    += mainwindow.ui \
    caixa.ui \
    gerente.ui \
    adicionar.ui \
    cadastrar.ui \
    alterar.ui \
    delete.ui \
    produtos.ui \
    financas.ui

# sudo apt-get install libmysqlclient-dev
LIBS += -lmysqlclient
