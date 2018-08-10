#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(480,640);
    MainMatrix = new Matrix(this);
}

MainWindow::~MainWindow()
{
    delete MainMatrix;
    delete ui;
}
