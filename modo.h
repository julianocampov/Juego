#ifndef MODO_H
#define MODO_H

#include <QWidget>

#include "menu.h"

namespace Ui {
class modo;
}

class modo : public QWidget
{
    Q_OBJECT

public:

    explicit modo(QWidget *parent = 0);
    ~modo();

private slots:

    void on_uno_clicked();
    void on_dos_clicked();

private:

    Ui::modo *ui;

};

#endif // MODO_H
