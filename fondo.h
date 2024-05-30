#ifndef FONDO_H
#define FONDO_H

#include <QWidget>
#include <QPixmap>
#include <QKeyEvent>


class fondo : public QWidget
{
    Q_OBJECT

public:
    explicit fondo(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;


private:
    QPixmap background1; //fondo1
    QPixmap background2; //fondo2
    bool useBackground1; //false

    void toggleBackground();//funcion cambio
};

#endif // FONDO_H
