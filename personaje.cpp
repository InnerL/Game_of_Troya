#include "personaje.h"

Personaje::Personaje(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
    currentFrame(0),
    frameWidth(54),
    frameHeight(60),
    maderaCount(6),
    piedraCount(4)
{
    spriteSheet = new QPixmap(":/PJMov.png");
    if(spriteSheet->isNull()){
        qWarning() << "No se pudo cargar la primera imagen de fondo. Verifica la ruta del recurso";
    }
    setPixmap(spriteSheet->copy(0, 0, frameWidth, frameHeight));

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Personaje::nextFrame);

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Personaje::updateMovement);
    movementTimer->start(16); // Aproximadamente 60 FPS
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
    if (pressedKeys.isEmpty()) {
        animationTimer->stop();
    }
}

void Personaje::updateMovement()
{
    int newX = x();
    int newY = y();

    if (pressedKeys.contains(Qt::Key_W)) {
        newY -= 2;
    }
    if (pressedKeys.contains(Qt::Key_S)) {
        newY += 2;
    }
    if (pressedKeys.contains(Qt::Key_A)) {
        newX -= 2;
    }
    if (pressedKeys.contains(Qt::Key_D)) {
        newX += 2;
    }

    if (!checkCollision(newX, newY)) {
        setPos(newX, newY);
        materialColision();
    }
}

void Personaje::nextFrame()
{
    currentFrame = (currentFrame + 1) % 5;
    int x = currentFrame * frameWidth;

    if (pressedKeys.contains(Qt::Key_A)) {
        //refleja horizontalmente el sprite
        setPixmap(spriteSheet->copy(x, 0, frameWidth, frameHeight).transformed(QTransform().scale(-1, 1)));
    } else {
        //No reflejar el sprite
        setPixmap(spriteSheet->copy(x, 0, frameWidth, frameHeight));
    }
}

bool Personaje::checkCollision(int newX, int newY)
{
    QRect newRect(newX, newY, frameWidth, frameHeight);
    for (const QRect &area : collisionAreas) {
        if (area.intersects(newRect)) {
            return true;
        }
    }
    return false;
}

void Personaje::setCollisionAreas(const QVector<QRect> &areas)
{
    collisionAreas = areas;
}

void Personaje::setMaterials(const QVector<Material*> &materials)
{
    this->materials = materials;
}

void Personaje::materialColision()
{
    QRect playerRect(x(), y(), frameWidth, frameHeight);
    Material* materialToDelete = nullptr;

    for (Material* material : materials) {
        if (!material->isCollected() && playerRect.intersects(material->getRect())) {
            material->setCollected(true);
            material->hide();
            materialToDelete = material;

            int maderaDelta = 0;
            int piedraDelta = 0;

            if (material->getType() == Material::Piedra) {
                qDebug() << "Recogiste una piedra en posición:" << material->pos();
                piedraDelta = -1;
            } else if (material->getType() == Material::Madera) {
                qDebug() << "Recogiste madera en posición:" << material->pos();
                maderaDelta = -1;
            }
            emit materialCollected(maderaDelta, piedraDelta);
            break;
        }
    }

    if (materialToDelete) {
        materials.removeOne(materialToDelete);
        delete materialToDelete;
    }
}
