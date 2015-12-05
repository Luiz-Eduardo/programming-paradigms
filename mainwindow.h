#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//includes Bibliotecas Qt
#include <QMainWindow>

//includes Classes do Desenvolvedor
#include "caixa.h"
#include "gerente.h"

namespace Ui {
    class MainWindow;
}

/** @mainpage manageFast - Cause time isn't just money
  */
/*! @brief Classe MainWindow
 *      é a Interface Gráfica responsável por logar no Software da empresa.
 *
 *  A Classe MainWindow consiste em uma QMainWindow e possui uma página de Login onde as informações
 *  serão tratadas e o usuário será enviado para o local apropriado de acordo com seu cargo na empresa.
 *
 *  @version 0.1
 *  @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 *  e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class MainWindow : public QMainWindow {
    Q_OBJECT

    /*! @brief Instância da classe Caixa.
     *
     *  Responsável por mostrar a Interface Gráfica Caixa após a emissão do sinal
     *  e o tratamento dos dados.
     */
    Caixa caixa;

    /*! @brief Instância da classe Gerente.
     *
     *  Responsável por mostrar a Interface Gráfica Gerente após a emissão do sinal
     *  e o tratamento dos dados.
     */
    Gerente gerente;

    /*! @brief Tipo Enumerado da classe MainWindow.
     *
     *
     * Responsável por gerenciar os Cargos dos funcionários, sendo 0 FALHA
     * 1 CAIXA e 2 GERENTE.
     */
    enum Cargos { FALHA, CAIXA, GERENTE };

public:
    /*! @brief Construtor da classe MainWindow.
     *  @param Ponteiro do tipo QWidget que aponta explicitamente para 0.
     *
     * Construtor da classe MainWindow, responsável por setar o nome da Janela, conectar os
     * sinais e slots presentes na Interface Gráfica e setar o campo linePass do tipo QLineEdit::Password.
     */
    explicit MainWindow(QWidget *parent = 0);

    /*! @brief Destrutor da classe MainWindow.
     *
     * Destrutor da classe MainWindow, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~MainWindow();

private slots:
    /*! @brief SLOT fechar() da classe Produtos.
     *
     * O SLOT fechar() sem nenhum parâmetro e sem retorno, é responsável por
     * finalizar o programa e exibir uma mensagem de finalização ao pegar o
     * SIGNAL(clicked(bool)) emitido ao clicar no botão exitButton.
     */
    void fechar();

    /*! @brief SLOT entrar() da classe Produtos.
     *
     * O SLOT entrar() sem nenhum parâmetro e sem retorno, é responsável por
     * entrar na Interface Gráfica seguinte ao pegar e tratar o SIGNAL(clicked(bool))
     * emitido ao clicar no enterButton.
     */
    void entrar();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
