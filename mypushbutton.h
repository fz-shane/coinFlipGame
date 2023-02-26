#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QString>
//#include <QWidget>
#include<QPushButton>
#include<QPropertyAnimation>
#include<QDebug>

//class MyPushButton : public QWidget
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //    explicit QPushButton(QWidget *parent = nullptr);// explicit 防止隐式类型转换来构造初始化
    //参数1：正常显示的图片的路径 参数2：按下后显示的图片的路径
    //    声明带默认参数，实现不带，否则报no matching function for call to
    MyPushButton(QString normalImg,QString pressImg = "" );// 可传可不传，《开始(start)》按钮图片不会变，一直是同一张图片，不需要传值；《返回(back)》按钮按下后图片会变，需要传值

    void zoom1();
    void zoom2();
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    QString normalImgPath;
    QString pressImgPath;
signals:

};

#endif // MYPUSHBUTTON_H
