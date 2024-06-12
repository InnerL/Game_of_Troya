#include "character.h"
#include "level2.h"
#include <iostream>
#include <ostream>

Character::Character(int x, int y, int w, int h, QGraphicsPixmapItem *item) :
    movingLeft(false), movingRight(false), jumping(false), tackling(false),  currentFrame(0), totalFrames(5), currentLevel(2)  {
    physics = new fisica(x, y, w, h, item);
    physics->set_initial_conditions(x, y, 0, 0);

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Character::updatePhysics2);
    connect(updateTimer, &QTimer::timeout, this, &Character::updatePhysics3);
    updateTimer->start(10);

    tackleTimer = new QTimer(this);
    tackleTimer->setSingleShot(true);
    connect(tackleTimer, &QTimer::timeout, this, &Character::stopTackle);

    spriteSheet = QPixmap(":/imagen/PJMov.png"); // Load your sprite sheet
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Character::updateAnimationFrame);
    animationTimer->start(100); // Update frame every 100 ms

    setLevel(currentLevel); // Establecer el nivel inicial
}

void Character::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        movingLeft = true;
    } else if (event->key() == Qt::Key_D) {
        movingRight = true;
    } else if (event->key() == Qt::Key_Space) {
        if (!jumping) {
            if (currentLevel == 2) {
                physics->jump2();
            } else if (currentLevel == 3) {
                physics->jump3();
            }
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
    if (currentLevel == 2) {
        if (event->button() == Qt::RightButton) {
            tackle();
        } else if (event->button() == Qt::LeftButton) {
            tackle4();
        }
    } else if (currentLevel == 3) {
        if (event->button() == Qt::RightButton) {
            tackle3();
        } else if (event->button() == Qt::LeftButton) {
            tackle4();
        }
    }
}

void Character::updatePhysics2() {
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


void Character::updatePhysics3() {
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
    } else if (characterX > 1280 - item->pixmap().width()) {  // Updated right limit
        physics->x = physics->get_phisical_x(1280 - item->pixmap().width());
        physics->set_vx(0);
    }

    // Allow the character to fall and detect landing
    if (physics->get_simulated_y(physics->get_y()) >= 250) {  // Coordenadas piso
        physics->set_y(physics->get_phisical_y(250));
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

void Character::tackle3() {
    tackling = true;
    physics->set_vx(1.0);
    tackleTimer->start(200);
}
void Character::tackle4() {
    tackling = true;
    physics->set_vx(-2.0);
    tackleTimer->start(200);
}

void Character::stopTackle() {
    tackling = false;
}

void Character::updateAnimationFrame() {
    currentFrame = (currentFrame + 1) % totalFrames; // Loop through frames

    int frameWidth = spriteSheet.width() / totalFrames;
    int frameHeight = spriteSheet.height();

    QPixmap frame = spriteSheet.copy(currentFrame * frameWidth, 0, frameWidth, frameHeight);
    physics->get_item()->setPixmap(frame);
}

void Character::setLevel(int level) {
    currentLevel = level;

    // Desconectar señales previas
    updateTimer->disconnect(this);

    if (currentLevel == 2) {
        connect(updateTimer, &QTimer::timeout, this, &Character::updatePhysics2);
    } else if (currentLevel == 3) {
        connect(updateTimer, &QTimer::timeout, this, &Character::updatePhysics3);
    }

    updateTimer->start(10);
}

void Character::destroyObstacle(Obstacle *obstacle) {
    obstacle->destroy();
}

fisica* Character::getPhysics() {
    return physics;
}

