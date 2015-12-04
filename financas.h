#ifndef FINANCAS_H
#define FINANCAS_H

#include <QMainWindow>

namespace Ui {
class Financas;
}

class Financas : public QMainWindow{
    Q_OBJECT

public:
    double employeePayment;
    double productExpenses;
    double total;
    explicit Financas(QWidget *parent = 0);
    ~Financas();

private:
    Ui::Financas *ui;
private slots:
    void showProfit();
};

#endif // FINANCAS_H
