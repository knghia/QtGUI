#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_graphics();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(upload_dc_motor()));
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_voltage_slider_valueChanged(int value)
{
    ui->voltage_la->setText(QString::number(value));
}

void MainWindow::on_load_bt_clicked(){
    int voltage = ui->voltage_slider->value();
    ui->dc_glwidget->set_voltage(voltage);
}

void MainWindow::upload_dc_motor(void){
    ui->dc_glwidget->set_time(0.01);
    float wt = ui->dc_glwidget->get_wt();
    float theta = ui->dc_glwidget->get_theta();
    show_data_graphics(0.01, wt, theta);
}

void MainWindow::setup_graphics(void){
    ui->xt_graphic->addGraph();
    ui->xt_graphic->xAxis->setLabel("t(s)");
    ui->xt_graphic->yAxis->setLabel("x(t)");
    ui->xt_graphic->xAxis->setRange(0, time_limit);
    ui->xt_graphic->yAxis->setRange(theta_min_limit, theta_max_limit);
    ui->xt_graphic->graph(0)->setPen(QPen(Qt::red));

    ui->wt_graphic->addGraph();
    ui->wt_graphic->xAxis->setLabel("t(s)");
    ui->wt_graphic->yAxis->setLabel("x(t)");
    ui->wt_graphic->xAxis->setRange(0, time_limit);
    ui->wt_graphic->yAxis->setRange(wt_min_limit, wt_max_limit);
    ui->wt_graphic->graph(0)->setPen(QPen(Qt::blue));
}

void MainWindow::show_data_graphics(float t, float xt, float wt){
    static QVector<double> t_axis;
    static QVector<double> xt_axis;
    static QVector<double> wt_axis;

    this->time+=t;

    QString xt_text;
    ui->xt_la->setText(xt_text.sprintf("%6.2f",xt));
    QString wt_text;
    ui->wt_la->setText(wt_text.sprintf("%4.2f",wt));

    t_axis.append(this->time);
    xt_axis.append(xt);
    wt_axis.append(wt);

    if(this->time > time_limit){
        time_limit += 2;

        ui->xt_graphic->xAxis->setRange(this->time - 2, time_limit);
        ui->wt_graphic->xAxis->setRange(this->time - 2, time_limit);
    }

    if(wt > wt_max_limit){
        wt_max_limit += wt;
        ui->wt_graphic->yAxis->setRange(wt_min_limit, wt_max_limit);
    }
    if(wt < wt_min_limit){
        wt_min_limit += wt;
        ui->wt_graphic->yAxis->setRange(wt_min_limit, wt_max_limit);
    }

    if(xt > theta_max_limit){
        theta_max_limit += xt;
        ui->xt_graphic->yAxis->setRange(theta_min_limit, theta_max_limit);
    }
    if(xt < theta_min_limit){
        theta_min_limit += xt;
        ui->xt_graphic->yAxis->setRange(theta_min_limit, theta_max_limit);
    }

    ui->xt_graphic->graph(0)->setData(t_axis, xt_axis);
    ui->xt_graphic->replot();

    ui->wt_graphic->graph(0)->setData(t_axis, wt_axis);
    ui->wt_graphic->replot();


}


