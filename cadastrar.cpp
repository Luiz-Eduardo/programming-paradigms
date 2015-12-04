//includes Classes do Desenvolvedor
#include "cadastrar.h"
#include "ui_cadastrar.h"
#include "conexao.h"

//includes Bibliotecas Qt
#include <QStandardItemModel>
#include <QStandardItem>
#include <QString>

Cadastrar::Cadastrar(QWidget *parent) : QMainWindow(parent), ui(new Ui::Cadastrar){
    ui->setupUi(this);

    /* Setando o título da janela como Cadastrar funcionários */
    this->setWindowTitle("Cadastrar funcionários");

    Conexao connection; //Instancia a classe Conexao.
    unsigned int tamanho = connection.selectEmployees(); //Método para selecionar os funcionários que retorna a quantidade de linhas.

    QStandardItemModel *model = new QStandardItemModel(tamanho, 5, this); //Quantidade de linhas recebida pelo metodo e 5 colunas.

    /* Setando os elementos da tabela como não editáveis. */
    ui->employeesView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /* Setando o nome das 5 colunas */
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Nome")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Idade")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Email")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Cargo")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Salário")));

    /* Preenchendo a tabela com a quantidade de linhas == tamanho */
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

    /* Setando o modelo da tableView (productsView) como o QStandardModel preenchido */
    ui->employeesView->setModel(model);

    /* Sinais e Slots */
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(addEmployee()));
    connect(ui->changeButton, SIGNAL(clicked()), this, SLOT(changEmployee()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(delEmployee()));
}

/* Destrutor da classe Cadastrar */
Cadastrar::~Cadastrar(){
    delete ui;
}

/* Slot addEmployee() da classe Cadastrar */
void Cadastrar::addEmployee(){
    newEmployee.show(); //Mostra a Interface Gráfica responsável por adicionar funcionários.
}

/* Slot changEmployee() da classe Cadastrar */
void Cadastrar::changEmployee(){
    changeEmployee.show(); //Mostra a Interface Gráfica responsável por alterar funcionários.
}

/* Slot delEmployee() da classe Cadastrar */
void Cadastrar::delEmployee(){
    deleteEmployee.show(); //Mostra a Interface Gráfica responsável por deletar funcionários.
}
