#include <stdio.h>
#include <stdbool.h>
#include <QList>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QSharedPointer>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QtDebug>

#include "Player.h"
#include "constants.h"
#include "prop.h"
#include "GameIsOver.h"
Player::Player(int _idx, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    for (int i = 0; i < 4; i++) record[i] = false;
    moveLeft = false;
    moveRight = false;
    moveUp = false;
    moveDown = false;
    xPlayer = x();
    yPlayer = y();
    idx = _idx;
    step = 3;
    Power = 1;
    MaxBomb = 2;
    UsedBomb = 0;
    TimeInterval = 16;
    movementTimer.setInterval(TimeInterval);
    connect(&movementTimer, SIGNAL(timeout()), this, SLOT(updateCharacterPosition()));
    movementTimer.start();
    if (idx == 0)
        setPixmap(QPixmap(":/pictures/bombermanPic/m_down.png"));
    else
        setPixmap(QPixmap(":/pictures/bombermanPic/f_down.png"));
}

void Player :: setGame(Game* game)
{
    this->game = game;
}

void Player :: keyPressEvent(char c)
{
    xPlayer = x();
    yPlayer = y();
    if (c == 'l') {
        moveLeft = true;
        record[0] = moveLeft;
        record[1] = moveRight;
        record[2] = moveUp;
        record[3] = moveDown;
        moveRight = false;
        moveUp = false;
        moveDown = false;
    }
    else if (c == 'r') {
        moveRight = true;
        record[0] = moveLeft;
        record[1] = moveRight;
        record[2] = moveUp;
        record[3] = moveDown;
        moveLeft = false;
        moveUp = false;
        moveDown = false;
    }
    else if (c == 'u') {
        moveUp = true;
        record[0] = moveLeft;
        record[1] = moveRight;
        record[2] = moveUp;
        record[3] = moveDown;
        moveLeft = false;
        moveRight = false;
        moveDown = false;
    }
    else if (c == 'd') {
        moveDown = true;
        record[0] = moveLeft;
        record[1] = moveRight;
        record[2] = moveUp;
        record[3] = moveDown;
        moveLeft = false;
        moveRight = false;
        moveUp = false;
    }
    else if (c == 's') {
        int blockSize = 40;
        int playerSize = 40;
        int x0 = 40;
        int y0 = 160;
        int bomb_x = xPlayer + 23;
        int bomb_y = yPlayer + 55;
        Map* map = this->game->map;
        if (!map->table[(bomb_y - bomb_y % 40 - y0) / blockSize][(bomb_x - bomb_x % 40 - x0) / blockSize]->bomb && UsedBomb < MaxBomb) {
            UsedBomb++;
            map->table[(bomb_y - bomb_y % 40 - y0) / blockSize][(bomb_x - bomb_x % 40 - x0) / blockSize]->bomb = setBomb(bomb_x, bomb_y);
        }
    }
}
Bomb* Player :: setBomb(int xBomb, int yBomb) {
    Bomb* bomb = new Bomb(xBomb, yBomb, Power, this, this->game);
    this->game->scene->addItem(bomb);
    return bomb;
}
void Player :: keyReleaseEvent(char c)
{
        if (c == 'l') {
            moveLeft = false;
            record[0] = false;
            moveRight = record[1];
            moveUp = record[2];
            moveDown = record[3];
        }
        else if (c == 'r') {
            moveRight = false;
            record[1] = false;
            moveLeft = record[0];
            moveUp = record[2];
            moveDown = record[3];
        }
        else if (c == 'u') {
            moveUp = false;
            record[2] = false;
            moveLeft = record[0];
            moveRight = record[1];
            moveDown = record[3];
        }
        else if (c == 'd') {
            moveDown = false;
            record[3] = false;
            moveLeft = record[0];
            moveRight = record[1];
            moveUp = record[2];
        }
}

void  Player :: updateCharacterPosition()
{
    int dx = 0;
    int dy = 0;
    xPlayer = x();
    yPlayer = y();
    int blockSize = 40;
    int playerSize = 40;
    int x0 = 40;
    int y0 = 160;
    int w = 520;
    int h = 320;
    int box_x1 = xPlayer - x0 + 10;
    int box_y1 = yPlayer - y0 + 30;
    int box_x2 = box_x1 + 25;
    int box_y2 = box_y1 + 25;

    Map* map = this->game->map;
    if (map->table[((yPlayer + 55) - (yPlayer + 55) % 40 - 160) / blockSize][((xPlayer + 23) - (xPlayer + 23) % 40 - 40) / blockSize]->item != NULL) {
            MapCell* cell = map->table[((yPlayer + 55) - (yPlayer + 55) % 40 - 160) / blockSize][((xPlayer + 23) - (xPlayer + 23) % 40 - 40) / blockSize];
        if (cell->item->idx == 0) {
            Power++;
            cell->item->Vanish();
            cell->item = NULL;
        }
        else if (cell->item->idx == 1) {
            MaxBomb++;
            cell->item->Vanish();
            cell->item = NULL;
        }
        else if (cell->item->idx == 2) {
            if (TimeInterval > 8)
                TimeInterval -= 1;
            disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(updateCharacterPosition()));
            movementTimer.setInterval(TimeInterval);
            connect(&movementTimer, SIGNAL(timeout()), this, SLOT(updateCharacterPosition()));
            movementTimer.start();
            cell->item->Vanish();
            cell->item = NULL;
        }
    }
    if (moveLeft)
        if (box_x1 - step >= 0 && map->table[box_y1 / blockSize][(box_x1 - step) / blockSize]->type == EMPTY
            && map->table[box_y2 / blockSize][(box_x1 - step) / blockSize]->type == EMPTY
            && (map->table[box_y1 / blockSize][(box_x1 - step) / blockSize]->bomb == NULL
                || map->table[box_y1 / blockSize][(box_x1 - step) / blockSize]->bomb->isObstacle[idx] == false)
            && (map->table[box_y2 / blockSize][(box_x1 - step) / blockSize]->bomb == NULL
                || map->table[box_y2 / blockSize][(box_x1 - step) / blockSize]->bomb->isObstacle[idx] == false)) {
            dx -= step;
        }
    if (moveRight)
        if (box_x2 + step < w && map->table[box_y1 / blockSize][(box_x2 + step) / blockSize]->type == EMPTY
            && map->table[box_y2 / blockSize][(box_x2 + step) / blockSize]->type == EMPTY
            && (map->table[box_y1 / blockSize][(box_x2 + step) / blockSize]->bomb == NULL
                || map->table[box_y1 / blockSize][(box_x2 + step) / blockSize]->bomb->isObstacle[idx] == false)
            && (map->table[box_y2 / blockSize][(box_x2 + step) / blockSize]->bomb == NULL
                || map->table[box_y2 / blockSize][(box_x2 + step) / blockSize]->bomb->isObstacle[idx] == false)) {
            dx += step;
        }

    if (moveUp)
        if (box_y1 - step >= 0 && map->table[(box_y1 - step) / blockSize][box_x1 / blockSize]->type == EMPTY
            && map->table[(box_y1 - step) / blockSize][box_x2 / blockSize]->type == EMPTY
            && (map->table[(box_y1 - step) / blockSize][box_x1 / blockSize]->bomb == NULL
                || map->table[(box_y1 - step) / blockSize][box_x1 / blockSize]->bomb->isObstacle[idx] == false)
            && (map->table[(box_y1 - step) / blockSize][box_x2 / blockSize]->bomb == NULL
                || map->table[(box_y1 - step) / blockSize][box_x2 / blockSize]->bomb->isObstacle[idx] == false)) {
            dy -= step;
        }

    if (moveDown)
        if (box_y2 + step < h && map->table[(box_y2 + step) / blockSize][box_x1 / blockSize]->type == EMPTY
            && map->table[(box_y2 + step) / blockSize][box_x2 / blockSize]->type == EMPTY
            && (map->table[(box_y2 + step) / blockSize][box_x1 / blockSize]->bomb == NULL
                || map->table[(box_y2 + step) / blockSize][box_x1 / blockSize]->bomb->isObstacle[idx] == false)
            && (map->table[(box_y2 + step) / blockSize][box_x2 / blockSize]->bomb == NULL
                || map->table[(box_y2 + step) / blockSize][box_x2 / blockSize]->bomb->isObstacle[idx] == false)) {
            dy += step;
        }

    if (dx > 0) {
        if (idx == 0)
            setPixmap(QPixmap(":/pictures/bombermanPic/m_right.png"));
        else
            setPixmap(QPixmap(":/pictures/bombermanPic/f_right.png"));
    }
    if (dx < 0) {
        if (idx == 0)
            setPixmap(QPixmap(":/pictures/bombermanPic/m_left.png"));
        else
            setPixmap(QPixmap(":/pictures/bombermanPic/f_left.png"));
    }
    if (dy > 0) {
        if (idx == 0)
            setPixmap(QPixmap(":/pictures/bombermanPic/m_down.png"));
        else
            setPixmap(QPixmap(":/pictures/bombermanPic/f_down.png"));
    }
    if (dy < 0) {
        if (idx == 0)
            setPixmap(QPixmap(":/pictures/bombermanPic/m_up.png"));
        else
            setPixmap(QPixmap(":/pictures/bombermanPic/f_up.png"));
    }
    // Update character position
    xPlayer += dx;
    yPlayer += dy;

    // Move the character
    setPos(xPlayer,yPlayer);
}


void Player :: die() {
    disconnect(&movementTimer, SIGNAL(timeout()), this, SLOT(updateCharacterPosition()));
    MaxBomb = 0;
    if (idx == 0)
        setPixmap(QPixmap(":/pictures/bombermanPic/cloth10101_cry_0_0.png"));
    else
        setPixmap(QPixmap(":/pictures/bombermanPic/cloth10301_cry_0_0.png"));
    if (this->game->endGame == 0) {
        this->game->endGame = 1;
        this->game->gameIsOver();
    }
}

//void Player :: keyPressEvent(QKeyEvent *event)
//{
//    xPlayer = x();
//    yPlayer = y();
//    int blockSize = 100;
//    int playerSize = 40;
//    int step = 10;
//    int x0 = 40;
//    int y0 = 160;
//    int w = 520;
//    int h = 320;

//    Map* map = this->game->map;

//    if (event->key() == Qt::Key_A)
//    {
//        if(xPlayer + 20 - step >= x0 &&
//           (map->table[(yPlayer + playerSize) / blockSize][(xPlayer - step) / blockSize]->type) == EMPTY
//           && (map->table[(yPlayer) / blockSize][(xPlayer - step) / blockSize]->type) == EMPTY)
//        {
//            setPos(xPlayer-step,yPlayer);
//        }
//    }
//    else if (event->key() == Qt::Key_D)
//    {

//        if(xPlayer + playerSize + step <= x0 + w &&
//           (((map->table[(yPlayer + playerSize) / blockSize][(xPlayer + step + playerSize) / blockSize]->type) == EMPTY
//           &&(map->table[(yPlayer) / blockSize][(xPlayer + step + playerSize) / blockSize])->type == EMPTY)  ||
//             ((map->table[(yPlayer + playerSize) / blockSize][(xPlayer + step+ playerSize) / blockSize]->type) == EXIT
//            && (map->table[(yPlayer) / blockSize][(xPlayer+ step + playerSize) / blockSize])->type == EXIT)))
//        {
//            setPos(xPlayer+step,yPlayer);
//        }


//    }
//    else if (event->key() == Qt::Key_W)
//    {
//        if(yPlayer + 40 - step >= y0 &&
//           (map->table[(yPlayer - step) / blockSize][(xPlayer + playerSize) / blockSize]->type) == EMPTY
//           &&(map->table[(yPlayer - step) / blockSize][(xPlayer) / blockSize]->type) == EMPTY)
//        {
//            setPos(xPlayer,yPlayer-step);
//        }
//    }
//    else if (event->key() == Qt::Key_S)
//    {

//        if(yPlayer + 20 + playerSize + step <= y0 + h &&
//           (map->table[(yPlayer + step + playerSize) / blockSize][(xPlayer + playerSize) / blockSize]->type == EMPTY)
//           && (map->table[(yPlayer + step + playerSize) / blockSize][(xPlayer) / blockSize])->type == EMPTY)
//        {
//            setPos(xPlayer,yPlayer+step);
//           /* if((map->table[(yPlayer + playerSize) / blockSize][(xPlayer + playerSize) / blockSize]->type == EMPTY)
//               && (map->table[(yPlayer + playerSize) / blockSize][(xPlayer) / blockSize])->type == EMPTY)
//            {
//                game->goToTheNextLevel();
//            }*/
//        }
//    }
//    else if(event->key() == Qt::Key_Space)
//    {
//        this->game->setBomb(xPlayer + 23, yPlayer + 55);
//    }

//}

//сделать по границам клетки пермещение и коллизию так же
