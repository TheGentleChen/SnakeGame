#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsView;
class QGraphicsScene;
class GameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void adjustViewSize();


private:
    void initToolBar();
    void initSence();
    void initSenceBackground();
    void resume();
    void pause();
    QToolBar *toolBarPause;
    QToolBar *toolBarResume;
    QGraphicsScene *scene;
    QGraphicsView *view;
    GameController *controller;
};

#endif // MAINWINDOW_H
