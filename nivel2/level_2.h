#ifndef LEVEL_2_H
#define LEVEL_2_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QLabel>
#include <vector>
#include "obstacle.h"
#include "character.h"

class Level_2 : public QObject {
    Q_OBJECT

public:
    Level_2(QGraphicsPixmapItem *background, Character *character, QLabel *counterLabel);
    std::vector<Obstacle*> getObstacles() const;
    void restartGame(); // Add restartGame function

signals:
    void progressUpdated(int value);
    void gameOver(); // Add signal to indicate game over

private slots:
    void updateBackground();

private:
    QGraphicsPixmapItem *background;
    QTimer *timer;
    int backgroundX;
    std::vector<Obstacle*> obstacles;
    Character *character;
    QLabel *counterLabel;
    int counter = 5;

    void createObstacles();
    void checkCollisions();
    void moveObstaclesWithBackground();
    void updateCounter();
    void resetBackground(); // Function to reset the background position
};

#endif // LEVEL_2_H
