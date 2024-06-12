#include "Mapa3.h"
#include "level3.h"


Mapa3::Mapa3(QWidget *parent)
    : QMainWindow(parent)
    , countdownValue(60)  // Inicializar el tiempo
    , vida(10)

{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Fondo
    QPixmap bgPixmap(":/imagen/map_3.png");
    QGraphicsPixmapItem *background = scene->addPixmap(bgPixmap);

    //PJ
    QPixmap characterPixmap(":/imagen/PJMov.png");
    QGraphicsPixmapItem *characterItem = scene->addPixmap(characterPixmap.copy(0, 0, 54, 60)); // Initial frame
    characterItem->setPos(5, 500);  // Updated spawn coordinates????? esto sobra

    character = new Character(10, 250, 1280, 720, characterItem);  // coordenada PJ y dimensiones
    level = new level3(this, background, character);  // Pasa el puntero this

    resize(1280, 600);  // Tamaño ventana ????? esto sobra

    labelN1();
}

void Mapa3::labelN1(){
    labelCont = new QLabel(QString("VIDA: %1").arg(vida), this);  // Inicializa con la vida actual
    labelCont->setGeometry(400, 30, 110, 35); // Posición y tamaño
    labelCont->setAlignment(Qt::AlignCenter);
    // Establecer estilo
    labelCont->setStyleSheet(
        "QLabel {"
        "   font-size: 17px;"           // Tamaño de fuente
        "   font-weight: bold;"         // Grosor del texto
        "   color: white;"              // Color del texto
        "   border: 2px solid white;"   // Borde
        "   border-radius: 15px;"       // Esquinas redondeadas
        "}"
        );


    // Configurar labelCountdown
    labelCountdown = new QLabel(this);
    labelCountdown->setGeometry(540, 30, 110, 35);//Posicion-Tamaño
    labelCountdown->setAlignment(Qt::AlignCenter);
    labelCountdown->setText(" ");

    labelCountdown->setStyleSheet(
        "QLabel {"
        "   font-size: 17px;"           // Tamaño de fuente
        "   font-weight: bold;"         // Grosor del texto
        "   color: white;"              // Color del texto
        "   border: 2px solid white;"   // Borde
        "   border-radius: 15px;"       // Esquinas redondeadas
        "}"
        );

    // Configurar countdownTimer
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &Mapa3::updateCountdown);
    countdownTimer->start(1000); // Actualizar cada segundo

    // Configurar history
    labelhistory = new QLabel(this);
    labelhistory->setGeometry(20, 30, 370, 35);//Posicion-Tamaño
    labelhistory->setAlignment(Qt::AlignCenter);
    labelhistory->setText("¡¡SOBREVIVE!!");

    labelhistory->setStyleSheet(
        "QLabel {"
        "   font-size: 17px;"           // Tamaño de fuente
        "   font-weight: bold;"         // Grosor del texto
        "   color: white;"              // Color del texto
        "   border: 2px solid white;"   // Borde
        "   border-radius: 15px;"       // Esquinas redondeadas
        "}"
        );

}

void Mapa3::updateCountdown()
{
    if (countdownValue > 0) {
        countdownValue--;
        labelCountdown->setText(QString("TIEMPO: %1").arg(countdownValue));
    } else {
        stopGame("Despues de tu arduo esfuerzo, troya cayo y empezara un nuevo imperio, tu nuevo imperio...");
    }
}

void Mapa3::updateVida()
{
    if (vida > 0) {
        vida--;
        labelCont->setText(QString("VIDA: %1").arg(vida));
        if (vida == 0) {
            countdownTimer->stop();
            QMessageBox::information(this, "Game Over", "¡Has perdido! Se reiniciará el nivel.");
            resetLevel();
        }
    }
}

void Mapa3::resetLevel()
{
    // Reinicia elementos del nivel
    countdownValue = 60;
    vida = 10;
    labelCont->setText(QString("VIDA: %1").arg(vida));
    labelCountdown->setText(QString("TIEMPO: %1").arg(countdownValue));
    countdownTimer->start(1000);
    character->getPhysics()->set_initial_conditions(10, 250, 0, 0);  // Reset character position and velocity
    level->resetGuards();  // Implementa esta función en level3
    level->resetArrows();
}

void Mapa3::stopGame(const QString &message)
{
    countdownTimer->stop();
    level->stopLevel();  // Implementa esta función en level3
    QMessageBox::information(this,"¡SOBREVIVISTE!", message);
    QTimer::singleShot(0, this, &QWidget::close); // Cierra la ventana después de 3 segundos (3000 ms)
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
