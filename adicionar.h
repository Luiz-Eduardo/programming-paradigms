#ifndef ADICIONAR_H
#define ADICIONAR_H

//includes Bibliotecas Qt
#include <QDialog>

namespace Ui {
    class Adicionar;
}

/*! @brief Tipo estruturado Funcionario
 *
 *
 *  Estrutura responsável por receber todos os dados que serão capazes
 *  de incluir um novo funcionário na empresa.
 *
 *  @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 *  e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

struct Funcionario {
    QString name; //Campo nome.
    QString age; //Campo idade.
    QString role; //Campo cargo.
    QString salary; //Campo salário.
    QString address; //Campo endereço.
    QString email; //Campo email.
    QString cpf; //Campo cpf.
};

/*! @brief Classe Adicionar
 *      é a Interface Gráfica responsável por adicionar novos funcionários no projeto.
 *
 *  A Classe Adicionar consiste em uma QDialog e possui os dados principais de um funcionário,
 *  que serão colocados no Banco de Dados Estoque na tabela employees, além disso, inclui no Banco users um usuário
 *  e senha para se logar no sistema, sendo este segundo composto de login: (primeiro nome da pessoa)
 *  e senha: cpf da pessoa.
 *
 *  @bug Ao adicionar um novo funcionário a tabela employees, é necessário reiniciar o projeto para
 *  que o mesmo apareça na employeesView (tabela de Funcionários).
 *
 *  @version 0.1
 *  @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 *  e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class Adicionar : public QDialog {
    Q_OBJECT

    /*! @brief Instância da Estrutura Funcionário.
     *
     *  Responsável por armazenar os dados que serão inseridos no Banco de Dados
     *  ao adicionar um novo funcionário.
     */
    Funcionario funcionario;
public:
    /*! @brief Construtor da classe Adicionar.
     *  @param Ponteiro do tipo QWidget que aponta explicitamente para 0.
     *
     * Construtor da classe Adicionar, responsável por setar o nome da Janela e conectar os
     * sinais e slots presentes na Interface Gráfica.
     */
    explicit Adicionar(QWidget *parent = 0);

    /*! @brief Destrutor da classe Adicionar.
     *
     * Destrutor da classe Adicionar, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~Adicionar();

private slots:
    /*! @brief SLOT clean() da classe Adicionar.
     *
     * O SLOT clean() sem nenhum parâmetro e sem retorno, é responsável apenas por
     * limpar todos os campos da interface Adicionar ao pegar o SIGNAL(clicked(bool))
     * emitido ao clicar no botão cleanButton.
     */
    void clean();

    /*! @brief SLOT add() da classe Adicionar.
     *
     * O SLOT add() sem nenhum parâmetro e sem retorno, é responsável - ao incluir a
     * classe Conexao - por inserir no Banco de Dados o novo funcionário ao pegar o SIGNAL(clicked(bool))
     * emitido ao clicar no botão addButton.
     */
    void add();

private:
    Ui::Adicionar *ui;
};

#endif // ADICIONAR_H
