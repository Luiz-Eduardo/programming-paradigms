#ifndef DELETE_H
#define DELETE_H

//includes Bibliotecas Qt
#include <QMainWindow>

namespace Ui {
    class Delete;
}

/*! @brief Classe Delete
 *      consiste em uma QMainWindow e mostra a possibilidade de excluir funcionários já existentes.
 *
 * A Classe Delete é a Interface Gráfica responsável por demitir funcionários já existentes no Banco de Dados Estoque
 * na tabela employees através do nome e email.
 *
 * @todo Criptografar dados do CPF e ao invés de pegar o email, pegar o CPF na hora de deletar,
 * para poder deletar também na tabela users.
 *
 * @bug Ao deletar um funcionário já existente no Banco de Dados, é necessário reiniciar o projeto para
 * que a exclusão apareça na employeesView (tabela de Funcionários).
 *
 * @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 * e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class Delete : public QMainWindow {
    Q_OBJECT

public:
    /*! @brief Construtor da classe Delete.
     *  @param Ponteiro do tipo QWidget que aponta explicitamente para 0.
     *
     * Construtor da classe Delete, responsável por setar o nome da Janela e conectar os
     * sinais e slots presentes na Interface Gráfica.
     */
    explicit Delete(QWidget *parent = 0);

    /*! @brief Destrutor da classe Delete.
     *
     * Destrutor da classe Delete, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~Delete();

private:
    Ui::Delete *ui;

private slots:
    /*! @brief SLOT deleteEmployee() da classe Delete.
     *
     * O SLOT deleteEmployee() sem nenhum parâmetro e sem retorno, é responsável por
     * deletar o funcionário existente - com auxílio da classe Conexao - acionado
     * pelo SIGNAL(clicked(bool)) do botão deleteButton.
     */
    void deleteEmployee();
};

#endif // DELETE_H
