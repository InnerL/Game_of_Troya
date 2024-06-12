#include "mapa2.h"
#include "mapa3.h"
#include <QBoxLayout>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMessageBox>


Mapa2::Mapa2(QWidget *parent) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap bgPixmap(":/imagen/map_2.png");
    QPixmap scaledBgPixmap = bgPixmap.scaled(5200, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *background = scene->addPixmap(scaledBgPixmap);

    QPixmap characterPixmap(":/imagen/PJMov.png");
    QGraphicsPixmapItem *characterItem = scene->addPixmap(characterPixmap.copy(0, 0, 54, 60)); // Initial frame
    characterItem->setPos(210, 560);


    QPixmap sidecharPixmap(":/imagen/horse.png");
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
    connect(restartButton, &QPushButton::clicked, this, &Mapa2::restartLevel);

    character = new Character(210, 560, 800, 600, characterItem);
    level = new Level2(background, character, counterLabel);

    connect(level, &Level2::progressUpdated, this, &Mapa2::updateProgressBar);
    connect(level, &Level2::gameOver, this, &Mapa2::showRestartButton);
    connect(level, &Level2::cleanUpRequested, this, &Mapa2::cleanUpResources); //señal limpieza
    resize(1280, 720);
}

Mapa2::~Mapa2() {
    cleanUpResources();
}

void Mapa2::cleanUpResources() {
    QMessageBox::information(this, "Nivel completado", "Has entregado el caballo de forma exitosa,ahora viene la accion!");
    if (level) {
        level->stopGame();
        level->clearObstacles();
        delete level;
        level = nullptr;
    }

    if (character) {
        delete character;
        character = nullptr;
    }

    if (scene) {
        scene->clear();
        delete scene;
        scene = nullptr;
    }

    if (view) {
        delete view;
        view = nullptr;
    }

    delete counterLabel;
    counterLabel = nullptr;

    delete progressBar;
    progressBar = nullptr;

    delete restartButton;
    restartButton = nullptr;

    Mapa3 *mapa3 = new Mapa3();
    mapa3->show();
    this->close();

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

void Mapa2::updateProgressBar(int value) {
    progressBar->setValue(value);
}

void Mapa2::showRestartButton() {
    level->stopGame();
    restartButton->show();
}

void Mapa2::restartLevel() {
    restartButton->hide();
    level->restartGame();
}
