#ifndef BASICWINDOW_H
#define BASICWINDOW_H
#include <QEventLoop>
#include <QDialog>
#include <QPushButton>
#include "titlebar.h"
#include "messagebox.h"
class BasicWindow : public QDialog
{
    Q_OBJECT
public:
    explicit BasicWindow(QWidget *parent = nullptr);
    void setMessage(bool fl);
    void setMessageBox(bool have);
    void setBackGround(const QString &mapPath);
    ~BasicWindow();
signals:
    void closeWidget();
    void restore();
protected slots:
    void oncloseBoxClicked(QString str);
    void onButtonMinClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();
    void onButtonRestoreClicked();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_setBtnClicked();
private:
    void init();
    void connectsToTitleBar();
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void showEvent(QShowEvent *);
private:
    virtual void closeEvent(QCloseEvent *e);
signals:
    //void signalScClosed();
    void cancelClose();
    void maxBtnClicked();
    void signalSetBtnClicked();
public:
    QString m_mapPath;
    bool m_ishave = true;
protected:
    QPushButton *m_setBtn;
    TitleBar *m_titleBar;
    QSystemTrayIcon *mSysTrayIcon;
    MessageBox *m_messageBox;
    QString m_boxreturn;
    QEventLoop loop;
    bool m_is_Message;
};

#endif // BASICWINDOW_H
