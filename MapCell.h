#ifndef BOMBERMANQT_MAPCELL_H
#define BOMBERMANQT_MAPCELL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

#include "constants.h"
class Bomb;
class Prop;
class MapCell: public QObject, public QGraphicsPixmapItem
{
public:
    CellType type;
    int iIndex;
    int jIndex;
    Bomb* bomb = NULL;
    Prop* item = NULL;
    MapCell(CellType cellType);
//    MapCell& operator=(const MapCell* right)
//    {
//        type = right->type;
//        iIndex = right->iIndex;
//        jIndex = right->jIndex;
//        return *this;
//    }
    MapCell();
    void removeItem();
};


#endif
