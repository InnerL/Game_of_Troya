#include "level_2.h"

Level_2::Level_2(QGraphicsPixmapItem *background) : background(background), backgroundX(0) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level_2::updateBackground);
    timer->start(30);
}

void Level_2::updateBackground() {
    if (backgroundX > -7200) {
        backgroundX -= 2;
        background->setPos(backgroundX, 0);
    }
}
