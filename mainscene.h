#ifndef MAINSCENE_H
#define MAINSCENE_H
#include<QPainter>
#include <QMainWindow>
#include"mypushbutton.h"
#include"chooselevelscene.h"
#include<QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void paintEvent(QPaintEvent*);
//    ChooseLevelScene *levelScene = NULL;//养成良好习惯，new完马上置空或者赋值，不同编译器不同处理方式，不是所有编译器都会帮你置空的
    ChooseLevelScene *chooseScene = nullptr; //使用nullptr确实没问题

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
