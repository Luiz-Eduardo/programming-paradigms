#ifndef ADICIONAR_H
#define ADICIONAR_H

#include <QDialog>

namespace Ui {
class Adicionar;
}

/*! @brief Classe Adicionar.
 *      Interface Gráfica responsável por adicionar novos funcionários no projeto.
 *
 * A Classe Adicionar consiste em uma QDialog e possui os dados principais de um funcionário,
 * que serão colocados no Banco de Dados employees, além disso, inclui no Banco user um usuário
 * e senha para se logar no sistema, sendo este segundo composto de login: (primeiro nome da pessoa)
 * e senha: cpf da pessoa.
 */
class Adicionar : public QDialog{
    Q_OBJECT

public:
    explicit Adicionar(QWidget *parent = 0);
    ~Adicionar();

private slots:
    /*! @brief Método clean().
     *      Método da classe Adicionar.
     *
     * O Método clean() sem nenhum parâmetro e sem retorno, é responsável apenas por
     * limpar todos os campos da interface Adicionar.
     */
    void clean();
    /*! @brief Método add().
     *      Método da classe Adicionar.
     *
     * O Método add() sem nenhum parâmetro e sem retorno, é responsável - ao incluir a
     * classe Conexao - por inserir no Banco de Dados o novo funcionário.
     */
    void add();

private:
    Ui::Adicionar *ui;
};

#endif // ADICIONAR_H
