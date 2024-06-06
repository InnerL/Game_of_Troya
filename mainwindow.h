#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "personaje.h"
#include "fondo.h"
#include <QLabel>
#include <QTimer>

#include <iostream>
#include <ostream>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createScene1();


protected:
    void mousePressEvent(QMouseEvent *event);


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Personaje *personaje;
    Fondo *fondo;
    QLabel *labelCont;  //Contador de objetos recogidos
    QLabel *labelCountdown; //Regresiva
    QLabel *labelhistory; //Historia
    int countdownValue;
    QTimer *countdownTimer;

    void labelN1();
    void createFondo();
    void createPersonaje();
    void addMaterials();
    void configureGraphicsView();
    void adjustWindowSizeToGraphicsView();

private slots:
    void updateCountdown();

};
#endif // MAINWINDOW_H
