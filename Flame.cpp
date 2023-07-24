#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Flame.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPointer>
#include <QList>
#include <QGraphicsItem>
#include <stdbool.h>
#include <prop.h>

Flame::Flame(int x, int y, Game* game, QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent)
{
    this->game = game;
    setPixmap(QPixmap(":/pictures/bombermanPic/flame1_stand_0_0.png"));
    setPos(x, y);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Vanish()));
    timer->start(500);
    if (game->player1->xPlayer + 23 >= x && game->player1->xPlayer + 23 < x + 40 && game->player1->yPlayer + 55 >= y && game->player1->yPlayer + 55 < y + 40)
        game->player1->die();
    if (game->player2->xPlayer + 23 >= x && game->player2->xPlayer + 23 < x + 40 && game->player2->yPlayer + 55 >= y && game->player2->yPlayer + 55 < y + 40)
        game->player2->die();
    if (game->map->table[(y - 160) / 40][(x - 40) / 40]->item != NULL) {
        game->map->table[(y - 160) / 40][(x - 40) / 40]->item->Vanish();
        game->map->table[(y - 160) / 40][(x - 40) / 40]->item = NULL;
    }
}
void Flame::Vanish() {
    QPointer<QGraphicsScene> scene = game->scene;
    scene->removeItem(this);
    delete timer;
    return;
}
