#ifndef FONDO_H
#define FONDO_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>


#include "material.h"


class Fondo : public QWidget
{
    Q_OBJECT

public:
    explicit Fondo(QWidget *parent = nullptr);
    const QVector<QRect>& getColisionArea() const;
    void aggMaterial(const QPixmap &pixmap, int x, int y, Material::MaterialType type);

    const QVector<Material*>& getMaterials() const;
    void updateLabels(int maderaCount, int piedraCount); //actualizar label


protected:
    void paintEvent(QPaintEvent *event) override;


private:
    QPixmap background1;
    QVector<QPixmap> tiles;
    QVector<QRect> colisionArea; // Áreas de colisión
    QVector<Material*> materials; // Almacenar los materiales

    QLabel *maderaLabel; // Etiqueta para la madera
    QLabel *piedraLabel; // Etiqueta para la piedra


};

#endif // FONDO_H
