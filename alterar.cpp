//includes das Classes criadas pelo Desenvolvedor
#include "alterar.h"
#include "ui_alterar.h"
#include "conexao.h"

//includes das Bibliotecas do Qt
#include <QMessageBox>

Alterar::Alterar(QWidget *parent) : QMainWindow(parent), ui(new Ui::alterar){
    ui->setupUi(this);
    this->setWindowTitle("Alterar funcionário");
    connect(ui->searchButton, SIGNAL(clicked(bool)), this, SLOT(searchEmployee()));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->updateButton, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->cleanButton, SIGNAL(clicked(bool)), this, SLOT(clean()));

    ui->salaryEdit->setEnabled(false);
    ui->emailEdit->setEnabled(false);
    ui->addressEdit->setEnabled(false);
    ui->roleEdit->setEnabled(false);
}

Alterar::~Alterar(){
    delete ui;
}

void Alterar::searchEmployee(){
    QString name = ui->nameEdit->text();
    Conexao conn;

    QString cpf, email, address, role, salary;

    bool flag = conn.select(name, cpf, email, address, role, salary);

    if(flag){
        ui->cpfLabel->setText(cpf);
        ui->emailEdit->setText(email);
        ui->roleEdit->setText(role);
        ui->salaryEdit->setText(salary);
        ui->addressEdit->setText(address);

        ui->salaryEdit->setEnabled(true);
        ui->emailEdit->setEnabled(true);
        ui->addressEdit->setEnabled(true);
        ui->roleEdit->setEnabled(true);
    } else {
        QMessageBox mensagem;

        mensagem.setWindowTitle("Controle de Estoque");
        mensagem.setText("Digite o nome do funcionário corretamente");
        mensagem.exec();

        ui->salaryEdit->setText("");
        ui->emailEdit->setText("");
        ui->cpfLabel->setText("");
        ui->roleEdit->setText("");
        ui->addressEdit->setText("");

        ui->salaryEdit->setEnabled(false);
        ui->emailEdit->setEnabled(false);
        ui->addressEdit->setEnabled(false);
        ui->roleEdit->setEnabled(false);
    }
}

void Alterar::update(){
    Conexao conn;

    QString name = ui->nameEdit->text();
    QString cpf = ui->cpfLabel->text();
    QString salary = ui->salaryEdit->text();
    QString email = ui->emailEdit->text();
    QString address =ui->addressEdit->text();
    QString role = ui->roleEdit->text();

    QMessageBox token;

    if(conn.updateEmployee(name, cpf, salary, email, address, role)){
        token.setText("Funcionário alterado com sucesso");
        token.exec();
        this->close();
    } else {
        token.setText("Erro no sistema contate o desenvolvedor");
    }

    token.exec();

}

void Alterar::clean(){
    ui->nameEdit->setText("");
    ui->salaryEdit->setText("");
    ui->emailEdit->setText("");
    ui->cpfLabel->setText("");
    ui->roleEdit->setText("");
    ui->addressEdit->setText("");

    ui->salaryEdit->setEnabled(false);
    ui->emailEdit->setEnabled(false);
    ui->addressEdit->setEnabled(false);
    ui->roleEdit->setEnabled(false);
}
