#ifndef FIRSTSCREEN_H
#define FIRSTSCREEN_H

#include <QList>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "basicwindow.h"
#include "chooseplantstitllbar.h"
#include "setbtndialog.h"
#include "mediaplayer.h"

#define ATTACKPATH ":/resources/jspvz/videos/sys/splat1.mp3"
#define WIN_VIDEO_PATH ":/resources/jspvz/videos/sys/winmusic.mp3"
#define PLAY_VIDEO_PATH ":/resources/jspvz/videos/sys/welcomvideo.mp3"
#define ENDING_VIDEO_PATH ":/resources/jspvz/videos/sys/evillaugh.mp3"
#define SUNBACK_PATH ":/resources/jspvz/SunBack.png"
class ChoosePlantsTitllBar;
class FirstScreen : public BasicWindow
{
    Q_OBJECT
public:
    explicit FirstScreen(QWidget *parent = nullptr);
    FirstScreen(int id,QList<int> list,QWidget *parent = nullptr);
    ~FirstScreen();
    void setSize(const QSize &size);
    void paintEvent(QPaintEvent *);
    void setZombies(QList<int> list);
    void setPlontAddCount(int count);
    void setZombieAddCount(int count);
    void init();
    void start();
    void stop();
    static void costSun(int mun);
    //void closeEvent(QCloseEvent *);
signals:
   void signalScClosed();
   void signalRestart(int id);
   void signalquit();
public slots:
   void onrestore();
   void onMinClicked();
   void onquit();
   void onrestart();
   void on_doRun();
   void on_sunMunChanged();
    void on_endGame();
    void onSetBtnClicked();
    void oncloseBtnClicked();
    void oncancelBtnClicked();
    void oncontinueBtnClicked();
    void on_timeout();
    void on_winGame();
    void oncloseWidget();
    void oncancelClose();
private:
    void winGame();


private:
    int id = -1;
    Label *m_sunBckLabel;
    QLabel *m_sunNumLabel;
    QLabel *ready_plants;
    int basicTimeCout = 20;
    int addZombies_times = 20;
    int m_timeCount = 1000;
    QList<int> m_zombielist;
    ChoosePlantsTitllBar *bar=nullptr;
    SetBtnDialog *dialog = nullptr;
    QTimer *m_timer;
    //QMediaPlayer *m_attackPlay = nullptr;
    QMediaPlayer *m_player;
    QMediaPlayer *m_readyplay;
    QMediaPlaylist *m_play_list;
    int zombiesmun =0;
    MediaPlayer *attackplay = nullptr;
    //QThreadPool *pool = nullptr;
public:
    static int sun_num;
};

#endif // FIRSTSCREEN_H
