#ifndef GERENTE_H
#define GERENTE_H

//includes Bibliotecas Qt
#include <QMainWindow>

//includes Classes do Desenvolvedor
#include "caixa.h"
#include "cadastrar.h"
#include "produtos.h"
#include "financas.h"

namespace Ui {
    class Gerente;
}

/*! @brief Classe Gerente
 *      é a Interface Gráfica responsável por mostrar as possibilidades do Gerente na hora de gerenciar a empresa.
 *
 * A Classe Gerente consiste em uma QMainWindow e mostra as 4 possibilidades do Gerente no projeto que são elas:
 * \htmlonly
 * <ol>
 *  <li> Adicionar, alterar e remover funcionários. </li>
 *  <li> Gerenciar o Estoque da empresa</li>
 *  <li> Visualizar as finanças de acordo com as despesas externas (como impostos, manutenções...)</li>
 *  <li> Utilizar o caixa para venda de produtos</li>
 * </ol>
 * \endhtmlonly
 *
 * @bug Como não foi possível finalizar a classe Caixa, o total não será calculado corretamente
 * (será sempre 0).
 * @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 * e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class Gerente : public QMainWindow {
    Q_OBJECT

    /*! @brief Instância da classe Caixa.
     *
     *  Responsável por mostrar a Interface Gráfica Caixa após a emissão do sinal
     *  e o tratamento dos dados.
     */
    Caixa caixa;

    /*! @brief Instância da classe Cadastrar.
     *
     *  Responsável por mostrar a Interface Gráfica Cadastrar após a emissão do sinal
     *  e o tratamento dos dados.
     */
    Cadastrar funcionario;

    /*! @brief Instância da classe Produtos.
     *
     *  Responsável por mostrar a Interface Gráfica Produtos após a emissão do sinal
     *  e o tratamento dos dados.
     */
    Produtos produtos;

    /*! @brief Instância da classe Financas.
     *
     *  Responsável por mostrar a Interface Gráfica Financas após a emissão do sinal
     *  e o tratamento dos dados.
     */
    Financas balanco;
public:
    /*! @brief Construtor da classe Gerente.
     *  @param Ponteiro do tipo QWidget que aponta explicitamente para 0.
     *
     * Construtor da classe Gerente, responsável por setar o nome da Janela e conectar os
     * sinais e slots presentes na Interface Gráfica.
     */
    explicit Gerente(QWidget *parent = 0);

    /*! @brief Destrutor da classe Gerente.
     *
     * Destrutor da classe Gerente, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~Gerente();

private slots:
    /*! @brief SLOT vendas() da classe Gerente.
     *
     * O SLOT vendas() sem nenhum parâmetro e sem retorno, é responsável por
     * mostrar a Interface Gráfica onde o usuário será capaz de vender produtos
     * já existentes no seu estoque, acionado pelo SIGNAL(clicked(bool)) do botão
     * vendasButton.
     */
    void vendas();

    /*! @brief SLOT cadastrar() da classe Gerente.
     *
     * O SLOT cadastrar() sem nenhum parâmetro e sem retorno, é responsável por
     * mostrar a Interface Gráfica onde o usuário será capaz de alterar, adicionar
     * ou até mesmo deletar funcionários na sua empresa, acionado pelo SIGNAL(clicked(bool))
     * do botão cadastrarButton.
     */
    void cadastrar();

    /*! @brief SLOT estoque() da classe Gerente.
     *
     * O SLOT estoque() sem nenhum parâmetro e sem retorno, é responsável por
     * mostrar a Interface Gráfica onde o usuário será capaz de adicionar produtos
     * no seu estoque, acionado pelo SIGNAL(clicked(bool)) do botão estoqueButton.
     */
    void estoque();

    /*! @brief SLOT financas() da classe Gerente.
     *
     * O SLOT financas() sem nenhum parâmetro e sem retorno, é responsável por
     * mostrar a Interface Gráfica onde o usuário será capaz de visualizar as
     * finanças da sua empresa, acionado pelo SIGNAL(clicked(bool)) do botão
     * financasButton.
     */
    void financas();

private:
    Ui::Gerente *ui;
};

#endif // GERENTE_H
