#include "level3.h"
#include "qgraphicsscene.h"
#include "mapa3.h"
#include <iostream>
#include <ostream>
#include <QTime>
#include <QRandomGenerator>



level3::level3(Mapa3 *mapa, QGraphicsPixmapItem *background, Character *character)
    :  background(background), backgroundX(0), character(character),mapa(mapa),
    currentGuardFrame(0), totalGuardFrames(5){

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &level3::updateBackground);
    timer->start(30);  // Update every 30 ms

    // Crear el segundo fondo
    QPixmap bgPixmap(":/imagen/map_3.png");
    background2 = new QGraphicsPixmapItem(bgPixmap);
    background2->setPos(background->boundingRect().width(), 0);  // Colocar el segundo fondo justo después del primero
    background->scene()->addItem(background2);

    // Crear el temporizador para generar enemigos después de intervalos aleatorios
    guardTimer = new QTimer(this);
    connect(guardTimer, &QTimer::timeout, this, &level3::createguard);
    generateRandomGuardInterval(); // Genera el primer de inmediato

    // Crear el temporizador para la animación de los enemigos
    guardSpriteSheet = QPixmap(":/imagen/NPCMov.png");
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &level3::updateGuardAnimationFrame);
    animationTimer->start(100);  // actualizar frame cada 100 ms

    arrowTimer = new QTimer(this); // Nuevo temporizador para flechas
    connect(arrowTimer, &QTimer::timeout, this, &level3::createArrow);
    generateRandomArrowInterval(); // Genera la primera flecha de inmediato

    character->setLevel(3);

}

void level3::updateBackground() {
    backgroundX -= 2; // velocidad fondo

    if (backgroundX <= -background->boundingRect().width()) {
        backgroundX = 0;
    }

    background->setPos(backgroundX, 0);
    background2->setPos(backgroundX + background->boundingRect().width(), 0);


    try {
        if (!guards.empty()) { // Verificar si hay guardias
            for (QGraphicsPixmapItem* guardItem : guards) {
                if (guardItem->isVisible()) {
                    moveguardTowardsCharacter();  // Mueve el enemigo hacia el personaje
                    if (character->getPhysics()->get_item()->collidesWithItem(guardItem)) {
                        handleCharacterguardCollision(guardItem);
                    }
                }
            }

            // Verificar si los enemigos están fuera de la pantalla y ocultarlos si es necesario
            for (auto it = guards.begin(); it != guards.end(); ) {
                QGraphicsPixmapItem* guardItem = *it;
                if (guardItem->x() < -guardItem->boundingRect().width()) {
                    guardItem->setVisible(false);
                    it = guards.erase(it);
                } else {
                    ++it;
                }
            }

            if (!arrows.empty()) {
                moveArrowTowardsCharacter();
                for (QGraphicsPixmapItem* arrowItem : arrows) {
                    if (character->getPhysics()->get_item()->collidesWithItem(arrowItem)) {
                        handleCharacterArrowCollision(arrowItem);
                    }
                }

                for (auto it = arrows.begin(); it != arrows.end(); ) {
                    QGraphicsPixmapItem* arrowItem = *it;
                    if (arrowItem->x() < -arrowItem->boundingRect().width()) {
                        arrowItem->setVisible(false);
                        it = arrows.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Ocurrio un error no identificado" << std::endl;
    }
}


void level3::createguard() {
    // Creamos un nuevo enemigo
    QPixmap guardPixmap = guardSpriteSheet.copy(0, 0, guardSpriteSheet.width() / totalGuardFrames, guardSpriteSheet.height());
    QGraphicsPixmapItem *guardItem = new QGraphicsPixmapItem(guardPixmap);
    guardItem->setPos(1300, 250);
    background->scene()->addItem(guardItem);
    guards.push_back(guardItem);    // Agrega el enemigo al vector

    // Generar el siguiente enemigo después de un intervalo aleatorio entre segundos
    generateRandomGuardInterval();
}

void level3::createArrow() {
    QPixmap arrowPixmap(":/imagen/lanza.png");
    QGraphicsPixmapItem *arrowItem = new QGraphicsPixmapItem(arrowPixmap);
    arrowItem->setPos(1300, 200);  // Posición inicial de la flecha (más arriba del guardia)
    background->scene()->addItem(arrowItem);
    arrows.push_back(arrowItem);    // Agrega la flecha al vector

    generateRandomArrowInterval();
}

void level3::moveguardTowardsCharacter() {
    // Mueve hacia el personaje
    float step = 4.0;  // Velocidad
    for (QGraphicsPixmapItem* guardItem : guards) {
        guardItem->moveBy(-step, 0);  // Mover hacia la izquierda
    }
}


void level3::moveArrowTowardsCharacter() {
    float step = 12.0;  // Velocidad de la flecha
    for (QGraphicsPixmapItem* arrowItem : arrows) {
        arrowItem->moveBy(-step, 0);  // Mover flecha hacia la izquierda
    }
}


void level3::handleCharacterguardCollision(QGraphicsPixmapItem* guardItem) {
    // Aquí puedes implementar la lógica para la alerta
    try {
        // Oculta el enemigo tocado
        guardItem->setVisible(false);

        if (mapa) {
            mapa->updateVida();
        }


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Ocurrio un error no identificado" << std::endl;
    }

}

void level3::handleCharacterArrowCollision(QGraphicsPixmapItem* arrowItem) {
    try {
        arrowItem->setVisible(false);

        auto it = std::find(arrows.begin(), arrows.end(), arrowItem);
        if (it != arrows.end()) {
            arrows.erase(it);
        }

        if (mapa) {
            mapa->updateVida();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Ocurrio un error no identificado" << std::endl;
    }
}



void level3::generateRandomGuardInterval() {
    // Genera un intervalo aleatorio
    int randomInterval = rand() % 1500 + 500; // 1000 = 1 segundo, 4000 = 4 segundos
    guardTimer->start(randomInterval); // Comienza el temporizador con el intervalo aleatorio
}

void level3::generateRandomArrowInterval() {
    int randomInterval = rand() % 3000 + 1500; // 500 ms a 2000 ms
    arrowTimer->start(randomInterval);
}

void level3::updateGuardAnimationFrame() {
    currentGuardFrame = (currentGuardFrame + 1) % totalGuardFrames;

    int frameWidth = guardSpriteSheet.width() / totalGuardFrames;
    int frameHeight = guardSpriteSheet.height();

    for (QGraphicsPixmapItem* guardItem : guards) {
        QPixmap frame = guardSpriteSheet.copy(currentGuardFrame * frameWidth, 0, frameWidth, frameHeight);
        guardItem->setPixmap(frame);
    }
}

void level3::resetGuards()
{
    for (QGraphicsPixmapItem* guardItem : guards) {
        guardItem->setVisible(false);
        background->scene()->removeItem(guardItem);
        delete guardItem;
    }
    guards.clear();
    generateRandomGuardInterval();
}

void level3::resetArrows() {
    for (QGraphicsPixmapItem* arrowItem : arrows) {
        arrowItem->setVisible(false);
        background->scene()->removeItem(arrowItem);
        delete arrowItem;
    }
    arrows.clear();
    generateRandomArrowInterval();
}
void level3::stopLevel()
{
    timer->stop();
    guardTimer->stop();
    resetGuards();
}
