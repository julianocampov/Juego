#include "menu.h"
#include "ingreso.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *plash = new QSplashScreen;
    plash->setPixmap(QPixmap(":/carro_rojo.png"));
    plash->show();
    ingreso w;

    QTimer::singleShot(1000, plash, SLOT(close()));
    QTimer::singleShot(1000, &w, SLOT(show()));

    return a.exec();
}
