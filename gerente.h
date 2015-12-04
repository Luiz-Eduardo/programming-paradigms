#ifndef GERENTE_H
#define GERENTE_H

#include <QMainWindow>
#include "caixa.h"
#include "cadastrar.h"
#include "produtos.h"
#include "financas.h"

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
    Produtos produtos;
    Financas balanco;

private slots:
    void vendas();
    void cadastrar();
    void estoque();
    void financas();

private:
    Ui::Gerente *ui;
};

#endif // GERENTE_H
