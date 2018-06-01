#include "cuerpograf.h"

Cuerpograf::Cuerpograf(float _Px, float _Py, float _Vx, float _Vy, QString _picture, float _W, float _H)
{
    cuer=new Cuerpo(_Px,_Py,_Vx,_Vy);

    picture = _picture;
    H = _H;
    W = _W;
}

Cuerpograf::~Cuerpograf()
{
    delete cuer;
}

Cuerpo *Cuerpograf::getCuerpo()
{
    return cuer;
}


QRectF Cuerpograf::boundingRect() const
{
    return QRect (0,0,W,H);
}

void Cuerpograf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPixmap pixmap;
    pixmap.load(picture);
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}


void Cuerpograf::Set_pos()
{
    setPos(cuer->getPx(),cuer->getPy());
}

void Cuerpograf::setPicture(const QString &value)
{
    picture = value;
}
