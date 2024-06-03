#ifndef MATERIAL_H
#define MATERIAL_H

#include <QWidget>
#include <QPixmap>

class Material : public QWidget
{
    Q_OBJECT

public:
    enum MaterialType {
        Piedra,
        Madera
    };

    Material(const QPixmap &pixmap, int x, int y, QWidget *parent = nullptr);
    void setCollected(bool collected);
    bool isCollected() const;
    QRect getRect() const;

    MaterialType getType() const; // Nueva función para obtener el tipo de material



protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap pixmap;
    bool collected;

    MaterialType type; // Nueva propiedad para almacenar el tipo de material



};

#endif // MATERIAL_H
