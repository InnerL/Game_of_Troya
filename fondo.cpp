#include "fondo.h"
#include <QPainter>
#include <QDebug>
#include <iostream>
#include <ostream>

Fondo::Fondo(QWidget *parent)
    : QWidget(parent),
    background1(":/map_1.png") // Ruta del fondo
{
    try {


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

        // Añadir áreas de colisión (marcando los bordes del mapa con true)
        colisionArea.append(qMakePair(QRect(0, 0, 768, 48), true)); // Área superior
        colisionArea.append(qMakePair(QRect(0, 720, 768, 48), true)); // Área inferior
        colisionArea.append(qMakePair(QRect(0, 0, 48, 768), true)); // Área izquierda
        colisionArea.append(qMakePair(QRect(720, 0, 48, 768), true)); // Área derecha
        //Vacios       
        colisionArea.append(qMakePair(QRect(48, 245, 40, 105), false)); // →(Aleft←, Atop↑, Awidth↔️,AHeight↕️)
        colisionArea.append(qMakePair(QRect(348, 197, 25, 95), false));//↕️
        colisionArea.append(qMakePair(QRect(690, 387, 47, 220), false));//↕️
        colisionArea.append(qMakePair(QRect(445, 100, 136, 10), false));//↔️
        colisionArea.append(qMakePair(QRect(348, 675, 130, 35), false));//↔️

        //Lapida-Piedra
        colisionArea.append(qMakePair(QRect(638, 590, 47, 25), false));//←
        colisionArea.append(qMakePair(QRect(500, 552, 50, 10), false));//←
        colisionArea.append(qMakePair(QRect(375, 388, 15, 45), false));//
        colisionArea.append(qMakePair(QRect(270, 171, 40, 10), false));//
        colisionArea.append(qMakePair(QRect(210, 676, 15, 45), false));//
        colisionArea.append(qMakePair(QRect(105, 387, 15, 5), false));//

        //Arboles-tronco
        colisionArea.append(qMakePair(QRect(200, 150, 45, 0), false));//tronco ↓
        colisionArea.append(qMakePair(QRect(185, 67, 70, 60), false));//planta ↓
        colisionArea.append(qMakePair(QRect(495, 345, 20, 0), false));// ↓
        colisionArea.append(qMakePair(QRect(470, 262, 55, 60), false));//↓
        colisionArea.append(qMakePair(QRect(110, 632, 25, 0), false));// ↓
        colisionArea.append(qMakePair(QRect(90, 552, 55, 50), false));//↓
        colisionArea.append(qMakePair(QRect(99, 249, 35, 10), false));//tronco
        colisionArea.append(qMakePair(QRect(500, 636, 35, 10), false));

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
    }

}
void Fondo::aggMaterial(const QPixmap &pixmap, int x, int y)
{
    try {
        Material *material = new Material(pixmap, x, y, this);
        materials.append(material);
        material->show();
        if (material->isVisible()) {
            qDebug() << "Material añadido en (" << x << "," << y << ")";
        } else {
            qWarning() << "El material no es visible. Posiblemente hubo un error.";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
    }


}

void Fondo::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // Aquí usamos Q_UNUSED para suprimir la advertencia
    try {
        QPainter painter(this);
        int numCols = width() / 48;
        int numRows = height() / 48;

        for (int y = 0; y < numRows; ++y) {
            for (int x = 0; x < numCols; ++x) {
                int tileIndex = (y % (background1.height() / 48)) * (background1.width() / 48) + (x % (background1.width() / 48));
                painter.drawPixmap(x * 48, y * 48, tiles[tileIndex]);
            }
        }


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
    }


}

const QVector<QPair<QRect, bool>>& Fondo::getColisionArea() const {
    return colisionArea;
}

const QVector<Material*>& Fondo::getMaterials() const {
    return materials;
}
