#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/s/click_2.mp3"));
    this->setWindowTitle("Levels");

}


void menu::on_pushButton_clicked()
{

    juego *escena = new juego();
    escena->setNivel(1);
    escena->timers();
    escena->setControl(_modo);
    escena->setCargar(cargar);
    escena->cargar_partida();

    escena->show();

    click->play();
    close();
}

void menu::on_pushButton_2_clicked()
{

    juego *escena = new juego();
    escena->setNivel(2);
    escena->timers();
    escena->setControl(_modo);
    escena->setCargar(cargar);
    escena->cargar_partida();

    escena->show();

    click->play();
    close();
}

void menu::on_pushButton_3_clicked()
{
    juego *escena = new juego();
    escena->setNivel(3);
    escena->timers();
    escena->setControl(_modo);
    escena->setCargar(cargar);
    escena->cargar_partida();

    escena->show();

    click->play();
    close();
}

void menu::setModo(int value)
{
    _modo = value;
}

int menu::getModo() const
{
    return _modo;
}

void menu::on_pushButton_4_clicked()
{
    click->play();
    cargar = 1;
}

void menu::on_pushButton_5_clicked()
{
    modo *modo_new = new modo();
    modo_new->show();

    click->play();
    close();
}

menu::~menu()
{
    delete ui;
}
