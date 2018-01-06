#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ipc.h"

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void LoginClicked(QString UserName, QString Password, QString IPAddress, int Port);

private slots:

    void on_PlayButton_clicked();

    void on_AddDeviceButton_clicked();

    void processImage(QImage img);


private:
    Ui::MainWindow *ui;
    IPC *ipc_device;
    int device_id;
};

#endif // MAINWINDOW_H
