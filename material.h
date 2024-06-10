#ifndef MATERIAL_H
#define MATERIAL_H

#include <QWidget>
#include <QPixmap>

class Material : public QWidget
{
    Q_OBJECT

public:

    Material(const QPixmap &pixmap, int x, int y, QWidget *parent = nullptr);
    void setCollected(bool collected);
    bool isCollected() const;
    QRect getRect() const;
    void setVisibility(bool visible);


protected:
    void paintEvent(QPaintEvent *event) override;


private:
    QPixmap pixmap;
    bool collected;
    static int paintCounter; // ContadorpaintEvent

    static int materialCont;

    QPixmap buffer; // Buffer para almacenar el contenido dibujado
    bool paintedOnce; // Indica si el contenido ya ha sido dibujado


};

#endif // MATERIAL_H
