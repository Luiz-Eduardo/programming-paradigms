#ifndef CAIXA_H
#define CAIXA_H

//includes Bibliotecas Qt
#include <QMainWindow>

namespace Ui {
    class Caixa;
}

/*! @brief Classe Caixa,
 *      é a Interface Gráfica responsável pelas vendas no caixa da empresa.
 *
 * A Classe Caixa consiste em uma QMainWindow que receberá os dados de compra de todos
 * os clientes da empresa, além disso, a classe é capaz de realizar o update - com o auxílio
 * da classe Conexao - para alterar os valores do Banco de Dados Estoque da tabela products
 *
 * @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 * e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class Caixa : public QMainWindow {
    Q_OBJECT
    /*! @brief Variável total,
     *      do tipo double que representa o total do valor da compra do cliente
     */
    double total;

    /*! @brief Variável tamanho,
     *      do tipo inteiro que representa a quantidade de linhas da tabela de compras
     */
    int tamanho;

public:
    /*! @brief Construtor da classe Caixa.
     *  @param Ponteiro do tipo QWidget que aponta explicitamente para 0.
     *
     * Construtor da classe Caixa, responsável por setar o nome da Janela, conectar os
     * sinais e slots presentes na Interface Gráfica, setar também se os componentes da
     * Interface estão ativados ou não e inicializar as variáveis privadas da classe.
     */
    explicit Caixa(QWidget *parent = 0);

    /*! @brief Destrutor da classe Caixa.
     *
     * Destrutor da classe Caixa, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~Caixa();

private:
    Ui::Caixa *ui;

private slots:
    /*! @brief SLOT nextPurchase() da classe Caixa.
     *
     * O SLOT nextPurchase() sem nenhum parâmetro e sem retorno, é responsável
     * por limpar todos os campos da Interface Gráfica e zerar as variáveis, é
     * acionado pelo SIGNAL(clicked(bool)) do botão nextButton.
     */
    void nextPurchase();

    /*! @brief SLOT addProduct() da classe Alterar.
     *
     * O SLOT addProduct() sem nenhum parâmetro e sem retorno, é responsável
     * por adicionar produtos ao carrinho, ao pegar os valores dos campos Código
     * e Quantidade da Interface Gráfica, é acionado pelo SIGNAL(clicked(bool)) do
     * botão addButton.
     */
    void addProduct();
};

#endif // CAIXA_H
