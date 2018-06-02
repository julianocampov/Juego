#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    if (cont < 2)
    {
        cont++;
        escena = new juego();
        escena->show();
        this->close();
    }
}

void menu::setPtos_2(int value)
{
    ptos_2 = value;
}

void menu::setPtos_1(int value)
{
    ptos_1 = value;
}
