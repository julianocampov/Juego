#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "juego.h"


namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = 0);
    ~menu();

    void jugador();

    void setPtos_1(int value);

    void setPtos_2(int value);

private slots:

    void on_pushButton_clicked();

private:

    Ui::menu *ui;
    juego *escena;

    int ptos_1 = 0;
    int ptos_2 = 0;
    int cont = 0;

};

#endif // MENU_H

