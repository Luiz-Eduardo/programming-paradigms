#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "caixa.h"
#include "gerente.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void fechar();
    void entrar();

private:
    Ui::MainWindow *ui;
    Caixa caixa;
    Gerente gerente;
};

#endif // MAINWINDOW_H
