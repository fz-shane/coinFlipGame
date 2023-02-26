#ifndef MAINSCENE_H
#define MAINSCENE_H
#include<QPainter>
#include <QMainWindow>
#include"mypushbutton.h"
#include"chooselevelscene.h"
#include<QTimer>
#include<QSound>
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
    ChooseLevelScene *levelScene ;//养成良好习惯，new完马上置空或者赋值，不同编译器不同处理方式，不是所有编译器都会帮你置空的
    // ChooseLevelScene *chooseScene = nullptr; //使用nullptr确实没问题
    // 这里不管是令 ChooseLevelScene *levelScene = NULL还是 = nullptr 都会报错，error C2065: “chooseScene”: 未声明的标识符
    //注：不可以在定义类的同时对其数据成员进行初始化，因为类不是一个实体，不合法但是能编译运行

    ChooseLevelScene *chooseScene;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
