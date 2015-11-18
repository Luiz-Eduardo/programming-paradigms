#ifndef GERENTE_H
#define GERENTE_H

#include <QMainWindow>
#include "caixa.h"
#include "cadastrar.h"

namespace Ui {
class Gerente;
}

class Gerente : public QMainWindow{
    Q_OBJECT

public:
    explicit Gerente(QWidget *parent = 0);
    ~Gerente();
    Caixa caixa;
    Cadastrar funcionario;

private slots:
    void vendas();
    void logout();
    void cadastrar();

private:
    Ui::Gerente *ui;
};

#endif // GERENTE_H
