#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPaintEvent>

#include "Map.h"

//Ebomb = 3,
//Eplayer = 4,
//Eenemies = 5

class Block : public QObject, public QGraphicsRectItem
{

public:

    int xBlock;
    int yBlock;
//    cellType blockType;
    Block(QGraphicsItem * parent=0);
    virtual void setBlock(int x, int y, QGraphicsItem *parent = 0)
    {
        xBlock = x;
        yBlock = y;
//        blockType = type;
    }


    void removeBlock(Block& removableItem);

    friend class Bomb;

};

#endif
//int xBlock, int yBlock, QGraphicsItem *parent): QGraphicsRectItem(parent)

