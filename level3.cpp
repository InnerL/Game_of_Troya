#include "level3.h"
#include "qgraphicsscene.h"

Level3::Level3(QGraphicsPixmapItem *background, Character *character)
    : background(background), backgroundX(0), character(character) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level3::updateBackground);
    timer->start(16);  // Update every 30 ms

    createObstacles();
}

void Level3::updateBackground() {
    if (backgroundX > -7200) {  // 8000 (image width) - 800 (window width)
        backgroundX -= 2;  // Scroll speed
        background->setPos(backgroundX, 0);
        moveObstaclesWithBackground();
    }

    checkCollisions();
}

void Level3::createObstacles() {
    QPixmap rockPixmap(":/spartan-obs.png");
    QPixmap cactusPixmap(":/spartan-cac.png");

    for (int i = 800; i < 8000; i += 800) {
        Obstacle *obstacle;
        if (i % 1600 == 0) {
            obstacle = new Obstacle(i, 910, rockPixmap);
            obstacle->setRock(true);
        } else {
            obstacle = new Obstacle(i, 910, cactusPixmap);
        }
        obstacles.push_back(obstacle);
        background->scene()->addItem(obstacle->getItem());
    }
}

void Level3::checkCollisions() {
    for (Obstacle *obstacle : obstacles) {
        character->checkCollision(obstacle);
    }
}

std::vector<Obstacle*> Level3::getObstacles() const {
    return obstacles;
}

void Level3::moveObstaclesWithBackground() {
    for (Obstacle *obstacle : obstacles) {
        if (!obstacle->isDestroyed()) {
            obstacle->getItem()->moveBy(-2, 0);  // Move with the background speed
        }
    }
}
