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

    int getModo() const;
    void setModo(int value);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:

    Ui::menu *ui;

    int modo = 0;


};

#endif // MENU_H

