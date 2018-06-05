#include "modo.h"
#include "ui_modo.h"

modo::modo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modo)
{
    ui->setupUi(this);
}


void modo::on_uno_clicked()
{
    menu *ing = new menu();
    ing->setModo(1);
    ing->show();
    close();
}

void modo::on_dos_clicked()
{
    menu *ing = new menu();
    ing->setModo(2);
    ing->show();
    close();
}

modo::~modo()
{
    delete ui;
}
