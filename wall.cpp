#include "wall.h"
#include "constants.h"
#include <QPainter>

Wall::Wall(qreal x, qreal y)
{
    setPos(x, y);
    setData(GD_Type, GO_Wall);
}

QRectF Wall::boundingRect() const
{
    return QRectF(0, 0,
                  TILE_SIZE, TILE_SIZE);
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.addRect(0, TILE_SIZE/4.0, TILE_SIZE, TILE_SIZE/2);
    return path;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    //反锯齿
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), QBrush(Qt::blue));
    painter->restore();
}
