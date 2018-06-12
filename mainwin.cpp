#include "ingreso.h"

#include <QTimer>
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *plash = new QSplashScreen;
    plash->setPixmap(QPixmap(":/EscUdeA_2.png"));
    plash->show();
    ingreso *w = new ingreso();

    QTimer::singleShot(2000, plash, SLOT(close()));
    QTimer::singleShot(2000, w, SLOT(show()));

    return a.exec();
}
