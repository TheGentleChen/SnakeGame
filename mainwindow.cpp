#include "mainwindow.h"
#include "gamecontroller.h"
#include <QGraphicsView>
#include <QTimer>
#include <QAction>
#include <QToolBar>

#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      controller(new GameController(*scene, this))
{
    setCentralWidget(view);
    resize(600, 664);
    setFixedSize(this->width(), this->height());

    initToolBar();
    initSence();
    initSenceBackground();

    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
}

void MainWindow::initToolBar()
{
    QAction *actionResume = new QAction(QIcon(":/toolbar/resume"), tr("&Resume"), this);
    actionResume->setShortcut(tr("CTRL+R"));
    actionResume->setStatusTip(tr("Resume game"));
    connect(actionResume, &QAction::triggered, this, &MainWindow::resume);
    toolBarResume = addToolBar(tr("&Resume"));
    toolBarResume->addAction(actionResume);

    QAction *actionPause = new QAction(QIcon(":/toolbar/pause"), tr("&Pause"), this);
    actionPause->setShortcut(tr("CTRL+P"));
    actionPause->setStatusTip(tr("Pause game"));
    connect(actionPause, &QAction::triggered, this, &MainWindow::pause);
    toolBarPause = addToolBar(tr("&Pause"));
    toolBarPause->addAction(actionPause);

    toolBarPause->setEnabled(true);
    toolBarResume->setEnabled(false);
    statusBar();
}

void MainWindow::initSence()
{
    scene->setSceneRect(LEFT_WALL, TOP_WALL, SCENE_SIZE, SCENE_SIZE);
}

void MainWindow::initSenceBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}

void MainWindow::resume()
{
    controller->resume();
    toolBarPause->setEnabled(true);
    toolBarResume->setEnabled(false);
}

void MainWindow::pause()
{
    controller->pause();
    toolBarPause->setEnabled(false);
    toolBarResume->setEnabled(true);
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

MainWindow::~MainWindow()
{

}
