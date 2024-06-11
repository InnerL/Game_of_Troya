#include "level_2.h"
#include "qgraphicsscene.h"

Level_2::Level_2(QGraphicsPixmapItem *background, Character *character)
    : background(background), backgroundX(0), character(character) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level_2::updateBackground);
    timer->start(30);  // Update every 30 ms

    createObstacles();
}

void Level_2::updateBackground() {
    if (backgroundX > -4400) {  // 8000 (image width) - 800 (window width)
        backgroundX -= 2;  // Scroll speed
        background->setPos(backgroundX, 0);
        moveObstaclesWithBackground();
    }

    checkCollisions();
}

void Level_2::createObstacles() {
    QPixmap rockPixmap(":/spartan-obs.png");
    QPixmap cactusPixmap(":/spartan-cac.png");

    for (int i = 600; i < 5200; i += 600) {
        Obstacle *obstacle;
        if (i % 600 == 0) {
            obstacle = new Obstacle(i, 600, rockPixmap);
            obstacle->setRock(true);
        } else {
            obstacle = new Obstacle(i, 600, cactusPixmap);
        }
        obstacles.push_back(obstacle);
        background->scene()->addItem(obstacle->getItem());
    }
}

void Level_2::checkCollisions() {
    for (Obstacle *obstacle : obstacles) {
        character->checkCollision(obstacle);
    }
}

std::vector<Obstacle*> Level_2::getObstacles() const {
    return obstacles;
}

void Level_2::moveObstaclesWithBackground() {
    for (Obstacle *obstacle : obstacles) {
        if (!obstacle->isDestroyed()) {
            obstacle->getItem()->moveBy(-2, 0);  // Move with the background speed
        }
    }
}
