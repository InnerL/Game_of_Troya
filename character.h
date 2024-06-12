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
    fisica *physics;
    fisica* getPhysics();

    void setLevel(int level);

private slots:
    void updatePhysics2();
    void updatePhysics3();
    void updateAnimationFrame();


private:
    bool movingLeft, movingRight, jumping, tackling;
    QTimer *updateTimer, *tackleTimer;
    const float maxVelocity = 3.0;
    const float friction = 4.0;
    void tackle();
    void tackle3();
    void tackle4();
    void stopTackle();
    void swingSword();
    void destroyObstacle(Obstacle *obstacle);

    QTimer *animationTimer;
    int currentFrame;
    int totalFrames;
    QPixmap spriteSheet;
    int currentLevel; // Variable para almacenar el nivel actual

};

#endif // CHARACTER_H
