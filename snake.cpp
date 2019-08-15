#include "snake.h"
#include "gamecontroller.h"
#include "constants.h"
#include <QPainter>
Snake::Snake(GameController &controller) :
    head(0, 0),
    forwarding(3),
    speed(3),
    dirction(NoMove),
    controller(controller)
{

}

QRectF Snake::boundingRect() const
{
    qreal maxX = head.x();
    qreal minX = head.x();
    qreal maxY = head.y();
    qreal minY = head.y();

    foreach (QPointF item, tail)
    {
        maxX = item.x() > maxX ? item.x() : maxX;
        minX = item.x() < minX ? item.x() : minX;
        maxY = item.y() > maxY ? item.y() : maxY;
        minY = item.y() < minY ? item.y() : minY;
    }
    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));

    return QRectF(tl.x(), tl.y(),
                 br.x()-tl.x()+SNAKE_SIZE,
                 br.y()-tl.y()+SNAKE_SIZE);
}

QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QPointF tmp = mapFromScene(head);
    path.addRect(tmp.x(), tmp.y(), SNAKE_SIZE, SNAKE_SIZE);

    foreach (QPointF item, tail)
    {
        tmp = mapFromScene(item);
        path.addRect(tmp.x(), tmp.y(), SNAKE_SIZE, SNAKE_SIZE);
    }

    return path;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillPath(shape(), QBrush(Qt::yellow));
    painter->restore();
}

void Snake::setDirction(Dirction dirction)
{
    if ((dirction == MoveUp && this->dirction == MoveDown) ||
        (dirction == MoveDown && this->dirction == MoveUp) ||
        (dirction == MoveLeft && this->dirction == MoveRight) ||
        (dirction == MoveRight && this->dirction == MoveLeft))
        return;

    this->dirction = dirction;
}

void Snake::advance(int step)
{
    if (0 == step)  return;
    //Simulate the movement delay time of snake,
    //the greater the speed, the slower the movement
    if (tickCounter++ % speed != 0)   return;
    if (dirction == NoMove) return;
    if (forwarding > 0) //When the snake body grows
    {
        forwarding--;
        QPointF growingPoint = head;
        tail << growingPoint;
    }
    else                //When the snake body does not grow
    {
        tail.takeFirst();
        tail << head;
    }

    switch (dirction)
    {
        case MoveUp:
            moveUp();
            break;
        case MoveDown:
            moveDown();
            break;
        case MoveLeft:
            moveLeft();
            break;
        case MoveRight:
            moveRight();
            break;
        default:
            break;
    }
    setPos(head);
    handleCollisions();
}

void Snake::moveUp()
{
    head.ry() -= SNAKE_SIZE;
    if (head.y() < TOP_WALL)
        head.ry() = BOTTOM_WALL;
}

void Snake::moveDown()
{
    head.ry() += SNAKE_SIZE;
    if (head.y() > BOTTOM_WALL)
        head.ry() = TOP_WALL;
}

void Snake::moveLeft()
{
    head.rx() -= SNAKE_SIZE;
    if (head.x() < LEFT_WALL)
        head.rx() = RIGHT_WALL;
}

void Snake::moveRight()
{
    head.rx() += SNAKE_SIZE;
    if (head.x() > RIGHT_WALL)
        head.rx() = LEFT_WALL;
}

void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();

    foreach (QGraphicsItem *item, collisions)
    {
        if (item->data(GD_Type) == GO_Food)
        {
            controller.snakeAteFood(this, (Food *)item);
            forwarding += 1;
        }
        else if(item->data(GD_Type) == GO_Wall)
        {
            controller.snakeHitWall(this, (Wall *)item);
        }
    }

    if (tail.contains(head))
        controller.snakeAteItself(this);
}

Snake::~Snake()
{

}
