#ifndef MODO_H
#define MODO_H

#include <QWidget>

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

private:
    Ui::modo *ui;

};

#endif // MODO_H
