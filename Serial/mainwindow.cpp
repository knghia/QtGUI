#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setup_gui();
}

void MainWindow::setup_gui(void){
    QList<QString> bauds ={"9600", "14400", "19200", "38400", "57600", "115200", "128000", "256000"};
    ui->baudrate_cb->addItems(bauds);

    QList<QSerialPortInfo> ports =serial_port_info.availablePorts();

    for(int i = 0 ; i < ports.size() ; i++){
        ui->port_cb->addItem(ports.at(i).portName());
    }

    QList<QString> data_bits ={"8", "7", "6", "5"};
    ui->data_cb->addItems(data_bits);

    QList<QString> paritys ={"None", "Even", "Odd"};
    ui->parity_cb->addItems(paritys);

    this->time_out = ui->timeout_le->text().toInt();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_conncet_bt_clicked()
{
    if (is_connect == false){
        QString port = ui->port_cb->currentText();
        serial_port.setPortName(port);

        QString baudrate = ui->baudrate_cb->currentText();
        serial_port.setBaudRate(baudrate.toInt());

        QString data = ui->data_cb->currentText();
        if (data == "8") serial_port.setDataBits(QSerialPort::Data8);
        else if (data == "7") serial_port.setDataBits(QSerialPort::Data7);
        else if (data == "6") serial_port.setDataBits(QSerialPort::Data6);
        else if (data == "5") serial_port.setDataBits(QSerialPort::Data5);

        QString parity = ui->parity_cb->currentText();
        if (parity == "None") serial_port.setParity(QSerialPort::NoParity);
        else if (parity == "Even") serial_port.setParity(QSerialPort::EvenParity);
        else if (parity == "Odd") serial_port.setParity(QSerialPort::OddParity);

        QString stop_bit = ui->stopbit_cb->currentText();
        if (stop_bit == "1") serial_port.setStopBits(QSerialPort::OneStop);
        else if (stop_bit == "1.5") serial_port.setStopBits(QSerialPort::OneAndHalfStop);
        else if (stop_bit == "2") serial_port.setStopBits(QSerialPort::TwoStop);

        serial_port.open(QIODevice::ReadWrite);
        if(!serial_port.isOpen()){
            QMessageBox::information(this, "Serial","Don't connect");
        }
        else{
            QMessageBox::information(this, "Serial","Connect");
            connect(&serial_port,SIGNAL(readyRead()),this,SLOT(receive_message()));
            is_connect = true;
            ui->config_gb->setEnabled(false);
        }
    }
}

void MainWindow::receive_message(void){
    if(is_connect == true){
        QByteArray dataBA = serial_port.readAll();
        QString data(dataBA);
        ui->show_data_tb->setTextColor(Qt::blue);
        ui->show_data_tb->append(data);
    }
}

void MainWindow::on_disconnect_bt_clicked()
{
    if (is_connect == true){
        serial_port.close();
        is_connect = false;
        ui->config_gb->setEnabled(true);
    }
}

void MainWindow::on_clean_data_bt_clicked()
{
    ui->show_data_tb->clear();
}
