//includes Classes do Desenvolvedor
#include "caixa.h"
#include "ui_caixa.h"
#include "conexao.h"

//includes Bibliotecas C++
#include <vector>
#include <string>
#include <sstream>

//includes Bibliotecas Qt
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>

using namespace std;

/* Construtor da classe Caixa */
Caixa::Caixa(QWidget *parent) : QMainWindow(parent), ui(new Ui::Caixa){
    ui->setupUi(this);

    /* Setando título da janela como Controle de Caixa */
    this->setWindowTitle("Controle de Caixa");

    /* Sinais e Slots */
    connect(ui->nextButton, SIGNAL(clicked(bool)), this , SLOT(nextPurchase()));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(addProduct()));

    /* Setando os campos como desativados */
    ui->saleEdit->setEnabled(false);

    /* Inicializando as variáveis total e tamanho */
    total = 0;
    tamanho = 0;
}

/* Destrutor da classe Caixa */
Caixa::~Caixa(){
    delete ui;
}

/* Slot nextPurchase() da classe Caixa */
void Caixa::nextPurchase(){
    /* Zerando todos os campos */
    ui->codeEdit->setText("");
    ui->quantityEdit->setText("");
    ui->payEdit->setText("");
    ui->saleEdit->setText("");
    ui->changeEdit->setText("");

    /* Zerando as variáveis total e tamanho */
    tamanho = 0;
    total = 0;
}

/* Slot addProduct() da classe Caixa */
void Caixa::addProduct(){
    Conexao conn; //Instancia da classe Conexao
    /* Recebe o valor pelo ID/Código */
    double valor = conn.getSellPrice(ui->codeEdit->text());

    /* Símbolo responsável pela exibição de uma mensagem de controle */
    QMessageBox token;

    /* Tratamento de erros */
    if(valor == -1){
        token.setText("Erro de conexão");
        token.exec();
    } else if(valor == -2){ // Tratamento de erros
        token.setText("Erro no sistema contate o desenvolvedor");
        token.exec();
    } else {
        /* Recebe o valor quantidade */
        QString _quantity = ui->quantityEdit->text();
        string quantity = _quantity.toUtf8().constData(); //typecasting QString >> string

        /* typecasting string >> stringstream >> int */
        stringstream buffer;
        buffer << quantity;

        int quantidade;
        buffer >> quantidade;

        /* Cálculo do Total */
        total += quantidade*valor;

        /* Setando o total, zerando o código e a quantidade */
        ui->saleEdit->setText("R$" + QString::number(total));
        ui->codeEdit->setText("");
        ui->quantityEdit->setText("");
    }
}
