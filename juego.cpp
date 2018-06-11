#include "juego.h"
#include "ui_juego.h"

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

    //FIN TIMERS **

    //ESCENE CON FONDO **
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("background : transparent");
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/carretera.png")));

    //SONIDOS **
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

//LECTURA DE BOTONES **
void juego::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_D)
    {
        if(inicio)                  //Se inicia cuando se acelera por primera vez.
        {
            timer->start(10);
            timer_mov->start(30);
            timer_gas->start(10000);
            timer_save->start(3000);
            timer_score->start(100);
            timer_bol->start(time1);
            timer_bus->start(time2);

            son_fondo->play();

            inicio = false;
        }

        timer_images->start(10);            //Efecto de movimiento de rudas.
        cargraf->getCuerpo()->aceleracion();//Modifica la Vx (velocidad en x) del carro.
    }

    //SALTAR**
    if (event->key() == Qt::Key_W && cargraf->getCuerpo()->getPy() == 440)
    {
        cargraf->getCuerpo()->setVy(-120);
    }

    //FRENAR **
    if(event->key() == Qt::Key_A)
    {
        cargraf->getCuerpo()->setVx(cargraf->getCuerpo()->getVx()*0.5);
    }

    //PITAR **
    if(event->key()==Qt::Key_P)
    {
        claxon->stop();
        claxon->play();
    }
}

//PARA DESACELERAR **
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


//TIMER_MOV / CAER, MOVIMIENTO DE BUSES, BOLAS Y COLISIONES **
void juego::caer()
{

    //BOLAS **
    for (int i = 0; i < _bolas.size(); i++)
    {
        _bolas.at(i)->actualizar_y();       //Velocidad.
        colision_bola(_bolas.at(i));        //Colisión.
    }

    //BUSES **
    for (int X = 0; X < _bus.size(); X++)
    {
        _bus.at(X)->actualizar_x();         //Velocidad.
        colision_bus(_bus.at(X));           //Colisicón.
    }

    //GASOLINA **
    for (int f = 0; f < _gas.size(); f++)
    {
        colision_gas(_gas.at(f));           //Colisión con gas.
    }

}

//GENERAR BOLAS**
void juego::bolas()
{
    float pos = 400 + rand()% (1000-400);       //Random de posición.

    _bolas.append(new Cuerpograf(0,0,0,0, picture = "", 45, 45));

    //Segun el nivel cambia de imagen**
    if (nivel == 1) _bolas.last()->setPicture(":/rocap.png");
    if (nivel == 2) _bolas.last()->setPicture(":/bola20.png");
    if (nivel == 3) _bolas.last()->setPicture(":/iceball.png");

    _bolas.last()->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+pos, 0, 0, 0); //Asigna posiciones.
    _bolas.last()->set_pos();   //Actualiza la posición asiganada.

    scene->addItem(_bolas.last());  //Añade a la escena.
}

//GENERAR GAS PARA VIDAS **
void juego::gasolina()
{
    float pos_x = 500 +rand()% (2000-500);  //Random X.
    float pos_y = 270 + rand()% (440-270);  //Random Y.

    _gas.append(new Cuerpograf(0, 0, 0, 0, picture = ":/gas.png", 30,40));
    _gas.last()->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+500+pos_x, pos_y, 0,0);
    _gas.last()->set_pos();

    scene->addItem(_gas.last());

}

//COLISION BUS **
void juego::colision_bus(Cuerpograf *bus)
{
    if(cargraf->collidesWithItem(bus))      //Indica si colisiona.
    {
        scene->removeItem(bus);             //Remueve el bus de la escena.
        _bus.removeOne(bus);                //Remueve el bus del QList
        _bus.append(new Cuerpograf(0, 0, 0, 0, picture = "", 0, 0));    //Agrega uno nuevo al QList para no generar problemas.
        vida--;                     //Resta vidas.
        ui->vidas->display(vida);   //Muestras las vidas.
    }

    //INDICA QUE YA PASÓ DE LA ESCENA Y SE BORRA **
    else if(bus->getCuerpo()->getPx() <= cargraf->getCuerpo()->getPx()-20 )
    {
        scene->removeItem(bus);
    }
}

//INDICA QUE COGIÓ UN GAS PARA VIDAS **
void juego::colision_gas(Cuerpograf *gas)
{
    if(cargraf->collidesWithItem(gas))      //Indica que cogió una vida.
    {
        scene->removeItem(gas);             //Remueve.
        _gas.removeOne(gas);
        _gas.append(new Cuerpograf(0,0,0,0, picture = "", 0, 0));

        //INDICADOR PARA NO TENER MAS DE 8 VIDAS **
        if(vida <= 8)
        {
            vida++;
            ui->vidas->display(vida);
        }
    }
}

//COLISIÓN BOLAS **
void juego::colision_bola(Cuerpograf *bola)
{
    if(cargraf->collidesWithItem(bola))
    {
        scene->removeItem(bola);            //Si colisiona con una bola.
        _bolas.removeOne(bola);
        _bolas.append(new Cuerpograf(0,0,0,0, picture = "", 0, 0));
        vida--;
        ui->vidas->display(vida);
    }

    //SE BORRA PASADA LA ESCENA **
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

     //Cambia de imagen según el nivel **
     if(nivel == 1) _bus.last()->setPicture(":/VPOLICE.png");
     if(nivel == 2) _bus.last()->setPicture(":/SWAT.png");
     if(nivel == 3) _bus.last()->setPicture(":/AMBULANCE.png");

     _bus.last()->getCuerpo()->setValores(cargraf->getCuerpo()->getPx()+600+pos, 415, 0, 0);
     _bus.last()->set_pos();

     scene->addItem(_bus.last());
}

//TIMER MOVE, MOVIMIENTO DEL CARRO, CONTROL DE VIDAS, Y MULTIJUGADOR **
void juego::move()
{
    //PARA DESACELERAR **
    if (flag)
    {
       cargraf->getCuerpo()->setVx(cargraf->getCuerpo()->getVx()-0.5);
    }

    //INDICA QUE YA DESACELERÓ LO SUFICIENTE **
    if (cargraf->getCuerpo()->getVx() < 1)
    {
        flag = false;
        timer_images->stop();
    }

    //INDICA QUE PERDIÓ **
    if (vida == 0)
    {
        save();     //Guarda la partida.

        if(control == 2)
        {
            //REINICIA EL CARRO Y CAMBIO DE IMAGEN **
            cargraf->getCuerpo()->setValores(0, 440, 0, 0);
            cargraf->setPicture(":/carro_1.png");
            cargraf->set_pos();

            //REINICIO DE VARIABLES **
            cont_imagen = 4;    //Movimiento de las ruedas del carro.
            stop_timers();      //Para los timers.
            vida = 5;
            ui->vidas->display(vida);

            puntaje_jugador = score;    //Guarda puntaje 1.

            score = 0;
            ui->puntos->display(score);

            QString texto = "Next palyer.";
            QSpacerItem* horizontal = new QSpacerItem(150, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            caja.setText(texto);
            QGridLayout* layout = (QGridLayout*)caja.layout();
            layout->addItem(horizontal, layout->rowCount(), 0, 1, layout->columnCount());
            caja.setStandardButtons(QMessageBox::Close);
            caja.setDefaultButton(QMessageBox::Close);
            caja.exec();

            inicio = true;  //Para iniciar los timers cuando se acelera.
            control++;      //Para no volver a entrar al multijugador.
        }

        //SI YA PERDIÓ O YA JUGARON LOS DOS JUGADORES **
        else
        {
            stop_timers();
            QString texto = "";

            //SI ES MULTIJUGADOR **
            if (control == 3)
            {
                if(puntaje_jugador > score)
                {
                    texto = "THE WINNER IS PLAYER ONE, SCORE "+QString::number(puntaje_jugador);
                }
                else
                {
                    texto = "THE WINNER IS PLAYER TWO, SCORE "+QString::number(score);
                }
            }
            else
            {
                texto = "YOU SCORE "+QString::number(score);
            }

            QSpacerItem* horizontal = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            caja.setText(texto);
            QGridLayout* layout = (QGridLayout*)caja.layout();
            layout->addItem(horizontal, layout->rowCount(), 0, 1, layout->columnCount());
            caja.setStandardButtons(QMessageBox::Close);
            caja.setDefaultButton(QMessageBox::Close);
            caja.exec();

            volver();       //VUELVE AL MENÚ.
        }
    }

    //MOVIMIENTO DEL CARRO **
    scene->setSceneRect(cargraf->getCuerpo()->getPx()-50, 0, 1000, 500);
    cargraf->getCuerpo()->acelerado();
    cargraf->set_pos();
}

//CARGAR PARTIDA **
void juego::cargar_partida()
{
    QString line;

    QFile file(RUTA_ARCHIVO);           //Abrir el archivo.
    file.open(QIODevice::ReadOnly);     //Modo lectura.
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

    //INDICA QUE SELECCIONÓ CARGAR PARTIDA Y TIENE VIDAS **
    if (datos.at(0).toInt() != 0 && cargar == 1)
    {
        cargraf = new Cuerpograf(0, 440, 0, 0, picture = ":/carro_2.png", 130, 55);
        vida = datos.at(n++).toInt();
        score = datos.at(n++).toInt();
    }

    //INDICA QUE NO TIENE VIDAS O JUGÓ DESDE CERO **
    else
    {
        cargraf = new Cuerpograf(0, 440, 0, 0, picture = ":/carro_2.png", 130, 55);
        vida = 5;
        score = 0;
    }

    //AGREGAR EL CARRO A LA ESCENA **
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
    out<<vida<<" "<<score;      //Se gaurda las vidas y el puntaje.

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

    _bus.clear();
    _bolas.clear();

    timer->stop();
    claxon->stop();
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

//VOLVER AL MENÚ **
void juego::volver()
{
    menu *_menu = new menu();
    if (control == 3) _menu->setModo(2);
    _menu->show();
    close();
}

//GUARDAR CON BOTÓN SAVE**
void juego::on_pushButton_clicked()
{
    click->play();
    save();
}

//VOLVER AL MENÚ CON BOTÓN GO BACK **
void juego::on_pushButton_2_clicked()
{
    click->play();
    save();
    stop_timers();
    volver();
}

void juego::setControl(int value)
{
    control = value;
}


void juego::setNivel(int value)
{
    nivel = value;
}


void juego::setCargar(int value)
{
    cargar = value;
}

int juego::getControl() const
{
    return control;
}

int juego::getNivel() const
{
    return nivel;
}

juego::~juego()
{

    delete timer;                 //Timer oficial.
    delete timer_mov;             //Timer parabolico.
    delete timer_bol;             //Timer generar bolas cayendo.
    delete timer_bus;             //Timer buses.
    delete timer_gas;             //Timer gasolina.
    delete timer_save;            //Timer guardar.
    delete timer_score;           //Timer score.
    delete timer_images;          //Timer mov imagen.

    delete cargraf;       //Carro principal.
    delete scene;         //Escena;

    delete ui;
}

