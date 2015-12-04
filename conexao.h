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

/*! @brief Classe Conexão.
 *      Classe C++ que inclui bibliotecas do Qt, C++ e MySQL para realizar a conexão entre Interface Gráfica,
 * C++ e Banco de Dados.
 *
 * A Classe Conexão consiste em uma Classe com suporte para Interface Gráfica responsável por realizar toda a
 * conexão do sistema com o Banco de Dados, esta é responsável pela validação e criptografia dos dados dos
 * funcionários que são cadastrados no Sistema de Controle de Estoque e Produção. A Classe é capaz de inserir
 * dados, alterar dados existentes, remover dados e selecionar dados, tornando-a a Classe que gerencia o projeto
 * inteiro.
 */

class Conexao : public QObject{
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

    map<int, string> vendidos; //Codigo do produto e quantidade de vendas do mesmo.

    explicit Conexao(QObject *parent = 0);
    ~Conexao();
    MYSQL conn;
    void addEmployee(QString _name, QString _age, QString _role, QString _salary, QString _cpf, QString _email, QString _address);
    void deletar(string nome, int age);
    bool updateEmployee(QString _name, QString _cpf, QString _salary, QString _email, QString _address, QString _role);
    int logar(QString login, QString senha);
    int funcionarios();
    bool validaCpf(QString cpf);
    bool select(QString name, QString &cpf, QString &email, QString &address, QString &role, QString &salary);
    bool insertProducts(QString _name, QString _purchasePrice, QString _sellPrice, QString _quantity, QString _validity);
    int selectProducts();
    bool delEmployees(QString name, QString email);
    int selectByCode(QString _id);
    QString getName(QString _id);
signals:

public slots:

};

#endif // CONEXAO_H
