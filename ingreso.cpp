#include "ingreso.h"
#include "ui_ingreso.h"

ingreso::ingreso(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ingreso)
{   
    ui->setupUi(this);
    ui->label->setText("BIENVENIDO AL HIMALAYA");
    menu_juego = new menu();
    QFile file("hola.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out<<"bienvenido";

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
        QFile file("hola.txt");
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out<<intento;
        menu_juego->show();
        close();
    }
}
