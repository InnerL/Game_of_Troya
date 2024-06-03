#include "Level1.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

Level1::Level1(QWidget *parent) : QWidget(parent), wood(0), stone(0), grass(0), water(0), playerX(50), playerY(50) {
    timeLeft = 180; // 3 minutes
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level1::updateGame);
    timer->start(1000);
}

void Level1::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    drawResources(painter);
    drawPlayer(painter);

    // Draw timer and resources collected
    painter.setPen(Qt::black);
    painter.drawText(10, 20, QString("Time Left: %1").arg(timeLeft));
    painter.drawText(10, 40, QString("Wood: %1").arg(wood));
    painter.drawText(10, 60, QString("Stone: %1").arg(stone));
    painter.drawText(10, 80, QString("Grass: %1").arg(grass));
    painter.drawText(10, 100, QString("Water: %1").arg(water));
}

void Level1::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W: // Move up
        playerY = qMax(playerY - 10, 0);
        break;
    case Qt::Key_A: // Move left
        playerX = qMax(playerX - 10, 0);
        break;
    case Qt::Key_S: // Move down
        playerY = qMin(playerY + 10, height() - 50);
        break;
    case Qt::Key_D: // Move right
        playerX = qMin(playerX + 10, width() - 50);
        break;
    case Qt::Key_E: // Collect resource
        collectResource();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
    update();
}

void Level1::updateGame() {
    timeLeft--;
    if (timeLeft <= 0) {
        timer->stop();
        // Show collected resources and move to the next level
        // For simplicity, just print to console here
        qDebug("Wood: %d, Stone: %d, Grass: %d, Water: %d", wood, stone, grass, water);
        // Transition to next level here
    }
    update();
}

void Level1::collectResource() {
    // Check player position and update the corresponding resource count
    // For simplicity, assume specific areas contain specific resources
    if (playerX < 100 && playerY < 100) {
        wood++;
    } else if (playerX > 100 && playerX < 200 && playerY < 100) {
        stone++;
    } else if (playerX < 100 && playerY > 100 && playerY < 200) {
        grass++;
    } else if (playerX > 100 && playerX < 200 && playerY > 100 && playerY < 200) {
        water++;
    }
}

void Level1::drawResources(QPainter &painter) {
    // Draw trees (wood)
    painter.setBrush(Qt::green);
    painter.drawRect(20, 20, 50, 50);
    // Draw rocks (stone)
    painter.setBrush(Qt::gray);
    painter.drawRect(120, 20, 50, 50);
    // Draw grass
    painter.setBrush(Qt::darkGreen);
    painter.drawRect(20, 120, 50, 50);
    // Draw water (lakes)
    painter.setBrush(Qt::blue);
    painter.drawRect(120, 120, 50, 50);
}

void Level1::drawPlayer(QPainter &painter) {
    // Draw the player as a simple rectangle
    painter.setBrush(Qt::red);
    painter.drawRect(playerX, playerY, 30, 30);
}
