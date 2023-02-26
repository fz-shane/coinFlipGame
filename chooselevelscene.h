﻿#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include<QPainter>
#include <QMainWindow>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QSound>
#include"playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    PlayScene *pScene;
signals:
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
