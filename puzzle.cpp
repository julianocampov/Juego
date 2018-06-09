#include "puzzle.h"
#include "ui_puzzle.h"

puzzle::puzzle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::puzzle)
{
    ui->setupUi(this);

    ui->vidas->display(vida);

    ui->im_1->setVisible(false);
    ui->im_2->setVisible(false);
    ui->im_3->setVisible(false);
    ui->im_4->setVisible(false);
    ui->im_5->setVisible(false);
    ui->im_6->setVisible(false);

    play = new QTimer();
    play->start(30);
    connect(play,SIGNAL(timeout()), this, SLOT(jugar()));
}

void puzzle::jugar()
{
    if(cont == 2)
    {
        qDebug()<<"entre";
        if(imagen_1 == imagen_7)
        {
            ima_1 = ima_7 = false;
            flag_vida = false;
            ui->IMAGEN_1->deleteLater();
            ui->IMAGEN_7->deleteLater();
            win++;
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

        if(flag_vida)
        {
            vida--;
            ui->vidas->display(vida);
        }

        flag_vida = true;
        cont = 0;
        start();

    }
    if(cont >= 3)
    {
        qDebug()<<"si";
        cont = 2;
    }

    if(vida == 0)
    {
        QString texto = "FALLASTE! Inténtalo de nuevo, SUERTE!";
        QSpacerItem* horizontal = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        caja.setText(texto);
        QGridLayout* layout = (QGridLayout*)caja.layout();
        layout->addItem(horizontal, layout->rowCount(), 0, 1, layout->columnCount());
        caja.setStandardButtons(QMessageBox::Close);
        caja.setDefaultButton(QMessageBox::Close);
        caja.exec();

        reinicio();
    }

    if(win == 4)
    {
        modo *modo_juego = new modo();
        play->stop();
        modo_juego->show();
        close();
    }
    qDebug()<<cont;
}

void puzzle::on_IMAGEN_1_clicked()
{
    if(cont <= 2){
        imagen_1 = 0;
        ui->im_1->setVisible(true);
        ui->in_1->setVisible(false);
        ima_1 = true;
        sumar();
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

void puzzle::start()
{
    imagen_1 = 1;
    imagen_2 = 2;
    imagen_3 = 3;
    imagen_4 = 4;
    imagen_5 = 5;
    imagen_6 = 6;
    imagen_7 = 7;
    imagen_8 = 8;

    if(ima_1)
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

void puzzle::reinicio()
{
    puzzle *new_puz = new puzzle();
    new_puz->show();
    play->stop();
    vida=5;
    close();
//    imagen_1 = 1;
//    imagen_2 = 2;
//    imagen_3 = 3;
//    imagen_4 = 4;
//    imagen_5 = 5;
//    imagen_6 = 6;
//    imagen_7 = 7;
//    imagen_8 = 8;

//    vida = 5;
//    ui->vidas->display(vida);

//    ui->im_1->setVisible(false);
//    ui->im_2->setVisible(false);
//    ui->im_3->setVisible(false);
//    ui->im_4->setVisible(false);
//    ui->im_5->setVisible(false);
//    ui->im_6->setVisible(false);

//    ui->in_1->setVisible(true);
//    ui->in_2->setVisible(true);
//    ui->in_3->setVisible(true);
//    ui->in_4->setVisible(true);
//    ui->in_5->setVisible(true);
//    ui->in_6->setVisible(true);
//    ui->in_7->setVisible(true);
//    ui->in_8->setVisible(true);

//    cont = 0;
}

puzzle::~puzzle()
{
    delete ui;
}

void puzzle::sumar()
{
    qDebug()<<"siiiii";
    cont++;
}

