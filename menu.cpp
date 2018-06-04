#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}


void menu::on_pushButton_clicked()
{
    juego *escena = new juego();
    escena->setNivel(1);
    escena->timers();
    escena->setControl(modo);
    escena->show();

    close();
}

void menu::on_pushButton_2_clicked()
{
    juego *escena = new juego();
    escena->setNivel(2);
    escena->timers();
    escena->setControl(modo);
    escena->show();

    close();

}

void menu::on_pushButton_3_clicked()
{
    juego *escena = new juego();
    escena->setNivel(3);
    escena->timers();
    escena->setControl(modo);
    escena->show();

    close();
}

int menu::getModo() const
{
    return modo;
}

void menu::setModo(int value)
{
    modo = value;
}

menu::~menu()
{
    delete ui;
}
