#ifndef FISICA_H
#define FISICA_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

#define time_period 10

class fisica : public QObject
{
    Q_OBJECT
public:
    fisica(int x, int y, int w, int h, QGraphicsPixmapItem *item);
    void set_movement_type(QString type);
    float get_vx() const;
    void set_vx(float vx);
    float get_x() const;
    float get_y() const;
    void set_y(float y);
    float get_vy() const;
    void set_vy(float vy);
    float get_phisical_x(float x);
    float get_phisical_y(float y);
    float get_simulated_x(float x);
    float get_simulated_y(float y);
    QGraphicsPixmapItem *get_item() const;
    void jump2();
    void jump3();
    int x_dimension, y_dimension, h, w;
    float x, y, vx, vy;
    QTimer *time;
    QGraphicsPixmapItem *item;
    QString type;

    void calculate_cinematics(float ax, float ay);
    void calculate_parabolic_dynamics();
    void calculate_MRU_dynamics();
    void set_initial_conditions(float x, float y, float vx, float vy);

private slots:
    void time_step();

signals:
    void is_moving(QGraphicsPixmapItem *, bool, bool);
};

#endif // FISICA_H
