#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
//    flower = new SunFlower(this);
//    flower->move(QPoint(300,100));
//    flower->show();
    title = new ChoosePlantsTitllBar(this);
    title->show();
    title->m_cintor->addPlant(1,1,"shooter",this);
    title->m_cintor->addPlant(0,0,"sunflower",this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
 //
}

void Form::on_pushButton_2_clicked()
{
  //  flower->deleted();
}
