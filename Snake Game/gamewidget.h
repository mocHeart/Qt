#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#define ROW 13
#define COL 16
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#include <QWidget>
#include <QSound>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

    // 按钮自定义槽函数
    void upbtnSlot();
    void downbtnSlot();
    void leftbtnSlot();
    void rightbtnSlot();
    void startbtnSlot();
    void returnbtnSlot();

    void timeoutSlot();

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);

signals:
    void upSignal();
    void downSignal();
    void leftSignal();
    void rightSignal();

public slots:

private:
    QSound *sound;
    QSound *sound1;

    QPushButton *upbtn;
    QPushButton *downbtn;
    QPushButton *leftbtn;
    QPushButton *rightbtn;
    QPushButton *startbtn;
    QPushButton *returnbtn;

    int score;
    int level;

    QLabel *scorelabel;
    QLabel *levellabel;

    QLabel *scoreshow;
    QLabel *levelshow;

    QString str1;
    QString str2;

    int direction;

    int snake1[100][2];
    int snake2[100][2];

    int foodx;
    int foody;
    int foodcount;

    QTimer *timer;

    void reStartGame();

};

#endif // GAMEWIDGET_H
