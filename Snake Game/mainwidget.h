#ifndef MIANWIDGET_H
#define MAINWIDGET_H

#include "gamewidget.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = 0);
    ~mainWidget();

    void startSlot();   // 开始按钮槽函数
    void exitSlot();    // 退出按钮槽函数

private:
    QPushButton *startbtn;   // 开始按钮
    QPushButton *exitbtn;    // 退出按钮
    QLabel *lable;    // 说明标签
    GameWidget *g;    // 游戏窗口


};

#endif // MAINWIDGET_H
