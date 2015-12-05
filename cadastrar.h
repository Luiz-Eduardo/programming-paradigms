#ifndef CADASTRAR_H
#define CADASTRAR_H

//includes Bibliotecas Qt
#include <QMainWindow>

//includes C++
#include <string>

//includes Classes do Desenvolvedor
#include "adicionar.h"
#include "alterar.h"
#include "delete.h"

namespace Ui {
    class Cadastrar;
}

/*! @brief Classe Cadastrar
 *      é a Interface Gráfica responsável por mostrar informações dos funcionários já existentes no Banco de Dados Estoque
 *      na tabela employees.
 *
 *  A Classe Cadastrar consiste em uma QMainWindow e mostra a tabela de funcionários já existentes e dá a possibilidade de
 *  fazer alterações nos dados de determinado funcionário, além de deletar funcionários e adicionar novos.
 *
 *  @version 0.1
 *  @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 *  e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class Cadastrar : public QMainWindow {
    Q_OBJECT

    /*! @brief Instância da classe Adicionar.
     *
     *  Responsável por mostrar a Interface Gráfica Adicionar após a emissão do sinal
     *  e o tratamento dos dados.
     */
    Adicionar newEmployee;

    /*! @brief Instância da classe Alterar.
     *
     *  Responsável por mostrar a Interface Gráfica Alterar após a emissão do sinal
     *  e o tratamento dos dados.
     */
    Alterar changeEmployee;

    /*! @brief Instância da classe Delete.
     *
     *  Responsável por mostrar a Interface Gráfica Delete após a emissão do sinal
     *  e o tratamento dos dados.
     */
    Delete deleteEmployee;

public:
    /*! @brief Construtor da classe Cadastrar.
     *  @param Ponteiro do tipo QWidget que aponta explicitamente para 0.
     *
     * Construtor da classe Cadastrar, responsável por setar o nome da Janela, conectar os
     * sinais e slots presentes na Interface Gráfica e setar também se os componentes da
     * Interface estão ativados ou não.
     */
    explicit Cadastrar(QWidget *parent = 0);

    /*! @brief Destrutor da classe Cadastrar.
     *
     * Destrutor da classe Cadastrar, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~Cadastrar();

private slots:
    /*! @brief SLOT addEmployee() da classe Cadastrar.
     *
     * O SLOT addEmployee() sem nenhum parâmetro e sem retorno, é responsável por
     * mostrar a Interface Gráfica onde o usuário será capaz de adicionar novos
     * funcionários para trabalhar na sua empresa, acionado pelo SIGNAL(clicked(bool))
     * do botão addButton.
     */
    void addEmployee();

    /*! @brief SLOT changEmployee() da classe Cadastrar.
     *
     * O SLOT changEmployee() sem nenhum parâmetro e sem retorno, é responsável por
     * mostrar a Interface Gráfica onde o usuário será capaz de alterar os funcionários
     * já existentes na sua empresa, acionado pelo SIGNAL(clicked(bool)) do botão changeButton
     */
    void changEmployee();

    /*! @brief SLOT delEmployee() da classe Cadastrar.
     *
     * O SLOT delEmployee() sem nenhum parâmetro e sem retorno, é responsável por
     * mostrar a Interface Gráfica onde o usuário será capaz de deletar os funcionários
     * já existentes na sua empresa, acionado pelo SIGNAL(clicked(bool)) do botão deleteButton.
     */
    void delEmployee();

private:
    Ui::Cadastrar *ui;
};

#endif // CADASTRAR_H
