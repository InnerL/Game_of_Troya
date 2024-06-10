#ifndef Mapa3_H
#define Mapa3_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "character.h"
#include "level3.h"

class Mapa3 : public QWidget {
    Q_OBJECT

public:
    Mapa3(QWidget *parent = nullptr);
    ~Mapa3();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Character *character;
    Level3 *level;
};

#endif // Mapa3_H
