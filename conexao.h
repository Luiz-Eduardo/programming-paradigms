#ifndef CONEXAO_H
#define CONEXAO_H

#include <QObject>
#include <QStringList>
#include <QString>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <clocale>
#include <mysql/mysql.h>

using namespace std;

class Conexao : public QObject{
    Q_OBJECT
public:    
    QStringList employees_name;
    QStringList employees_age;
    QStringList employees_email;
    QStringList employees_role;
    QStringList employees_salary;

    explicit Conexao(QObject *parent = 0);
    ~Conexao();
    MYSQL conn;
    void addEmployee(QString _name, QString _age, QString _role, QString _salary, QString _cpf, QString _email, QString _address);
    void deletar(string nome, int age);
    void alterar(string newname, string age);
    int logar(QString login, QString senha);
    int funcionarios();
    bool validaCpf(QString cpf);

signals:

public slots:

};

#endif // CONEXAO_H
