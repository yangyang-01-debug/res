#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QMovie>
#define FIRE_PBS ":/res/PBfire.gif"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMovie *m = new QMovie(QString("%1").arg(FIRE_PBS));
    QLabel *mlabel = new QLabel(this);
    mlabel->setFixedSize(56,30);
    mlabel->setMovie(m);
    m->start();

//    create_databases(db);
//    open_database(db);
//    //db.exec(create_table("t3","class_id int , class_name varchar(128), class_teacher varchar(64)"));
//    //db.exec(insertinto_table("t3","101, '六年级一班', '马老师'"));
//    QStringList tables = db.tables();
//    foreach(QString table, tables)//add_constraints("t3","class_id int(11)",property_primary_key)
//        qDebug()<<table;//alter table t3 modify class_id int(11) PRIMARY KEY;
//    //db.exec(create_table("t4","class_id int , class_name varchar(128), class_teacher varchar(64)"));
//    //db.exec(add_constraints("t4","class_id int",property_primary_key));

//    QSqlQuery result = db.exec(select_table_where(tables.at(0),"*","id=2"));
//    QString str;
//    while(result.next()){
//        str += result.value(0).toString()+result.value(1).toString();
//    }

//    result.clear();
//    db.close();
//    ui->textBrowser->setText(str);
}

MainWindow::~MainWindow()
{
    delete ui;
}

