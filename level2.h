#ifndef Level2_H
#define Level2_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QLabel>
#include <vector>
#include "obstacle.h"
#include "character.h"

class Level2 : public QObject {
    Q_OBJECT

public:
    Level2(QGraphicsPixmapItem *background, Character *character, QLabel *counterLabel);
    ~Level2();

    std::vector<Obstacle*> getObstacles() const;
    void stopGame();
    void restartGame();
    void clearAll();
    bool endLevel = false;
    void clearObstacles();


signals:
    void progressUpdated(int value);
    void gameOver();
    void cleanUpRequested(); //señal para limpiar recursos

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
    void resetBackground();
};

#endif // Level2_H
