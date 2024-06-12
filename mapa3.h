#ifndef MAPA3_H
#define MAPA3_H

#include <Qmainwindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include "character.h"
#include <QLabel>
#include <QTimer>


/*declaración anticipada, o forward declarationes una técnica utilizada en C++ para
  informar al compilador sobre la existencia de una clase antes de su definición completa.
  Esto es útil para evitar dependencias circulares y reducir los tiempos de compilación.
 */
class level3;


class   Mapa3 : public QMainWindow {
    Q_OBJECT

public:
    Mapa3(QWidget *parent = nullptr);
    ~Mapa3();

    void updateVida();
    void resetLevel();
    void stopGame(const QString &message);  // Añade esta función




protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void updateCountdown();


private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Character *character;
    level3 *level;

    QLabel *labelCont;      //Contador de objetos recogidos
    QLabel *labelCountdown; //Regresiva
    QLabel *labelhistory;   //Historia
    int countdownValue;
    QTimer *countdownTimer;


    int vida;


    void labelN1();
};

#endif // MAPA3_H
