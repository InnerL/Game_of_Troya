#include "fisica.h"

fisica::fisica(int x, int y, int w, int h, QGraphicsPixmapItem *item)
{
    x_dimension = 4;
    y_dimension = 4;
    this->w = w;
    this->h = h;
    this->item = item;
    set_initial_conditions(x, y, 0, 0);

    time = new QTimer;
    connect(time, SIGNAL(timeout()), this, SLOT(time_step()));
    time->start(time_period);
}

void fisica::set_movement_type(QString type)
{
    this->type = type;
    if (type == "parabolic")
        set_initial_conditions(item->x(), item->y(), vx, vy + 3);
    else if (type == "MRU")
        set_initial_conditions(item->x(), item->y(), vx + 1, 0);
}

float fisica::get_phisical_x(float x)
{
    return x_dimension * x / w;
}

float fisica::get_phisical_y(float y)
{
    return y_dimension - y_dimension * y / h;
}

float fisica::get_simulated_x(float x)
{
    return w * x / x_dimension;
}

float fisica::get_simulated_y(float y)
{
    return h * (y_dimension - y) / y_dimension;
}

void fisica::calculate_cinematics(float ax, float ay)
{
    x += vx * time_period / 1000.0;
    y += vy * time_period / 1000.0;
    vx += ax * time_period / 1000.0;
    vy += ay * time_period / 1000.0;

    item->setPos(get_simulated_x(x), get_simulated_y(y));
}

void fisica::calculate_parabolic_dynamics()
{
    float ay = -9.8;

    calculate_cinematics(0, ay);
}

void fisica::calculate_MRU_dynamics()
{
    calculate_cinematics(0, 0);
}

void fisica::set_initial_conditions(float x, float y, float vx, float vy)
{
    this->x = get_phisical_x(x);
    this->y = get_phisical_y(y);
    this->vx = vx;
    this->vy = vy;
}

void fisica::time_step()
{
    if (type == "parabolic")
        calculate_parabolic_dynamics();
    else if (type == "MRU")
        calculate_MRU_dynamics();
    emit is_moving(item, true, true);
}

float fisica::get_vx() const
{
    return vx;
}

void fisica::set_vx(float vx)
{
    this->vx = vx;
}

float fisica::get_x() const
{
    return x;
}

float fisica::get_y() const
{
    return y;
}

void fisica::set_y(float y)
{
    this->y = y;
}

float fisica::get_vy() const
{
    return vy;
}

void fisica::set_vy(float vy)
{
    this->vy = vy;
}

QGraphicsPixmapItem *fisica::get_item() const
{
    return item;
}

void fisica::jump()
{
    if (y <= get_phisical_y(300)) {  // Assuming 300 is the y coordinate of the floor
        vy = 5.0;  // Set the initial vertical speed for the jump
    }
}
