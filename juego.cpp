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

    this->setWindowTitle("University Race");

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
    timer_images->stop();
    connect(timer_score,SIGNAL(timeout()),this,SLOT(imagen()));

    timer_gas = new QTimer();
    timer_gas->stop();
    connect(timer_gas,SIGNAL(timeout()),this,SLOT(gasolina()));

//    timer_coli = new QTimer();
//    timer_coli->start(20);
//    connect(timer_gas,SIGNAL(timeout()),this,SLOT(colision()));


    //FIN TIMERS **

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("background : transparent");
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/carretera.png")));

    acelerar = new QMediaPlayer(this);
    acelerar->setMedia(QUrl("qrc:/s/ace.mp3"));

    claxon = new QMediaPlayer(this);
    claxon->setMedia(QUrl("qrc:/s/claxon.mp3"));
    claxon->setVolume(40);

    son_fondo = new QMediaPlayer(this);
    son_fondo->setMedia(QUrl("qrc:/s/takeon.mp3"));
    son_fondo->setVolume(50);

    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/s/click_2.mp3"));

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
            timer_gas->start(5000);
            timer_save->start(3000);
            timer_score->start(100);
            timer_bol->start(time1);
            timer_bus->start(time2);

            son_fondo->play();

            inicio = false;
        }

        //acelerar->play();
        timer_images->start(10);
        cargraf->getCuerpo()->aceleracion();
    }

    if (event->key() == Qt::Key_W && cargraf->getCuerpo()->getPy() == 440)
    {
        cargraf->getCuerpo()->setVy(-120);
    }

    if(event->key() == Qt::Key_A)
    {

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
        _bolas.at(i)->actualizar_y();
        colision_bola(_bolas.at(i));
    }

    //BUSES **
    for (int X = 0; X < _bus.size(); X++)
    {
        _bus.at(X)->actualizar_x();
        colision_bus(_bus.at(X));
    }

}

//GENERAR BOLAS**

void juego::bolas()
{
    float pos = 400 + rand()% (1000-400);

    _bolas.append(new Cuerpograf(0,0,0,0, picture = "", 45, 45));
    if (nivel == 1) _bolas.last()->setPicture(":/rocap.png");
    if (nivel == 2) _bolas.last()->setPicture(":/bola20.png");
    if (nivel == 3) _bolas.last()->setPicture(":/iceball.png");
    _bolas.last()->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+pos, 0, 0, 0);
    _bolas.last()->set_pos();

    scene->addItem(_bolas.last());
}


void juego::gasolina()
{
    float pos_x = 500 +rand()% (2000-500);
    float pos_y = 270 + rand()% (440-270);

    //_gas.append(new Cuerpograf(0, 0, 0, 0, picture = ":/" ));

}

//COLISION BUS **

void juego::colision_bus(Cuerpograf *bus)
{
    if(cargraf->collidesWithItem(bus))
    {
        scene->removeItem(bus);
        _bus.removeOne(bus);
        _bus.append(new Cuerpograf(0, 0, 0, 0, picture = "", 0, 0));
        vida--;
        ui->vidas->display(vida);
    }

    else if(bus->getCuerpo()->getPx()<=-20)
    {
        scene->removeItem(bus);
    }
}

//COLISIÓN BOLAS **

void juego::colision_bola(Cuerpograf *bola)
{
    if(cargraf->collidesWithItem(bola))
    {
        scene->removeItem(bola);
        _bolas.removeOne(bola);
        _bolas.append(new Cuerpograf(0,0,0,0, picture = "", 0, 0));
        vida--;
        ui->vidas->display(vida);
    }

    else if(bola->getCuerpo()->getPy() > 550)
    {
        scene->removeItem(bola);
    }
}


//GENERAR BUSES **

void juego::bus()
{
     float pos = 400 + rand()% (1000-400);

     _bus.append(new Cuerpograf(0,0,0,0, picture = "", 160, 80));
     if(nivel == 1) _bus.last()->setPicture(":/camioneta.png");
     if(nivel == 2) _bus.last()->setPicture(":/police.png");
     //if(nivel == 3) _bus.last()->setPicture(":/");

     _bus.last()->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+600+pos, 415, 0, 0);
     _bus.last()->set_pos();

     scene->addItem(_bus.last());
}

//TIMER MOVE **

void juego::move()
{
    if (flag)
    {
       cargraf->getCuerpo()->setVx(cargraf->getCuerpo()->getVx()-0.5);
    }

    if (cargraf->getCuerpo()->getVx() < 1)
    {
        flag = false;
        timer_images->stop();
    }

    if (vida == 0)
    {
        save();

        if(control == 2)
        {
            cargraf->getCuerpo()->setValores(0, 440, 0, 0);
            cargraf->setPicture(":/carro_1.png");
            cargraf->set_pos();
            //scene->addItem(cargraf);

            cont_imagen = 4;

            stop_timers();

            vida = 5;
            ui->vidas->display(vida);

            puntaje_jugador = score;

            score = 0;
            ui->puntos->display(score);

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

    if (datos.at(0).toInt() != 0 && cargar == 1)
    {
        cargraf = new Cuerpograf(0, 440, 0, 0, picture = ":/carro_2.png", 130, 55);
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


// CAMBIO DE IMAGEN **

void juego::imagen()
{
    if (cont_imagen >= 0 && control != 3)
    {
        if(cont_imagen == 4) cargraf->setPicture(":/carro_2.png");

        if(cont_imagen == 3) cargraf->setPicture(":/carro_2(1).png");

        if(cont_imagen == 3) cargraf->setPicture(":/carro_2(1,5).png");

        if(cont_imagen == 1) cargraf->setPicture(":/carro_2(2).png");

        if(cont_imagen == 0) cargraf->setPicture(":/carro_2(3).png");
    }

    else if (cont_imagen >= 0 && control == 3)
    {
        if(cont_imagen == 4) cargraf->setPicture(":/carro_1.png");

        if(cont_imagen == 3) cargraf->setPicture(":/carro_1(1).png");

        if(cont_imagen == 3) cargraf->setPicture(":/carro_1(1,5).png");

        if(cont_imagen == 1) cargraf->setPicture(":/carro_1(2).png");

        if(cont_imagen == 0) cargraf->setPicture(":/carro_1(3).png");
    }

    else cont_imagen = 4;

    cont_imagen--;
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
        QPixmap string (":/fondo_2.jpg");
        ui->label->setPixmap(string);
    }

    if (nivel == 3)
    {
        RUTA = "nivel_3.txt";
//        QSize size(200, 200);
//        QMovie *movie = new QMovie(":/tornado.gif");
//        movie->setScaledSize(size);
//        ui->torn->setMovie(movie);
//        movie->start();

//        QSize size_2(500, 300);
//        QMovie *movie_2 = new QMovie(":/cloud rain.gif");
//        movie_2->setScaledSize(size_2);
//        ui->storm->setMovie(movie_2);
//        movie_2->start();

        QPixmap string (":/fondo3.png");
        ui->label->setPixmap(string);
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
    out<<vida<<" "<<score;

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

    //scene->removeItem(cargraf);

    _bus.clear();
    _bolas.clear();

    timer->stop();
    claxon->stop();
    acelerar->stop();
    timer_bol->stop();
    son_fondo->stop();
    timer_bus->stop();
    timer_mov->stop();
    timer_save->stop();
    timer_score->stop();
    timer_images->stop();

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
    click->play();
    save();
}

void juego::on_pushButton_2_clicked()
{
    click->play();
    save();
    stop_timers();
    volver();
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

    delete timer;                 //Timer oficial.
    delete timer_mov;             //Timer parabolico.
    delete timer_bol;             //Timer generar bolas cayendo.
    delete timer_bus;             //Timer buses.
    delete timer_gas;             //Timer gasolina.
    delete timer_save;            //Timer guardar.
    delete timer_coli;            //Timer colisión;
    delete timer_score;           //Timer score.
    delete timer_images;          //Timer mov imagen.

    delete cargraf;            //Carro principal.
    delete scene;         //Escena;

    delete ui;
}

