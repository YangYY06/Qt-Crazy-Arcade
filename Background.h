#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>


class Background: public QObject, public QGraphicsPixmapItem
{
public:
    Background(QGraphicsItem* parent = 0);
};

#endif