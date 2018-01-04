#include "logindialog.h"
#include "ui_logindialog.h"
#include <QLineEdit>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::RegisteUserName(){

   return ui->UserNameEdit->text();

}

QString LoginDialog::RegistePassword(){

   return ui->PasswordEdit->text();

}


QString LoginDialog::RegisteIPAddress(){

   return ui->IPAddressEdit->text();

}

int LoginDialog::RegistePort(){

   bool ok;
   return ui->PortEdit->text().toInt(&ok);
}

