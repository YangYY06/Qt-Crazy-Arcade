#ifndef INDESTRUCTIBLE_H
#define INDESTRUCTIBLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

#include "MapCell.h"

//public QGraphicsPixmapItem
class IndestructibleBlock: virtual public MapCell
{
Q_OBJECT
public:
    IndestructibleBlock(int x, int y, CellType type, QGraphicsItem* parent = nullptr) :
        MapCell(type)
    {
        setPixmap(QPixmap(":/pictures/bombermanPic/doesntBroke.png"));
    }
};

#endif
