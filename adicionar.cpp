//includes das Classes criadas pelo Desenvolvedor
#include "adicionar.h"
#include "ui_adicionar.h"
#include "conexao.h"

//includes das Bibliotecas do Qt
#include <QRegExp>
#include <QMessageBox>

Adicionar::Adicionar(QWidget *parent) : QDialog(parent), ui(new Ui::Adicionar){
    ui->setupUi(this);
    this->setWindowTitle("Adicionar novo funcionário");
    connect(ui->cleanButton, SIGNAL(clicked(bool)), this, SLOT(clean()));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(add()));
}

Adicionar::~Adicionar(){
    delete ui;
}

void Adicionar::clean(){
    ui->nameEdit->setText("");
    ui->ageEdit->setText("");
    ui->cpfEdit->setText("");
    ui->salaryEdit->setText("");
    ui->roleEdit->setText("");
    ui->emailEdit->setText("");
    ui->addressEdit->setText("");
}

void Adicionar::add(){
    Conexao connection;

    QString name, age, role, salary, address, email, cpf;

    name = ui->nameEdit->text();
    age = ui->ageEdit->text();
    role = ui->roleEdit->text();
    salary = ui->salaryEdit->text();
    address = ui->addressEdit->text();
    email = ui->emailEdit->text();
    cpf = ui->cpfEdit->text();

    cpf = cpf.remove(QChar('.'), Qt::CaseInsensitive);
    cpf = cpf.remove(QChar('-'), Qt::CaseInsensitive);

    for(int i = 0; i < cpf.size(); i++){
        if(cpf[i] == '.' || cpf[i] == '-'){
            cpf[i] = cpf[i+1];
        }
    }

    role = role.toUpper();

    QMessageBox token;
    QRegExp valida("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    valida.setCaseSensitivity(Qt::CaseInsensitive);
    valida.setPatternSyntax(QRegExp::RegExp);

    if(!name.compare("") || !age.compare("") || !role.compare("") || !salary.compare("") || !address.compare("") || !email.compare("") || !cpf.compare("") ){ //Campos vazios.
        token.setText("Preencha todos os campos!");
        token.exec();
    } else if(age.size() > 2) { //Campo linePass com o tamanho maior que 2.
        token.setText("Digite uma idade válida!");
        token.exec();
    } else if(!valida.exactMatch(email)){
        token.setText("Digite um email válido");
        token.exec();
    } else {
        for(int i = 0; i < salary.size(); i++)
            if(salary[i] == ',')
                salary[i] = '.';

        bool flag = false;

        for(int i = 0; i < age.size(); i++)
            if(age[i] < '0' || age[i] > '9')
                flag = true;

        if(flag){
            token.setText("Digite uma idade válida!");
            token.exec();
        } else {
            if(!role.compare("GERENTE")){
                role = "2";
            } else if(!role.compare("CAIXA")){
                role = "1";
            } else {
                role = "0";
            }

            if(!connection.validaCpf(cpf)){
                token.setText("Digite um CPF válido!");
                token.exec();
            } else {
                connection.addEmployee(name, age, role, salary, cpf, email, address);
                ui->nameEdit->setText("");
                ui->ageEdit->setText("");
                ui->roleEdit->setText("");
                ui->salaryEdit->setText("");
                ui->cpfEdit->setText("");
                ui->emailEdit->setText("");
                ui->addressEdit->setText("");
                this->close();
            }

        }
    }
}
