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



};

#endif // MATERIAL_H
