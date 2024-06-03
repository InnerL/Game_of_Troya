#ifndef LEVEL_2_H
#define LEVEL_2_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Level_2 : public QObject {
    Q_OBJECT

public:
    Level_2(QGraphicsPixmapItem *background);

private slots:
    void updateBackground();

private:
    QGraphicsPixmapItem *background;
    QTimer *timer;
    int backgroundX;
};

#endif // LEVEL_2_H
