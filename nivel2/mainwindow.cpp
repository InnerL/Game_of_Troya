#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    QPixmap bgPixmap(":/map_2.png");
    QGraphicsPixmapItem *background = scene->addPixmap(bgPixmap);

    QPixmap characterPixmap(":/spartan-solo.png");
    QGraphicsPixmapItem *characterItem = scene->addPixmap(characterPixmap);
    characterItem->setPos(10, 910);  // Updated spawn coordinates

    character = new Character(10, 910, 1280, 720, characterItem);  // Updated spawn coordinates and window dimensions
    level = new Level_2(background, character);

    resize(1280, 720);  // Updated window size
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

void MainWindow::mousePressEvent(QMouseEvent *event) {
    character->mousePressEvent(event);
}
