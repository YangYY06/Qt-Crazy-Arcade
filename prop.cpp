#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Prop.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPointer>
#include <QList>
#include <QGraphicsItem>
#include <stdbool.h>


Prop::Prop(int y_idx, int x_idx, int idx, Game* game, QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent)
{
    this->idx = idx;
    this->game = game;
    if (idx == 0)
        setPixmap(QPixmap(":/pictures/bombermanPic/power.png"));
    if (idx == 1)
        setPixmap(QPixmap(":/pictures/bombermanPic/num.png"));
    if (idx == 2)
        setPixmap(QPixmap(":/pictures/bombermanPic/shoe.png"));;
    setPos(x_idx * 40 + 40, y_idx * 40 + 160);
    game->scene->addItem(this);
}
void Prop::Vanish() {
    QPointer<QGraphicsScene> scene = game->scene;
    scene->removeItem(this);
    return;
}
