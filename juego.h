#ifndef JUEGO_H
#define JUEGO_H

#include <QFile>
#include <QTimer>
#include <QDebug>
#include <time.h>
#include <QPixmap>
#include <QWidget>
#include <QtWidgets>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include <QGraphicsScene>


#include "menu.h"
#include "cuerpo.h"
#include "cuerpograf.h"


namespace Ui {
class juego;
}

class juego : public QWidget
{
    Q_OBJECT

public slots:

    void bus();
    void move();
    void caer();
    void save();
    void bolas();
    void imagen();
    void gasolina();
    void stop_timers();
    void sumar_score();
    void cargar_partida();

public:

    juego(QWidget *parent = 0);
    ~juego();

    void volver();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void timers();

    int getNivel() const;
    int getControl() const;


    void setNivel(int value);
    void setControl(int value);
    void setCargar(int value);

    void colision_bus(Cuerpograf *bus);
    void colision_gas(Cuerpograf *gas);
    void colision_bola(Cuerpograf *bola);

private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_close_clicked();

    void on_pause_clicked();

private:

    Ui::juego *ui;

    int vida = 5;
    int paus = 0;
    int time1 = 0;
    int time2 = 0;
    int score = 0;
    int nivel = 0;
    int cargar = 0;
    int control = 0;
    int cont_imagen = 4;

    int puntaje_jugador = 0;

    QMediaPlayer * error;
    QMediaPlayer * click;
    QMediaPlayer * claxon;
    QMediaPlayer * son_blue;
    QMediaPlayer * son_fondo;
    QMediaPlayer * golpe_bola;
    QMediaPlayer * son_africa;
    QMediaPlayer * golpe_carro;

    float X,Y,W,H;

    bool flag = false;
    bool pause = true;
    bool flagD = false;
    bool inicio = true;


    QTimer * timer;                 //Timer oficial.
    QTimer * timer_mov;             //Timer parabolico.
    QTimer * timer_bol;             //Timer generar bolas cayendo.
    QTimer * timer_bus;             //Timer buses.
    QTimer * timer_gas;             //Timer gasolina.
    QTimer * timer_save;            //Timer guardar.
    QTimer * timer_score;           //Timer score.
    QTimer * timer_images;          //Timer mov imagen.

    QString picture;                //Seleccionar imagenes respectivas.
    QMessageBox caja;
    Cuerpograf *cargraf;            //Carro principal.
    QGraphicsScene * scene;         //Escena;
    QList < Cuerpograf * > _bus;    //Buses moviendose, obstaculos.
    QList < Cuerpograf * > _bolas;  //Bolas cayendo, obstaculos.
    QList < Cuerpograf * > _gas;    //Gas BONUS.

};

#endif // JUEGO_H
