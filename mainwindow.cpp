#include "mainwindow.h"
#include "gamecontroller.h"
#include <QGraphicsView>
#include <QTimer>

#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      controller(new GameController(*scene, this))
{
    setCentralWidget(view);
    resize(600, 600);

    initSence();
    initSenceBackground();

    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
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

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

MainWindow::~MainWindow()
{

}
