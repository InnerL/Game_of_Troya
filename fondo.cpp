#include "fondo.h"
#include <QPainter>
#include <QDebug>
#include <QDir>

fondo::fondo(QWidget *parent) :
    QWidget(parent),
    background1(":/imagen/map_1.png"), // Ruta del primer recurso
    background2(":/imagen/map_2.png"), // Ruta del segundo recurso
    useBackground1(true)
{
    if (background1.isNull()) {
        qWarning() << "No se pudo cargar la primera imagen de fondo. Verifica la ruta del recurso";
    } else {
        qDebug() << "Imagen de fondo cargada correctamente desde el recurso.";
    }
    if (background2.isNull()) {
        qWarning() << "No se pudo cargar la segunda imagen de fondo. Verifica la ruta";
    } else {
        qDebug() << "Imagen de fondo cargada correctamente desde el recurso.";
    }
    //tamaño de tu widget
    setFixedSize(692, 692);
    setFocusPolicy(Qt::StrongFocus);

}

void fondo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (useBackground1) {
        painter.drawPixmap(0, 0, width(), height(), background1);
    } else {
        double zoomFactor = 1.5;
        QPixmap scaledBackground2 = background2.scaled(background2.width() * zoomFactor,
                                                       background2.height() * zoomFactor,
                                                       Qt::KeepAspectRatio,
                                                       Qt::SmoothTransformation);
        // Centrar la imagen escalada
        int x = (width() - scaledBackground2.width()) / 2;
        int y = (height() - scaledBackground2.height()) / 2;
        painter.drawPixmap(x, y, scaledBackground2);
    }
}
void fondo::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_K) {
        toggleBackground();
    }
    // Llama al método base para manejar otros eventos de tecla
    QWidget::keyPressEvent(event);
}

void fondo::toggleBackground()
{
    useBackground1 = !useBackground1;
    update(); // Redibuja el widget
}
