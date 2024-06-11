#include "mainwindow.h"
#include <iostream>
#include <ostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap bgPixmap(":/map_2.png");
    QPixmap scaledBgPixmap = bgPixmap.scaled(5200, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *background = scene->addPixmap(scaledBgPixmap);

    QPixmap characterPixmap(":/spartan-solo.png");
    QGraphicsPixmapItem *characterItem = scene->addPixmap(characterPixmap);
    characterItem->setPos(210, 560);

    QPixmap sidecharPixmap(":/horse.png");
    QPixmap scaledsidecharPixmap = sidecharPixmap.scaled(200, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *sidecharItem = scene->addPixmap(scaledsidecharPixmap);
    sidecharItem->setPos(10, 470);


    counterLabel = new QLabel(this);
    counterLabel->setGeometry(10, 10, 250, 30);
    counterLabel->setStyleSheet("QLabel { background-color : transparent; color : black; font-size: 24px; font-weight: bold;}");

    progressBar = new QProgressBar(this);
    progressBar->setGeometry(270, 10, 250, 30);
    progressBar->setRange(0, 5);
    progressBar->setValue(5);

    restartButton = new QPushButton("Reiniciar", this);
    restartButton->setGeometry(540, 10, 100, 30);
    restartButton->hide();
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::restartLevel);

    character = new Character(210, 560, 800, 600, characterItem);
    level = new Level_2(background, character, counterLabel);

    connect(level, &Level_2::progressUpdated, this, &MainWindow::updateProgressBar);
    connect(level, &Level_2::gameOver, this, &MainWindow::showRestartButton);

    resize(1280, 720);
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

void MainWindow::updateProgressBar(int value) {
    progressBar->setValue(value);
}

void MainWindow::showRestartButton() {
    level->stopGame();
    restartButton->show();
}

void MainWindow::restartLevel() {
    restartButton->hide();
    level->restartGame();
}
