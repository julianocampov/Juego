#include "modo.h"
#include "ui_modo.h"
#include "ingreso.h"

modo::modo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modo)
{
    ui->setupUi(this);
}

modo::~modo()
{
    delete ui;
}

void modo::on_uno_clicked()
{
    ingreso *ing = new ingreso();
    ing->show();
    close();
}
