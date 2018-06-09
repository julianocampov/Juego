#ifndef INGRESO_H
#define INGRESO_H

#include <QWidget>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QGraphicsScene>

#include <QFile>

#include "puzzle.h"

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
    QList<QString> datos;
    QString usuario, int_usuario, contrasena, int_contrasena;
    QMediaPlayer * click;
    QMessageBox caja;

};

#endif // INGRESO_H
