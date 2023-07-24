#ifndef PROP_H
#define PROP_H

#include <stdio.h>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointer>

#include "Map.h"

class Prop: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int xProp_idx;
    int yProp_idx;
    int idx;
    QPointer<Game> game;
    Prop(int y_idx, int x_idx, int idx, Game* game, QGraphicsItem* parent = 0);
    void Vanish();
};

#endif // PROP_H
