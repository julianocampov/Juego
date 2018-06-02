#ifndef CUERPOGRAF_H
#define CUERPOGRAF_H

#include <string>
#include <QObject>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "cuerpo.h"

class Cuerpograf : public QGraphicsItem,public QObject
{
public:

    Cuerpograf(float _Px,float _Py,float _Vx,float _Vy, QString _picture, float _W, float _H);
    ~Cuerpograf();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void pintar();
    Cuerpo * getCuerpo();
    void Set_pos();

    void setPicture(const QString &value);

private:

    Cuerpo *cuer;
    QString picture;

    float W, H;
    int cont = 0;

};

#endif // CUERPOGRAF_H
