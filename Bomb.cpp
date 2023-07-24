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

Bomb::Bomb(int x, int y, int _Power, Player* _p, Game* game, QGraphicsItem* parent): QObject(), QGraphicsPixmapItem(parent)
{
    this->game = game;
    int bombSize = 40;
    Power = _Power;
    player = _p;
    active = true;
    setPixmap(QPixmap(":/pictures/bombermanPic/bomb1_stand_0_0.png"));
    setPos(x - x % 40, y - y % 40);
    xBomb = x - x % 40;
    yBomb = y - y % 40;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(destroyItem()));
    timer->start(3000);
    timerStage = new QTimer(this);
    connect(timerStage,SIGNAL(timeout()),this,SLOT(reshape()));
    timerStage->start(500);
    isObstacle[0] = false;
    isObstacle[1] = false;
    timerObstacle[0] = new QTimer(this);
    timerObstacle[1] = new QTimer(this);
    connect(timerObstacle[0],SIGNAL(timeout()),this,SLOT(updateObstacle1()));
    timerObstacle[0]->start(8);
    connect(timerObstacle[1],SIGNAL(timeout()),this,SLOT(updateObstacle2()));
    timerObstacle[1]->start(8);
}
void Bomb::updateObstacle1() {
    int box_x1 = this->game->player1->xPlayer + 10;
    int box_y1 = this->game->player1->yPlayer + 30;
    int box_x2 = box_x1 + 25;
    int box_y2 = box_y1 + 25;
    if (box_x1 > xBomb + 40 || box_x2 < xBomb || box_y1 > yBomb + 40 || box_y2 < yBomb) {
        isObstacle[0] = true;
        timerObstacle[0]->stop();
    }
}
void Bomb::updateObstacle2() {
    int box_x1 = this->game->player2->xPlayer + 10;
    int box_y1 = this->game->player2->yPlayer + 30;
    int box_x2 = box_x1 + 25;
    int box_y2 = box_y1 + 25;
    if (box_x1 > xBomb + 40 || box_x2 < xBomb || box_y1 > yBomb + 40 || box_y2 < yBomb) {
        isObstacle[1] = true;
        timerObstacle[1]->stop();
    }
}
void Bomb::reshape() {
    stage = (stage + 1) % 4;
    if (stage == 0)
        setPixmap(QPixmap(":/pictures/bombermanPic/bomb1_stand_0_0.png"));
    if (stage == 1)
        setPixmap(QPixmap(":/pictures/bombermanPic/bomb1_stand_0_1.png"));
    if (stage == 2)
        setPixmap(QPixmap(":/pictures/bombermanPic/bomb1_stand_0_2.png"));
    if (stage == 3)
        setPixmap(QPixmap(":/pictures/bombermanPic/bomb1_stand_0_3.png"));
}
void Bomb::destroy() {
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(destroyItem()));
    timer->start(0);
}
void Bomb::setFlame(int x, int y) {
    Flame* flame = new Flame(x, y, this->game);
    this->game->scene->addItem(flame);
}
void Bomb :: destroyItem() {
    if (!active) {
        return;
    }
    active = false;
    int blockSize = 40;
    int bombSize = 40;
    int x0 = 40;
    int y0 = 160;
    int w = 520;
    int h = 320;
    QPointer<Map> map = this->game->map;
    QPointer<Player> player = this->player;
    QPointer<QGraphicsScene> scene = game->scene;

//    for (int i = 1; i <= Power; i++) {
//        if ((xBomb - x0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->type == EMPTY) {
//            setFlame(xBomb - i * blockSize, yBomb);
//            if (map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->bomb)
//                map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->bomb->destroy();
//        }
//        if ((yBomb - y0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == EMPTY) {
//            setFlame(xBomb, yBomb - i * blockSize);
//            if (map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb)
//                map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb->destroy();
//        }
//        if ((xBomb - x0 + i * blockSize) / blockSize <= 12 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->type == EMPTY) {
//            setFlame(xBomb + i * blockSize, yBomb);
//            if (map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->bomb)
//                map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->bomb->destroy();
//        }
//        if ((yBomb - y0 + i * blockSize) / blockSize <= 7 && map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == EMPTY) {
//            setFlame(xBomb, yBomb + i * blockSize);
//            if (map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb)
//                map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb->destroy();
//        }

//    }

//for destroy block and set flame
    setFlame(xBomb, yBomb);
    bool a[4] = {0};
    for (int i = 1; i <= Power; i++) {
        if (!a[0] && (xBomb - x0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->type == EMPTY) {
            setFlame(xBomb - i * blockSize, yBomb);
            if (map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->bomb)
                map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->bomb->destroy();
        }
        if (!a[0] && (xBomb - x0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->type == DESTRUCTIBLE_BLOCK) {
            setFlame(xBomb - i * blockSize, yBomb);
            //map->table[(yBomb - y0)/ blockSize][(xBomb - x0 - i * blockSize) / blockSize]->removeItem();
            map->setEmptyTriger((yBomb - y0) / blockSize, (xBomb - x0 - i * blockSize) / blockSize);
            a[0] = true;
        }
        if (!a[1] && (yBomb - y0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == EMPTY) {
            setFlame(xBomb, yBomb - i * blockSize);
            if (map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb)
                map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb->destroy();
        }
        if (!a[1] && (yBomb - y0 - i * blockSize) / blockSize >= 0 && map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == DESTRUCTIBLE_BLOCK) {
            setFlame(xBomb, yBomb - i * blockSize);
            //map->table[(yBomb - y0 - i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->removeItem();
            map->setEmptyTriger((yBomb - y0 - i * blockSize) / blockSize, (xBomb - x0) / blockSize);
            a[1] = true;
        }
        if (!a[2] && (xBomb - x0 + i * blockSize) / blockSize <= 12 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->type == EMPTY) {
            setFlame(xBomb + i * blockSize, yBomb);
            if (map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->bomb)
                map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->bomb->destroy();
        }
        if (!a[2] && (xBomb - x0 + i * blockSize) / blockSize <= 12 && map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->type == DESTRUCTIBLE_BLOCK) {
            setFlame(xBomb + i * blockSize, yBomb);
            //map->table[(yBomb - y0)/ blockSize][(xBomb - x0 + i * blockSize) / blockSize]->removeItem();
            map->setEmptyTriger((yBomb - y0) / blockSize, (xBomb - x0 + i * blockSize) / blockSize);
            a[2] = true;
        }
        if (!a[3] && (yBomb - y0 + i * blockSize) / blockSize <= 7 && map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == EMPTY) {
            setFlame(xBomb, yBomb + i * blockSize);
            if (map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb)
                map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->bomb->destroy();
        }
        if (!a[3] && (yBomb - y0 + i * blockSize) / blockSize <= 7 && map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->type == DESTRUCTIBLE_BLOCK) {
            setFlame(xBomb, yBomb + i * blockSize);
            //map->table[(yBomb - y0 + i * blockSize)/ blockSize][(xBomb - x0) / blockSize]->removeItem();
            map->setEmptyTriger((yBomb - y0 + i * blockSize) / blockSize, (xBomb - x0) / blockSize);
            a[3] = true;
        }
    }

    scene->removeItem(this);
    this->game->map->table[(yBomb - y0)/ blockSize][(xBomb - x0) / blockSize]->bomb = NULL;
    this->player->UsedBomb--;
    delete timer;
}

/*
(map->table[(player->yPlayer)/blockSize][(player->xPlayer + player->playerSize)/blockSize] ==
map->table[yBomb/blockSize][xBomb/blockSize]) ||
(map->table[(player->yPlayer+ player->playerSize)/blockSize][(player->xPlayer + player->playerSize)/blockSize] ==
map->table[(yBomb+bombSize)/blockSize][xBomb/blockSize])||
((map->table[(player->yPlayer + player->playerSize)/blockSize][(player->xPlayer + player->playerSize)/blockSize] ==
map->table[yBomb/blockSize][(xBomb + bombSize)/blockSize] ||
(map->table[(player->yPlayer + player->playerSize)/blockSize][(player->xPlayer)/blockSize] ==
map->table[yBomb/blockSize][xBomb/blockSize]) ||
(map->table[(player->yPlayer)/blockSize][(player->xPlayer)/blockSize] ==
map->table[yBomb/blockSize][(xBomb + bombSize)/blockSize]) ||
(map->table[(player->yPlayer + player->playerSize)/blockSize][(player->xPlayer)/blockSize] ==
map->table[(yBomb + bombSize)/blockSize][(xBomb + bombSize)/blockSize]) ||
(map->table[(player->yPlayer)/blockSize][(player->xPlayer)/blockSize] ==
map->table[(yBomb + bombSize)/blockSize][(xBomb)/blockSize]) ||
(map->table[(player->yPlayer)/blockSize][(player->xPlayer + player->playerSize)/blockSize] ==
map->table[(yBomb + bombSize)/blockSize][(xBomb + bombSize)/blockSize]))))*/
