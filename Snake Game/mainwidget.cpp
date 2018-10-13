#include "mainwidget.h"
#include "gamewidget.h"
#include <QIcon>
#include <QPalette>
#include <QPushButton>
#include <QFont>
#include <QMessageBox>

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口大小
    this->resize(480, 270);
    this->setMaximumSize(480, 270);

    // 设置窗口标题和Icon
    this->setWindowTitle("snake");
    this->setWindowIcon(QIcon(":/new/prefix1/img/icon.png"));

    // 设置调色板  (设置背景图片)
    QPalette palette;
    /*QPixmap  .scaled() 设置图片大小 */
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/img/back.jpg").scaled(this->size())));
    this->setPalette(palette);

    // 添加开始按钮
    startbtn = new QPushButton(this);
    startbtn->setIcon(QIcon(":/new/prefix1/img/start.png"));
    startbtn->setIconSize(QSize(75, 75));
    startbtn->setGeometry(QRect(250, 170, 75, 75));
    startbtn->setFlat(true);

    // 添加退出按钮
    exitbtn = new QPushButton(this);
    exitbtn->setIcon(QIcon(":/new/prefix1/img/quit.png"));
    exitbtn->setIconSize(QSize(70, 70));
    exitbtn->setGeometry(QRect(350, 170, 70, 70));
    exitbtn->setFlat(true);

    // 设置文字说明
    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(13);
    lable = new QLabel(this);
    lable->setText("游戏说明：贪吃蛇游戏可使用按钮或者w a s d控制蛇的走动.");
    lable->setFont(font);
    lable->setGeometry(QRect(10, 10, 400, 50));

    // 开始、退出按钮连接对应槽函数
    connect(startbtn, &QPushButton::clicked, this, &mainWidget::startSlot);
    connect(exitbtn, &QPushButton::clicked, this, &mainWidget::exitSlot);
}

mainWidget::~mainWidget()
{
    // 动态申请的类如果指定了父对象，不需要手动释放。
}

// 开始按钮槽函数
void mainWidget::startSlot()
{
    g = new GameWidget(this);
    g->show();
}

// 退出按钮槽函数
void mainWidget::exitSlot()
{
    if (QMessageBox::question(this, "退出游戏", "是否退出当前游戏？", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        delete this;
        exit(0);
    }
}
