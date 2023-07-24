#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QList>
#include <QPointer>
#include <stdbool.h>
#include "Game.h"

class Player : public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
    int xPlayer;
    int yPlayer;
    int idx;
    int Power;
    int MaxBomb;
    int alive = 1;
    int UsedBomb;
    int playerSize;
    int TimeInterval;
    QPointer<Game> game;
    QTimer movementTimer;
    bool record[4];
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
    int step;
    Player(int idx, QGraphicsItem * parent=0);
    void keyPressEvent(char c);
    void keyReleaseEvent(char c);
    void setGame(Game* game);
    void die();
private slots:
    void updateCharacterPosition();
    //void spawnEnemy();
    Bomb* setBomb(int xBomb, int yBomb);
};

#endif
