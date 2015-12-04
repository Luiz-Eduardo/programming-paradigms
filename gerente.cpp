//includes das Classes criadas pelo Desenvolvedor
#include "gerente.h"
#include "ui_gerente.h"

Gerente::Gerente(QWidget *parent) : QMainWindow(parent), ui(new Ui::Gerente){
    ui->setupUi(this);
    this->setWindowTitle("Página do Gerente");

    connect(ui->vendasButton, SIGNAL(clicked(bool)), this, SLOT(vendas()));
    connect(ui->cadastrarButton, SIGNAL(clicked(bool)), this, SLOT(cadastrar()));
    connect(ui->estoqueButton, SIGNAL(clicked(bool)), this, SLOT(estoque()));
    connect(ui->financasButton, SIGNAL(clicked(bool)), this, SLOT(financas()));
}

Gerente::~Gerente(){
    delete ui;
}

void Gerente::vendas(){
    caixa.show();
    this->close();
}

void Gerente::cadastrar(){
    funcionario.show();\
}

void Gerente::estoque(){
    produtos.show();
}

void Gerente::financas(){
    balanco.show();
}
