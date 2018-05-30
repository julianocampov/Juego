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
    cargraf = new Cuerpograf(0,0,0,0, picture = ":/carro_rojo.png", 150, 150);

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

    // FIN TIMERS**

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/fondo.jpg")));

    cargraf->getCuerpo()->setValores(0,400);
    cargraf->Set_pos();
    scene->addItem(cargraf);
    scene->setFocusItem(cargraf);

    srand(time(NULL));
}

juego::~juego()
{
    delete ui;
}

void juego::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_D){

        cargraf->getCuerpo()->aceleracion();

    }

    if (event->key() == Qt::Key_W && cargraf->getCuerpo()->getPy() == 400){

        cargraf->getCuerpo()->setVy(-100);
    }

    if(event->key()==Qt::Key_A){

        cargraf->getCuerpo()->setVx(cargraf->getCuerpo()->getVx()*0.5);

    }
}

void juego::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()){
        return;
    }

    else if (event->key() == Qt::Key_D)
     {
        flag = true;
    }
}

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

void juego::caer()
{
    for (int i = 0; i < _bolas.size(); i++){
        _bolas[i]->getCuerpo()->velocidad_Y();
        _bolas[i]->Set_pos();
    }
    for (int j = 0;j<_bolas.size();j++){
        if(cargraf->collidesWithItem(_bolas[j])){
            scene->removeItem(_bolas[j]);
        }
    }

}


void juego::bolas()
{
    float pos = 400 + rand()% (1000-400);

    _bolas.append(new Cuerpograf(0,0,0,0,picture = ":/bola_png.png", 90, 90));
    _bolas[cont]->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+pos, 0);
    _bolas[cont]->Set_pos();

    scene->addItem(_bolas[cont]);
    cont++;
}
