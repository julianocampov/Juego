#include "juego.h"
#include "ui_juego.h"

#include "menu.h"

#define RUTA_ARCHIVO "info.txt"

juego::juego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::juego)

{

    X=0, Y=0, W=1000, H=500;

    ui->setupUi(this);
    scene = new QGraphicsScene(X, Y, W, H);

    //TIMERS **

    timer_bol= new QTimer();
    timer_bol->stop();
    connect(timer_bol,SIGNAL(timeout()),this,SLOT(bolas()));

    timer_bus = new QTimer();
    timer_bus->stop();
    connect(timer_bus,SIGNAL(timeout()),this,SLOT(bus()));

    timer = new QTimer();
    timer->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer_mov = new QTimer();
    timer_mov->stop();
    connect(timer_mov,SIGNAL(timeout()),this,SLOT(caer()));

    timer_save = new QTimer();
    timer_save->stop();
    connect(timer_save,SIGNAL(timeout()),this,SLOT(save()));

    timer_score = new QTimer();
    timer_score->stop();
    connect(timer_score,SIGNAL(timeout()),this,SLOT(sumar_score()));

    timer_images = new QTimer();
    timer_images->start(10);
    connect(timer_score,SIGNAL(timeout()),this,SLOT(imagen()));

    //FIN TIMERS **

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("background : transparent");
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/carretera.png")));

    acelerar = new QMediaPlayer(this);
    acelerar->setMedia(QUrl("qrc:/s/ace.mp3"));

    claxon = new QMediaPlayer(this);
    claxon->setMedia(QUrl("qrc:/s/claxon.mp3"));
    claxon->setVolume(60);

    son_fondo = new QMediaPlayer(this);
    son_fondo->setMedia(QUrl("qrc:/s/takeon.mp3"));

    srand(time(NULL));
}


void juego::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_D)
    {
        if(inicio)
        {
            timer->start(10);
            timer_mov->start(30);
            timer_save->start(3000);
            timer_score->start(100);
            timer_bol->start(time1);
            timer_bus->start(time2);
            son_fondo->play();

            inicio = false;
        }

        //acelerar->play();

        cargraf->getCuerpo()->aceleracion();
    }

    if (event->key() == Qt::Key_W && cargraf->getCuerpo()->getPy() == 440)
    {
        cargraf->getCuerpo()->setVy(-120);
    }

    if(event->key()==Qt::Key_A)
    {
        cargraf->getCuerpo()->setVx(cargraf->getCuerpo()->getVx()*0.5);
    }

    if(event->key()==Qt::Key_P)
    {
        claxon->stop();
        claxon->play();
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
        acelerar->stop();
        flag = true;
    }
}


//TIMER_MOV / CAER **

void juego::caer()
{

    //BOLAS **
    for (int i = 0; i < _bolas.size(); i++)
    {
        _bolas.at(i)->getCuerpo()->velocidad_Y();
        _bolas.at(i)->set_pos();
    }

    //COLISIÓN BOLAS **
    for (int j = 0; j < _bolas.size(); j++)
    {
        if(cargraf->collidesWithItem(_bolas.at(j)))
        {
             scene->removeItem(_bolas.at(j));
            _bolas.removeOne(_bolas.at(j));
            _bolas.append(new Cuerpograf(0,0,0,0, picture = "", 1, 1));
            vida--;
            ui->vidas->display(vida);
        }
    }

    //REMUEVE DE LA ESCENA BOLAS **
    for (int H = 0; H < _bolas.size(); H++)
    {
        if(_bolas.at(H)->getCuerpo()->getPy() > 550)
        {
            scene->removeItem(_bolas.at(H));
        }
    }

    //BUSES **
    for (int X = 0; X < _bus.size(); X++)
    {
        _bus.at(X)->getCuerpo()->velocidad_X();
        _bus.at(X)->set_pos();
    }

    //COLISIÓN BUSES **
    for(int Y = 0 ; Y < _bus.size() ; Y++)
    {
        if(cargraf->collidesWithItem(_bus.at(Y)))
        {
            scene->removeItem(_bus.at(Y));
            _bus.removeOne(_bus.at(Y));
            _bus.append(new Cuerpograf(cargraf->getCuerpo()->getPx()+600, 600,0,0, picture = "", 1, 1));
            vida--;
            ui->vidas->display(vida);
        }
    }

    //REMUEVE DE LA ESCENA BUSES **
    for(int k=0 ; k < _bus.size() ; k++)
    {
        if(_bus.at(k)->getCuerpo()->getPx()<=-20)
        {
            scene->removeItem(_bus.at(k));
        }
    }
}

//GENERAR BOLAS**

void juego::bolas()
{
    float pos = 400 + rand()% (1000-400);

    _bolas.append(new Cuerpograf(0,0,0,0, picture = ":/rocap.png", 60, 60));
    _bolas.last()->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+pos, 0, 0, 0);
    _bolas.last()->set_pos();

    scene->addItem(_bolas.last());
}

void juego::imagen()
{
    if (cont_imagen >= 0)
    {
        if(cont_imagen == 3) cargraf->setPicture(":/carro_2.png");

        if(cont_imagen == 2) cargraf->setPicture(":/carro_2(1).png");

        if(cont_imagen == 1) cargraf->setPicture(":/carro_2(2).png");

        if(cont_imagen == 0) cargraf->setPicture(":/carro_2(3).png");
    }
    else cont_imagen = 3;

    cont_imagen--;

}


//GENERAR BUSES **

void juego::bus()
{
     float pos = 400 + rand()% (1000-400);

     _bus.append(new Cuerpograf(0,0,0,0, picture = ":/bus.png", 180, 100));
     _bus.last()->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+600+pos, 400, 0, 0);
     _bus.last()->set_pos();

     scene->addItem(_bus.last());
}

//TIMER **

void juego::move()
{
    if (flag)
    {
       cargraf->getCuerpo()->setVx(cargraf->getCuerpo()->getVx()-0.5);
    }

    if (cargraf->getCuerpo()->getVx() < 1) flag = false;

    if (vida == 0)
    {
        save();

        if(control == 2)
        {
            cargraf->getCuerpo()->setValores(0, 440, 0, 0);
            cargraf->setPicture(picture = ":/carro_1.png");
            cargraf->set_pos();

            vida = 5;
            ui->vidas->display(vida);

            score = 0;
            ui->puntos->display(score);

            stop_timers();

            puntaje_jugador = score;
            inicio = true;
            control++;
        }

        else
        {
            stop_timers();
            QString texto = "";

            if (control == 3)
            {
                if(puntaje_jugador > score)
                {
                    texto = "El ganador fue el jugador 1, puntaje "+QString::number(puntaje_jugador);
                }
                else
                {
                    texto = "El ganador fue el jugador 2, puntaje "+QString::number(score);
                }
            }
            else
            {
                texto = "Puntaje "+QString::number(score);
            }

            QSpacerItem* horizontal = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            caja.setText(texto);
            QGridLayout* layout = (QGridLayout*)caja.layout();
            layout->addItem(horizontal, layout->rowCount(), 0, 1, layout->columnCount());
            caja.setStandardButtons(QMessageBox::Close);
            caja.setDefaultButton(QMessageBox::Close);
            caja.exec();

            volver();
        }
    }

    scene->setSceneRect(cargraf->getCuerpo()->getPx()-50, 0, 1000, 500);
    cargraf->getCuerpo()->acelerado();
    cargraf->set_pos();
}

//CARGAR PARTIDA **

void juego::cargar_partida()
{
    QString line;

    QFile file(RUTA_ARCHIVO);
    file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
    line = file.readLine();
    file.close();

    QList<QString> datos;

    int n=0;

    while(n>=0)
    {
        n = line.indexOf(" ");
        if(n!=0)
        {
            datos.append(line.left(n));
        }
        line = line.remove(0,n+1);
    }

    n = 0;

    if (datos.at(2).toInt() != 0 && cargar == 1)
    {
        n++;
        cargraf = new Cuerpograf(0, datos.at(n++).toFloat(), 0, 0, picture = ":/carro_2.png", 130, 55);
        vida = datos.at(n++).toInt();
        score = datos.at(n++).toInt();
    }

    else
    {
        cargraf = new Cuerpograf(0, 440, 0, 0, picture = ":/carro_2.png", 130, 55);
        vida = 5;
        score = 0;
    }

    cargraf->set_pos();
    scene->addItem(cargraf);
    scene->setFocusItem(cargraf);
    scene->setSceneRect(cargraf->getCuerpo()->getPx()-50, 0, 1000, 500);

    ui->vidas->display(vida);
    ui->puntos->display(score);

}


//TIMERS / DIFICULTAD**

void juego::timers()
{
    QString RUTA = "";

    if (nivel == 1)
    {
        RUTA = "nivel_1.txt";
        QPixmap string (":/FondoUDEA.jpg");
        ui->label->setPixmap(string);
    }

    if (nivel == 2)
    {
        RUTA = "nivel_2.txt";
        QPixmap string (":/fondo3.jpg");
        ui->label->setPixmap(string);
    }

    if (nivel == 3)
    {
        RUTA = "nivel_3.txt";
    }

    //LEER ARCHIVO **

    QString line;
    QFile file(RUTA);
    file.open(QIODevice::ReadOnly);
    line = file.readLine();
    file.close();

    QList<QString> datos;

    int n=0;

    while(n>=0)
    {
        n = line.indexOf(" ");
        if(n!=0)
        {
            datos.append(line.left(n));
        }
        line = line.remove(0,n+1);
    }

    n = 0;

    //ASIGNAR DATOS **

    time1 = datos.at(n++).toInt();      //Timer bolas.
    time2 = datos.at(n++).toInt();      //Timer buses.
}

//GUARDAR PARTIDA **

void juego::save()
{
    QFile file(RUTA_ARCHIVO);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out<<cargraf->getCuerpo()->getPy()<<" "<<cargraf->getCuerpo()->getPx()<<" "<<vida<<" "<<score;

    file.close();
}

// STOP TIMERS **

void juego::stop_timers()
{

    //REMUEVE DE LA ESCENA BOLAS **
    for (int H = 0; H < _bolas.size(); H++)
    {
        scene->removeItem(_bolas.at(H));
    }

    //REMUEVE DE LA ESCENA BUSES **
    for(int k=0 ; k < _bus.size() ; k++)
    {
        scene->removeItem(_bus.at(k));
    }

    scene->removeItem(cargraf);

    _bus.clear();
    _bolas.clear();

    timer->stop();
    acelerar->stop();
    timer_bol->stop();
    son_fondo->stop();
    timer_bus->stop();
    timer_mov->stop();
    timer_save->stop();
    timer_score->stop();

}

//TIMER SCORE**

void juego::sumar_score()
{
    score++;
    ui->puntos->display(score);
}

//VOLVER **

void juego::volver()
{
    menu *_menu = new menu();
    if (control == 3) _menu->setModo(2);
    _menu->show();
    close();
}

void juego::on_pushButton_clicked()
{
    save();
}

int juego::getControl() const
{
    return control;
}

void juego::setControl(int value)
{
    control = value;
}

int juego::getNivel() const
{
    return nivel;
}

void juego::setNivel(int value)
{
    nivel = value;
}



void juego::setCargar(int value)
{
    cargar = value;
}

juego::~juego()
{
    delete ui;
}
