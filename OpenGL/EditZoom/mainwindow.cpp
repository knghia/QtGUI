#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case 16777235:
        x_tran += 0.1;
        break;
    case 16777237:
        x_tran -= 0.1;
        break;
    case 16777234:
        y_tran -= 0.1;
        break;
    case 16777236:
        y_tran += 0.1;
        break;

    case 83:
        zoom -= 0.1;
        break;
    case 68:
        zoom += 0.1;
        break;
    default:
        break;
    }
    qDebug()<<zoom<<x_tran<<y_tran;

    ui->gl_widget->set_zoom(zoom);
    ui->gl_widget->set_translatef(x_tran, y_tran);
}














