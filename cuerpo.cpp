#include "cuerpo.h"

float Cuerpo::getPy() const
{
    return Py;
}

float Cuerpo::getVx() const
{
    return Vx;
}

void Cuerpo::setVx(float value)
{
    Vx = value;
}

float Cuerpo::getPx() const
{
    return Px;
}

float Cuerpo::getVy() const
{
    return Vy;
}

void Cuerpo::setVy(float value)
{
    Vy = value;
}

float Cuerpo::getA() const
{
    return A;
}

void Cuerpo::setA(float value)
{
    A = value;
}

void Cuerpo::setPy(float value)
{
    Py = value;
}

void Cuerpo::setPx(float value)
{
    Px = value;
}

Cuerpo::Cuerpo(float _Px, float _Py, float _Vx, float _Vy)
{
    Px = _Px;
    Py = _Py;
    Vx = _Vx;
    Vy = _Vy;

}

void Cuerpo::setValores(float x, float y)
{
    Px = x;
    Py = y;
}

void Cuerpo::setneg(float value)
{
    Px -= value;
    Py -= value;
}

void Cuerpo::acelerado()
{
    velocidad();

    Px = Px + Vx*dt;
    Py = Py + Vy*dt + g*pow(dt,2)*0.5;

    if (Py>=400)
    {
        Py = 400;
    }
}

void Cuerpo::aceleracion()
{
    if (Vx >= 50){
        Vx = Vx;
    }
    else
    {
        Vx = Vx + 20*dt;
    }
}

void Cuerpo::velocidad()
{
    Vy = Vy + g*dt;
}

void Cuerpo::velocidad_Y()
{
    Vy = Vy + g*dt;
    Py = Py + Vy*dt + 2*pow(dt,2)*0.5;

}


