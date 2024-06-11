#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    QPixmap bgPixmap(":/map_2.png");
    QPixmap scaledBgPixmap = bgPixmap.scaled(5200, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *background = scene->addPixmap(scaledBgPixmap);

    QPixmap characterPixmap(":/spartan-solo.png");
    QGraphicsPixmapItem *characterItem = scene->addPixmap(characterPixmap);
    characterItem->setPos(10, 490);  // Updated spawn coordinates

    character = new Character(10, 490, 800, 600, characterItem);  // Updated spawn coordinates and window dimensions
    level = new Level_2(background, character); // Updated window size

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

void MainWindow::mousePressEvent(QMouseEvent *event) {
    character->mousePressEvent(event);
}
