#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>

class Level1 : public QWidget {
    Q_OBJECT
public:
    Level1(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void updateGame();
private:
    QTimer *timer;
    int timeLeft;
    int wood, stone, grass, water;
    int playerX, playerY;
    void collectResource();
    void drawResources(QPainter &painter);
    void drawPlayer(QPainter &painter);
};

#endif // LEVEL1_H
