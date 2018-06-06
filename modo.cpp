#include "modo.h"
#include "ui_modo.h"

modo::modo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modo)
{
    ui->setupUi(this);
    this->setWindowTitle("Select modo");

    click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/s/click_2.mp3"));
}


void modo::on_uno_clicked()
{
    menu *ing = new menu();
    ing->setModo(1);
    ing->show();

    click->play();
    close();
}

void modo::on_dos_clicked()
{
    menu *ing = new menu();
    ing->setModo(2);
    ing->show();

    click->play();
    close();
}

modo::~modo()
{
    delete ui;
}
