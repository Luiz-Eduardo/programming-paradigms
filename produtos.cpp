//includes das Classes criadas pelo Desenvolvedor
#include "produtos.h"
#include "ui_produtos.h"
#include "conexao.h"

//includes das Bibliotecas do Qt
#include <QString>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>

Produtos::Produtos(QWidget *parent) : QMainWindow(parent), ui(new Ui::Produtos){
    ui->setupUi(this);
    this->setWindowTitle("Cadastro de Produtos");
    connect(ui->exitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(add()));

    Conexao connection;
    unsigned int tamanho = connection.selectProducts();
    QStandardItemModel *model = new QStandardItemModel(tamanho,6,this); //Quantidade de linhas recebida pelo metodo e 5 colunas.
    ui->productsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Código")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Nome")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Preço de Compra")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Preço de Venda")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Quantidade em Estoque")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Valido até")));

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


    ui->productsView->setModel(model);

}

Produtos::~Produtos(){
    delete ui;
}

void Produtos::add(){
    Conexao conn;

    QString name = ui->nameEdit->text();
    QString validity = ui->validityEdit->text();
    QString purchasePrice = ui->purchaseEdit->text();
    QString sellPrice = ui->sellEdit->text();
    QString quantity = ui->quantityEdit->text();

    QRegExp valida("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/[12][0-9]{3}$");
    valida.setCaseSensitivity(Qt::CaseInsensitive);
    valida.setPatternSyntax(QRegExp::RegExp);


    QMessageBox token;

    if(!valida.exactMatch(validity)){
        token.setText("Digite uma data de validade válida");
        token.exec();
    } else {
        bool flag = false;

        for(int i = 0; i < sellPrice.size(); i++){
            if(sellPrice[i] < '0' || sellPrice[i] > '9')
                flag = true;
        }

        for(int i = 0; i < purchasePrice.size(); i++){
            if(purchasePrice[i] < '0' || purchasePrice[i] > '9')
                flag = true;
        }

        if(flag){
            token.setText("Digite apenas números nos preços.");
            token.exec();
        } else {
            bool flag = conn.insertProducts(name, purchasePrice, sellPrice, quantity, validity);

            if(flag){
                token.setText("Inserido com sucesso");

                Conexao connection;
                unsigned int tamanho = connection.selectProducts();
                QStandardItemModel *model = new QStandardItemModel(tamanho,6,this); //Quantidade de linhas recebida pelo metodo e 6 colunas.
                ui->productsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
                model->setHorizontalHeaderItem(0, new QStandardItem(QString("Código")));
                model->setHorizontalHeaderItem(1, new QStandardItem(QString("Nome")));
                model->setHorizontalHeaderItem(2, new QStandardItem(QString("Preço de Compra")));
                model->setHorizontalHeaderItem(3, new QStandardItem(QString("Preço de Venda")));
                model->setHorizontalHeaderItem(4, new QStandardItem(QString("Quantidade em Estoque")));
                model->setHorizontalHeaderItem(5, new QStandardItem(QString("Valido até")));

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


                ui->productsView->setModel(model);
                ui->sellEdit->setText("");
                ui->purchaseEdit->setText("");
                ui->nameEdit->setText("");
                ui->quantityEdit->setText("");
                ui->validityEdit->setText("");
            } else
                token.setText("Erro no sistema, contate o desenvolvedor");

            token.exec();
        }
    }
}
