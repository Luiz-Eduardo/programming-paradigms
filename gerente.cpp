#include "gerente.h"
#include "ui_gerente.h"

Gerente::Gerente(QWidget *parent) : QMainWindow(parent), ui(new Ui::Gerente) {
    ui->setupUi(this);
    this->setWindowTitle("Página do Gerente");

    connect(ui->vendasButton, SIGNAL(clicked(bool)), this, SLOT(vendas()));
    connect(ui->logoutButton, SIGNAL(clicked(bool)), this, SLOT(logout()));
    connect(ui->cadastrarButton, SIGNAL(clicked(bool)), this, SLOT(cadastrar()));
}

Gerente::~Gerente(){
    delete ui;
}

void Gerente::vendas(){
    caixa.show();
    this->close();
}

void Gerente::logout(){
}

void Gerente::cadastrar(){
    funcionario.show();
    this->close();
}
