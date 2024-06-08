#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMouseEvent>
#include "fisica.h"
#include "obstacle.h"

class Character : public QObject {
    Q_OBJECT

public:
    Character(int x, int y, int w, int h, QGraphicsPixmapItem *item);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void checkCollision(Obstacle *obstacle);

private slots:
    void updatePhysics();

private:
    fisica *physics;
    bool movingLeft, movingRight, jumping, tackling;
    QTimer *updateTimer, *tackleTimer;
    const float maxVelocity = 3.0;
    const float friction = 4.0;

    void tackle();
    void stopTackle();
    void swingSword();
    void destroyObstacle(Obstacle *obstacle);
};

#endif // CHARACTER_H
