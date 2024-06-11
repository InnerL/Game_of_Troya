#include "level_2.h"
#include "mainwindow.h"
#include "qgraphicsscene.h"
#include <cstdlib>
#include <ctime>

Level_2::Level_2(QGraphicsPixmapItem *background, Character *character, QLabel *counterLabel)
    : background(background), backgroundX(0), character(character), counterLabel(counterLabel), counter(5) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level_2::updateBackground);
    timer->start(30);

    createObstacles();


    counterLabel->setText("Vida caballo: 5");
}

void Level_2::updateBackground() {
    if (backgroundX > -4400) {
        backgroundX -= 2;
        background->setPos(backgroundX, 0);
        moveObstaclesWithBackground();
    }

    checkCollisions();
}

void Level_2::createObstacles() {
    QPixmap rockPixmap(":/rock-only.png");

    int nextPosition = 600;

    while (nextPosition < 12000) {
        Obstacle *obstacle;
        int randomDistance = 400 + std::rand() % 401;
        nextPosition += randomDistance;

            obstacle = new Obstacle(nextPosition, 610, rockPixmap);
            obstacle->setRock(true);

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
            obstacle->getItem()->moveBy(-12, 0);
            if (obstacle->getItem()->x() <= 210) {
                updateCounter();

                obstacle->destroy();
            }
        }
    }
}

void Level_2::updateCounter() {
    counter--;
    counterLabel->setText("Vida caballo: " + QString::number(counter));
    emit progressUpdated(counter);

    if (counter == 0) {
        emit gameOver();
        stopGame();
    }
}

void Level_2::restartGame() {
    counter = 5;
    counterLabel->setText("Vida caballo: 5");
    emit progressUpdated(counter);


    clearObstacles();


    createObstacles();


    character->physics->get_item()->setPos(210, 560);
    character->physics->set_vx(0);
    character->physics->set_vy(0);


    resetBackground();


    timer->start(30);
}

void Level_2::resetBackground() {
    backgroundX = 0;
    background->setPos(backgroundX, 0);
}

void Level_2::clearObstacles() {
    for (Obstacle *obstacle : obstacles) {
        background->scene()->removeItem(obstacle->getItem());
        delete obstacle;
    }
    obstacles.clear();
}

void Level_2::stopGame() {
    timer->stop();
}
