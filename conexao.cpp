#include "conexao.h"
#include <QMessageBox>
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


Conexao::Conexao(QObject *parent) :
    QObject(parent){

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

void Conexao::deletar(string nome, int age){
    //if(mysql_real_connect(&conn, hostname, username, password, dbname, portnumber, socketname, flags)){
    //string sql = "DELETE FROM pessoa WHERE name='" + nome + "' AND age='" + to_string(age) + "'";

    //char query[sql.size()];

   // strcpy(query, sql.c_str());
   // mysql_query(&conn, query);
    //}
}

void Conexao::alterar(string newname, string age){
    string sql = "UPDATE pessoa SET name='" + newname + "' WHERE age='" + age +"'";

    char query[sql.size()];

    strcpy(query, sql.c_str());
    mysql_query(&conn, query);
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
