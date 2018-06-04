#include "ingreso.h"
#include "ui_ingreso.h"

ingreso::ingreso(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ingreso)
{   
    ui->setupUi(this);
    ui->label->setText("BIENVENIDO AL HIMALAYA");
    menu_juego = new menu();
}

ingreso::~ingreso()
{
    delete ui;
}

void ingreso::on_pushButton_clicked()
{
    intento = ui->Res->text();
    if (intento == rpta)
    {
        menu_juego->setModo(_modo);
        menu_juego->show();
        close();
    }
}

int ingreso::modo() const
{
    return _modo;
}

void ingreso::setModo(int modo)
{
    _modo = modo;
}
