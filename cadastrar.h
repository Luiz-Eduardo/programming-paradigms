#ifndef CADASTRAR_H
#define CADASTRAR_H

#include <QMainWindow>
#include <string>
#include <QStringList>

#include "adicionar.h"
#include "alterar.h"
#include "delete.h"

namespace Ui {
class Cadastrar;
}

class Cadastrar : public QMainWindow{
    Q_OBJECT
    Adicionar newEmployee;
    Alterar changeEmployee;
    Delete deleteEmployee;

public:
    explicit Cadastrar(QWidget *parent = 0);
    ~Cadastrar();
    QStringList funcionarios;

private slots:
    void adicionar();
    void back();
    void change();
    void delet();
private:
    Ui::Cadastrar *ui;
};

#endif // CADASTRAR_H
