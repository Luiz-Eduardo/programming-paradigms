//includes das Classes criadas pelo Desenvolvedor
#include "cadastrar.h"
#include "ui_cadastrar.h"
#include "conexao.h"

//includes das Bibliotecas do Qt
#include <QStandardItemModel>
#include <QStandardItem>
#include <QString>

Cadastrar::Cadastrar(QWidget *parent) : QMainWindow(parent), ui(new Ui::Cadastrar){
    ui->setupUi(this);
    this->setWindowTitle("Cadastrar funcionários");


    Conexao connection;
    unsigned int tamanho = connection.funcionarios();

    QStandardItemModel *model = new QStandardItemModel(tamanho,5,this); //Quantidade de linhas recebida pelo metodo e 5 colunas.
    ui->employeesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Nome")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Idade")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Email")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Cargo")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Salário")));

    for(unsigned int i = 0; i < tamanho; i++){
        QStandardItem *name = new QStandardItem(QString(connection.employees_name[i]));
        QStandardItem *age = new QStandardItem(QString(connection.employees_age[i] + " anos"));
        QStandardItem *email = new QStandardItem(connection.employees_email[i]);

        QStandardItem *role;
        if(!connection.employees_role[i].compare("1"))
            role = new QStandardItem(QString("Caixa"));
        else if(!connection.employees_role[i].compare("2"))
            role = new QStandardItem(QString("Gerente"));
        else
            role = new QStandardItem(QString("Erro"));

        QString _salary = connection.employees_salary[i];
        for(int i = 0; i < _salary.size(); i++)
            if(_salary[i] == '.')
                _salary[i] = ',';
        QStandardItem *salary = new QStandardItem(QString("R$ " + _salary));

        model->setItem(i, 0, name);
        model->setItem(i, 1, age);
        model->setItem(i, 2, email);
        model->setItem(i, 3, role);
        model->setItem(i, 4, salary);
    }


    ui->employeesView->setModel(model);

   connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(adicionar()));
   connect(ui->changeButton, SIGNAL(clicked()), this, SLOT(change()));
   connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(delet()));
}

Cadastrar::~Cadastrar(){
    delete ui;
}

void Cadastrar::adicionar(){
    newEmployee.show();
}

void Cadastrar::back(){
    this->close();
}

void Cadastrar::change(){
    changeEmployee.show();
}

void Cadastrar::delet(){
    deleteEmployee.show();
}
