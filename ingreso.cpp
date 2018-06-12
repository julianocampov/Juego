#include "ingreso.h"
#include "ui_ingreso.h"

#define RUTA_ARCHIVO "ingreso.txt"

ingreso::ingreso(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ingreso)
{   
    ui->setupUi(this);
    this->setWindowTitle("University Race");
    this->setWindowIcon(QIcon(":/EscUdeA_2.png"));

    //SONIDO CLICK **
    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/s/click_2.mp3"));


    //LEER ARCHIVO PARA USUARIO Y CONTRASEÑA **

    QString line;

    QFile file(RUTA_ARCHIVO);           //Abre archivo.
    file.open(QIODevice::ReadOnly);     //Modo lectura.
    line = file.readLine();             //Trae la linea completa del archivo.
    file.close();                       //Cierra el archivo.

    int n=0;                            //Recorrer el archivo.

    while(n>=0)                         //Indica que no a acabado de leer la linea
    {
        n = line.indexOf(" ");          //Busca un espacio y retorna la posición.
        if(n!=0)
        {
            datos.append(line.left(n)); //Ingresa la linea de texto al QList.
        }
        line = line.remove(0,n+1);      //Borra lo que ya se ingresó.
    }

    n = 0;

    usuario = datos.at(n++);        //Guarda usuario.
    contrasena = datos.at(n++);     //Guarda contraseña

    ui->error->setVisible(false);   //Mensaje de error de usuario o contraseña.
}


void ingreso::on_pushButton_clicked()
{

    int_usuario = ui->rspta_usuario->text();        //Lee el usuario.
    int_contrasena = ui->rspta_contrasena->text();  //Lee la contraseña.
    click->play();

    //VERIFICAR USUARIO Y CONTRASEÑA **
    if (int_usuario == usuario && int_contrasena == contrasena)
    {
        ui->error->setVisible(false);
        QString texto = "WELCOME TO UNIVERSITY RACE. first win the puzzle for play, good luck!";
        QSpacerItem* horizontal = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        caja.setText(texto);
        QGridLayout* layout = (QGridLayout*)caja.layout();
        layout->addItem(horizontal, layout->rowCount(), 0, 1, layout->columnCount());
        caja.setStandardButtons(QMessageBox::Close);
        caja.setDefaultButton(QMessageBox::Close);
        caja.setWindowIcon(QIcon(":/EscUdeA_2.png"));
        caja.exec();

        //EJECUTAR EL PUZZLE**
        puzzle *puzzle_juego = new puzzle();
        puzzle_juego->show();
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
