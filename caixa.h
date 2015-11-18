#ifndef CAIXA_H
#define CAIXA_H

#include <QMainWindow>

namespace Ui {
class Caixa;
}

class Caixa : public QMainWindow{
    Q_OBJECT

public:
    explicit Caixa(QWidget *parent = 0);
    ~Caixa();

private:
    Ui::Caixa *ui;
};

#endif // CAIXA_H
