#ifndef ALTERAR_H
#define ALTERAR_H

//includes Bibliotecas Qt
#include <QMainWindow>

namespace Ui {
    class alterar;
}

/*! @brief Classe Alterar,
 *      é a Interface Gráfica responsável por alterar informações dos funcionários já existentes no Banco de Dados Estoque
 * na tabela employees.
 *
 * A Classe Alterar consiste em uma QMainWindow e recebe o nome de um funcionário para que suas outras informações possam
 * ser alteradas.
 *
 * @bug Ao alterar um funcionário já existente no Banco de Dados, é necessário reiniciar o projeto para
 * que a alteração apareça na employeesView (tabela de Funcionários).
 *
 * @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 * e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class Alterar : public QMainWindow {
    Q_OBJECT

public:
    /*! @brief Construtor da classe Alterar.
     *  @param Ponteiro do tipo QWidget que aponta explicitamente para 0.
     *
     * Construtor da classe Alterar, responsável por setar o nome da Janela, conectar os
     * sinais e slots presentes na Interface Gráfica e setar também se os componentes da
     * Interface estão ativados ou não.
     */
    explicit Alterar(QWidget *parent = 0);

    /*! @brief Destrutor da classe Alterar.
     *
     * Destrutor da classe Alterar, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~Alterar();

private:
    Ui::alterar *ui;

private slots:
    /*! @brief SLOT searchEmployee() da classe Alterar.
     *
     * O SLOT searchEmployee() sem nenhum parâmetro e sem retorno, é responsável por
     * selecionar os dados do funcionário através do nome recebido pelo nameEdit e
     * acionado pelo SIGNAL(clicked(bool)) do botão searchButton através da classe Conexão.
     */
    void searchEmployee();

    /*! @brief SLOT update() da classe Alterar.
     *
     * O SLOT update() sem nenhum parâmetro e sem retorno, é responsável por
     * atualizar os dados do funcionário após receber os campos salaryEdit,
     * emailEdit, addressEdit e roleEdit, acionado pelo SIGNAL(clicked(bool)) do botão
     * updateButton através da classe Conexão.
     */
    void update();

    /*! @brief SLOT clean() da classe Alterar.
     *
     * O SLOT clean() sem nenhum parâmetro e sem retorno, é responsável
     * apenas por limpar todos os campos da Interface Gráfica, acionado
     * pelo SIGNAL(clicked(bool)) do botão cleanButton.
     */
    void clean();
};

#endif // ALTERAR_H
