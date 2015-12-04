//includes das Classes criadas pelo Desenvolvedor
#include "financas.h"
#include "ui_financas.h"
#include "conexao.h"

//include da Classe de Manipulação de stringstreams
#include <sstream>

//includes das Bibliotecas do Qt
#include <QStandardItem>
#include <QStandardItemModel>

Financas::Financas(QWidget *parent) : QMainWindow(parent), ui(new Ui::Financas){
    ui->setupUi(this);
    this->setWindowTitle("Finanças da Empresa");

    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->expensesEdit, SIGNAL(textChanged(QString)), this, SLOT(showProfit()));
    employeePayment = 0;

    Conexao conn;

    unsigned int tamanho = conn.funcionarios();

    for(auto i : conn.employees_salary)
        employeePayment += i.toDouble();


    productExpenses = 0;

    Conexao secondConn;

    secondConn.selectProducts();

    for(int i = 0; i < secondConn.products_purchaseprice.size(); i++)
         productExpenses += (secondConn.products_purchaseprice[i].toDouble())*(secondConn.products_quantity[i].toDouble());

    ui->payEdit->setEnabled(false);
    ui->productsEdit->setEnabled(false);
    ui->totalEdit->setEnabled(false);

    ui->payEdit->setText("R$ " + QString::number(employeePayment));
    ui->productsEdit->setText("R$ " + QString::number(productExpenses));

    QStandardItemModel *model = new QStandardItemModel(tamanho, 3, this); //Quantidade de linhas recebida pelo metodo e 3 colunas.
    ui->employeesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Nome")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Cargo")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Salário")));

    for(unsigned int i = 0; i < tamanho; i++){
        QStandardItem *name = new QStandardItem(QString(conn.employees_name[i]));

        QStandardItem *role;
        if(!conn.employees_role[i].compare("1"))
            role = new QStandardItem(QString("Caixa"));
        else if(!conn.employees_role[i].compare("2"))
            role = new QStandardItem(QString("Gerente"));
        else
            role = new QStandardItem(QString("Erro"));

        QString _salary = conn.employees_salary[i];
        for(int i = 0; i < _salary.size(); i++)
            if(_salary[i] == '.')
                _salary[i] = ',';
        QStandardItem *salary = new QStandardItem(QString("R$ " + _salary));

        model->setItem(i, 0, name);
        model->setItem(i, 1, role);
        model->setItem(i, 2, salary);
    }


    ui->employeesView->setModel(model);
    total = 1000;
}

Financas::~Financas(){
    delete ui;
}

//Quando for digitado o campo Despesas Externas
//QString total =
//QString profit = (total -
//ui->profitEdit->setText()

void Financas::showProfit(){
    QString expenses = ui->expensesEdit->text();
    string gastos = expenses.toUtf8().constData();

    stringstream buffer;
    buffer << gastos;

    double prejuizo;
    buffer >> prejuizo;

    ui->profitEdit->setText("R$ " + QString::number(total - (prejuizo + employeePayment + productExpenses)));

}
