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
    this->setWindowIcon(QIcon(":/EscUdeA_2.png"));
}

//LEVEL 1 **
void menu::on_pushButton_clicked()
{

    juego *escena = new juego();        //Genera un nuevo juego.
    escena->setNivel(1);                //Indica que level se seleccionó.
    escena->timers();                   //Según el setNivel, se incian los timers.
    escena->setControl(_modo);          //Para saber si es multijugador.
    escena->setCargar(cargar);          //Indica si es para cargar partida.
    escena->cargar_partida();           //Según setCargar, se carga la partida.

    escena->show();                     //Muestra el juego.

    click->play();
    close();
}

//LEVEL 2 **
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

//LEVEL 3 **
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

//INDICA SI ES PARA CARGAR NIVEL **
void menu::on_pushButton_4_clicked()
{
    click->play();
    cargar = 1;
}

//VOLVER AL SELECT MODO **
void menu::on_pushButton_5_clicked()
{
    modo *modo_new = new modo();
    modo_new->show();

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

menu::~menu()
{
    delete ui;
}
