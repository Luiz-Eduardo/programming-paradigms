#ifndef CAIXA_H
#define CAIXA_H

#include <QMainWindow>

namespace Ui {
class Caixa;
}

class Caixa : public QMainWindow{
    Q_OBJECT
    double total;
    int tamanho;

public:
    explicit Caixa(QWidget *parent = 0);
    ~Caixa();

private:
    Ui::Caixa *ui;
private slots:
    void nextPurchase();
    void addProduct();
};

#endif // CAIXA_H
