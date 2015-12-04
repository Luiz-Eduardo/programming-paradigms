#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <QMainWindow>

namespace Ui {
class Produtos;
}

class Produtos : public QMainWindow{
    Q_OBJECT

public:
    explicit Produtos(QWidget *parent = 0);
    ~Produtos();

private:
    Ui::Produtos *ui;

private slots:
    void add();
};


#endif // PRODUTOS_H
