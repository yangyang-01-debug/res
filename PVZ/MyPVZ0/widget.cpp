#include "widget.h"
#include "ui_widget.h"
#include "logindialog.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    dia = new LoginDialog();
//    dia->show();
}

Widget::~Widget()
{
    delete ui;
    if(dia != nullptr){
        delete dia;
        dia = nullptr;
    }
}


void Widget::on_pushButton_clicked()
{
    dia->show();
}

void Widget::on_pushButton_2_clicked()
{
    dia->close();
}
