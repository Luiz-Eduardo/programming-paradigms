//includes das Classes criadas pelo Desenvolvedor.
#include "conexao.h"

//includes das Bibliotecas do Qt
#include <QMessageBox>

//includes Bibliotecas do C++
#include <cstdlib>
#include <sstream>
#include <ctime>

#define hostname "localhost"
#define username "root"
#define password "2701"
#define dbname "Estoque"
#define socketname NULL
#define portnumber 1563
#define flags 0


Conexao::Conexao(QObject *parent) : QObject(parent){
    setlocale(LC_ALL, "Portuguese");

    mysql_init(&conn);
}

Conexao::~Conexao(){
    mysql_close(&conn);
}

void Conexao::addEmployee(QString _name, QString _age, QString _role, QString _salary, QString _cpf, QString _email, QString _address){
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        string name = _name.toUtf8().constData();
        string age = _age.toUtf8().constData();
        string role = _role.toUtf8().constData();
        string salary = _salary.toUtf8().constData();
        string address = _address.toUtf8().constData();
        string email = _email.toUtf8().constData();
        string cpf = _cpf.toUtf8().constData();
        string sql = "INSERT INTO employees(name, age, role, salary, cpf, email, address) VALUES (AES_ENCRYPT('" + name + "', \"estoque\"), '" + age + "', '" + role + "', '" + salary + "', '" + cpf + "', '" + email + "', '" + address + "')";
        //AES_ENCRYPT("CHAVE", "VALOR");

        char query[sql.size()];
        strcpy(query, sql.c_str());

        string user, pass = cpf;

        for(unsigned int i = 0; i < name.size(); i++){
            user += name[i];

            if(name[i] == 32)
                break;
        }

        string users = "INSERT INTO users(username, password, role) VALUES ('" + user + "', '" + pass + "', '" + role + "')";

        char log[users.size()];
        strcpy(log, users.c_str());

        mysql_query(&conn, query);
        mysql_query(&conn, log);
    } else {
        QMessageBox erro;
        erro.setText("Falha de Conexão");
        erro.exec();

    }
}

bool Conexao::delEmployees(QString _name, QString _email){
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        string name = _name.toUtf8().constData();
        string email = _email.toUtf8().constData();

        string sql = "DELETE FROM employees WHERE name = AES_ENCRYPT('" + name + "', \"estoque\") AND email='" + email + "'";

        char query[sql.size()];

        strcpy(query, sql.c_str());
        mysql_query(&conn, query);

        return true;
    } else {
        return false;
    }

}

bool Conexao::select(QString name, QString &cpf, QString &email, QString &address, QString &role, QString &salary){
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        char query[] = "SELECT id, AES_DECRYPT(name, \"estoque\"), age, role, salary, cpf, email, address FROM employees";

        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return false;
        }

        if(!(res = mysql_store_result(&conn))){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return false;
        }

        while((row = mysql_fetch_row(res))){
            if(row[1] && row[2] && row[3] && row[4] && row[6]){
                QString nome = row[1];
                QString cargo = row[3];
                QString salario = row[4];
                QString doc = row[5];
                QString mail = row[6];
                QString endereco = row[7];

                if(!nome.compare(name)){
                    email = mail;
                    role = cargo;
                    salary = salario;
                    cpf = doc;
                    address = endereco;
                }
            }
        }

        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return false;
        }

        mysql_free_result(res);
        return true;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return false;
    }

    return false;
}

bool Conexao::updateEmployee(QString _name, QString _cpf, QString _salary, QString _email, QString _address, QString _role){
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        string name = _name.toUtf8().constData();
        string cpf = _cpf.toUtf8().constData();
        string salary = _salary.toUtf8().constData();
        string email = _email.toUtf8().constData();
        string address = _address.toUtf8().constData();
        string role = _role.toUtf8().constData();

        string sql = "UPDATE employees SET salary='" + salary + "', email='" + email + "', address = '" + address + "', role='" + role +  "' WHERE name=AES_ENCRYPT('" + name + "', \"estoque\") AND cpf='" + cpf + "'";

        char query[sql.size()];
        strcpy(query, sql.c_str());

        mysql_query(&conn, query);
        return true;
    }

    return false;
}

int Conexao::funcionarios(){
    int tamanho = 0;

    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        char query[] = "SELECT id, AES_DECRYPT(name, \"estoque\"), age, role, salary, cpf, email, address FROM employees";

        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        if(!(res = mysql_store_result(&conn))){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        while((row = mysql_fetch_row(res))){
            if(row[1] && row[2] && row[3] && row[4] && row[6]){
                QString name = row[1];
                QString age = row[2];
                QString email = row[6];
                QString role = row[3];
                QString salary = row[4];

                employees_name.append(name);
                employees_age.append(age);
                employees_email.append(email);
                employees_role.append(role);
                employees_salary.append(salary);

                tamanho++;
            }
        }

        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        mysql_free_result(res);
        return tamanho;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return 0;
    }
}

int Conexao::logar(QString login, QString senha){
    int conexao;

    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        string log = login.toUtf8().constData();
        string pass = senha.toUtf8().constData();

        string cmd = "SELECT * FROM users WHERE username = '" + log + "'  AND password = '" + pass + "' LIMIT 1";

        char query[cmd.size()];
        strcpy(query, cmd.c_str());

        if (mysql_query(&conn, query)){
                 printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
                 return 0;
        }

        if(!(res = mysql_store_result(&conn))){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        while((row = mysql_fetch_row(res))){
            if(row[3])
                conexao = atoi(row[3]); //atoi (função responsável por converter valores *char em int.
        }

        if(!mysql_eof(res)){
           printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
           return 0;
       }

         mysql_free_result(res);
         return conexao;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return -1;
    }
}

bool Conexao::validaCpf(QString cpf){
    string document = cpf.toUtf8().constData();
    string teste, resultado;

    for(int i = 0; i < cpf.size(); i++)
        teste += document[i];

    for(int i = 0; i < 9; i++)
        resultado += document[i];

    stringstream res;

    int soma = 0;

    for(int i = 0; i < 9; i++)
        soma += (teste[i]-48)*(i+1);

    if(soma%11 != 10)
        res << soma%11;
    else
        res << 0;

    soma = 0;

    for(int i = 0; i < 9; i++)
        soma += (teste[i]-48)*(9-i);

    if(soma%11 != 10)
        res << soma%11;
    else
        res << 0;

    resultado += res.str();

    if(!resultado.compare(teste))
        return true;
    return false;
}

bool Conexao::insertProducts(QString _name, QString _purchasePrice, QString _sellPrice, QString _quantity, QString _validity){
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        string name = _name.toUtf8().constData();
        string purchasePrice = _purchasePrice.toUtf8().constData();
        string sellPrice = _sellPrice.toUtf8().constData();
        string quantity = _quantity.toUtf8().constData();
        string validity = _validity.toUtf8().constData();
        string sql = "INSERT INTO products(name, purchaseprice, saleprice, quantity, validity) VALUES ('" + name + "', '" + purchasePrice + "', '" + sellPrice + "', '" + quantity + "', '" + validity + "')";
        //AES_ENCRYPT("CHAVE", "VALOR");

        char query[sql.size()];
        strcpy(query, sql.c_str());

        mysql_query(&conn, query);
        return true;
    } else {
        QMessageBox erro;
        erro.setText("Falha de Conexão");
        erro.exec();
        return false;
    }

    return false;
}

int Conexao::selectProducts(){
    int tamanho = 0;

    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        char query[] = "SELECT id, name, purchaseprice, saleprice, quantity, validity FROM products";

        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        if(!(res = mysql_store_result(&conn))){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        while((row = mysql_fetch_row(res))){
            if(row[0] && row[1] && row[2] && row[3] && row[4] && row[5]){
                QString id = row[0];
                QString name = row[1];
                QString purchaseprice = row[2];
                QString saleprice = row[3];
                QString quantity = row[4];
                QString validity = row[5];

                products_id.append(id);
                products_name.append(name);
                products_purchaseprice.append(purchaseprice);
                products_saleprice.append(saleprice);
                products_quantity.append(quantity);
                products_validity.append(validity);

                tamanho++;
            }
        }

        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        mysql_free_result(res);
        return tamanho;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return 0;
    }
}

int Conexao::selectByCode(QString _id){
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        string id = _id.toUtf8().constData();

        string sql = "SELECT saleprice FROM products WHERE id =" + id;

        char query[sql.size()];
        strcpy(query, sql.c_str());

        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return -1;
        }

        if(!(res = mysql_store_result(&conn))){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return -1;
        }

        QString saleprice;

        while((row = mysql_fetch_row(res))){
            if(row[0]){
                saleprice = row[0];
                break;
            }
        }

        string sale = saleprice.toUtf8().constData();
        stringstream buffer;

        buffer << sale;

        double valor;
        buffer >> valor;

        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return false;
        }

        mysql_free_result(res);
        return valor;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return -1;
    }

    return -2;
}

QString Conexao::getName(QString _id){
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        string id = _id.toUtf8().constData();

        string sql = "SELECT name FROM products WHERE id =" + id;

        char query[sql.size()];
        strcpy(query, sql.c_str());

        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return "-1";
        }

        if(!(res = mysql_store_result(&conn))){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return "-1";
        }

        QString name;

        while((row = mysql_fetch_row(res))){
            if(row[0]){
                name = row[0];
                break;
            }
        }

        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return "false";
        }

        mysql_free_result(res);
        return name;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return "-1";
    }

    return "-2";
}
