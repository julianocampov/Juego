#ifndef PUZZLE_H
#define PUZZLE_H

#include <QWidget>
#include <QMessageBox>

#include "modo.h"

namespace Ui {
class puzzle;
}

class puzzle : public QWidget
{
    Q_OBJECT

public:

    explicit puzzle(QWidget *parent = 0);
    ~puzzle();

    void sumar();
    void start();
    void reinicio();

public slots:

    void jugar();

private slots:

    void on_IMAGEN_1_clicked();
    void on_IMAGEN_2_clicked();
    void on_IMAGEN_3_clicked();
    void on_IMAGEN_4_clicked();
    void on_IMAGEN_5_clicked();
    void on_IMAGEN_6_clicked();
    void on_IMAGEN_7_clicked();
    void on_IMAGEN_8_clicked();

private:

    Ui::puzzle *ui;
    QTimer *cartas;
    QTimer *play;

    QMessageBox caja;

    int win = 0;
    int cont = 0;
    int vida = 5;

    bool flag = true;
    bool flagB = false;
    bool flag_vida = true;

    bool ima_1 = true;
    bool ima_2 = true;
    bool ima_3 = true;
    bool ima_4 = true;
    bool ima_5 = true;
    bool ima_6 = true;
    bool ima_7 = true;
    bool ima_8 = true;

    int imagen_1 = 1;
    int imagen_2 = 2;
    int imagen_3 = 3;
    int imagen_4 = 4;
    int imagen_5 = 5;
    int imagen_6 = 6;
    int imagen_7 = 7;
    int imagen_8 = 8;

};

#endif // PUZZLE_H
