#include "material.h"
#include <QPainter>
#include <QDebug>
#include <iostream>
#include <ostream>

int Material::materialCont = 0;
int Material::paintCounter = 0;


Material::Material(const QPixmap &pixmap, int x, int y, QWidget *parent)
    : QWidget(parent), pixmap(pixmap), collected(false), paintedOnce(false)

{
    try {
        if (pixmap.isNull()) {
            qWarning() << "No se pudo cargar la imagen del material. Verifica la ruta del recurso";
        } else {
            qDebug() << "Imagen del material cargada correctamente.";
        }
        setFixedSize(pixmap.size());
        move(x, y); // Colocar el material en la posición deseada
        materialCont++; // Incrementar el contador de instancias
        qDebug() << "Material creado en posición:" << x << y << "con tamaño:" << pixmap.size();
        qDebug() << "Número de instancias de Material: " << materialCont;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
    }
    // Inicializar el buffer
    buffer = QPixmap(size());
    buffer.fill(Qt::transparent);
}

void Material::setCollected(bool collected)
{
    this->collected = collected;
    update();
}

bool Material::isCollected() const
{
    return collected;
}

void Material::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // Aquí usamos Q_UNUSED para suprimir la advertencia


    if (!paintedOnce) {
        QPainter bufferPainter(&buffer);
        bufferPainter.drawPixmap(0, 0, pixmap);
        paintedOnce = true;
        qDebug() << "Material dibujado una vez en el buffer.";
    }

    QPainter painter(this);
    painter.drawPixmap(0, 0, buffer);

}

QRect Material::getRect() const
{
    return QRect(pos(), size());
}


