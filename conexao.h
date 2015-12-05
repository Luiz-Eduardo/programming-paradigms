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

/*! *  @brief Classe Conexao
 *          é a responsável pela inclusão de bibliotecas do Qt, C++ e MySQL para realizar
 *          a conexão entre Interface Gráfica, C++ e Banco de Dados
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
 *
 *  @bug Funcionário é deletado da tabela employees, porém não da tabela users, ou seja, o funcionário ainda tem
 *  acesso ao sistema.
 *
 *  @version 0.1
 *  @copyright \htmlonly <a href = "https://github.com/Luiz-Eduardo"> Luiz Eduardo Barros de Araújo Filho </a> \endhtmlonly
 *  e \htmlonly <a href = "https://www.facebook.com/mariaelena.nascimento"> Marielena Nascimento Silveira </a> \endhtmlonly
 */

class Conexao : public QObject {
    Q_OBJECT

public:    
    /*! @brief Lista de Strings
     *      responsável por armazenar o nome de todos os funcionários da empresa.
     */
    QStringList employees_name;


    /*! @brief Lista de Strings
     *      responsável por armazenar a idade de todos os funcionários da empresa.
     */
    QStringList employees_age;

    /*! @brief Lista de Strings
     *      responsável por armazenar o email de todos os funcionários da empresa.
     */
    QStringList employees_email;

    /*! @brief Lista de Strings
     *      responsável por armazenar o cargo de todos os funcionários da empresa.
     */
    QStringList employees_role;

    /*! @brief Lista de Strings
     *      responsável por armazenar o salário de todos os funcionários da empresa.
     */
    QStringList employees_salary;

    /*! @brief Lista de Strings
     *      responsável por armazenar o código de todos os produtos no estoque.
     */
    QStringList products_id;

    /*! @brief Lista de Strings
     *      responsável por armazenar o nome de todos os produtos no estoque.
     */
    QStringList products_name;

    /*! @brief Lista de Strings
     *      responsável por armazenar o preço de compra de todos os produtos no estoque.
     */
    QStringList products_purchaseprice;

    /*! @brief Lista de Strings
     *      responsável por armazenar o preço de venda de todos os produtos no estoque.
     */
    QStringList products_saleprice;

    /*! @brief Lista de Strings
     *      responsável por armazenar a quantidade de todos os produtos no estoque.
     */
    QStringList products_quantity;

    /*! @brief Lista de Strings
     *      responsável por armazenar a validade de todos os produtos no estoque.
     */
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
    /*!
     * @brief Método responsável por inserir novos funcionários a empresa.
     * @param _name nome do funcionário a ser inserido, parâmetro recebido da classe Adicionar.
     * @param _age idade do funcionário a ser inserido, parâmetro recebido da classe Adicionar.
     * @param _role cargo do funcionário a ser inserido, parâmetro recebido da classe Adicionar.
     * @param _salary salário do funcionário a ser inserido, parâmetro recebido da classe Adicionar.
     * @param _cpf cpf do funcionário a ser inserido, parâmetro recebido da classe Adicionar.
     * @param _email email do funcionário a ser inserido, parâmetro recebido da classe Adicionar.
     * @param _address endereço do funcionário a ser inserido, parâmetro recebido da classe Adicionar.
     * @return retorna true caso o funcionário tenha sido inserido,
     * caso contrário retorna false.
     */
    bool addEmployee(QString _name, QString _age, QString _role, QString _salary, QString _cpf, QString _email, QString _address);

    /*!
     * @brief Método responsável por deletar funcionários da empresa.
     * @param name nome do funcionário a ser deletado, parâmetro recebido da classe Delete.
     * @param email email do funcionário a ser deletado, parâmetro recebido da classe Delete.
     * @return retorna true caso o funcionário tenha sido deletado,
     * caso contrário retorna false.
     */
    bool deleteEmployee(QString name, QString email);

    /*!
     * @brief Método responsável por selecionar um funcionário da empresa.
     * @param name nome do funcionário a ser selecionado, parâmetro recebido da classe Alterar.
     * @param cpf cpf do funcionário selecionado.
     * @param email email do funcionário selecionado.
     * @param address endereço do funcionário selecionado.
     * @param role cargo do funcionário selecionado.
     * @param salary salário do funcionário selecionado.
     * @return retorna true caso o funcionário tenha sido selecionado,
     * caso contrário retorna false.
     */
    bool selectEmployee(QString name, QString &cpf, QString &email, QString &address, QString &role, QString &salary);

    /*!
     * @brief Método responsável por atualizar um funcionário já existente.
     * @param _name nome do funcionário que será atualizado, parâmetro recebido da classe Alterar
     * @param _cpf cpf do funcionário que será atualizado.
     * @param _salary salário do funcionário que será atualizado.
     * @param _email email do funcionário que será atualizado.
     * @param _address endereço do funcionário que será atualizado.
     * @param _role cargo do funcionário que será atualizado.
     * @return retorna true caso o funcionário tenha sido alterado,
     * caso contrário retorna false.
     */
    bool updateEmployee(QString _name, QString _cpf, QString _salary, QString _email, QString _address, QString _role);

    /*!
     * @brief Método responsável por selecionar todos os funcionários na tabela employees.
     * @return retorna a quantidade de funcionários.
     */
    int selectEmployees();

    /* Add and select products */
    /*!
     * @brief Método responsável por inserir produtos na tabela products.
     * @param _name nome do produto a ser inserido, parâmetro recebido da classe Produtos
     * @param _purchasePrice preço de venda do produto a ser inserido, parâmetro recebido da classe Produtos
     * @param _sellPrice preço de venda do produto a ser inserido, parâmetro recebido da classe Produtos
     * @param _quantity quantidade do produto a ser inserido, parâmetro recebido da classe Produtos
     * @param _validity validade do produto a ser inserido, parâmetro recebido da classe Produtos
     * @return
     */
    bool insertProducts(QString _name, QString _purchasePrice, QString _sellPrice, QString _quantity, QString _validity);

    /*!
     * @brief Método responsável por selecionar todos os produtos na tabela products.
     * @return retorna a quantidade de produtos.
     */
    int selectProducts();

    /*!
     * @brief Método responsável por selecionar um preço de venda a partir de um id.
     * @param _id id do produto  pesquisado, parâmetro recebido da classe Caixa
     * @return retorna um int valor, caso o código do produto seja encontrado,
     * caso contrário retorna flags relatando erros.
     */
    int getSellPrice(QString _id);

    /*!
     * @brief Método responsável por selecionar um nome a partir de um id.
     * @param _id id do produto pesquisado, parâmetro recebido da classe Caixa
     * @return retorna um QString nome, caso o código do produto seja encontrado,
     * caso contrário retorna flags relatando erros.
     */
    QString getName(QString _id);

    /* Algoritmos de Validação */
    /*!
     * @brief Método responsável por logar o usuário no sistema.
     * @param login login do usuário que tenta logar, parâmetro recebido da classe MainWindow
     * @param senha senha do usuário que tenta logar, parâmetro recebido da classe MainWindow
     * @return retorna o cargo do usuário ou flags relatando erros.
     */
    int logar(QString login, QString senha);

    /*!
     * @brief Método responsável pela validação de cpf do usuário.
     * @param cpf cpf do funcionário a ser adicionado, parâmetro recebido da classe Adicionar
     * @return Caso o CPF seja válido retorna true, caso contrário retorna false.
     *
     */
    bool validaCpf(QString cpf);

protected:
    /*!
     * @brief Variável responsável pela conexão com o Banco de Dados.
     */
    MYSQL conn;
};

#endif // CONEXAO_H
