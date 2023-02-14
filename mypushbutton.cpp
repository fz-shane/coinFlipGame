#include "mypushbutton.h"

//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg ){
    normalImgPath = normalImg;
    pressImgPath = pressImg;
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret){
        qDebug()<<normalImg<<"，图片加载失败！"<<endl;
        return;
    }
    //设置图片大小
    this->setFixedSize(QSize(pix.width(),pix.height()));
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(QIcon(pix));
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
// 这个界面有BUG，点击过快还是会下降，延时越短越不明显
void MyPushButton::zoom1(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");//this 代表给谁做特效，这里就是给MyPushButton做特效
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::zoom2(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");//this 代表给谁做特效，这里就是给MyPushButton做特效
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::mousePressEvent(QMouseEvent* e){
    if(this->pressImgPath!=""){
        QPixmap *pix = new QPixmap;
        bool ret = pix->load(pressImgPath);
        if(!ret){
            qDebug()<<"图片加载失败！"<<endl;
            return ;
        }
        //    设置按钮固定大小
        this->setFixedSize(pix->width(),pix->height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(*pix);
        this->setIconSize(QSize(pix->width(),pix->height()));
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent* e){
    if(this->pressImgPath!=""){
        QPixmap *pix = new QPixmap;
        bool ret = pix->load(normalImgPath);
        if(!ret){
            qDebug()<<"图片加载失败！"<<endl;
            return ;
        }
        //    设置按钮固定大小
        this->setFixedSize(pix->width(),pix->height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(*pix);
        this->setIconSize(QSize(pix->width(),pix->height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}

