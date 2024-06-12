#ifndef LEVEL3_H
#define LEVEL3_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <vector>
#include "character.h"
#include "mapa3.h"

class Mapa3;

class level3 : public QObject {
    Q_OBJECT

public:
    level3(Mapa3* mapa, QGraphicsPixmapItem *background, Character *character);  // Modifica el constructor
    void resetGuards();
    void resetArrows(); // Nuevo método para resetear flechas
    void stopLevel();  // Añade esta función


private slots:
    void updateBackground();
    void handleCharacterguardCollision(QGraphicsPixmapItem* guardItem);
    void handleCharacterArrowCollision(QGraphicsPixmapItem* arrowItem); // Nuevo método para manejar colisiones de flechas

    void createguard();
    void createArrow(); // Nuevo método para crear flechas

    void updateGuardAnimationFrame();



private:
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *background2; //fondo infinito
    QTimer *timer;
    int backgroundX;
    Character *character;

    void moveguardTowardsCharacter();
    void moveArrowTowardsCharacter(); // Nuevo método para mover flechas


    std::vector<QGraphicsPixmapItem*> guards; // Vector para almacenar múltiples guardias
    std::vector<QGraphicsPixmapItem*> arrows;

    QTimer *guardTimer;
    QTimer *arrowTimer;


    void generateRandomGuardInterval();
    void generateRandomArrowInterval(); // Nuevo método para generar intervalos aleatorios de flechas

    Mapa3* mapa;  // Añade un puntero a Mapa3

    QTimer *animationTimer;
    QPixmap guardSpriteSheet;
    int currentGuardFrame;
    int totalGuardFrames;



};

#endif // LEVEL3_H
