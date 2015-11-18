#ifndef ADICIONAR_H
#define ADICIONAR_H

#include <QDialog>

namespace Ui {
class Adicionar;
}

class Adicionar : public QDialog
{
    Q_OBJECT

public:
    explicit Adicionar(QWidget *parent = 0);
    ~Adicionar();

private slots:
    void clean();
    void cancel();
    void add();

private:
    Ui::Adicionar *ui;
};

#endif // ADICIONAR_H
