//includes Classes do Desenvolvedor
#include "produtos.h"
#include "ui_produtos.h"
#include "conexao.h"

//includes Bibliotecas Qt
#include <QString>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>

/* Construtor da classe Produtos */
Produtos::Produtos(QWidget *parent) : QMainWindow(parent), ui(new Ui::Produtos){
    ui->setupUi(this);

    /* Setando o título da janela como Cadastro de Produtos */
    this->setWindowTitle("Cadastro de Produtos");

    Conexao conn; //Instancia a classe Conexao.

    /* Sinais e Slots */
    connect(ui->exitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(add()));

    unsigned int tamanho = conn.selectProducts(); //Método para selecionar os produtos que retorna a quantidade de linhas.

    QStandardItemModel *model = new QStandardItemModel(tamanho, 6, this); //Quantidade de linhas recebida pelo metodo e 6 colunas.
    /* Setando os elementos da tabela como não editáveis. */
    ui->productsView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /* Setando o nome das 6 colunas */
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Código")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Nome")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Preço de Compra")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Preço de Venda")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Quantidade em Estoque")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Valido até")));

    /* Preenchendo a tabela com a quantidade de linhas == tamanho */
    for(unsigned int i = 0; i < tamanho; i++){
        QStandardItem *id = new QStandardItem(conn.products_id[i]);
        QStandardItem *name = new QStandardItem(conn.products_name[i]);
        QStandardItem *purchaseprice = new QStandardItem(conn.products_purchaseprice[i]);
        QStandardItem *sellprice = new QStandardItem(conn.products_saleprice[i]);
        QStandardItem *quantity = new QStandardItem(conn.products_quantity[i]);
        QStandardItem *validity = new QStandardItem(conn.products_validity[i]);

        model->setItem(i, 0, id);
        model->setItem(i, 1, name);
        model->setItem(i, 2, purchaseprice);
        model->setItem(i, 3, sellprice);
        model->setItem(i, 4, quantity);
        model->setItem(i, 5, validity);
    }

    /* Setando o modelo da tableView (productsView) como o QStandardModel preenchido */
    ui->productsView->setModel(model);

}

/* Destrutor da classe Produtos */
Produtos::~Produtos(){
    delete ui;
}

/* Slot add() da classe Produtos */
void Produtos::add(){
    Conexao conn; //Instancia a classe Conexao.

    /* Recebendo os valores inseridos nos campos */
    produto.name = ui->nameEdit->text();
    produto.validity = ui->validityEdit->text();
    produto.purchasePrice = ui->purchaseEdit->text();
    produto.sellPrice = ui->sellEdit->text();
    produto.quantity = ui->quantityEdit->text();

    /* Expressão regular responsável pela validação da validade do produto */
    QRegExp valida("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/[12][0-9]{3}$");
    valida.setCaseSensitivity(Qt::CaseInsensitive); //Setando a expressão regular como CaseInsesitive.
    valida.setPatternSyntax(QRegExp::RegExp); //Setando a sintaxe padrão como QRegExp.


    /* Símbolo responsável pela exibição de uma mensagem de controle */
    QMessageBox token;

    if(!valida.exactMatch(produto.validity)){ //Campo emailEdit diferente do aceitado pela Expressão regular.
        token.setText("Digite uma data de validade válida");
        token.exec();
    } else {
        bool flag = false;

        /* Conferindo se o preço de compra e venda possuem valores diferentes de números */
        for(int i = 0; i < produto.sellPrice.size(); i++){
            if(produto.sellPrice[i] < '0' || produto.sellPrice[i] > '9')
                flag = true;
        }

        for(int i = 0; i < produto.purchasePrice.size(); i++){
            if(produto.purchasePrice[i] < '0' || produto.purchasePrice[i] > '9')
                flag = true;
        }

        if(flag){
            token.setText("Digite apenas números nos preços.");
            token.exec();
        } else {
            /* Inserindo produtos */
            bool flag = conn.insertProducts(produto.name, produto.purchasePrice, produto.sellPrice, produto.quantity, produto.validity);

            if(flag){
                token.setText("Inserido com sucesso");

                /* Atualizando em tempo real a tabela de Produtos */
                Conexao connection; //Instancia a classe Conexao.

                unsigned int tamanho = connection.selectProducts(); //Método para selecionar os produtos que retorna a quantidade de linhas.

                QStandardItemModel *model = new QStandardItemModel(tamanho, 6, this); //Quantidade de linhas recebida pelo metodo e 6 colunas.

                /* Setando os elementos da tabela como não editáveis. */
                ui->productsView->setEditTriggers(QAbstractItemView::NoEditTriggers);

                /* Setando o nome das 6 colunas */
                model->setHorizontalHeaderItem(0, new QStandardItem(QString("Código")));
                model->setHorizontalHeaderItem(1, new QStandardItem(QString("Nome")));
                model->setHorizontalHeaderItem(2, new QStandardItem(QString("Preço de Compra")));
                model->setHorizontalHeaderItem(3, new QStandardItem(QString("Preço de Venda")));
                model->setHorizontalHeaderItem(4, new QStandardItem(QString("Quantidade em Estoque")));
                model->setHorizontalHeaderItem(5, new QStandardItem(QString("Valido até")));

                /* Preenchendo a tabela com a quantidade de linhas == tamanho */
                for(unsigned int i = 0; i < tamanho; i++){
                    QStandardItem *id = new QStandardItem(connection.products_id[i]);
                    QStandardItem *name = new QStandardItem(connection.products_name[i]);
                    QStandardItem *purchaseprice = new QStandardItem(connection.products_purchaseprice[i]);
                    QStandardItem *sellprice = new QStandardItem(connection.products_saleprice[i]);
                    QStandardItem *quantity = new QStandardItem(connection.products_quantity[i]);
                    QStandardItem *validity = new QStandardItem(connection.products_validity[i]);

                    model->setItem(i, 0, id);
                    model->setItem(i, 1, name);
                    model->setItem(i, 2, purchaseprice);
                    model->setItem(i, 3, sellprice);
                    model->setItem(i, 4, quantity);
                    model->setItem(i, 5, validity);
                }

                /* Setando o modelo da tableView (productsView) como o QStandardModel preenchido */
                ui->productsView->setModel(model);

                /* Setando os campos como vazios novamente */
                ui->sellEdit->setText("");
                ui->purchaseEdit->setText("");
                ui->nameEdit->setText("");
                ui->quantityEdit->setText("");
                ui->validityEdit->setText("");
            } else {
                token.setText("Erro no sistema, contate o desenvolvedor");
                token.exec();
            }
        }
    }
}
