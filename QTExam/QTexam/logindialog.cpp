#include "logindialog.h"
#include "ui_logindialog.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDebug>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
   // QFile info_file("a.txt");//account.txt
    QFile file("out.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug()<<"fsfsd";
        return;
    }
    QTextStream out(&file);
    out << "The magic number is: " << 49 << "\n";

    file.close();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginpushButton_clicked()
{

}
