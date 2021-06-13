#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QList>
#include <QMessageBox>
#include <QHBoxLayout>
#include "titlebar.h"
#include "mybtn.h"
class MessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit MessageBox(QWidget *parent = nullptr);
    MessageBox(const QStringList namelist, QWidget *parent = nullptr);
    virtual ~MessageBox();
    //QString getReturn();
    void setText(const QString &title,const QString &text);
private:
    void connectsToTitle();
    void setstyle();
    void paintEvent(QPaintEvent *);
signals:
    void closebox(QString str);
private slots:
    void onButtonCloseClicked();
    void onButtonClicked(const QString &str);
private:
    QString m_title;
    QString m_text;
    TitleBar *m_titleBar;
    QList<MyBtn*> m_mylist_mybtn;
   // QString m_return;
};

#endif // MESSAGEBOX_H
