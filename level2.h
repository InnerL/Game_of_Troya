#ifndef LEVEL2_H
#define LEVEL2_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <vector>
#include "obstacle.h"
#include "character.h"

class Level2 : public QObject {
    Q_OBJECT

public:
    Level2(QGraphicsPixmapItem *background, Character *character);
    std::vector<Obstacle*> getObstacles() const;

private slots:
    void updateBackground();

private:
    QGraphicsPixmapItem *background;
    QTimer *timer;
    int backgroundX;
    std::vector<Obstacle*> obstacles;
    Character *character;

    void createObstacles();
    void checkCollisions();
    void moveObstaclesWithBackground();
};

#endif // LEVEL2_H
