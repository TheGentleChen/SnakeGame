#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include "constants.h"
#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>


GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject (parent),
    scene(scene),
    snake(new Snake(*this))
{
    timer.start(1000/33);

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
    scene.clear();
    snake = new Snake(*this);
    scene.addItem(snake);
    addNewFood();
}

void GameController::snakeAteFood(Snake *snake, Food *food)
{
    scene.removeItem(food);
    delete food;
    addNewFood();
}

void GameController::snakeHitWall(Snake *snake, Wall *wall)
{}

void GameController::snakeAteItself(Snake *snake)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::addNewFood()
{
    int x, y;
    do
    {
        x = (int)(qrand() % 10) * 10;
        y = (int)(qrand() % 10) * 10;
    } while(snake->shape().contains(snake->mapFromScene(QPointF(x + TILE_SIZE/2, y + TILE_SIZE/2))));
    Food *food = new Food(x, y);
    scene.addItem(food);
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

GameController::~GameController()
{}
