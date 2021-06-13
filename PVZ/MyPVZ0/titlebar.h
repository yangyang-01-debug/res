#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "config.h"

enum ButtonType{
    MIN_BUTTON,//最小化关闭
    MIN_MAX_BUTTON,//最小最大化
    ONLY_CLOSE_BUTTON//只有关闭
};

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
    void setTitleColor(const QColor &color);
    void setTitleIcon(QString &filepath);//设置标题栏图标
    void setTitleContent(QString &titlecontent);//设置标题栏内容
    void setTitleWidth(int width);//设置标题栏长度
    void setButtonType(ButtonType type);//设置按钮类型

    //保存、获取窗口最大化前的位置以及大小
    void saveRestoreInfo(const QPoint &point,const QSize &size);
    void getRestoreInfo(QPoint &point,QSize &size);

private:
    void paintEvent(QPaintEvent *);//绘图事件
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件
    void mousePressEvent(QMouseEvent *event);//鼠标点击事件
    void mouseDoubleClickEvent(QMouseEvent *event);//鼠标双击事件
    void mouseReleaseEvent(QMouseEvent *event);//鼠标施放事件

    void initControl();//初始化控件
    void initConnections();//初始化信号与槽连接
    void loadStyleSheet(const QString &sheetName);//加载样式表

    static QPushButton *getBtn(QWidget *parent,int w,int h,QString name);
signals:
    void signalButtonMinClicked();//最小化按钮点击
    void signalButtonMaxClicked();//最大化按钮点击
    void signalButtonRestoreClicked();//最大化还原按钮点击
    void signalButtonCloseClicked();//关闭按钮点击

private slots:
    //按钮响应
    void onButtonMinClicked();
    void onButtonMaxClicked();
    void onButtonRestoreClicked();
    void onButtonCloseClicked();

private:
    //两个显示信息
    QLabel *m_pIcon;
    QLabel *m_pTitleContent;
    //四个按钮
    QPushButton *m_pButtonMin;
    QPushButton *m_pButtonMax;
    QPushButton *m_pButtonRestore;
    QPushButton *m_pButtonClose;
    //窗口信息
    QPoint m_restorPos;
    QSize m_restoreSize;
    bool m_isPressed;
    QPoint m_startMovePos;
    QString m_titleContent;
    ButtonType m_buttonType;
    QColor m_titleBarColor;
};

#endif // TITLEBAR_H
