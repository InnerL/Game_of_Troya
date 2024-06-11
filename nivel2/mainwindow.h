#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include "character.h"
#include "level_2.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void updateProgressBar(int value);
    void showRestartButton(); // Slot to show restart button
    void restartLevel(); // Add slot to handle game restart

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Character *character;
    Level_2 *level;
    QLabel *counterLabel;
    QProgressBar *progressBar;
    QPushButton *restartButton; // Add restart button
};

#endif // MAINWINDOW_H
