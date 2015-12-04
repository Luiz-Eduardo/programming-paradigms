//includes Classes do Desenvolvedor
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "conexao.h"

//includes Bibliotecas Qt
#include <QString>
#include <QMessageBox>

/* Construtor da classe MainWindow */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    /* Setando o título da janela como Login Page */
    this->setWindowTitle("Login Page");

    /* Setando o campo passEdit como do tipo Password */
    ui->linePass->setEchoMode(QLineEdit::Password);

    /* Sinais e Slots */
    connect(ui->exitButton, SIGNAL(clicked(bool)), this, SLOT(fechar()));
    connect(ui->enterButton,SIGNAL(clicked(bool)), this, SLOT(entrar()));
    connect(ui->linePass, SIGNAL(returnPressed()), this, SLOT(entrar()));
}

/* Destrutor da classe MainWindow */
MainWindow::~MainWindow(){
    delete ui;
}

/* Slot fechar() da classe MainWindow */
void MainWindow::fechar(){
  QMessageBox mensagem;

  mensagem.setWindowTitle("Controle de Estoque");
  mensagem.setText("Finalizando o programa");
  mensagem.exec();

  this->close();
}

/* Slot entrar() da Classe MainWindow */
void MainWindow::entrar(){
    Conexao connection; //Instancia da classe Conexão.

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

    /* Tratamento dos dados de login e senha. */
    if(!login.compare("") || !senha.compare("")){ //Campos login e/ou senha vazios.
        token.setText("Preencha todos os campos!");
        token.exec();
    } else if(senha.size() < 8 && senha.compare("O")) { //Campo linePass com o tamanho menor que 8.
        token.setText("A senha deve conter no mínimo 8 dígitos!");
        token.exec();
    } else { //Campos login e senha preenchidos.
        int resposta = connection.logar(login, senha);

        switch(resposta){
            case FALHA:{
              QMessageBox erro;

              erro.setText("Erro no sistema, contate o desenvolvedor");
              erro.exec();
            } break;
            case CAIXA: {
                //Caso a resposta seja igual a 1: vá para a página do caixa.
                caixa.show();
                this->close(); //Como o usuário já está logado, a tela de login é fechada.
            } break;
            case GERENTE: {
                //Caso a resposta seja igual a 2: vá para a página do gerente.
                gerente.show();
                this->close(); //Como o usuário já está logado, a tela de login é fechada.
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
