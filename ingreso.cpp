#include "ingreso.h"
#include "ui_ingreso.h"

#define RUTA_ARCHIVO "ingreso.txt"

ingreso::ingreso(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ingreso)
{   
    ui->setupUi(this);
    this->setWindowTitle("University Race");

    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/s/click_2.mp3"));


    QString line;

    QFile file(RUTA_ARCHIVO);
    file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
    line = file.readLine();
    file.close();

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

   qDebug()<<"USUARIO: "<<datos.at(n++);
   qDebug()<<"CONTRASEÑA: "<<datos.at(n++);

   n = 0;

    usuario = datos.at(n++);
    contrasena = datos.at(n++);

    ui->error->setVisible(false);
}


void ingreso::on_pushButton_clicked()
{

    int_usuario = ui->rspta_usuario->text();
    int_contrasena = ui->rspta_contrasena->text();
    click->play();

    if (int_usuario == usuario && int_contrasena == contrasena)
    {
        modo *modo_juego = new modo();
        modo_juego->show();
        close();
    }
    else
    {
        ui->error->setVisible(true);
    }
}

ingreso::~ingreso()
{
    delete ui;
}
