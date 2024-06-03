#include "fondo.h"
#include <QPainter>
#include <QDebug>

Fondo::Fondo(QWidget *parent)
    : QWidget(parent),
    background1(":/map_1.png"), // Ruta del fondo
    maderaLabel(new QLabel(this)),
    piedraLabel(new QLabel(this))
{
    if (background1.isNull()) {
        qWarning() << "No se pudo cargar la primera imagen de fondo. Verifica la ruta del recurso";
    }
    // Tamaño de tu widget
    setFixedSize(768, 768);
    setFocusPolicy(Qt::StrongFocus);

    // Dividir el fondo en cuadros de 48x48
    int rows = background1.height() / 48;
    int cols = background1.width() / 48;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QPixmap tile = background1.copy(col * 48, row * 48, 48, 48);
            tiles.append(tile);
        }
    }

    colisionArea.append(QRect(0, 0, 768, 48)); // Área superior
    colisionArea.append(QRect(0, 720, 768, 48)); // Área inferior
    colisionArea.append(QRect(0, 0, 48, 768)); // Área izquierda
    colisionArea.append(QRect(720, 0, 48, 768)); // Área derecha
    //Vacios
    colisionArea.append(QRect(48, 245, 40, 105)); // →(Aleft←, Atop↑, Awidth↔️,AHeight↕️)
    colisionArea.append(QRect(348, 197, 25, 95));//↕️
    colisionArea.append(QRect(690, 387, 47, 220));//↕️
    colisionArea.append(QRect(445, 100, 136, 10));//↔️
    colisionArea.append(QRect(348, 675, 130, 35));//↔️

    //Lapida-Piedra
    colisionArea.append(QRect(638, 590, 47, 25));//←
    colisionArea.append(QRect(500, 552, 50, 10));//←
    colisionArea.append(QRect(375, 388, 15, 45));//
    colisionArea.append(QRect(270, 171, 40, 10));//
    colisionArea.append(QRect(210, 676, 15, 45));//
    colisionArea.append(QRect(105, 387, 15, 5));//

    //Arboles-tronco
    colisionArea.append(QRect(200, 150, 45, 0));//tronco ↓
    colisionArea.append(QRect(185, 67, 70, 60));//planta ↓
    colisionArea.append(QRect(495, 345, 20, 0));// ↓
    colisionArea.append(QRect(470, 262, 55, 60));//↓
    colisionArea.append(QRect(110, 632, 25, 0));// ↓
    colisionArea.append(QRect(90, 552, 55, 50));//↓
    colisionArea.append(QRect(99, 249, 35, 10));//tronco
    colisionArea.append(QRect(500, 636, 35, 10));//

}
void Fondo::aggMaterial(const QPixmap &pixmap, int x, int y, Material::MaterialType type)
{
    Material *material = new Material(pixmap, x, y, this);
    if (material->isVisible()) {
        qDebug() << "Material añadido en (" << x << "," << y << ")";
    } else {
        qWarning() << "El material no es visible. Posiblemente hubo un error.";
    }
    material->setPixmap(pixmap);
    material->setPos(x, y);
    materials.append(material);
    scene()->addItem(material);
}

void Fondo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int numCols = width() / 48;
    int numRows = height() / 48;

    for (int y = 0; y < numRows; ++y) {
        for (int x = 0; x < numCols; ++x) {
            int tileIndex = (y % (background1.height() / 48)) * (background1.width() / 48) + (x % (background1.width() / 48));
            painter.drawPixmap(x * 48, y * 48, tiles[tileIndex]);
        }
    }

    for (Material* material : materials) {
        if (!material->isCollected()) {
            material->show();

        }
    }

}

const QVector<QRect>& Fondo::getColisionArea() const {
    return colisionArea;
}

const QVector<Material*>& Fondo::getMaterials() const {
    return materials;
}

void Fondo::updateLabels(int maderaCount, int piedraCount)
{
    maderaLabel->setText(QString("Madera: %1").arg(maderaCount));
    piedraLabel->setText(QString("Piedra: %1").arg(piedraCount));
}
