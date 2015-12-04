//includes Classes do Desenvolvedor
#include "gerente.h"
#include "ui_gerente.h"

/* Construtor da classe Gerente */
Gerente::Gerente(QWidget *parent) : QMainWindow(parent), ui(new Ui::Gerente){
    ui->setupUi(this);

    /* Setando o título da janela como Página do Gerente */
    this->setWindowTitle("Página do Gerente");

    /* Sinais e Slots */
    connect(ui->vendasButton, SIGNAL(clicked(bool)), this, SLOT(vendas()));
    connect(ui->cadastrarButton, SIGNAL(clicked(bool)), this, SLOT(cadastrar()));
    connect(ui->estoqueButton, SIGNAL(clicked(bool)), this, SLOT(estoque()));
    connect(ui->financasButton, SIGNAL(clicked(bool)), this, SLOT(financas()));
}

/* Destrutor da classe Gerente */
Gerente::~Gerente(){
    delete ui;
}

/* Slot vendas() da classe Gerente */
void Gerente::vendas(){
    caixa.show(); //Mostra a Interface Gráfica responsável pelas vendas.
}

/* Slot cadastrar() da classe Gerente */
void Gerente::cadastrar(){
    funcionario.show(); //Mostra a Interface Gráfica responsável por adicionar, alterar e excluir funcionários.
}

/* Slot estoque() da classe Gerente */
void Gerente::estoque(){
    produtos.show(); //Mostra a Interface Gráfica responsável pela alteração de produtos no estoque.
}

/* Slot financas() da classe Gerente */
void Gerente::financas(){
    balanco.show(); //Mostra a Interface Gráfica responsável pelas finanças.
}
