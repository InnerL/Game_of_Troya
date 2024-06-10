#include "personaje.h"
#include <iostream>
#include <ostream>

Personaje::Personaje(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
    currentFrame(0),
    frameWidth(54),
    frameHeight(60),
    collectedCount(0),
    facingLeft(false),
    reboundSteps(0),
    reboundDeltaX(0),
    reboundDeltaY(0)
{
    spriteSheet = new QPixmap(":/PJMov.png");
    if(spriteSheet->isNull()){
        qWarning() << "No se pudo cargar la primera imagen de fondo. Verifica la ruta del recurso";
    }
    setPixmap(spriteSheet->copy(0, 0, frameWidth, frameHeight));

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Personaje::nextFrame);
    animationTimer->start(100); // Cambiar cada 100 ms para repetir constantemente


    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Personaje::updateMovement);
    movementTimer->start(16); // Aproximadamente 60 FPS

    reboundTimer = new QTimer(this);  // Inicializar el temporizador de rebote
    connect(reboundTimer, &QTimer::timeout, this, &Personaje::updateRebound);
}

//animacion al presionar
void Personaje::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (!pressedKeys.contains(key)) {
        pressedKeys.insert(key);
        if (!animationTimer->isActive()) {
            animationTimer->start(100); // Cambiar cada 100 ms
        }
    }
}

//Para la animacion
void Personaje::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys.remove(event->key());
    /*
    if (pressedKeys.isEmpty()) {
        animationTimer->stop();
    }
*/
}

void Personaje::updateMovement()
{
    try {
        if (reboundSteps > 0) {
            return; // Si está en medio de un rebote, no procesar movimiento normal
        }
        int newX = x();
        int newY = y();
        int deltaX = 0;
        int deltaY = 0;

        if (pressedKeys.contains(Qt::Key_W)) {
            deltaY -= 2;
        }
        if (pressedKeys.contains(Qt::Key_S)) {
            deltaY += 2;
        }
        if (pressedKeys.contains(Qt::Key_A)) {
            deltaX -= 2;
            facingLeft = true;
        }
        if (pressedKeys.contains(Qt::Key_D)) {
            deltaX += 2;
            facingLeft = false;
        }

        newX += deltaX;
        newY += deltaY;

        bool isBorderCollision = false;
        if (!checkCollision(newX, newY, &isBorderCollision)) {

            setPos(newX, newY);
            materialColision();
        }else if (isBorderCollision){
            // Iniciar el rebote
            reboundSteps = 7; // Número de pasos para el rebote
            reboundDeltaX = -deltaX;  // Ajustamos el rebote para mover el personaje en la dirección opuesta
            reboundDeltaY = -deltaY;
            reboundTimer->start(16); // Aproximadamente 60 FPS
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
    }

}

void Personaje::nextFrame()
{
    currentFrame = (currentFrame + 1) % 5;
    int x = currentFrame * frameWidth;

    if (facingLeft) {
        //refleja horizontalmente el sprite
        setPixmap(spriteSheet->copy(x, 0, frameWidth, frameHeight).transformed(QTransform().scale(-1, 1)));
    } else {
        //No reflejar el sprite
        setPixmap(spriteSheet->copy(x, 0, frameWidth, frameHeight));
    }
}

bool Personaje::checkCollision(int newX, int newY, bool *isBorderCollision)
{
    QRect newRect(newX, newY, frameWidth, frameHeight);
    for (const QPair<QRect, bool> &area : collisionAreas) {
        if (area.first.intersects(newRect)) {
            if (isBorderCollision) {
                *isBorderCollision = area.second;
            }
            return true;
        }
    }
    return false;
}

void Personaje::setCollisionAreas(const QVector<QPair<QRect, bool>> &areas)
{
    collisionAreas = areas;
}

void Personaje::setMaterials(const QVector<Material*> &materials)
{
    this->materials = materials;
}

void Personaje::materialColision()
{
    try {
        QRect playerRect(x(), y(), frameWidth, frameHeight);
        Material* materialToDelete = nullptr;

        for (Material* material : materials) {
            if (!material->isCollected() && playerRect.intersects(material->getRect())) {
                material->setCollected(true);
                material->hide();
                materialToDelete = material;
                ++collectedCount;
                emit objectCollected(collectedCount); // Emitir la señal cuando se recoja un objeto
                break;
            }
        }

        if (materialToDelete) {
            if (materials.removeOne(materialToDelete)) {
                delete materialToDelete;
                qDebug() << "Material eliminado correctamente.";
            } else {
                qWarning() << "No se pudo encontrar el material para eliminar.";
            }
        }
    }catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
    }
}


void Personaje::updateRebound()
{

    if (reboundSteps > 0) {
        setPos(x() + reboundDeltaX, y() + reboundDeltaY);
        reboundSteps--;
    } else {
        reboundTimer->stop();
    }
}
