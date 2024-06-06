#ifndef INICIO_H
#define INICIO_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "mainwindow.h"

#include <iostream>
#include <ostream>

class Inicio : public QWidget
{
    Q_OBJECT

public:
    explicit Inicio( QWidget *parent = nullptr);

signals: //Recomendable no usar


public slots:  //timer o boton, activar algun tipo de evento y se puede usar conect
    void iniciarClicked();

private:
    QLabel *backgroundLabel;
    QPushButton *iniciarButton;
    QPushButton *salirButton;


};

#endif // INICIO_H
