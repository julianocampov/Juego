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

    void move();
    void caer();
    void bolas();

public:

    juego(QWidget *parent = 0);
    ~juego();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:

    Ui::juego *ui;

    int cont = 0;
    bool hola = false;

    float contAC = 0;
    float contREV = 0;
    float X,Y,W,H;

    bool flag = false;


    QTimer * timer;                 //Timer oficial.
    QTimer * timer_mov;             //Timer parabolico.
    QTimer * timer_bol;             //Timer generar bolas cayendo.

    QString picture;                //Seleccionar imagenes respectivas.
    Cuerpograf *cargraf;            //Carro principal.
    QGraphicsScene * scene;         //Escena;
    QList < Cuerpograf * > _bolas;  //Bolas cayendo, obstaculos.

};

#endif // JUEGO_H