#ifndef SNAKE_H
#define SNAKE_H
#include <QGraphicsItem>
#include <QRectF>

class GameController;

class Snake : public QGraphicsItem
{
public:
    enum Dirction
    {
        NoMove,
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight
    };
    Snake(GameController &controller);
    ~Snake();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void setDirction(Dirction dirction);
protected:
    void advance(int step);
private:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void handleCollisions();

    QPointF head;
    int forwarding;
    int speed;
    QList<QPointF> tail;
    int tickCounter;
    Dirction dirction;
    GameController &controller;
};

#endif // SNAKE_H
