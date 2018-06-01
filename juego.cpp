#include "juego.h"
#include "ui_juego.h"

juego::juego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::juego)

{
    X=0, Y=0, W=1000, H=500;

    ui->setupUi(this);
    scene = new QGraphicsScene(X, Y, W, H);
    //scene->setSceneRect(0,0,1000,500);
    cargraf = new Cuerpograf(0,0,0,0, picture = ":/carro_rojo.png", 100, 55);

    // TIMERS**
    int m = 10;
    timer = new QTimer();
    timer->start(m);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer_mov = new QTimer();
    timer_mov->start(20);
    connect(timer_mov,SIGNAL(timeout()),this,SLOT(caer()));

    timer_bol= new QTimer();
    timer_bol->start(600);
    connect(timer_bol,SIGNAL(timeout()),this,SLOT(bolas()));

    timer_bus = new QTimer();
    timer_bus->start(3000);
    connect(timer_bus,SIGNAL(timeout()),this,SLOT(bus()));


    // FIN TIMERS**

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/apo.png")));

    cargraf->getCuerpo()->setValores(0,450);
    cargraf->Set_pos();
    scene->addItem(cargraf);
    scene->setFocusItem(cargraf);

    srand(time(NULL));
}


void juego::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_D)
    {
        cargraf->getCuerpo()->aceleracion();
    }

    if (event->key() == Qt::Key_W && cargraf->getCuerpo()->getPy() == 450)
    {
        cargraf->getCuerpo()->setVy(-130);
    }

    if(event->key()==Qt::Key_A)
    {
        cargraf->getCuerpo()->setVx(cargraf->getCuerpo()->getVx()*0.5);
    }
}

void juego::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        return;
    }

    else if (event->key() == Qt::Key_D)
    {
        flag = true;
    }
}

//TIMER_MOV **

void juego::caer()
{
    //BOLAS **
    for (int i = 0; i < _bolas.size(); i++)
    {
        _bolas[i]->getCuerpo()->velocidad_Y();
        _bolas[i]->Set_pos();
    }

    //COLISIÓN **
    for (int j = 0; j < _bolas.size(); j++)
    {
        if(cargraf->collidesWithItem(_bolas[j]))
        {
            //_bolas[j]->setPicture(":/carro_rojo.png");
            scene->removeItem(_bolas[j]);
        }
    }

    //BUSES **
    for (int X = 0; X < _bus.size(); X++)
    {
        _bus[X]->getCuerpo()->velocidad_X();
        _bus[X]->Set_pos();
    }

    //COLISIÓN **
    for(int Y = 0 ; Y < _bus.size() ; Y++){
        if(_bus[Y]->collidesWithItem(cargraf)){
            scene->removeItem(_bus[Y]);
        }
    }

    //REMOVE PASADA LA ESCENA **
    for(int k=0 ; k < _bus.size() ; k++){
        if(_bus[k]->getCuerpo()->getPx()<=-20){
            scene->removeItem(_bus[k]);
        }
    }
}

//TIMER_BOL **

void juego::bolas()
{
    float pos = 400 + rand()% (1000-400);

    _bolas.append(new Cuerpograf(0,0,0,0, picture = ":/bola_png.png", 90, 90));
    _bolas[cont_bola]->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+pos, 0);
    _bolas[cont_bola]->Set_pos();

    scene->addItem(_bolas[cont_bola]);
    cont_bola++;
}

void juego::bus()
{
     float pos = 400 + rand()% (1000-400);
    _bus.append(new Cuerpograf(0,0,0,0, picture = ":/bus.png", 200, 150));
    _bus[cont_bus]->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+500+pos, 390);
    _bus[cont_bus]->Set_pos();
    scene->addItem(_bus[cont_bus]);
    cont_bus++;
}

//TIMER **

void juego::move()
{
    if (flag){
       cargraf->getCuerpo()->setVx(cargraf->getCuerpo()->getVx()-0.5);
    }
    if (cargraf->getCuerpo()->getVx() < 1) flag = false;

    scene->setSceneRect(cargraf->getCuerpo()->getPx()-50, 0, 1000, 500);
    cargraf->getCuerpo()->acelerado();
    cargraf->Set_pos();
}

juego::~juego()
{
    delete ui;
}
