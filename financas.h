#ifndef FINANCAS_H
#define FINANCAS_H

//includes Bibliotecas Qt
#include <QMainWindow>

namespace Ui {
    class Financas;
}

/*! @brief Classe Financas,
 *      é a Interface Gráfica responsável pelas Finanças da empresa.
 *
 * A Classe Financas consiste em uma QMainWindow que mostrará os dados de pagamento
 * de funcionários, as despesas com produtos e receberá o valor das despesas externas,
 * tais como:
 *
 * \htmlonly
 *  <ol>
 *      <li> Impostos </li>
 *      <li> Manutenção na empresa </li>
 *      <li> Reformas </li>
 *      <li> Contas de energia, luz, aluguel...</li>
 * </ol>
 * \endhtmlonly
 *
 * @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 * e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class Financas : public QMainWindow {
    Q_OBJECT

public:
    /*! @brief Variável employeePayment,
     *      do tipo double que representa o total do pagamento dos funcionários.
     */
    double employeePayment;


    /*! @brief Variável productExpenses,
     *      do tipo double que representa o total da despesa com produtos.
     */
    double productExpenses;


    /*! @brief Variável total,
     *      do tipo double que representa o total seja de lucro ou prejuízo da empresa.
     */
    double total;

    /*! @brief Construtor da classe Financas.
     *  @param Ponteiro do tipo QWidget que aponta explicitamente para 0.
     *
     * Construtor da classe Financas, responsável por setar o nome da Janela e conectar os
     * sinais e slots presentes na Interface Gráfica.
     */
    explicit Financas(QWidget *parent = 0);

    /*! @brief Destrutor da classe Financas.
     *
     * Destrutor da classe Delete, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~Financas();

private:
    Ui::Financas *ui;

private slots:
    /*! @brief SLOT showProfit() da classe Financas.
     *
     * O SLOT showProfit() sem nenhum parâmetro e sem retorno, é responsável por
     * mostrar o lucro ou prejuízo da empresa de acordo com o valor inserido no
     * campo despesas externas e é acionado pelo SIGNAL(textChanged(QString)) do
     * expensesEdit.
     */
    void showProfit();
};

#endif // FINANCAS_H
