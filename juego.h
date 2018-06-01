#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QtWidgets>
#include <QTimer>
#include <QDebug>
#include <time.h>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>

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
    void bolas();

public:

    juego(QWidget *parent = 0);
    ~juego();

    void volver();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_lcdNumber_overflow();

private:

    Ui::juego *ui;

    int cont_bola = 0;
    int cont_bus = 0;
    int vida = 0;

    float contAC = 0;
    float contREV = 0;
    float X,Y,W,H;

    bool flag = false;
    bool flagD = false;


    QTimer * timer;                 //Timer oficial.
    QTimer * timer_mov;             //Timer parabolico.
    QTimer * timer_bol;             //Timer generar bolas cayendo.
    QTimer * timer_bus;

    QString picture;                //Seleccionar imagenes respectivas.
    Cuerpograf *cargraf;            //Carro principal.
    QGraphicsScene * scene;         //Escena;
    QList < Cuerpograf * > _bus;    //Buses moviendose, obstaculos.
    QList < Cuerpograf * > _bolas;  //Bolas cayendo, obstaculos.

};

#endif // JUEGO_H
