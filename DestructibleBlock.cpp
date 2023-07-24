#include "DestructibleBlock.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPainterPath>
#include "prop.h"
//DestructibleBlock::DestructibleBlock(qreal x, qreal y, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
//{
//    setPixmap(QPixmap(":/pictures/bombermanPic/broken.png"));
//    setPos(x, y);
//}


//DestructibleBlock ::
//    DestructibleBlock(int x, int y, CellType type, QGraphicsItem *parent): MapCell(type)
//{
//
//}
//DestructibleBlock :: DestructibleBlock(QGraphicsItem *parent): QGraphicsRectItem(parent)
//{
//
//}
DestructibleBlock :: DestructibleBlock(int x, int y, CellType type, int n, Game * game) : MapCell(type)
{
    this->game = game;
    idx_x = x;
    idx_y = y;
    if (n == 0) setPixmap(QPixmap(":/pictures/bombermanPic/elem2_stand_0_0.png"));
    else if (n == 1) setPixmap(QPixmap(":/pictures/bombermanPic/elem3_stand_0_0.png"));
}
void DestructibleBlock :: removeBlock(DestructibleBlock &block)
{
    scene()->removeItem(this);
}


