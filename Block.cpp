#include "Block.h"


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPainterPath>

Block::Block(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
{

}

void Block :: removeBlock(Block &removableItem)
{
    scene()->removeItem(this);
}
