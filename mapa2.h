#ifndef MAPA2_H
#define MAPA2_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include "character.h"
#include "level2.h"

class Mapa2 : public QWidget {
    Q_OBJECT

public:
    Mapa2(QWidget *parent = nullptr);
    ~Mapa2();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void updateProgressBar(int value);
    void showRestartButton();
    void restartLevel();


private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Character *character;
    Level2 *level;
    QLabel *counterLabel;
    QProgressBar *progressBar;
    QPushButton *restartButton;

    void cleanUpResources();
};

#endif // MAPA2_H
