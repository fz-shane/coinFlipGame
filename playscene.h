#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QDebug>
#include<QMenuBar>
#include<QPaintEvent>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    int levelIndex;
    void paintEvent(QPaintEvent *e);
    int gameArray[4][4];
    MyCoin *coinBtn[4][4];
    //判断胜利的标志
    bool isWin;
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
