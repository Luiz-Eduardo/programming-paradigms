#ifndef DELETE_H
#define DELETE_H

#include <QMainWindow>

namespace Ui {
class Delete;
}

class Delete : public QMainWindow{
    Q_OBJECT

public:
    explicit Delete(QWidget *parent = 0);
    ~Delete();

private:
    Ui::Delete *ui;

private slots:
    void cancel();
    void delEmployee();
};

#endif // DELETE_H
