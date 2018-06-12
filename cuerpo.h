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
    float getPy() const;
    float getVx() const;
    float getVy() const;
    float getA() const;

    void setPy(float value);
    void setVx(float value);
    void setVy(float value);
    void setA(float value);
    void setPx(float value);

    void setValores(float x,float y, float _Vx, float _Vy);

    void acelerado();
    void velocidad();
    void aceleracion();
    void velocidad_Y();
    void velocidad_X();
};

#endif // CUERPO_H
