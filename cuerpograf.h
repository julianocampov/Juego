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

    Cuerpo * getCuerpo();
    void setPicture(const QString &value);
    void set_pos();

private:

    Cuerpo *cuer;
    QString picture;

    float W, H;
    int cont = 0;

};

#endif // CUERPOGRAF_H
