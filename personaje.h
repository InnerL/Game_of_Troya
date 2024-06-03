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
    void setCollisionAreas(const QVector<QRect> &areas);
    void setMaterials(const QVector<Material*> &materials);

signals:
    void materialCollected(int maderaCount, int piedraCount); // Señal para la recolección de materiales

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;


private slots:
    void updateMovement();
    void nextFrame();


private:
    QPixmap *spriteSheet;
    QTimer *animationTimer;
    QTimer *movementTimer;
    int currentFrame;
    int frameWidth;
    int frameHeight;
    QSet<int> pressedKeys;


    bool checkCollision(int newX, int newY);
    QVector<QRect> collisionAreas;

    QVector<Material*> materials;
    void materialColision();

    int maderaCount; // Contador de madera
    int piedraCount; // Contador de piedra
};

#endif // PERSONAJE_H
