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

void MainWindow::on_alpha_slider_valueChanged(int value)
{
    ui->gl_widget->setAlpha(value);
}

void MainWindow::on_beta_slider_valueChanged(int value)
{
    ui->gl_widget->setBeta(value);
}
