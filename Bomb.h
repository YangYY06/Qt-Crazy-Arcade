#ifndef BOMB_H
#define BOMB_H

#include <stdio.h>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointer>
#include <vector>
#include "Flame.h"
#include "Map.h"
class Player;
class Bomb: public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
private:
    int xBomb;
    int yBomb;
    int stage = 0;
    int Power;
    bool active;
    Player* player;
    QTimer* timer;
    QTimer* timerStage;
    QTimer* timerObstacle[2];
public slots:
    void destroyItem();
    void reshape();
    void updateObstacle1();
    void updateObstacle2();
public:
    QPointer<Game> game;
    Bomb(int x, int y, int _Power, Player * _p, Game* game, QGraphicsItem* parent = 0);
    void setFlame(int x, int y);
    void destroy();
    bool isObstacle[2];
};

#endif
