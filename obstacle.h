#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Obstacle : public QObject {
    Q_OBJECT

public:
    Obstacle(int x, int y, const QPixmap &pixmap);
    QGraphicsPixmapItem* getItem() const;
    bool isRock() const;
    void setRock(bool rock);
    bool isDestroyed() const;
    void destroy();

private:
    QGraphicsPixmapItem *item;
    bool rock;
    bool destroyed;
};

#endif // OBSTACLE_H
