#include <QGraphicsScene>
#include <QTimer>
#include "MapCell.h"

MapCell::MapCell(CellType cellType)
{
    type = cellType;
}
void MapCell::removeItem()
{
    scene()->removeItem(this);
}
MapCell::MapCell(){}
