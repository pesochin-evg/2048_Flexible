#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(480,640);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMaximumSize(480,640);
    this->setMinimumSize(480,640);
    this->setWindowTitle("2048");
    MainMatrix = new Matrix(this);
}

MainWindow::~MainWindow()
{
    delete MainMatrix;
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    last_press = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
    QPoint release = event->pos();

    if(abs(last_press.x() - release.x()) > abs(last_press.y() - release.y()))
    {
        if(last_press.x() > release.x())
        {
            MainMatrix->Left();
        } else {
            MainMatrix->Right();
        }
    } else {
        if(last_press.y() > release.y())
        {
            MainMatrix->Up();
        } else {
            MainMatrix->Down();
        }
    }
}
