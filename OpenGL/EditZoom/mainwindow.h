#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* );

private:
    Ui::MainWindow *ui;

    float zoom = 1.0;
    float x_tran = 0;
    float y_tran = 0;
};

#endif // MAINWINDOW_H
