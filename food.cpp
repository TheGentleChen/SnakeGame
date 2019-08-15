#include "food.h"
#include "constants.h"
#include <QPainter>

Food::Food(qreal x, qreal y)
{
    setPos(x, y);
    setData(GD_Type, GO_Food);
}

QRectF Food::boundingRect() const
{
    return QRectF(-TILE_SIZE, -TILE_SIZE,
                  TILE_SIZE*2, TILE_SIZE*2);
}

QPainterPath Food::shape() const
{
    QPainterPath path;
    path.addEllipse(TILE_SIZE/2, TILE_SIZE/2,
                    FOOD_RADIUS, FOOD_RADIUS);
    return path;
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    //反锯齿
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), QBrush(Qt::red));
    painter->restore();
}
