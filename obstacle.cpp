#include "obstacle.h"

Obstacle::Obstacle(int x, int y, const QPixmap &pixmap) : QObject(), rock(false), destroyed(false) {
    item = new QGraphicsPixmapItem(pixmap);
    item->setPos(x, y);
}

QGraphicsPixmapItem* Obstacle::getItem() const {
    return item;
}

bool Obstacle::isRock() const {
    return rock;
}

void Obstacle::setRock(bool rock) {
    this->rock = rock;
}

bool Obstacle::isDestroyed() const {
    return destroyed;
}

void Obstacle::destroy() {
    if (!destroyed) {
        destroyed = true;
        delete item;
        item = nullptr;
    }
}
