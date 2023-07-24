#ifndef DESTRUCTIBLEBLOCK_H
#define DESTRUCTIBLEBLOCK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPaintEvent>

#include "MapCell.h"

//#include "Block.h"
//
class Game;
class DestructibleBlock:  virtual public MapCell
{
private:
    int idx_x;
    int idx_y;
public:
    Game * game;
    DestructibleBlock(int x, int y, CellType type, int n, Game* game);
    void removeBlock(DestructibleBlock& block);
    friend class Bomb;
};

#endif
