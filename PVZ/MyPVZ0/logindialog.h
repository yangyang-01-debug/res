#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "titlebar.h"
#include "mybtn.h"
#include "messagebox.h"
#include <QEventLoop>
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void do_timeout();
    void onButtonStartGameClicked();

    void oncloseBoxClicked(QString str);
    void onButtonMinClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();
    void onButtonRestoreClicked();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
private:
    void init();
    void connectsToTitleBar();

    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    Ui::LoginDialog *ui;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_play_list;
    TitleBar *m_titleBar;
    QSystemTrayIcon *mSysTrayIcon;
    QTimer *m_timer;
    MyBtn *m_btn;

    MessageBox *m_messageBox;
    QString m_boxreturn;
    QEventLoop loop;
    bool m_is_Message;

    static int m_timer_count;
    static bool m_is_connected;
    static float m_progressBar_value;
};

#endif // LOGINDIALOG_H
