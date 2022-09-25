#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

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
    void receive_message();
    void on_disconnect_bt_clicked();

    void on_clean_data_bt_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort serial_port;
    QSerialPortInfo serial_port_info;
    qint32 time_out = 100;
    bool is_connect;
};

#endif // MAINWINDOW_H
