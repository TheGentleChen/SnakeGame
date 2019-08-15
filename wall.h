#ifndef WALL_H
#define WALL_H
#include <QGraphicsItem>

class Wall : public QGraphicsItem
{
public:
    Wall(qreal x, qreal y);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif // WALL_H
