#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include "wall.h"
#include "constants.h"
#include "mainwindow.h"
#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>


GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject (parent),
    scene(scene),
    snake(new Snake(*this))
{
    this->parent = (MainWindow *)parent;
    timer.start(1000/30);

    scene.addItem(snake);
    addNewFood();
    scene.installEventFilter(this);

    resume();
}

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
}

void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
}

void GameController::gameOver()
{
    pause();
    if (QMessageBox::Yes == QMessageBox::question(this->parent, tr("Continue or Quit"), tr("Game Over!\nRestart the game?"),
                                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
        resume();
        scene.clear();
        snake = new Snake(*this);
        scene.addItem(snake);
        addNewFood();
    }
    else
    {
        this->parent->close();
    }
}

void GameController::snakeAteFood(Snake *snake, Food *food)
{
    scene.removeItem(food);
    delete food;
    addNewFood();
}

void GameController::snakeHitWall(Snake *snake, Wall *wall)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::snakeAteItself(Snake *snake)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::addNewFood()
{
    int fx, fy;
    findTowRandom(fx, fy);
    Food *food = new Food(fx, fy);
    scene.addItem(food);

    //Remove comment to open difficult mode
    /*int wx, wy;
    findTowRandom(wx, wy);
    while (wx == fx && wy == fy)
        findTowRandom(wx, wy);
    Wall *wall = new Wall(wx, wy);
    scene.addItem(wall);*/
}

void GameController::handleKeyPress(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Up:
            snake->setDirction(Snake::MoveUp);
            break;
        case Qt::Key_Down:
            snake->setDirction(Snake::MoveDown);
            break;
        case Qt::Key_Left:
            snake->setDirction(Snake::MoveLeft);
            break;
        case Qt::Key_Right:
            snake->setDirction(Snake::MoveRight);
            break;
        default:
            break;
    }
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        handleKeyPress((QKeyEvent *)event);
        return true;
    }
    return QObject::eventFilter(object, event);
}

void GameController::findTowRandom(int &x, int &y)
{
    do
    {
        x = (int)(qrand() % 10) * 10;
        y = (int)(qrand() % 10) * 10;
    } while(snake->shape().contains(snake->mapFromScene(QPointF(x + TILE_SIZE/2, y + TILE_SIZE/2))));
}

GameController::~GameController()
{}
