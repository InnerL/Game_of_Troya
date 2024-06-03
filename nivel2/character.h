#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "fisica.h"

class Character : public QObject {
    Q_OBJECT

public:
    Character(int x, int y, int w, int h, QGraphicsPixmapItem *item);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void updatePhysics();

private:
    fisica *physics;
    bool movingLeft, movingRight, jumping;
    QTimer *updateTimer;
    const float maxVelocity = 5.0;
    const float friction = 0.2;
};

#endif // CHARACTER_H
