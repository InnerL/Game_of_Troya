#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    QPixmap bgPixmap(":/map_2.png");
    QGraphicsPixmapItem *background = scene->addPixmap(bgPixmap);

    QPixmap characterPixmap(":/spartan-solo.png");
    QGraphicsPixmapItem *characterItem = scene->addPixmap(characterPixmap);
    characterItem->setPos(200, 300);

    character = new Character(200, 300, 800, 600, characterItem);
    level = new Level_2(background);

    resize(800, 600);
}

MainWindow::~MainWindow() {
    delete scene;
    delete view;
    delete character;
    delete level;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    character->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    character->keyReleaseEvent(event);
}
