#ifndef PRODUTOS_H
#define PRODUTOS_H

//includes Bibliotecas Qt
#include <QMainWindow>

namespace Ui {
    class Produtos;
}

/*! @brief Tipo estruturado Produto
 *
 *
 *  Estrutura responsável por receber todos os dados que serão capazes
 *  de incluir um novo Produto no estoque da empresa.
 *
 *  @copyright Luiz Eduardo Barros de Araújo Filho e Marielena Nascimento Silveira
 */

struct Produto {
    QString name;
    QString validity;
    QString purchasePrice;
    QString sellPrice;
    QString quantity;

};

/*! @brief Classe Produtos,
 *      é a Interface Gráfica responsável por adicionar novos Produtos no estoque da empresa.
 *
 * A Classe Produtos consiste em uma QMainWindow e possui todos os dados importantes de um produto,
 * que serão colocados no Banco de Dados Estoque na tabela products.
 *
 * @todo Ao inserir novo produto testar se já não existe produto com o mesmo nome e após isso,
 * testar se o preço de compra, venda e validade são o mesmo, se sim, apenas atualizar a quantidade
 * daquele produto de acordo com o valor inserido, se não inserir como produto novo com novo código.
 *
 *
 * @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 * e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */
class Produtos : public QMainWindow {
    Q_OBJECT

    /*! @brief Instância da Estrutura Produto.
     *
     *  Responsável por armazenar os dados que serão inseridos no Banco de Dados
     *  ao adicionar um novo produto.
     */
    Produto produto;

public:
    /*! @brief Construtor da classe Produtos.
     *  @param Ponteiro do tipo QWidget que aponta explicitamente para 0.
     *
     * Construtor da classe Produtos, responsável por setar o nome da Janela, conectar os
     * sinais e slots presentes na Interface Gráfica e exibir os dados presentes no Banco
     * de Dados products na TableView productsView.
     */
    explicit Produtos(QWidget *parent = 0);

    /*! @brief Destrutor da classe Produtos.
     *
     * Destrutor da classe Produtos, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~Produtos();

private:
    Ui::Produtos *ui;

private slots:
    /*! @brief SLOT add() da classe Produtos.
     *
     * O SLOT add() sem nenhum parâmetro e sem retorno, é responsável por
     * inserir novos produtos no Banco de Dados e atualizar a productsView
     * em tempo real ao pegar o SIGNAL(clicked(bool)) emitido ao clicar no
     * botão addButton.
     */
    void add();
};


#endif // PRODUTOS_H
