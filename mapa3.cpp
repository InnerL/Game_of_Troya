#include "mapa3.h"
#include <QBoxLayout>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMouseEvent>

Mapa3::Mapa3(QWidget *parent) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    QPixmap bgPixmap(":/map_3.png");
    if (bgPixmap.isNull()) {
        qWarning() << "No se pudo cargar la primera imagen de fondo. Verifica la ruta del recurso";
    }
    scene->setSceneRect(0, 0, bgPixmap.width(), bgPixmap.height());
    view->setFixedSize(bgPixmap.width(), bgPixmap.height());

    QGraphicsPixmapItem *background = scene->addPixmap(bgPixmap);
    background->setPos(0, 0);

    QPixmap characterPixmap(":/spartan-solo.png");
    if (bgPixmap.isNull()) {
        qWarning() << "No se pudo cargar la primera imagen de fondo. Verifica la ruta del recurso";
    }
    QGraphicsPixmapItem *characterItem = scene->addPixmap(characterPixmap);
    characterItem->setPos(10, 0);  // Updated spawn coordinates

    character = new Character(10, 0, bgPixmap.width(), bgPixmap.height(), characterItem);  // Updated spawn coordinates and window dimensions
    level = new Level3(background, character);


    setFixedSize(1280, 720);  // Updated window size

    qDebug() << "Mapa3";



}

Mapa3::~Mapa3() {
    delete scene;
    delete view;
    delete character;
    delete level;
}

void Mapa3::keyPressEvent(QKeyEvent *event) {
    character->keyPressEvent(event);
}

void Mapa3::keyReleaseEvent(QKeyEvent *event) {
    character->keyReleaseEvent(event);
}

void Mapa3::mousePressEvent(QMouseEvent *event) {
    character->mousePressEvent(event);
}
