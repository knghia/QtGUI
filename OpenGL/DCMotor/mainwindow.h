#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <qcustomplot.h>
#include <glwidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setup_graphics(void);
    void show_data_graphics(float t, float xt, float wt);

private slots:
    void on_voltage_slider_valueChanged(int value);
    void on_load_bt_clicked();
    void upload_dc_motor(void);

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    float time = 0;

    int time_limit = 2;
    int wt_min_limit= -2;
    int wt_max_limit= 2;

    int theta_min_limit= -2;
    int theta_max_limit= 2;
};

#endif // MAINWINDOW_H
