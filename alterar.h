#ifndef ALTERAR_H
#define ALTERAR_H

#include <QMainWindow>

namespace Ui {
class alterar;
}

class Alterar : public QMainWindow{
    Q_OBJECT

public:
    explicit Alterar(QWidget *parent = 0);
    ~Alterar();

private:
    Ui::alterar *ui;

private slots:
    void searchEmployee();
    void update();
    void clean();
};

#endif // ALTERAR_H
