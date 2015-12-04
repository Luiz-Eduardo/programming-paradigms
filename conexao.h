#ifndef CONEXAO_H
#define CONEXAO_H

//includes Bibliotecas Qt
#include <QObject>
#include <QString>
#include <QStringList>

//includes C++
#include <iostream> //Biblioteca padrão de entrada e saída.
#include <string> //Biblioteca padrão para manipulação de strings.
#include <cstring> //Biblioteca para utilizar funções para facilitar a cópia, comparação e concatenação de strings no estilo char[].
#include <iomanip>
#include <clocale>

//include MySQL
#include <mysql/mysql.h> //Biblioteca para utilizar o CRUD (Create, Remove, Update and Delete) entre C++ e MySQL no Banco de Dados.

using namespace std;

/*! *  @brief Classe Conexao,
 *  é a responsável pela inclusão de bibliotecas do Qt, C++ e MySQL para realizar
 *  a conexão entre Interface Gráfica, C++ e Banco de Dados
 *
 *  A Classe Conexão consiste em uma Classe com suporte para Interface Gráfica responsável por realizar toda a
 *  conexão do sistema com o Banco de Dados, esta é responsável pela validação e criptografia dos dados dos
 *  funcionários que são cadastrados no Sistema de Controle de Estoque e Produção. A Classe é capaz de inserir
 *  dados, alterar dados existentes, remover dados e selecionar dados, tornando-a a Classe que gerencia o projeto
 *  inteiro.
 *
 *  @warning Não deve ser vísivel para o usuário, apenas para o desenvolvedor, todos os dados devem
 *  permanecer criptografados.
 *  @warning É necessário a instalação do pacote libmysqlclient-dev
 * @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 * e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class Conexao : public QObject {
    Q_OBJECT

public:    
    QStringList employees_name;
    QStringList employees_age;
    QStringList employees_email;
    QStringList employees_role;
    QStringList employees_salary;

    QStringList products_id;
    QStringList products_name;
    QStringList products_purchaseprice;
    QStringList products_saleprice;
    QStringList products_quantity;
    QStringList products_validity;

    /*! @brief Construtor da classe Conexao.
     *  @param Ponteiro do tipo QObject que aponta explicitamente para 0.
     *
     * Construtor da classe Conexao, responsável por inicializar a conexão com o Banco de Dados.
     */
    explicit Conexao(QObject *parent = 0);

    /*! @brief Destrutor da classe Conexao.
     *
     * Destrutor da classe Conexao, responsável por automatizar o gerenciamento de memória, recuperando
     * uma área de memória que antes estava inutilizada.
     */
    ~Conexao();

    /* Add, update, select and delete employees */
    bool addEmployee(QString _name, QString _age, QString _role, QString _salary, QString _cpf, QString _email, QString _address);
    bool deleteEmployee(QString name, QString email);
    bool selectEmployee(QString name, QString &cpf, QString &email, QString &address, QString &role, QString &salary);
    bool updateEmployee(QString _name, QString _cpf, QString _salary, QString _email, QString _address, QString _role);
    int selectEmployees();

    /* Add and select products */
    bool insertProducts(QString _name, QString _purchasePrice, QString _sellPrice, QString _quantity, QString _validity);
    int selectProducts();
    int getSellPrice(QString _id);
    QString getName(QString _id);

    /* Algoritmos de Validação */
    int logar(QString login, QString senha);
    bool validaCpf(QString cpf);

protected:
    MYSQL conn;
};

#endif // CONEXAO_H
