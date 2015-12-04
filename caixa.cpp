//includes Classes do Desenvolvedor
#include "caixa.h"
#include "ui_caixa.h"
#include "conexao.h"

#include <vector>
#include <string>
#include <sstream>

//includes Bibliotecas Qt
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>

using namespace std;

Caixa::Caixa(QWidget *parent) : QMainWindow(parent), ui(new Ui::Caixa){
    ui->setupUi(this);
    this->setWindowTitle("Controle de Caixa");

    connect(ui->nextButton, SIGNAL(clicked(bool)), this , SLOT(nextPurchase()));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(addProduct()));
    ui->saleEdit->setEnabled(false);

    total = 0;
    tamanho = 0;
}

Caixa::~Caixa(){
    delete ui;
}

void Caixa::nextPurchase(){
    ui->codeEdit->setText("");
    ui->quantityEdit->setText("");
    ui->payEdit->setText("");
    ui->saleEdit->setText("");
    ui->changeEdit->setText("");
    tamanho = 0;
}

void Caixa::addProduct(){
    Conexao conn;
    double valor = conn.getSellPrice(ui->codeEdit->text());

    QMessageBox token;

    if(valor == -1){
        token.setText("Erro de conexão");
        token.exec();
    } else if(valor == -2){
        token.setText("Erro no sistema contate o desenvolvedor");
        token.exec();
    } else {
        QString _quantity = ui->quantityEdit->text();
        string quantity = _quantity.toUtf8().constData();

        stringstream buffer;
        buffer << quantity;

        int quantidade;
        buffer >> quantidade;

        total += quantidade*valor;

        ui->saleEdit->setText("R$" + QString::number(total));
        ui->codeEdit->setText("");
        ui->quantityEdit->setText("");
    }
}
