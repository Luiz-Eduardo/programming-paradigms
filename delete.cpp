//includes Classes do Desenvolvedor
#include "delete.h"
#include "ui_delete.h"
#include "conexao.h"

//includes Bibliotecas Qt
#include <QMessageBox>

/* Construtor da classe Delete */
Delete::Delete(QWidget *parent) : QMainWindow(parent), ui(new Ui::Delete){
    ui->setupUi(this);

    /* Setando título da janela como Página de Demissão */
    this->setWindowTitle("Página de Demissão");

    /* Sinais e Slots */
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteEmployee()));
}

/* Destrutor da classe Delete */
Delete::~Delete(){
    delete ui;
}

/* Slot deleteEmployee() da classe Delete */
void Delete::deleteEmployee(){
    Conexao conn; //Instancia a classe Conexão.

    /* Pegando o nome e o email */
    QString name = ui->nameEdit->text();
    QString email = ui->emailEdit->text();

    /* Símbolo responsável pela exibição de uma mensagem de controle */
    QMessageBox token;

    if(conn.deleteEmployee(name, email)){ //Caso a conexão encontre o funcionário atráves do nome e email.
        token.setText("Funcionário demitido com sucesso");
        token.exec();
        this->close();
    } else { //Caso contrário.
        token.setText("Funcionário não encontrado");
        token.exec();
    }
}
