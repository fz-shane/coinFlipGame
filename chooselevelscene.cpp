#include "chooselevelscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(480,882);
    setWindowIcon(QIcon(":/game_res/res/Coin0001.png"));

    //    painter->drawPixmap();
    setWindowTitle("选择关卡场景");
    //开始菜单栏
    QMenuBar *startBar = new QMenuBar(this);
    setMenuBar(startBar);

    //退出菜单项
    QMenu *startM = startBar->addMenu("开始");
    //   startM->setTitle("开始");
    QAction *quitAction = startM->addAction("退出");
    //   quitAction->setText("退出");
    //   startM->addAction(quitAction);
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/game_res/res/BackButton.png",":/game_res/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击返回了返回按钮"<<endl;
        QTimer::singleShot(400,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //这里把label的父亲设置成menuBtn就不需要移动了
    //label的parent是menuBtn就可以获得穿透的点击事件了
    //关卡号 label 会把 “关卡按钮” 的点击事件屏蔽，点击事件不能穿透 label 让“关卡按钮接收”
    for(int i = 0;i<20;i++){
        MyPushButton *menuBtn = new MyPushButton(":/game_res/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(70+i%5*70,250+i/5*130);
        //监听每个关卡按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            qDebug()<<"点击第"<<i+1<<"关"<<endl;
        });

//        QLabel *menuLabel = new QLabel(menuBtn);
         QLabel *menuLabel = new QLabel(this);
//         QLabel *menuLabel = new QLabel;
//         menuLabel->setParent(menuBtn);
        menuLabel->setFixedSize(menuBtn->width(),menuBtn->height());
        menuLabel->setText(QString::number(i+1));
        menuLabel->move(70+i%5*70,250+i/5*130);
//       menuLabel->setAlignment(::WA_TransparentForMouseEvents);
        menuLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        menuLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    }
}
void ChooseLevelScene::paintEvent(QPaintEvent*){
    QPixmap pix;
    pix.load(":/game_res/res/OtherSceneBg.png");
    QPainter *painter = new QPainter(this);
    painter->drawPixmap(0,0,this->width(),this->height(),pix);
    //画上背景图标
    pix.load(":/game_res/res/Title.png");
    painter->drawPixmap(this->width()*0.5-pix.width()*0.5,50,pix.width(),pix.height(),pix);

}
