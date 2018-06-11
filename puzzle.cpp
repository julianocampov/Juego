#include "puzzle.h"
#include "ui_puzzle.h"

puzzle::puzzle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::puzzle)
{
    ui->setupUi(this);

    ui->vidas->display(vida);

    //TAPA LAS IMAGENES **

    ui->im_1->setVisible(false);
    ui->im_2->setVisible(false);
    ui->im_3->setVisible(false);
    ui->im_4->setVisible(false);
    ui->im_5->setVisible(false);
    ui->im_6->setVisible(false);

    play = new QTimer();
    play->start(30);
    connect(play,SIGNAL(timeout()), this, SLOT(jugar()));

    this->setWindowTitle("Puzzle University Race");
}

//BUSCA SI SON CORRRECTAS LAS CARTAS SELECCIONADAS **
void puzzle::jugar()
{
    if(cont == 2)
    {
        if(imagen_1 == imagen_7)            //Son iguales **
        {
            ima_1 = ima_7 = false;          //Para que no se tapen las cartas de nuevo.
            flag_vida = false;              //Para no restar vidas.
            ui->IMAGEN_1->deleteLater();    //Borra el botón para no generar problemas.
            ui->IMAGEN_7->deleteLater();    //Borra el botón para no generar problemas.
            win++;                          //Indica que ya hay una cartas acertadas.
        }
        if(imagen_2 == imagen_6)
        {
            ima_2 = ima_6 = false;
            flag_vida = false;
            ui->IMAGEN_2->deleteLater();
            ui->IMAGEN_6->deleteLater();
            win++;
        }
        if(imagen_5 == imagen_8)
        {
            ima_5 = ima_8 = false;
            flag_vida = false;
            ui->IMAGEN_5->deleteLater();
            ui->IMAGEN_8->deleteLater();
            win++;
        }

        if(imagen_3 == imagen_4)
        {
            ima_3 = ima_4 = false;
            flag_vida = false;
            ui->IMAGEN_3->deleteLater();
            ui->IMAGEN_4->deleteLater();
            win++;
        }

        //SI NO ACERTÓ **
        if(flag_vida)
        {
            vida--;
            ui->vidas->display(vida);
        }

        //REINICIA CONT Y FLAG_VIDA **
        flag_vida = true;
        cont = 0;
        start();

    }

    //SI SE SELECCIONAN MAS DE DOS CARTAS **
    if(cont >= 3)
    {
        cont = 2;
    }

    //SI PIERDE SE REINICIA TODO **
    if(vida == 0)
    {
        QString texto = "YOU FAILED. Try again, GOOD LUCK!";
        QSpacerItem* horizontal = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        caja.setText(texto);
        QGridLayout* layout = (QGridLayout*)caja.layout();
        layout->addItem(horizontal, layout->rowCount(), 0, 1, layout->columnCount());
        caja.setStandardButtons(QMessageBox::Close);
        caja.setDefaultButton(QMessageBox::Close);
        caja.exec();

        reinicio();
    }

    //PASAR EL PUZZLE, GENERA SELECT MODO **

    if(win == 4)
    {
        modo *modo_juego = new modo();
        play->stop();
        modo_juego->show();
        close();
    }
}


//MOSTRAR IMAGENES AL PRESIONAR UN BOTÓN **
void puzzle::on_IMAGEN_1_clicked()
{
    if(cont <= 2){                      //Deja mostrar si no se han presionado mas de dos.
        imagen_1 = 0;                   //Indica que fue seleccionada.
        ui->im_1->setVisible(true);     //Muestra la imagen.
        ui->in_1->setVisible(false);    //Quita la de imagen de interrogación.
        ima_1 = true;                   //Para que no se Tape la imagen.
        sumar();                        //Suma al contador para indicar que ya hay una ficha seleccionada.
    }
}

void puzzle::on_IMAGEN_2_clicked()
{
    if(cont <= 2){
        imagen_2 = 0;
        ui->im_2->setVisible(true);
        ui->in_2->setVisible(false);
        ima_2 = true;
        sumar();
    }
}

void puzzle::on_IMAGEN_3_clicked()
{
    if(cont <= 2){
        imagen_3 = 0;
        ui->im_3->setVisible(true);
        ui->in_3->setVisible(false);
        ima_3 = true;
        sumar();
    }
}

void puzzle::on_IMAGEN_4_clicked()
{
    if(cont <= 2){
        imagen_4 = 0;
        ui->im_4->setVisible(true);
        ui->in_4->setVisible(false);
        ima_4 = true;
        sumar();
    }
}

void puzzle::on_IMAGEN_5_clicked()
{
    if(cont <= 2){
       imagen_5 = 0;
       ui->im_5->setVisible(true);
       ui->in_5->setVisible(false);
       ima_5 = true;
       sumar();
    }
}


void puzzle::on_IMAGEN_6_clicked()
{
    if(cont <= 2){
        imagen_6 = 0;
        ui->im_6->setVisible(true);
        ui->in_6->setVisible(false);
        ima_6 = true;
        sumar();
    }
}

void puzzle::on_IMAGEN_7_clicked()
{
    if(cont <= 2){
        imagen_7 = 0;
        ui->im_7->setVisible(true);
        ui->in_7->setVisible(false);
        ima_7 = true;
        sumar();
    }
}

void puzzle::on_IMAGEN_8_clicked()
{
    if(cont <= 2){
        imagen_8 = 0;
        ui->im_8->setVisible(true);
        ui->in_8->setVisible(false);
        ima_8 = true;
        sumar();
    }
}

//REINICIA TODO **
void puzzle::start()
{
    //REINICIA VARIABLES **

    imagen_1 = 1;
    imagen_2 = 2;
    imagen_3 = 3;
    imagen_4 = 4;
    imagen_5 = 5;
    imagen_6 = 6;
    imagen_7 = 7;
    imagen_8 = 8;

    if(ima_1)                           //Si es false, deja la imagen que es y no muestra la de interrogación.
    {
        ui->im_1->setVisible(false);
        ui->in_1->setVisible(true);
    }

    if(ima_2)
    {
        ui->im_2->setVisible(false);
        ui->in_2->setVisible(true);
    }

    if(ima_3)
    {
        ui->im_3->setVisible(false);
        ui->in_3->setVisible(true);
    }

    if(ima_4)
    {
        ui->im_4->setVisible(false);
        ui->in_4->setVisible(true);
    }

    if(ima_5)
    {
        ui->im_5->setVisible(false);
        ui->in_5->setVisible(true);
    }

    if(ima_6)
    {
        ui->im_6->setVisible(false);
        ui->in_6->setVisible(true);
    }

    if(ima_7)
    {
        ui->im_7->setVisible(false);
        ui->in_7->setVisible(true);
    }

    if(ima_8)
    {
        ui->im_8->setVisible(false);
        ui->in_8->setVisible(true);
    }
}

//SI PIERDE SE EJECUTA DE NUEVO **

void puzzle::reinicio()
{
    puzzle *new_puz = new puzzle();
    new_puz->show();
    play->stop();
    vida=5;
    close();
}

void puzzle::sumar()
{
    cont++;
}

puzzle::~puzzle()
{
    delete ui;
}


