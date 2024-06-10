#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "material.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>

#include <QSet>
#include <QVector>
#include <QRect>



class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Personaje(QGraphicsItem *parent = nullptr);
    void setCollisionAreas(const QVector<QPair<QRect, bool>> &areas);
    void setMaterials(const QVector<Material*> &materials);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;



private slots:
    void updateMovement();
    void nextFrame();
    void updateRebound();//rebote

signals:
    void objectCollected(int collectedCount); // Señal para notificar cuando se recoge un objeto

private:
    QPixmap *spriteSheet;
    QTimer *animationTimer;
    QTimer *movementTimer;
    int currentFrame;
    int frameWidth;
    int frameHeight;
    QSet<int> pressedKeys;
    
    
    bool checkCollision(int newX, int newY, bool *isBorderCollision);
    QVector<QPair<QRect, bool>> collisionAreas;

    QVector<Material*> materials;
    void materialColision();


    int collectedCount = 0;//contador objeto
    bool facingLeft; // true izquierda, false si está mirando a la derecha

    QTimer *reboundTimer;  // Nuevo temporizador para el rebote
    int reboundSteps;      // Número de pasos para el rebote
    int reboundDeltaX;     // Incremento X en cada paso del rebote
    int reboundDeltaY;     // Incremento Y en cada paso del rebote

    //
};

#endif // PERSONAJE_H
