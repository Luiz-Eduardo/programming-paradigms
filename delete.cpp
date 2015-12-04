//includes das Classes criadas pelo Desenvolvedor
#include "delete.h"
#include "ui_delete.h"
#include "conexao.h"

//includes das Bibliotecas do Qt
#include <QMessageBox>

Delete::Delete(QWidget *parent) : QMainWindow(parent), ui(new Ui::Delete){
    ui->setupUi(this);
    this->setWindowTitle("Página de Demissão");
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(cancel()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(delEmployee()));
}

Delete::~Delete(){
    delete ui;
}

void Delete::cancel(){
    this->close();
}

void Delete::delEmployee(){
    Conexao conn;

    QString name = ui->nameEdit->text();
    QString email = ui->emailEdit->text();

    QMessageBox token;

    if(conn.delEmployees(name, email)){
        token.setText("Funcionário demitido com sucesso");
        token.exec();
        this->close();
    } else {
        token.setText("Funcionário não encontrado");
        token.exec();
    }
}
