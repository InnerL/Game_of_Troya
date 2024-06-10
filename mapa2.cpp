#include "mapa2.h"
#include <QBoxLayout>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMouseEvent>

Mapa2::Mapa2(QWidget *parent) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    QPixmap bgPixmap(":/map_2.png");
    QGraphicsPixmapItem *background = scene->addPixmap(bgPixmap);

    QPixmap characterPixmap(":/spartan-solo.png");
    QGraphicsPixmapItem *characterItem = scene->addPixmap(characterPixmap);
    characterItem->setPos(10, 910);  // Updated spawn coordinates

    character = new Character(10, 910, 1280, 720, characterItem);  // Updated spawn coordinates and window dimensions
    level = new Level2(background, character);

    setFixedSize(1280, 720);  // Updated window size
}

Mapa2::~Mapa2() {
    delete scene;
    delete view;
    delete character;
    delete level;
}

void Mapa2::keyPressEvent(QKeyEvent *event) {
    character->keyPressEvent(event);
}

void Mapa2::keyReleaseEvent(QKeyEvent *event) {
    character->keyReleaseEvent(event);
}

void Mapa2::mousePressEvent(QMouseEvent *event) {
    character->mousePressEvent(event);
}
