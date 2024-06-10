#include "character.h"
#include "level2.h"

Character::Character(int x, int y, int w, int h, QGraphicsPixmapItem *item) :
    movingLeft(false), movingRight(false), jumping(false), tackling(false) {
    physics = new fisica(x, y, w, h, item);
    physics->set_initial_conditions(x, y, 0, 0);  // Start completely still

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
        ax = -3.0;  // Updated acceleration for left movement
    } else if (movingRight) {
        ax = 3.0;  // Updated acceleration for right movement
    } else {
        ax = -physics->get_vx() * friction;  // Apply updated friction
    }

    physics->calculate_cinematics(ax, 0);

    // Apply gravity
    physics->calculate_parabolic_dynamics();

    // Limit the velocity
    if (physics->get_vx() > maxVelocity) {
        physics->set_vx(maxVelocity);
    } else if (physics->get_vx() < -maxVelocity) {
        physics->set_vx(-maxVelocity);
    }

    // Limit the character's position
    float characterX = physics->get_simulated_x(physics->get_x());
    QGraphicsPixmapItem *item = physics->get_item();
    if (characterX < 0) {
        physics->x = physics->get_phisical_x(0);
        physics->set_vx(0);
    } else if (characterX > 1920 - item->pixmap().width()) {  // Updated right limit
        physics->x = physics->get_phisical_x(1920 - item->pixmap().width());
        physics->set_vx(0);
    }

    // Allow the character to fall and detect landing
    if (physics->get_simulated_y(physics->get_y()) >= 910) {  // Updated y coordinate of the floor
        physics->set_y(physics->get_phisical_y(910));
        physics->set_vy(0);
        jumping = false;
    }
}

void Character::checkCollision(Obstacle *obstacle) {
    if (!obstacle->isDestroyed() && physics->get_item()->collidesWithItem(obstacle->getItem())) {
        if (tackling && obstacle->isRock()) {
            destroyObstacle(obstacle);
        } else if (!obstacle->isRock() && !tackling) {
            // Implement collision logic with cactus here if needed
        }
    }
}

void Character::tackle() {
    tackling = true;
    physics->set_vx(5.0);
    tackleTimer->start(200);  // Tackle duration
}

void Character::stopTackle() {
    tackling = false;
}

void Character::swingSword() {
    // Handle sword swinging logic
    for (Obstacle *obstacle : dynamic_cast<Level2*>(parent())->getObstacles()) {
        if (!obstacle->isRock() && !obstacle->isDestroyed()) {
            float distance = std::abs(physics->get_simulated_x(physics->get_x()) - obstacle->getItem()->x());
            if (distance <= 30) {
                destroyObstacle(obstacle);
            }
        }
    }
}

void Character::destroyObstacle(Obstacle *obstacle) {
    obstacle->destroy();
}
