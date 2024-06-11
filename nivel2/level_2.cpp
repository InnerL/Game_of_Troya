#include "level_2.h"
#include "mainwindow.h"
#include "qgraphicsscene.h"

Level_2::Level_2(QGraphicsPixmapItem *background, Character *character, QLabel *counterLabel)
    : background(background), backgroundX(0), character(character), counterLabel(counterLabel), counter(5) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level_2::updateBackground);
    timer->start(30);  // Update every 30 ms

    createObstacles();

    // Initialize the counter label
    counterLabel->setText("Vida caballo: 5");
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
            obstacle->getItem()->moveBy(-10, 0);  // Move with the background speed
            if (obstacle->getItem()->x() <= 210) {
                updateCounter();
                // Optionally, remove the obstacle after counting
                obstacle->destroy();
            }
        }
    }
}

void Level_2::updateCounter() {
    counter--;
    counterLabel->setText("Vida caballo: " + QString::number(counter));
    emit progressUpdated(counter);  // Emit signal to update progress bar

    if (counter == 0) {
        emit gameOver();  // Emit signal to indicate game over
    }
}

void Level_2::restartGame() {
    counter = 5;
    counterLabel->setText("Vida caballo: 5");
    emit progressUpdated(counter);  // Reset progress bar

    // Clear existing obstacles
    for (Obstacle *obstacle : obstacles) {
        delete obstacle;
    }
    obstacles.clear();

    // Recreate obstacles
    createObstacles();

    // Reset character position and velocities
    character->physics->get_item()->setPos(210, 560);
    character->physics->set_vx(0);
    character->physics->set_vy(0);
    // Reset background position
    resetBackground();
}

void Level_2::resetBackground() {
    backgroundX = 0;
    background->setPos(backgroundX, 0);
}
