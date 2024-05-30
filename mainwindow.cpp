#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pixmap(":/map_1.png");
    ui->imageLabel->setPixmap(pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}
