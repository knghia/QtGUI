#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <qcustomplot.h>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setup_gui(void);

private slots:
    void on_conncet_bt_clicked();
    void show_data_graphics();
    void on_disconnect_bt_clicked();
    void receive_message();

private:
    Ui::MainWindow *ui;

    QSerialPort serial_port;
    QSerialPortInfo serial_port_info;
    QTimer *timer_plot;

    qint32 time_out = 100;
    bool is_connect = false;

    float temperature = 0;
    float time = 0;
};

#endif // MAINWINDOW_H
