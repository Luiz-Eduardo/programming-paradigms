//includes Classes do Desenvolvedor
#include "alterar.h"
#include "ui_alterar.h"
#include "conexao.h"

//includes Bibliotecas Qt
#include <QMessageBox>

/* Construtor da classe Alterar */
Alterar::Alterar(QWidget *parent) : QMainWindow(parent), ui(new Ui::alterar){
    ui->setupUi(this);

    /* Setando o título da janela como Alterar funcionário */
    this->setWindowTitle("Alterar funcionário");

    /* Sinais e Slots */
    connect(ui->searchButton, SIGNAL(clicked(bool)), this, SLOT(searchEmployee()));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->updateButton, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->cleanButton, SIGNAL(clicked(bool)), this, SLOT(clean()));

    /* Setando os campos como desativados */
    ui->salaryEdit->setEnabled(false);
    ui->emailEdit->setEnabled(false);
    ui->addressEdit->setEnabled(false);
    ui->roleEdit->setEnabled(false);
}

/* Destrutor da classe Alterar */
Alterar::~Alterar(){
    delete ui;
}

/* Slot searchEmployee() da classe Aterar */
void Alterar::searchEmployee(){
    /* Pegando o nome do campo nameEdit */
    QString name = ui->nameEdit->text();
    QString cpf, email, address, role, salary;

    Conexao conn; //Instancia a classe Conexao.

    //Atribuindo o valor dos outros campos por referência através da seleção pelo campo nome.
    bool flag = conn.selectEmployee(name, cpf, email, address, role, salary);

    if(flag){
        /* Setando o valor nos campos */
        ui->cpfLabel->setText(cpf);
        ui->emailEdit->setText(email);
        ui->roleEdit->setText(role);
        ui->salaryEdit->setText(salary);
        ui->addressEdit->setText(address);

        /* Setando os campos como ativados */
        ui->salaryEdit->setEnabled(true);
        ui->emailEdit->setEnabled(true);
        ui->addressEdit->setEnabled(true);
        ui->roleEdit->setEnabled(true);
    } else {
        QMessageBox mensagem;

        mensagem.setWindowTitle("Controle de Estoque");
        mensagem.setText("Digite o nome do funcionário corretamente");
        mensagem.exec();

        /* Limpando os campos */
        ui->salaryEdit->setText("");
        ui->emailEdit->setText("");
        ui->cpfLabel->setText("");
        ui->roleEdit->setText("");
        ui->addressEdit->setText("");

        /* Setando os campos como desativados */
        ui->salaryEdit->setEnabled(false);
        ui->emailEdit->setEnabled(false);
        ui->addressEdit->setEnabled(false);
        ui->roleEdit->setEnabled(false);
    }
}

/* Slot update() da classe Aterar */
void Alterar::update(){
    Conexao conn; //Instancia a classe Conexao.

    /* Pega os valores de todos os campos */
    QString name = ui->nameEdit->text();
    QString cpf = ui->cpfLabel->text();
    QString salary = ui->salaryEdit->text();
    QString email = ui->emailEdit->text();
    QString address =ui->addressEdit->text();
    QString role = ui->roleEdit->text();

    /* Símbolo responsável pela exibição de uma mensagem de controle */
    QMessageBox token;

    if(conn.updateEmployee(name, cpf, salary, email, address, role)){ //Caso o retorno seja verdadeiro.
        token.setText("Funcionário alterado com sucesso");
        token.exec();
        this->close();
    } else { //Se não...
        token.setText("Erro no sistema contate o desenvolvedor");
        token.exec();
    }
}

/* Slot clean() da classe Aterar */
void Alterar::clean(){
    /* Limpando todos os campos */
    ui->nameEdit->setText("");
    ui->salaryEdit->setText("");
    ui->emailEdit->setText("");
    ui->cpfLabel->setText("");
    ui->roleEdit->setText("");
    ui->addressEdit->setText("");

    /* Setando os campos como desativados */
    ui->salaryEdit->setEnabled(false);
    ui->emailEdit->setEnabled(false);
    ui->addressEdit->setEnabled(false);
    ui->roleEdit->setEnabled(false);
}
