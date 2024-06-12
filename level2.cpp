#include "Level2.h"
#include "qgraphicsscene.h"
#include <cstdlib>
#include <QMessageBox>


Level2::Level2(QGraphicsPixmapItem *background, Character *character, QLabel *counterLabel)
    : background(background), backgroundX(0), character(character), counterLabel(counterLabel), counter(5) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level2::updateBackground);
    timer->start(30);

    createObstacles();

    character->setLevel(2);
    counterLabel->setText("Vida: 5");
}

Level2::~Level2() {
    clearObstacles();
    delete timer;
}


void Level2::updateBackground() {
    if (backgroundX > -3900) {
        backgroundX -= 2;
        background->setPos(backgroundX, 0);
        moveObstaclesWithBackground();
    }

    checkCollisions();


    if (backgroundX <= -3900){
        emit cleanUpRequested(); // Emitir la señal para limpiar recursos
    }

}

void Level2::createObstacles() {
    QPixmap rockPixmap(":/imagen/rock.png");

    int nextPosition = 600;

    while (nextPosition < 24000) {
        Obstacle *obstacle;
        int randomDistance = 400 + std::rand() % 401;
        nextPosition += randomDistance;

        obstacle = new Obstacle(nextPosition, 610, rockPixmap);
        obstacle->setRock(true);

        obstacles.push_back(obstacle);
        background->scene()->addItem(obstacle->getItem());
    }
}

void Level2::checkCollisions() {
    for (Obstacle *obstacle : obstacles) {
        character->checkCollision(obstacle);
    }
}

std::vector<Obstacle*> Level2::getObstacles() const {
    return obstacles;
}

void Level2::moveObstaclesWithBackground() {
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

void Level2::updateCounter() {
    counter--;
    counterLabel->setText("Vida: " + QString::number(counter));
    emit progressUpdated(counter);

    if (counter == 0) {
        emit gameOver();
        stopGame();
    }
}

void Level2::restartGame() {
    counter = 5;
    counterLabel->setText("Vida: 5");
    emit progressUpdated(counter);


    clearObstacles();


    createObstacles();


    character->physics->get_item()->setPos(210, 560);
    character->physics->set_vx(0);
    character->physics->set_vy(0);


    resetBackground();


    timer->start(30);
}

void Level2::resetBackground() {
    backgroundX = 0;
    background->setPos(backgroundX, 0);
}

void Level2::clearObstacles() {
    for (Obstacle *obstacle : obstacles) {
        background->scene()->removeItem(obstacle->getItem());
        delete obstacle;
    }
    obstacles.clear();
}

void Level2::stopGame() {
    timer->stop();
}
