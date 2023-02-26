#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString imgPath);
    //金币的属性
    int posx;
    int posy;
    bool flag;
    //金币的方法
    void changeFlag();
//    QTimer *timer1;
//    QTimer *timer2;
    QTimer *timer1;
    QTimer *timer2;
//    int min;
//    int max;
    int min = 1;
    int max = 8;
    bool isWin;

    //是否正做翻转动画
    bool isAnimation;
    //重写按下和释放事件
    void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // MUCOIN_H
