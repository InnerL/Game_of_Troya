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
    const QVector<QPair<QRect, bool>>& getColisionArea() const;
    void aggMaterial(const QPixmap &pixmap, int x, int y);

    const QVector<Material*>& getMaterials() const;


protected:
    void paintEvent(QPaintEvent *event) override;


private:
    QPixmap background1;
    QVector<QPixmap> tiles;
    QVector<QPair<QRect, bool>> colisionArea;
    QVector<Material*> materials; // Almacenar los materiales


};

#endif // FONDO_H
