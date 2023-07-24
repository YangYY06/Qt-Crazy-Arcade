
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QBrush>

#include "Background.h"


Background::Background(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{

    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
//    setPixmap(QPixmap(":/pictures/bombermanPic/ground.png"));
}
