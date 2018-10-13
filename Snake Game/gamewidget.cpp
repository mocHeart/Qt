#include "gamewidget.h"
#include <QIcon>
#include <QTime>
#include <QMessageBox>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);   // 启用后将导致Qt在调用paint事件之前填充小部件的背景
    this->setWindowTitle("sanke");
    this->setWindowIcon(QIcon(":/new/prefix1/img/1.png"));

    this->resize(480, 270);
    this->setMaximumSize(480, 270);

    this->setFocusPolicy(Qt::ClickFocus);

    // 调色板 (设置背景)
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/new/prefix1/img/green.jpg").scaled(this->size())));
    this->setPalette(palette);

    // 加载音频文件
    sound = new QSound(":/listen/img/5611.wav", this);
    sound1 = new QSound(":/listen/img/die.wav", this);

    upbtn = new QPushButton(this);
    upbtn->setText("↑");
    upbtn->setGeometry(QRect(380, 90, 40, 30));

    downbtn = new QPushButton(this);
    downbtn->setText("↓");
    downbtn->setGeometry(QRect(380, 170, 40, 30));

    leftbtn = new QPushButton(this);
    leftbtn->setText("←");
    leftbtn->setGeometry(QRect(340, 130, 40, 30));

    rightbtn = new QPushButton(this);
    rightbtn->setText("→");
    rightbtn->setGeometry(QRect(420, 130, 40, 30));

    startbtn = new QPushButton("开始", this);
    startbtn->setGeometry(QRect(350, 220, 40, 30));
    startbtn->setFocusPolicy(Qt::NoFocus);

    returnbtn = new QPushButton("返回", this);
    returnbtn->setGeometry(QRect(410, 220, 40, 30));

    // 分数和等级
    score = 0;
    level = 1;
    foodcount = 0;

    QFont font;
    font.setBold(true);
    font.setFamily("Consolas");
    font.setPixelSize(19);

    // 分数和等级标签
    scorelabel = new QLabel("分数：", this);
    scorelabel->setFont(font);
    scorelabel->setGeometry(QRect(325, 1, 60, 30));

    levellabel = new QLabel("等级：", this);
    levellabel->setFont(font);
    levellabel->setGeometry(QRect(325, 30, 60, 30));

    str1 = QString::number(score);
    str2 = QString::number(level);

    scoreshow = new QLabel(str1, this);
    scoreshow->setFont(font);
    scoreshow->setGeometry(QRect(385, 1, 60, 30));
    levelshow = new QLabel(str2,this);
    levelshow->setFont(font);
    levelshow->setGeometry(QRect(385, 30, 60, 30));

    // 按钮单击信号连接槽
    connect(upbtn, &QPushButton::clicked, this, &GameWidget::upbtnSlot);
    connect(downbtn, &QPushButton::clicked, this, &GameWidget::downbtnSlot);
    connect(leftbtn, &QPushButton::clicked, this, &GameWidget::leftbtnSlot);
    connect(rightbtn, &QPushButton::clicked, this, &GameWidget::rightbtnSlot);
    connect(startbtn, &QPushButton::clicked, this, &GameWidget::startbtnSlot);
    connect(returnbtn, &QPushButton::clicked, this, &GameWidget::returnbtnSlot);

    // 自定义信号连接槽
    connect(this, &GameWidget::upSignal, upbtn, &QPushButton::click);
    connect(this, &GameWidget::downSignal, downbtn, &QPushButton::click);
    connect(this, &GameWidget::leftSignal, leftbtn, &QPushButton::click);
    connect(this, &GameWidget::rightSignal, rightbtn, &QPushButton::click);

    // 设置随机数
    QTime t;
    t = QTime::currentTime();
    qsrand(t.msec() + t.second()*1000);

    snake1[0][0] = qrand() % COL;
    snake1[0][1] = qrand() % ROW;

    foodx = qrand() % COL;
    foody = qrand() % ROW;

    direction = qrand() % 4;

    // 确保 初始时,蛇头的位置和食物的位置不重合
    while ((snake1[0][0] == foodx) && (snake1[0][1] == foody))
    {
        foodx = qrand() % COL;
        foody = qrand() % ROW;
    }


    timer = new QTimer(this);
    timer->setInterval(500);   // 定时时间500ms
    connect(timer, &QTimer::timeout, this, &GameWidget::timeoutSlot);

}

GameWidget::~GameWidget()
{
    // 动态申请的类如果指定了父对象，不需要手动释放。
}

// 向上按钮槽函数
void GameWidget::upbtnSlot()
{
    if (direction == DOWN)
    {
        return;
    }
    else
    {
        direction = UP;
    }
}

// 向下按钮槽函数
void GameWidget::downbtnSlot()
{
    if (direction == UP)
    {
        return;
    }
    else
    {
        direction = DOWN;
    }
}

// 向左按钮槽函数
void GameWidget::leftbtnSlot()
{
    if (direction == RIGHT)
    {
        return;
    }
    else
    {
        direction = LEFT;
    }
}

// 向右按钮槽函数
void GameWidget::rightbtnSlot()
{
    if (direction == LEFT)
    {
        return;
    }
    else
    {
        direction = RIGHT;
    }
}

// 开始按钮槽函数
void GameWidget::startbtnSlot()
{
    timer->start();
}

// 返回按钮槽函数
void GameWidget::returnbtnSlot()
{
    delete this;
}

void GameWidget::reStartGame()
{
    QTime t;
    t = QTime::currentTime();
    qsrand(t.msec() + t.second()*1000);

    snake1[0][0] = qrand() % COL;
    snake1[0][1] = qrand() % ROW;

    foodx = qrand() % COL;
    foody = qrand() % ROW;

    direction = qrand() % 4;

    // 确保 初始时,蛇头的位置和食物的位置不重合
    while ((snake1[0][0] == foodx) && (snake1[0][1] == foody))
    {
        foodx = qrand() % COL;
        foody = qrand() % ROW;
    }

    score = 0;
    level = 1;
    foodcount = 0;

    str1 = QString::number(score);
    scoreshow->setText(str1);

    str2 = QString::number(level);
    levelshow->setText(str2);
}

// 定时器溢出槽函数
void GameWidget::timeoutSlot()
{
    // 判断是否吃到食物
    if( snake1[0][0] == foodx && snake1[0][1] == foody)
    {
        sound->play();
        foodcount++;
        score++;
        str1 = QString::number(score);
        scoreshow->setText(str1);
        // 生成新的食物位置
        QTime t;
        t = QTime::currentTime();
        qsrand(t.msec() + t.second()*1000);
        foodx = qrand() % COL;
        foody = qrand() % ROW;
        // 新食物的位置不能在蛇上
        int i= 0;
        while (i <= foodcount)
        {
            if (foodx == snake1[i][0] && foody == snake1[i][1])
            {
                foodx = qrand() % COL;
                foody = qrand() % ROW;
                i = 0;  // 需要重新判断
            }
            i++;
        }
        // 根据分数调整难度
        switch(score)
        {
        case 1: timer->setInterval(200); level++; break;
        case 2: timer->setInterval(150); level++; break;
        case 3: timer->setInterval(120); level++; break;
        case 4: timer->setInterval(100); level++; break;
        case 5: timer->setInterval(90); level++; break;
        case 6: timer->setInterval(80); level++; break;
        case 7: timer->setInterval(70); level++; break;
        case 8: timer->setInterval(60); level++; break;
        case 9: timer->setInterval(55); level++; break;
        case 10: timer->setInterval(50); level++; break;
        }
        str2 = QString::number(level);
        levelshow->setText(str2);
    }

    // 蛇的游走
    for (int i = foodcount; i > 0; i--)  // 蛇身
    {
        snake1[i][0] = snake1[i-1][0];
        snake1[i][1] = snake1[i-1][1];
    }
    switch (direction)   // 蛇头
    {
    case UP:    snake1[0][1]--; break;
    case DOWN:  snake1[0][1]++; break;
    case LEFT:  snake1[0][0]--; break;
    case RIGHT: snake1[0][0]++; break;
    }

    // 判断是否撞到自身
    for (int i = 1; i <= foodcount; i++)
    {
        if (snake1[0][0] == snake1[i][0] && snake1[0][1] == snake1[i][1])
        {
            sound1->play();
            timer->stop();
            if( (QMessageBox::question(this, "提示", "游戏结束,是否重新开始？", QMessageBox::Yes, QMessageBox::No) ) == QMessageBox::Yes)
            {
                reStartGame();
            }
            // 否则停在该状态
            return;
        }
    }

    // 判断是否撞到墙
    if (snake1[0][0] < 0 || snake1[0][0] >= COL || snake1[0][1] < 0 || snake1[0][1] >= ROW)
    {
        sound1->play();
        timer->stop();
        if( (QMessageBox::question(this, "提示", "游戏结束,是否重新开始？", QMessageBox::Yes, QMessageBox::No) ) == QMessageBox::Yes)
        {
            reStartGame();
        }
        else
        {// 退出游戏界面，返回主界面
            delete this;
            return;
        }
    }

    // 最后：更新界面
    this->update();
}

// 绘图事件
void GameWidget::paintEvent(QPaintEvent *)
{

    //画方格
    QPainter painter(this);

    //方案1   画矩形
//    for(int i=0;i<ROW*20;i+=20)
//        for(int j=0;j<COL*20;j+=20)
//        painter.drawRect(i,j,20,20);

    // 方案2  画横竖线
    for (int i=0; i <= ROW*20; i += 20)  // 画横线
    {
        painter.drawLine(0, i, 20*COL, i);
    }
    for (int i=0; i <= COL*20; i += 20)  // 画竖线
    {
        painter.drawLine(i, 0, i, 20*ROW);
    }



    //画食物
   painter.drawImage(foodx*20,foody*20,QImage(":/new/prefix1/img/apple.png").scaled(QSize(20,20)));


    //画蛇头
    /* 知识点：图片旋转
     * QMatrix matrix;
     * matrix.rotate(180.0);  // 顺时针旋转180度，-90.0则为逆时针旋转90度
     * QImage image = QImage(":/new/prefix1/img/apple.png").scaled(QSize(20,20));
     * QImage image = image.transformed(matrix, Qt::SmoothTransformation);
   */

   // 原始版
/*    switch(direction)
//    {
//    case UP:    //蛇头向上
//        painter.drawImage(snake1[0][0]*20,snake1[0][1]*20,QImage(":/new/prefix1/img/headup.png").scaled(QSize(20,20)));break;
//    case DOWN:  //蛇头向下
//        painter.drawImage(snake1[0][0]*20,snake1[0][1]*20,QImage(":/new/prefix1/img/headdown.png").scaled(QSize(20,20)));break;
//    case LEFT:  //蛇头向左
//        painter.drawImage(snake1[0][0]*20,snake1[0][1]*20,QImage(":/new/prefix1/img/headleft.png").scaled(QSize(20,20)));break;
//    case RIGHT:  //蛇头向右
//        painter.drawImage(snake1[0][0]*20,snake1[0][1]*20,QImage(":/new/prefix1/img/headright.png").scaled(QSize(20,20)));break;
//    }
*/
   QMatrix matrix;
   QImage imageUp = QImage(":/new/prefix1/img/headup.png").scaled(QSize(20,20));
   matrix.rotate(180.0);
   QImage imageDown = imageUp.transformed(matrix,Qt::FastTransformation);
    matrix.rotate(90.0);
    QImage imageLeft = imageUp.transformed(matrix,Qt::FastTransformation);
    matrix.rotate(180.0);
    QImage imageRight = imageUp.transformed(matrix,Qt::FastTransformation);
    switch(direction)
    {
    case UP:    //蛇头向上
        painter.drawImage(snake1[0][0]*20, snake1[0][1]*20, imageUp);break;
    case DOWN:  //蛇头向下
        painter.drawImage(snake1[0][0]*20, snake1[0][1]*20, imageDown);break;
    case LEFT:  //蛇头向左
        painter.drawImage(snake1[0][0]*20, snake1[0][1]*20, imageLeft);break;
    case RIGHT:  //蛇头向右
        painter.drawImage(snake1[0][0]*20, snake1[0][1]*20, imageRight);break;
    }


    //画蛇身
    for(int i=1;i<=foodcount;i++)
    {
        if(i!=foodcount)
        {
        if( (snake1[i][0]==snake1[i-1][0]&&snake1[i][1]==snake1[i-1][1]-1&&
           snake1[i][0]==snake1[i+1][0]-1&&snake1[i][1]==snake1[i+1][1]) ||
           (snake1[i][0]==snake1[i-1][0]-1&&snake1[i][1]==snake1[i-1][1] &&
            snake1[i][0]==snake1[i+1][0]&&snake1[i][1]==snake1[i+1][1]-1))
         painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/tl_corner.png").scaled(QSize(20,20)));

        else if((snake1[i][0]==snake1[i-1][0]-1&&snake1[i][1]==snake1[i-1][1]&&
                 snake1[i][0]==snake1[i+1][0]&&snake1[i][1]==snake1[i+1][1]+1)||
                 (snake1[i][0]==snake1[i-1][0]&&snake1[i][1]==snake1[i-1][1]+1&&
                  snake1[i][0]==snake1[i+1][0]-1&&snake1[i][1]==snake1[i+1][1]))
         painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/bl_corner.png").scaled(QSize(20,20)));

        else if((snake1[i][0]==snake1[i-1][0]+1&&snake1[i][1]==snake1[i-1][1]&&
                 snake1[i][0]==snake1[i+1][0]&&snake1[i][1]==snake1[i+1][1]-1)||
                 (snake1[i][0]==snake1[i-1][0]&&snake1[i][1]==snake1[i-1][1]-1&&
                  snake1[i][0]==snake1[i+1][0]+1&&snake1[i][1]==snake1[i+1][1]))
         painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/tr_corner.png").scaled(QSize(20,20)));

        else if((snake1[i][0]==snake1[i-1][0]&&snake1[i][1]==snake1[i-1][1]+1&&
                 snake1[i][0]==snake1[i+1][0]+1&&snake1[i][1]==snake1[i+1][1])||
                 (snake1[i][0]==snake1[i-1][0]+1&&snake1[i][1]==snake1[i-1][1]&&
                  snake1[i][0]==snake1[i+1][0]&&snake1[i][1]==snake1[i+1][1]+1))
         painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/br_corner.png").scaled(QSize(20,20)));

        else if(snake1[i][1]==snake1[i-1][1]&&snake1[i][0]!=snake1[i-1][0])
       painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/h_body.png").scaled(QSize(20,20)));

        else if(snake1[i][0]==snake1[i-1][0]&&snake1[i][1]!=snake1[i-1][1])
         painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/v_body.png").scaled(QSize(20,20)));
        }
        else
        {
            //画蛇尾
            if(snake1[i][0]==snake1[i-1][0]+1&&snake1[i][1]==snake1[i-1][1])
                painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/tailleft.png").scaled(QSize(20,20)));
            else if(snake1[i][0]==snake1[i-1][0]-1&&snake1[i][1]==snake1[i-1][1])
                painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/tailright.png").scaled(QSize(20,20)));
            else if(snake1[i][0]==snake1[i-1][0]&&snake1[i][1]==snake1[i-1][1]-1)
                painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/taildown.png").scaled(QSize(20,20)));
            else if(snake1[i][0]==snake1[i-1][0]&&snake1[i][1]==snake1[i-1][1]+1)
                painter.drawImage(snake1[i][0]*20,snake1[i][1]*20,QImage(":/new/prefix1/img/tail.png").scaled(QSize(20,20)));
        }
    }
}
void GameWidget::keyPressEvent(QKeyEvent *k)
{
  int key = k->key();
  switch (key)
  {
  case Qt::Key_W:    emit upSignal();    break;
  case Qt::Key_Up:   emit upSignal();    break;

  case Qt::Key_S:    emit downSignal();  break;
  case Qt::Key_Down: emit downSignal();  break;

  case Qt::Key_A:    emit leftSignal();  break;
  case Qt::Key_Left: emit leftSignal();  break;

  case Qt::Key_D:    emit rightSignal(); break;
  case Qt::Key_Right:emit rightSignal(); break;
  }
}










