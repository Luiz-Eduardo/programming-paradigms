//includes das Classes criadas pelo Desenvolvedor
#include "mainwindow.h"

//includes das Bibliotecas do Qt
#include <QApplication>


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
