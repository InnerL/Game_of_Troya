    #include "mainwindow.h"
    #include "ui_mainwindow.h"
    #include "material.h"
    #include <QDebug>


    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);


        createScene1();

        adjustWindowSizeToGraphicsView();

        ui->maderaLabel->setText("Madera: 6");
        ui->piedraLabel->setText("Piedra: 4");

    }

    void MainWindow::createScene1()
    {
        scene = new QGraphicsScene(this);

        // Crear e insertar el fondo en la escena
        fondo = new Fondo();
        scene->addWidget(fondo);

        // Crear e insertar el personaje en la escena
        personaje = new Personaje();
        scene->addItem(personaje);
        personaje->setFlag(QGraphicsItem::ItemIsFocusable);
        personaje->setFocus();
        personaje->setCollisionAreas(fondo->getColisionArea());

        // Agregar materiales
        QPixmap materialPixmap1(":/piedra.png");
        if (materialPixmap1.isNull()) {
            qWarning() << "No se pudo cargar la imagen del material. Verifica la ruta del recurso";
        } else {
            qDebug() << "Imagen del material cargada correctamente.";
            fondo->aggMaterial(materialPixmap1, 200, 200, Material::Piedra);
            fondo->aggMaterial(materialPixmap1, 672, 101, Material::Piedra);
        }
        QPixmap materialPixmap2(":/madera.png");
        if (materialPixmap2.isNull()) {
            qWarning() << "No se pudo cargar la imagen del material. Verifica la ruta del recurso";
        } else {
            qDebug() << "Imagen del material cargada correctamente.";
            fondo->aggMaterial(materialPixmap2, 264, 108, Material::Madera);
            fondo->aggMaterial(materialPixmap2, 484, 686, Material::Madera);
        }



        personaje->setMaterials(fondo->getMaterials());


        // Conectar la señal de actualización de materiales con las etiquetas de UI
        connect(personaje, &Personaje::materialCollected, this, [=](int maderaDelta, int piedraDelta){
            int maderaCount = ui->maderaLabel->text().split(": ").last().toInt() + maderaDelta;
            int piedraCount = ui->piedraLabel->text().split(": ").last().toInt() + piedraDelta;

            ui->maderaLabel->setText(QString("Madera: %1").arg(maderaCount));
            ui->piedraLabel->setText(QString("Piedra: %1").arg(piedraCount));
        });


        ui->graphicsView->setScene(scene);
        ui->graphicsView->setFixedSize(768, 768);
        ui->graphicsView->setRenderHint(QPainter::Antialiasing);
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        personaje->setPos(100, 100); // Cambia las coordenadas según desees
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


    MainWindow::~MainWindow()
    {
        delete ui;
    }
