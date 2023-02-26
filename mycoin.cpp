#include "mycoin.h"

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}
MyCoin::MyCoin(QString imgPath)
{
    QPixmap pix;
    min = 1;
    max = 8;
    isWin = false;
    isAnimation = false;
    bool ret = pix.load(imgPath);
    if(!ret)
    {
        qDebug()<<imgPath<<",image load error!"<<endl;
    }
    //设置金币属性
    //    this->setFixedSize(this->width(),this->height());//这里的长宽一定不能设置为 this->width(),this->height() 这样坐标会混乱
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面金币翻转信号，同时翻转金币
    connect(timer1,&QTimer::timeout,this,[=](){
        //    connect(timer1,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str = QString("://game_res/res/Coin000%1.png").arg(min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //        this->move(posx+320,posy+235);
        if(min>max)
        {
            min = 1;
            isAnimation = false;
            timer1->stop();

        }
    }
    );

    //监听反面金币翻转信号，同时翻转金币
    connect(timer2,&QTimer::timeout,this,[=](){
        //    connect(timer1,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str = QString("://game_res/res/Coin000%1.png").arg(max--);
        qDebug()<<"str = "<<str<<endl;
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //        this->move(posx+320,posy+235);
        if(min>max)
        {
            qDebug()<<"flip end"<<endl;
            max = 8;
             isAnimation = false;
            timer2->stop();

        }
    }
    );
}
void MyCoin::changeFlag()
{
    if(flag)
    {
        //        timer1->start(30);
        timer1->start(30);
        isAnimation = true;
        flag = false;
    }else
    {
        timer2->start(30);
        isAnimation = true;
        flag = true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(isAnimation||isWin)
    {
        return;
    }else
    {
        QPushButton::mousePressEvent(e);
    }
}
