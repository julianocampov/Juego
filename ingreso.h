#ifndef INGRESO_H
#define INGRESO_H

#include <QWidget>
#include <QGraphicsScene>

#include "menu.h"
#include <QFile>

namespace Ui {
class ingreso;
}

class ingreso : public QWidget
{
    Q_OBJECT

public:
    explicit ingreso(QWidget *parent = 0);
    ~ingreso();

    int modo() const;
    void setModo(int modo);

private slots:

    void on_pushButton_clicked();

private:

    Ui::ingreso *ui;
    QString intento, rpta = "d";

    int _modo = 0;

    menu *menu_juego;

};

#endif // INGRESO_H
