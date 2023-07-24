#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QGraphicsObject>
#include <QGraphicsItem>

#include "DestructibleBlock.h"
#include "EmptyBlock.h"

class Game;
//add value exit

class Map : public QObject, public QGraphicsPixmapItem
{
Q_OBJECT


public:
    Game* game;
    MapCell *table[8][13];
    int LEVEL;
    Map(int level, QGraphicsScene* scene, QGraphicsItem* parent = 0);
    void outputField(QGraphicsScene* scene);
    void setGame(Game* game);
    Map();
    void setEmptyTriger(int i, int j);
public slots:
    void setEmptyCell(int i, int j);
};

#endif
