#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fondo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //una instancia de Fondo y se establece como el widget central
    fondo *fondoWidget = new fondo(this);
    setCentralWidget(fondoWidget);

    fondoWidget->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}
