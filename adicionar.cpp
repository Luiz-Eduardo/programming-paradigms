//includes Classes do Desenvolvedor
#include "adicionar.h"
#include "ui_adicionar.h"
#include "conexao.h"

//includes Bibliotecas Qt
#include <QRegExp>
#include <QMessageBox>

/* Construtor da classe Adicionar */
Adicionar::Adicionar(QWidget *parent) : QDialog(parent), ui(new Ui::Adicionar){
    ui->setupUi(this);

    /* Setando o título da janela como Adicionar novo funcionário */
    this->setWindowTitle("Adicionar novo funcionário");

    /* Sinais e Slots */
    connect(ui->cleanButton, SIGNAL(clicked(bool)), this, SLOT(clean()));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(add()));
}

/* Destrutor da classe Adicionar */
Adicionar::~Adicionar(){
    delete ui;
}

/* Slot clean() da classe Adicionar */
void Adicionar::clean(){
    ui->nameEdit->setText(""); //Limpa o campo nameEdit.
    ui->ageEdit->setText(""); //Limpa o campo ageEdit.
    ui->cpfEdit->setText(""); //Limpa o campo cpfEdit.
    ui->salaryEdit->setText(""); //Limpa o campo salaryEdit.
    ui->roleEdit->setText(""); //Limpa o campo roleEdit.
    ui->emailEdit->setText(""); //Limpa o campo emailEdit.
    ui->addressEdit->setText(""); //Limpa o campo addressEdit.
}

/* Slot add() da classe Adicionar */
void Adicionar::add(){
    Conexao connection; //Instancia a classe Conexão.

    /* Recebendo os valores inseridos nos campos */
    funcionario.name = ui->nameEdit->text();
    funcionario.age = ui->ageEdit->text();
    funcionario.role = ui->roleEdit->text();
    funcionario.salary = ui->salaryEdit->text();
    funcionario.address = ui->addressEdit->text();
    funcionario.email = ui->emailEdit->text();
    funcionario.cpf = ui->cpfEdit->text();

    /* Removendo pontos e hífens no CPF antes de inserir no Banco de Dados */
    funcionario.cpf = funcionario.cpf.remove(QChar('.'), Qt::CaseInsensitive);
    funcionario.cpf = funcionario.cpf.remove(QChar('-'), Qt::CaseInsensitive);

    /* Colocando o campo cargo para maiúsculo antes de tratar o valor */
    funcionario.role = funcionario.role.toUpper();

    /* Símbolo responsável pela exibição de uma mensagem de controle */
    QMessageBox token;

    /* Expressão regular responsável pela validação do email */
    QRegExp valida("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    valida.setCaseSensitivity(Qt::CaseInsensitive); //Setando a Expressão Regular como CaseInsesitive.
    valida.setPatternSyntax(QRegExp::RegExp); //Setando a sintaxe padrão como QRegExp.

    if(!funcionario.name.compare("") || !funcionario.age.compare("") || !funcionario.role.compare("") || !funcionario.salary.compare("") || !funcionario.address.compare("") || !funcionario.email.compare("") || !funcionario.cpf.compare("") ){ //Campos vazios.
        token.setText("Preencha todos os campos!");
        token.exec();
    } else if(funcionario.age.size() != 2) { //Campo ageEdit com o tamanho diferente de 2 (menores de idade ou maiores de 100 anos).
        token.setText("Digite uma idade válida!");
        token.exec();
    } else if(!valida.exactMatch(funcionario.email)){ //Campo emailEdit diferente do aceitado pela Expressão regular.
        token.setText("Digite um email válido");
        token.exec();
    } else { //Campos preenchidos corretamente.
        /* Alterando a vírgula por ponto no salário antes de inserir no Banco de Dados */
        for(int i = 0; i < funcionario.salary.size(); i++)
            if(funcionario.salary[i] == ',')
                funcionario.salary[i] = '.';

        bool flag = false;

        //Caso o valor digitado na idade não tenha sido um número.
        for(int i = 0; i < funcionario.age.size(); i++)
            if(funcionario.age[i] < '0' || funcionario.age[i] > '9')
                flag = true;

        if(flag){
            token.setText("Digite uma idade válida!");
            token.exec();
        } else {
            if(!funcionario.role.compare("GERENTE"))
                funcionario.role = "2";
             else if(!funcionario.role.compare("CAIXA"))
                funcionario.role = "1";
             else
                funcionario.role = "0";

            /* Teste de validação do CPF */
            if(!connection.validaCpf(funcionario.cpf)){
                token.setText("Digite um CPF válido!");
                token.exec();
            } else {
                /* Símbolo responsável pela exibição de uma mensagem de controle */
                QMessageBox token;

                /* Adicionando o novo funcionário na Empresa */
                if(connection.addEmployee(funcionario.name, funcionario.age, funcionario.role, funcionario.salary, funcionario.cpf, funcionario.email, funcionario.address)){
                    token.setText("Funcionário inserido com sucesso");
                    token.exec();
                } else {
                    token.setText("Falha de Conexão");
                    token.exec();
                }

                /* Limpando todos os campos */
                ui->nameEdit->setText("");
                ui->ageEdit->setText("");
                ui->roleEdit->setText("");
                ui->salaryEdit->setText("");
                ui->cpfEdit->setText("");
                ui->emailEdit->setText("");
                ui->addressEdit->setText("");

                /* Fechando a janela */
                this->close();
            }
        }
    }
}
