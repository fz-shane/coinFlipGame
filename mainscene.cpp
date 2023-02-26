#include "mainscene.h"
#include "ui_mainscene.h"
#pragma execution_character_set("utf-8")

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景
    //设置固定大小
    setFixedSize(480,882);
    //设置图标
    //    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowIcon(QIcon("://game_res/res/Coin0001.png"));//2种前缀的写法都可以
    //设置标题
    setWindowTitle("翻金币主场景");
    chooseScene = new ChooseLevelScene();
    connect(ui->actionquit,&QAction::triggered,this,[=](){
        this->close();
    });
    //添加开始按钮音效
    QSound *startSound = new QSound("://game_res/res/TapButtonSound.wav");

    //开始按钮
    MyPushButton *startBtn = new MyPushButton("://game_res/res/MenuSceneStartButton.png");
    //    MyPushButton *startBtn = new MyPushButton(":/game_res/res/MenuSceneStartButton.png");//game_res前面只加一个“/”可以？
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    //监听选择关卡的返回按钮信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        chooseScene->hide();
        this->setGeometry(chooseScene->geometry());
        this->show();
    });
    connect(startBtn,&MyPushButton::clicked,this,[=](){
        //        qDebug("点击开始");
        startSound->play();
        startBtn->zoom1();
        startBtn->zoom2();

        QTimer::singleShot(400,this,[=](){//不确定这个QTIMER::singleShot是不是去其他线程执行了, 如果是, 那sleep替代显然不好, 他阻塞了进程
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });

    });
}
void MainScene::paintEvent(QPaintEvent*)//重写paintEvent的函数，QT运行时会自动调用这个事件
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("://game_res/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画上背景图标
    pix.load("://game_res/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
MainScene::~MainScene()
{
    delete ui;
}

