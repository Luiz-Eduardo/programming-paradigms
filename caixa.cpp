#include "caixa.h"
#include "ui_caixa.h"

Caixa::Caixa(QWidget *parent) : QMainWindow(parent), ui(new Ui::Caixa){
    ui->setupUi(this);
    this->setWindowTitle("Controle de Caixa");
}

Caixa::~Caixa(){
    delete ui;
}
