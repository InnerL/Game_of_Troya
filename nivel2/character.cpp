#include "character.h"
#include "level_2.h"
#include <iostream>
#include <ostream>

Character::Character(int x, int y, int w, int h, QGraphicsPixmapItem *item) :
    movingLeft(false), movingRight(false), jumping(false), tackling(false) {
    physics = new fisica(x, y, w, h, item);
    physics->set_initial_conditions(x, y, 0, 0);

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Character::updatePhysics);
    updateTimer->start(10);

    tackleTimer = new QTimer(this);
    tackleTimer->setSingleShot(true);
    connect(tackleTimer, &QTimer::timeout, this, &Character::stopTackle);
}

void Character::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        movingLeft = true;
    } else if (event->key() == Qt::Key_D) {
        movingRight = true;
    } else if (event->key() == Qt::Key_Space) {
        if (!jumping) {
            physics->jump();
            jumping = true;
        }
    }
}

void Character::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        movingLeft = false;
    } else if (event->key() == Qt::Key_D) {
        movingRight = false;
    }
}

void Character::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        tackle();
    } else if (event->button() == Qt::LeftButton) {
        swingSword();
    }
}

void Character::updatePhysics() {
    float ax = 0.0;
    if (movingLeft) {
        ax = -3.0;
    } else if (movingRight) {
        ax = 3.0;
    } else {
        ax = -physics->get_vx() * friction;
    }

    physics->calculate_cinematics(ax, 0);


    physics->calculate_parabolic_dynamics();


    if (physics->get_vx() > maxVelocity) {
        physics->set_vx(maxVelocity);
    } else if (physics->get_vx() < -maxVelocity) {
        physics->set_vx(-maxVelocity);
    }


    float characterX = physics->get_simulated_x(physics->get_x());
    QGraphicsPixmapItem *item = physics->get_item();
    if (characterX < 210) {
        physics->x = physics->get_phisical_x(210);
        physics->set_vx(0);
    } else if (characterX > 1280 - item->pixmap().width()) {
        physics->x = physics->get_phisical_x(1280 - item->pixmap().width());
        physics->set_vx(0);
    }


    if (physics->get_simulated_y(physics->get_y()) >= 600) {
        physics->set_y(physics->get_phisical_y(600));
        physics->set_vy(0);
        jumping = false;
    }
}

void Character::checkCollision(Obstacle *obstacle) {
    if (!obstacle->isDestroyed() && physics->get_item()->collidesWithItem(obstacle->getItem())) {
        if (tackling && obstacle->isRock()) {
            destroyObstacle(obstacle);
        } else if (!obstacle->isRock() && !tackling) {
        }
    }
}

void Character::tackle() {
    tackling = true;
    physics->set_vx(5.0);
    tackleTimer->start(200);
}

void Character::stopTackle() {
    tackling = false;
}

void Character::swingSword() {
    std::cout << "Swing sword triggered" << std::endl;

    Level_2 *level = dynamic_cast<Level_2*>(parent());
    if (level) {
        for (Obstacle *obstacle : level->getObstacles()) {
            if (!obstacle->isRock() && !obstacle->isDestroyed()) {
                float dx = physics->get_simulated_x(physics->get_x()) - obstacle->getItem()->x();
                float dy = physics->get_simulated_y(physics->get_y()) - obstacle->getItem()->y();
                float distance = std::sqrt(dx * dx + dy * dy);

                std::cout << "Checking obstacle at distance: " << distance << std::endl;

                if (distance <= 60) {
                    std::cout << "Destroying obstacle at distance: " << distance << std::endl;
                    destroyObstacle(obstacle); //o
                }
            }
        }
    }
}



void Character::destroyObstacle(Obstacle *obstacle) {
    obstacle->destroy();
}
