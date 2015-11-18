#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "conexao.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowTitle("Login Page");

    ui->linePass->setEchoMode(QLineEdit::Password);

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(fechar()));
    connect(ui->enterButton,SIGNAL(clicked(bool)), this, SLOT(entrar()));
    connect(ui->linePass, SIGNAL(returnPressed()), this, SLOT(entrar()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::fechar(){
  QMessageBox mensagem;

  mensagem.setWindowTitle("Controle de Estoque");
  mensagem.setText("Finalizando o programa");
  mensagem.exec();

  exit(0);
}

void MainWindow::entrar(){
    Conexao connection; //Instancia a classe de conexão.

    /*
     * Ao clicar no botão, o sinal clicked() é emitido,
     * o login e a senha são atribuidos a objetos do tipo
     * QString sendo eles: login e senha que são recebidos
     * através dos textEdits: lineLogin e linePass.
    */

    QString login, senha;
    login = ui->lineLogin->text();
    senha = ui->linePass->text();

    QMessageBox token;
    if(!login.compare("") || !senha.compare("")){ //Campos login e/ou senha vazios.
        token.setText("Preencha todos os campos!");
        token.exec();
    } else if(senha.size() < 8 && senha.compare("O")) { //Campo linePass com o tamanho menor que 8.
        token.setText("A senha deve conter no mínimo 8 dígitos!");
        token.exec();
    } else { //Campos login e senha preenchidos.
        int resposta = connection.logar(login, senha);

        enum { FALHA, CAIXA, GERENTE };

        switch(resposta){
            case FALHA:{
              QMessageBox erro;
              erro.setText("Contate o desenvolvedor");
              erro.exec();
            } break;
            case CAIXA: {
                //Caso a resposta seja igual a 1: vá para a página do caixa.
                caixa.show();
                this->close(); //Como usuário já está logado, fecha a tela de login.
            } break;
            case GERENTE: {
                //Caso a resposta seja igual a 2: vá para a página do gerente.
                gerente.show();
                this->close(); //Como usuário já está logado, fecha a tela de login.
            }  break;
            default: {
                //Login ou senha incorretos.
                QMessageBox usuario;
                usuario.setText("Funcionário não cadastrado no sistema ou login/senha incorretos");
                usuario.exec();
            } break;
        }
    }
}
