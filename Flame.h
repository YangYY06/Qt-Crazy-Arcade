#ifndef FLAME_H
#define FLAME_H

#include <stdio.h>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointer>

#include "Map.h"

class Flame: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int xFlame;
    int yFlame;
    QTimer* timer;
public slots:
    void Vanish();
public:
    QPointer<Game> game;
    Flame(int x, int y, Game* game, QGraphicsItem* parent = 0);
};

#endif // FLAME_H
