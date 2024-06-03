#include "character.h"
#include "qevent.h"

Character::Character(int x, int y, int w, int h, QGraphicsPixmapItem *item) :
    movingLeft(false), movingRight(false), jumping(false) {
    physics = new fisica(x, y, w, h, item);
    physics->set_initial_conditions(x, y, 0, 0);  // Start completely still

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Character::updatePhysics);
    updateTimer->start(10);
}

void Character::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        movingLeft = true;
    } else if (event->key() == Qt::Key_D) {
        movingRight = true;
    } else if (event->key() == Qt::Key_Space) {
        physics->jump();
    }
}

void Character::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        movingLeft = false;
    } else if (event->key() == Qt::Key_D) {
        movingRight = false;
    }
}

void Character::updatePhysics() {
    float ax = 0.0;
    if (movingLeft) {
        ax = -1.0;  // Accelerate left
    } else if (movingRight) {
        ax = 1.0;  // Accelerate right
    } else {
        ax = -physics->get_vx() * friction;  // Apply friction
    }

    physics->calculate_cinematics(ax, 0);

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
    } else if (characterX > 8000 - item->pixmap().width()) {
        physics->x = physics->get_phisical_x(8000 - item->pixmap().width());
        physics->set_vx(0);
    }
}
