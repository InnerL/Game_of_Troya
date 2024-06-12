#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>


    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , countdownValue(100)  // Inicializar el tiempo
    {
        ui->setupUi(this);
        adjustWindowSizeToGraphicsView();
    }

    void MainWindow::createScene1()
    {
        try {
            QMessageBox::information(this, "Comienzo", "Construye el caballo.");

            scene = new QGraphicsScene(this);
            createFondo();
            createPersonaje();
            addMaterials();
            configureGraphicsView();
            labelN1();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Ocurrio un error no identificado" << std::endl;
        }

    }

    void MainWindow::labelN1(){
        labelCont = new QLabel(QString("OBJETOS:   "), this);
        labelCont->setGeometry(400, 11, 110, 35); // Posición y tamaño
        labelCont->setAlignment(Qt::AlignCenter);
        // Establecer estilo
        labelCont->setStyleSheet(
            "QLabel {"
            "   font-size: 17px;"           // Tamaño de fuente
            "   font-weight: bold;"         // Grosor del texto
            "   color: brown;"              // Color del texto
            "   border: 2px solid brown;"   // Borde
            "   border-radius: 15px;"       // Esquinas redondeadas
            "}"
            );


        // Configurar labelCountdown
        labelCountdown = new QLabel(this);
        labelCountdown->setGeometry(540, 11, 110, 35);//Posicion-Tamaño
        labelCountdown->setAlignment(Qt::AlignCenter);
        labelCountdown->setText(" ");

        labelCountdown->setStyleSheet(
            "QLabel {"
            "   font-size: 17px;"           // Tamaño de fuente
            "   font-weight: bold;"         // Grosor del texto
            "   color: brown;"              // Color del texto
            "   border: 2px solid brown;"   // Borde
            "   border-radius: 15px;"       // Esquinas redondeadas
            "}"
            );

        // Configurar countdownTimer
        countdownTimer = new QTimer(this);
        connect(countdownTimer, &QTimer::timeout, this, &MainWindow::updateCountdown);
        countdownTimer->start(1000); // Actualizar cada segundo

        // Configurar history
        labelhistory = new QLabel(this);
        labelhistory->setGeometry(20, 11, 370, 35);//Posicion-Tamaño
        labelhistory->setAlignment(Qt::AlignCenter);
        labelhistory->setText("Busca y recoge los 9 materiales para avanzar.");

        labelhistory->setStyleSheet(
            "QLabel {"
            "   font-size: 17px;"           // Tamaño de fuente
            "   font-weight: bold;"         // Grosor del texto
            "   color: brown;"              // Color del texto
            "   border: 2px solid brown;"   // Borde
            "   border-radius: 15px;"       // Esquinas redondeadas
            "}"
            );



    }

    void MainWindow::createFondo()
    {
        fondo = new Fondo();
        scene->addWidget(fondo);
    }

    void MainWindow::createPersonaje()
    {
        // Crear e insertar el personaje en la escena
        personaje = new Personaje();
        scene->addItem(personaje);
        personaje->setFlag(QGraphicsItem::ItemIsFocusable);
        personaje->setFocus();
        personaje->setCollisionAreas(fondo->getColisionArea());
        personaje->setPos(100, 100); // Cambia las coordenadas según desees

        connect(personaje, &Personaje::objectCollected, this, [this](int collectedCount) {
            labelCont->setText(QString("OBJETOS: %1").arg(collectedCount));
            if (collectedCount >= 9) {
                transitionToNivel2();
            }
        });
    }

    void MainWindow::addMaterials(){
        try {
            // Agregar materiales
            QPixmap materialPixmap1(":/imagen/piedra.png");
            fondo->aggMaterial(materialPixmap1, 672, 101);
            fondo->aggMaterial(materialPixmap1, 677, 640);
            fondo->aggMaterial(materialPixmap1, 53, 637);
            fondo->aggMaterial(materialPixmap1, 264, 108);

            QPixmap materialPixmap2(":/imagen/vacio.png");
            fondo->aggMaterial(materialPixmap2, 488, 320);//poner invicible
            fondo->aggMaterial(materialPixmap2, 294, 251);//poner invicible
            fondo->aggMaterial(materialPixmap2, 503, 648);
            fondo->aggMaterial(materialPixmap2, 294, 688);
            fondo->aggMaterial(materialPixmap2, 210, 140);

            personaje->setMaterials(fondo->getMaterials());
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Ocurrio un error no identificado" << std::endl;
        }
    }

    void MainWindow::configureGraphicsView()
    {
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setFixedSize(768, 768);
        ui->graphicsView->setRenderHint(QPainter::Antialiasing);
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        adjustWindowSizeToGraphicsView();  // Asegúrate de que esto se llame después de configurar el tamaño del graphicsView
    }

    void MainWindow::adjustWindowSizeToGraphicsView()
    {
        // Obtener el tamaño del QGraphicsView
        QSize graphicsViewSize = ui->graphicsView->size();

        // Calcular el tamaño total necesario incluyendo los márgenes y bordes
        QSize newSize = graphicsViewSize + (centralWidget()->size());

        // Ajustar el tamaño de la ventana principal
        setFixedSize(newSize);
    }

    void MainWindow::transitionToNivel2() {
        // Show message
        QMessageBox::information(this, "Nivel Completado", "Camina hacia Troya y entrega el caballo.");

        // Clean up current level
        cleanupCurrentLevel();

        // Transition to Mapa2
        Mapa2 *mapa2 = new Mapa2();
        mapa2->show();
        this->close();
    }


    void MainWindow::cleanupCurrentLevel() {
        if (countdownTimer) {
            countdownTimer->stop();
        }

        // Delete or reset pointers to the current scene and related objects
        if (scene) {
            delete scene;
            scene = nullptr;
        }

        fondo = nullptr;
        personaje = nullptr;
        labelCont = nullptr;
        labelCountdown = nullptr;
        labelhistory = nullptr;
        countdownTimer = nullptr;

    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::updateCountdown()
    {
        if (countdownValue > 0) {
            countdownValue--;
            labelCountdown->setText(QString("Tiempo: %1").arg(countdownValue));
        } else {
            countdownTimer->stop();

        }
    }
