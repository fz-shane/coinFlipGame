#include "playscene.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelNum)
{
    qDebug()<<"进入第"<<levelNum<<"关"<<endl;
    levelIndex = levelNum;
    //设置游戏场景
    setWindowIcon(QIcon("://game_res/res/Coin0001.png"));
    setFixedSize(480,882);
    setWindowTitle(QString::fromUtf16(u"翻金币场景"));

    //创建菜单栏
    QMenuBar *startBar = new QMenuBar(this);
    setMenuBar(startBar);
    QMenu *startMenu = startBar->addMenu(QString::fromUtf16(u"开始"));
    QAction *quitAct = startMenu->addAction(QString::fromUtf16(u"退出"));
    connect(quitAct,&QAction::triggered,this,[=]()
    {
        this->close();
    });

    //添加点击金币/翻转金币/返回按钮/胜利音效
    QSound *clickSound = new QSound("://game_res/res/TapButtonSound.wav");
    QSound *flipSound = new QSound("://game_res/res/ConFlipSound.wav");
    QSound *backSound = new QSound("://game_res/res/BackButtonSound.wav");
    QSound *winSound = new QSound("://game_res/res/LevelWinSound.wav");
    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/game_res/res/BackButton.png",":/game_res/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,this,[=](){
        qDebug()<<"点击返回了返回按钮"<<endl;
        backSound->play();
        QTimer::singleShot(400,this,[=]()
        {
            emit this->chooseSceneBack();
        });
    });

    //显示关卡数标签
    QFont font;
    //    font.setFamily("华文新魏");//直接写“华文新魏”的话，中文不识别，所以setfont()不起作用
    font.setFamily(QString::fromUtf16(u"华文新魏"));
    font.setPointSize(18);
    QLabel *label = new QLabel(this);
    label->setFont(font);
    label->setText(QString("level:%1").arg(levelNum));
    label->setGeometry(30,this->height()-60,170,60);

    //设置胜利图片
    QPixmap pix;
    pix.load("://game_res/res/LevelCompletedDialogBg.png");
    QLabel *winLabel = new QLabel;
    winLabel->setParent(this);
    winLabel->setPixmap(pix);
    winLabel->setFixedSize(pix.width(),pix.height());
    winLabel->setGeometry((this->width()-winLabel->width())*0.5,-winLabel->height(),pix.width(),pix.height());


    //显示金币
    dataConfig config;
    QString coinPath;
    for(int i = 0;i<4;i++)
    {
        for(int j = 0;j<4;j++)
        {
            //绘制背景图片
            QPixmap pix = QPixmap("://game_res/res/BoardNode.png");
            QLabel *label = new QLabel(this);
            //            label->setFixedSize(pix.width(),pix.height());
            label->setPixmap(pix);
            label->setGeometry(140+j*50,380+i*50,pix.width(),pix.height());
            //dataconfig 的二维数组的xy下标
            //            {
            //               (0,0)，(0,1)，(0,2)，(0,3)
            //               (1,0)，(1,1)，(1,2)，(1,3)
            //               (2,0)，(2,1)，(2,2)，(2,3)
            //               (3,0)，(3,1)，(3,2)，(3,3)
            //            }
            //gameArray 中的xy坐标(数学上的xy坐标)
            //            {
            //               (0,0)，(1,0)，(2,0)，(3,0)
            //               (0,1)，(1,1)，(2,1)，(3,1)
            //               (0,2)，(1,2)，(2,2)，(3,2)
            //               (0,3)，(1,3)，(2,3)，(3,3)
            //            }
            //2各坐标系统不一样，xy对换一下就是对的
            //            label->setGeometry(0,0,pix.width(),pix.height());
            //            qDebug()<<"BoardNode  label->x() : "<<label->x()<<"   "<<"label->y() : "<<label->y()<<endl;

            gameArray[i][j] =config.mData[levelNum][j][i];
            if(gameArray[i][j])//金币
            {
                coinPath = "://game_res/res/Coin0001.png";
            }else
            {
                coinPath = "://game_res/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(coinPath);
            coin->setParent(this);
            //            coin->move(j*50-170,i*50+170);
            coin->move(140+j*50,380+i*50);
            //            coin->move(210,0);
            //            qDebug()<<"coin coin->x()-25 : "<<coin->x()-25<<"   "<<"coin->y()-25 : "<<coin->y()-25<<endl;
            //给金币属性赋值
            //            coin->posx = i;
            //            coin->posy = j;
            coin->posx = j;
            coin->posy = i;
            coin->flag = this->gameArray[i][j];
            //把金币放到二维数组中，以便后期维护
            coinBtn[j][i] = coin;
            //监听金币翻转信号
            connect(coin,&MyCoin::clicked,[=]()
            {
                clickSound->play();
                //点击金币的时候，禁用其他金币
                for(int i = 0;i<4;i++)
                {
                    for(int j = 0;j<4;j++)
                    {
                        coinBtn[i][j]->isWin = true;
                    }
                }
                coin->changeFlag();
                this->gameArray[i][j] = !(this->gameArray[i][j]);
                //翻转周围金币
                QTimer::singleShot(400,this,[=]()
                {
                    //左边
                    flipSound->play();
                    if(coin->posx-1>=0)
                    {
                        coinBtn[coin->posx-1][coin->posy]->changeFlag();
                    }
                    //右边
                    if(coin->posx+1<=3)
                    {
                        coinBtn[coin->posx+1][coin->posy]->changeFlag();
                    }
                    //上边
                    if(coin->posy-1>=0)
                    {
                        coinBtn[coin->posx][coin->posy-1]->changeFlag();
                    }
                    //下边
                    if(coin->posy+1<=3)
                    {
                        coinBtn[coin->posx][coin->posy+1]->changeFlag();
                    }

                    //周围金币翻完后，不再禁用其他金币
                    for(int i = 0;i<4;i++)
                    {
                        for(int j = 0;j<4;j++)
                        {
                            coinBtn[i][j]->isWin = false;
                        }
                    }
                    //goto 可以退出 2 层循环
                    isWin = true;
                    for(int i = 0;i<4;i++)
                    {
                        for(int j = 0;j<4;j++)
                        {
                            if(!(coinBtn[i][j]->flag))
                            {
                                isWin = false;
                                break;
                            }
                        }
                    }
                    if(isWin)
                    {
                        winSound->play();
                        qDebug()<<"succeed!"<<endl;
                        //将所有金币的标志标志位改为胜利，再次点击金币，直接返回，不翻转
                        for(int i = 0;i<4;i++)
                        {
                            for(int j = 0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                        //弹出胜利图片
                        QPropertyAnimation *winAnimation = new QPropertyAnimation(winLabel,"geometry");
                        winAnimation->setDuration(1000);
                        winAnimation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        winAnimation->setEndValue(QRect(winLabel->x(),250+winLabel->y(),winLabel->width(),winLabel->height()));
                        winAnimation->setEasingCurve(QEasingCurve::OutBounce);
                        winAnimation->start();
                    }
                });
            });

            //            qDebug()<<"this->width : "<<this->width()<<"   "<<"this->height : "<<this->height()<<endl;

        }
    }

}
void PlayScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPixmap pix;
    pix.load("://game_res/res/PlayLevelSceneBg.png");
    //    setGeometry(0,0,pix.width(),pix.height());
    //    qDebug()<<"PlayLevelSceneBg  pix.width() : "<<pix.width()<<"   "<<"pix.height() : "<<pix.height()<<endl;
    //    qDebug()<<"PlayLevelSceneBg  this->width() : "<<this->width()<<"   "<<"this->height() : "<<this->height()<<endl;
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题图片
    pix.load("://game_res/res/Title.png");
    painter.drawPixmap(10,30,pix);
    //    qDebug()<<"Title  pix.width() : "<<pix.width()<<"   "<<"pix.height() : "<<pix.height()<<endl;



}
