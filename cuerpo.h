#ifndef CUERPO_H
#define CUERPO_H

#include <cmath>
#include <QDebug>

#define dt 0.1
#define g 40

class Cuerpo{

private:

    float Px;
    float Py;
    float Vx;
    float Vy;
    float A=0;

public:

    Cuerpo(float _Px,float _Py,float _Vx,float _Vy);

    float getPx() const;
    void setPx(float value);
    float getPy() const;
    void setPy(float value);
    float getVx() const;
    void setVx(float value);
    float getVy() const;
    void setVy(float value);
    float getA() const;
    void setA(float value);

    void setValores(float x,float y);

    void acelerado();
    void velocidad();
    void aceleracion();
    void velocidad_Y();
    void velocidad_X();
};

#endif // CUERPO_H
