#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logindialog.h"

#include <QStatusBar>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ipc_device = new IPC();

    device_id = -1;
}

MainWindow::~MainWindow()
{
    ipc_device->Logout(device_id);

    delete ui;
    delete ipc_device;
}

void MainWindow::LoginClicked(QString UserName, QString Password, QString IPAddress, int Port)
{
    int result, error_code;

    result = ipc_device->LoginToDevice(UserName, Password, IPAddress, Port);


    if(result == -1)
    {
        error_code = ipc_device->GetLastError();
        ui->statusBar->showMessage(tr("Login Failure! Error Code %1").arg(error_code));
    }
    else
    {
        ui->statusBar->showMessage(tr("Login Success!"));
        device_id = result;
    }

    ui->frame->winId();
}

void MainWindow::on_PlayButton_clicked()
{

    int result, error_code;

    if(device_id != -1)
    {
        result = ipc_device->StartRealPlay(device_id, /*ui->frame->winId()*/NULL);

        if(result == -1)
        {
            error_code = ipc_device->GetLastError();
            ui->statusBar->showMessage(tr("Start RealPlay Failure! Error Code %1").arg(error_code));
        }
        else
        {
            ui->statusBar->showMessage(tr("RealPlay Success!"));
            device_id = result;
        }
    }
}



void MainWindow::on_AddDeviceButton_clicked()
{
    LoginDialog *dialog = new LoginDialog();

    if(dialog->exec())
    {
       LoginClicked(dialog->RegisteUserName(),
                    dialog->RegistePassword(),
                    dialog->RegisteIPAddress(),
                    dialog->RegistePort());
    }

    delete dialog;
}
