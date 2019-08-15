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
        minX = item.x() < maxX ? item.x() : minX;
        maxY = item.y() > maxY ? item.y() : maxY;
        minY = item.y() < maxY ? item.y() : minY;
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
    this->dirction = dirction;
}

void Snake::advance(int step)
{
    if (0 == step)  return;
    //模拟snake的移动延迟时间，speed越大，移动越慢
    if (tickCounter++ % speed != 0)   return;
    if (dirction == NoMove) return;
    if (forwarding > 0) //蛇体有增长时
    {
        forwarding--;
        QPointF growingPoint = head;
        tail << growingPoint;
    }
    else                //蛇体无增长时
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
    if (head.x() < TOP_WALL)
        head.rx() = BOTTOM_WALL;
}

void Snake::moveDown()
{
    head.ry() += SNAKE_SIZE;
    if (head.y() > BOTTOM_WALL)
        head.rx() = TOP_WALL;
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
        else if (item->data(GD_Type) == GO_Wall)
        {
            controller.snakeHitWall(this, (Wall *)item);
        }
        else
        {
            controller.snakeAteItself(this);
        }
    }

    //if (tail.contains(head))
    //    controller.snakeAteItself(this);
}

Snake::~Snake()
{

}
