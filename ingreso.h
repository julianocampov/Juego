#ifndef INGRESO_H
#define INGRESO_H

#include <QWidget>
#include <QGraphicsScene>

#include "menu.h"

namespace Ui {
class ingreso;
}

class ingreso : public QWidget
{
    Q_OBJECT

public:
    explicit ingreso(QWidget *parent = 0);
    ~ingreso();

private slots:

    void on_pushButton_clicked();

private:

    Ui::ingreso *ui;
    QString intento, rpta = "hola";

    menu *menu_juego;

};

#endif // INGRESO_H