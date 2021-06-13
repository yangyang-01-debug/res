#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "sunflower.h"
#include "chooseplantstitllbar.h"
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Form *ui;
    //SunFlower *flower;
    //ChoosePlantsTitllBar
    ChoosePlantsTitllBar *title;
};

#endif // FORM_H
