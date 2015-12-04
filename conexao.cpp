//includes Classes do Desenvolvedor
#include "conexao.h"

//includes Bibliotecas C++
#include <sstream>
#include <ctime>

#define hostname "localhost" //Definição do nome do servidor.
#define username "root" //Definição do nome do usuário do phpMyAdmin.
#define password "2701" //Definição da senha do usuário do phpMyAdmin.
#define dbname "Estoque" //Definição do Banco de Dados utilizado.
#define socketname NULL //Definição do socket utilizado.
#define portnumber 1563 //Definição da porta do Software.
#define flags 0 //Definição da quantidade de flags.

/* Construtor da classe Conexao */
Conexao::Conexao(QObject *parent) : QObject(parent){
    setlocale(LC_ALL, "Portuguese"); //Setando a linguagem como Português para utilizar acentos no cout.

    mysql_init(&conn); //Iniciando a conexão.
}

/* Destrutor da classe Conexao */
Conexao::~Conexao(){
    mysql_close(&conn); //Fechando a conexão.
}

/* Método addEmpoyee() da classe Conexao */
bool Conexao::addEmployee(QString _name, QString _age, QString _role, QString _salary, QString _cpf, QString _email, QString _address){
    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        string name = _name.toUtf8().constData(); //typecasting QString >> string
        string age = _age.toUtf8().constData(); //typecasting QString >> string
        string role = _role.toUtf8().constData(); //typecasting QString >> string
        string salary = _salary.toUtf8().constData(); //typecasting QString >> string
        string address = _address.toUtf8().constData(); //typecasting QString >> string
        string email = _email.toUtf8().constData(); //typecasting QString >> string
        string cpf = _cpf.toUtf8().constData(); //typecasting QString >> string

        /* Atribuindo a variável sql o comando do banco de dados para inserção */
        string sql = "INSERT INTO employees(name, age, role, salary, cpf, email, address) VALUES (AES_ENCRYPT('" + name + "', \"estoque\"), '" + age + "', '" + role + "', '" + salary + "', '" + cpf + "', '" + email + "', '" + address + "')";

        char query[sql.size()];
        strcpy(query, sql.c_str()); //Copiando de string para char[]

        string user;
        string pass = cpf; //Atribuindo cpf ao valor da senha.


        unsigned int i;

        /* Atribuindo apenas o primeiro nome a variável user */
        for(i = 0; i < name.size(); i++){
            user += name[i];

            if(name[i] == 32) //Valor ASCII correspondente ao espaço.
                break;
        }

        name[i] = '\0'; //Atribuindo o caractere terminal '\0' indicando o final da string.


        /* Atribuindo a variável users o comando do banco de dados para inserção */
        string users = "INSERT INTO users(username, password, role) VALUES ('" + user + "', '" + pass + "', '" + role + "')";

        char log[users.size()];
        strcpy(log, users.c_str()); //Copiando de string para char[]

        mysql_query(&conn, query); //Executando a query.
        mysql_query(&conn, log); //Executando a query.
        return true;
    }

    return false;
}

/* Slot deleteEmpoyee() da classe Conexao */
bool Conexao::deleteEmployee(QString _name, QString _email){
    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        string name = _name.toUtf8().constData(); //typecasting QString >> string
        string email = _email.toUtf8().constData(); //typecasting QString >> string

        string sql = "DELETE FROM employees WHERE name = AES_ENCRYPT('" + name + "', \"estoque\") AND email='" + email + "'";

        char query[sql.size()];
        strcpy(query, sql.c_str());

        mysql_query(&conn, query); //Executando a query.

        return true;
    } else {
        return false;
    }

}

/* Método selectEmployee() da classe Conexao */
bool Conexao::selectEmployee(QString name, QString &cpf, QString &email, QString &address, QString &role, QString &salary){
    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        char query[] = "SELECT id, AES_DECRYPT(name, \"estoque\"), age, role, salary, cpf, email, address FROM employees";

        /* Tratamento de erros */
        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return false;
        }

        /* Tratamento de erros */
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

        /* Tratamento de erros */
        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return false;
        }

        mysql_free_result(res); //Liberando a memória do ponteiro res.
        return true;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return false;
    }

    return false;
}

/* Método updateEmpoyee() da classe Conexao */
bool Conexao::updateEmployee(QString _name, QString _cpf, QString _salary, QString _email, QString _address, QString _role){
    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        string name = _name.toUtf8().constData(); //typecasting QString >> string
        string cpf = _cpf.toUtf8().constData(); //typecasting QString >> string
        string salary = _salary.toUtf8().constData(); //typecasting QString >> string
        string email = _email.toUtf8().constData(); //typecasting QString >> string
        string address = _address.toUtf8().constData(); //typecasting QString >> string
        string role = _role.toUtf8().constData(); //typecasting QString >> string

        string sql = "UPDATE employees SET salary='" + salary + "', email='" + email + "', address = '" + address + "', role='" + role +  "' WHERE name=AES_ENCRYPT('" + name + "', \"estoque\") AND cpf='" + cpf + "'";

        char query[sql.size()];
        strcpy(query, sql.c_str());

        mysql_query(&conn, query); //Executando a query.
        return true;
    }

    return false;
}

/* Método selectEmployees() da classe Conexao */
int Conexao::selectEmployees(){
    int tamanho = 0;

    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        char query[] = "SELECT id, AES_DECRYPT(name, \"estoque\"), age, role, salary, cpf, email, address FROM employees";

        /* Tratamento de erros */
        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        /* Tratamento de erros */
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

        /* Tratamento de erros */
        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        mysql_free_result(res); //Liberando a memória do ponteiro res.
        return tamanho;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return 0;
    }
}

/* Método logar() da classe Conexao */
int Conexao::logar(QString login, QString senha){
    int conexao;

    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        string log = login.toUtf8().constData(); //typecasting QString >> string
        string pass = senha.toUtf8().constData(); //typecasting QString >> string

        string cmd = "SELECT * FROM users WHERE username = '" + log + "'  AND password = '" + pass + "' LIMIT 1";

        char query[cmd.size()];
        strcpy(query, cmd.c_str());

        /* Tratamento de erros */
        if (mysql_query(&conn, query)){ //Executando a query.
                 printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
                 return 0;
        }

        /* Tratamento de erros */
        if(!(res = mysql_store_result(&conn))){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        while((row = mysql_fetch_row(res))){
            if(row[3])
                conexao = atoi(row[3]); //atoi (função responsável por converter valores *char em int.
        }

        /* Tratamento de erros */
        if(!mysql_eof(res)){
           printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
           return 0;
       }

         mysql_free_result(res); //Liberando a memória do ponteiro res.
         return conexao;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return -1;
    }
}

/* Método validaCpf() da classe Conexao */
bool Conexao::validaCpf(QString cpf){
    string document = cpf.toUtf8().constData(); //typecasting QString >> string
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

/* Método insertProducts() da classe Conexao */
bool Conexao::insertProducts(QString _name, QString _purchasePrice, QString _sellPrice, QString _quantity, QString _validity){
    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        string name = _name.toUtf8().constData(); //typecasting QString >> string
        string purchasePrice = _purchasePrice.toUtf8().constData(); //typecasting QString >> string
        string sellPrice = _sellPrice.toUtf8().constData(); //typecasting QString >> string
        string quantity = _quantity.toUtf8().constData(); //typecasting QString >> string
        string validity = _validity.toUtf8().constData(); //typecasting QString >> string

        string sql = "INSERT INTO products(name, purchaseprice, saleprice, quantity, validity) VALUES ('" + name + "', '" + purchasePrice + "', '" + sellPrice + "', '" + quantity + "', '" + validity + "')";

        char query[sql.size()];
        strcpy(query, sql.c_str());

        mysql_query(&conn, query); //Executando a query.
        return true;
    }

    return false;
}

/* Método selectProducts() da classe Conexao */
int Conexao::selectProducts(){
    int tamanho = 0;

    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        char query[] = "SELECT id, name, purchaseprice, saleprice, quantity, validity FROM products";

        /* Tratamento de erros */
        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        /* Tratamento de erros */
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

        /* Tratamento de erros */
        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 0;
        }

        mysql_free_result(res); //Liberando a memória do ponteiro res.
        return tamanho;
    } else {
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return 0;
    }
}

/* Método getSellPrice() da classe Conexao */
int Conexao::getSellPrice(QString _id){
    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        string id = _id.toUtf8().constData(); //typecasting QString >> string

        string sql = "SELECT saleprice FROM products WHERE id =" + id;

        char query[sql.size()];
        strcpy(query, sql.c_str());

        /* Tratamento de erros */
        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return -1;
        }

        /* Tratamento de erros */
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

        string sale = saleprice.toUtf8().constData(); //typecasting QString >> string
        stringstream buffer;

        buffer << sale;

        double valor;
        buffer >> valor;

        /* Tratamento de erros */
        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return false;
        }

        mysql_free_result(res); //Liberando a memória do ponteiro res.
        return valor;
    } else { // Tratamento de erros
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return -1;
    }

    return -2;
}

/* Método getName() da classe Conexao */
QString Conexao::getName(QString _id){
    /* Testando a conexão */
    if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
        MYSQL_RES *res; //Ponteiro que receberá os resultados.
        MYSQL_ROW row;

        string id = _id.toUtf8().constData(); //typecasting QString >> string

        string sql = "SELECT name FROM products WHERE id =" + id;

        char query[sql.size()];
        strcpy(query, sql.c_str());

        /* Tratamento de erros */
        if(mysql_query(&conn, query)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return "-1";
        }

        /* Tratamento de erros */
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

        /* Tratamento de erros */
        if(!mysql_eof(res)){
            printf("Error %u: %s\n", mysql_errno(&conn), mysql_error(&conn));
            return "false";
        }

        mysql_free_result(res); //Liberando a memória do ponteiro res.
        return name;
    } else { // Tratamento de erros
        cout << "Falha de conexao\n";
        cout << "Erro << " << mysql_errno(&conn) << " : " << mysql_error(&conn) << endl;
        return "-1";
    }

    return "-2";
}
