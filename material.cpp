#include "material.h"
#include <QPainter>
#include <QDebug>

Material::Material(const QPixmap &pixmap, int x, int y, QWidget *parent)
    : QWidget(parent), pixmap(pixmap), collected(false)
{
    try {
        if (pixmap.isNull()) {
            qWarning() << "No se pudo cargar la imagen del material. Verifica la ruta del recurso";
        } else {
            qDebug() << "Imagen del material cargada correctamente.";
        }
        setFixedSize(pixmap.size());
        move(x, y); // Colocar el material en la posición deseada
        qDebug() << "Material creado en posición:" << x << y << "con tamaño:" << pixmap.size();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
    }
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

    if (isVisible()) {
        QPainter painter(this);
        if (!collected) {
            painter.drawPixmap(0, 0, pixmap);
            qDebug() << "Dibujando material en posición:" << pos();
        }
    }
}

QRect Material::getRect() const
{
    return QRect(pos(), size());
}


