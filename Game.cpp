
#include <QGraphicsTextItem>
#include <QBrush>
#include <QImage>
#include <QGraphicsRectItem>
#include <iostream>
#include "Game.h"
#include <cstdlib>
#include <ctime>
//#include <QMediaPlayer>
//#include <QAudioOutput>


void Game::gameIsOver() {
    GameIsOver * gameOver = new GameIsOver();
    gameOver->setPos(50, 250);
    scene->addItem(gameOver);
    //std::exit(0);
    timerOver = new QTimer(this);
    connect(timerOver,SIGNAL(timeout()),this,SLOT(reStart()));
    timerOver->start(3000);
}



Game::Game(int level, QWidget* parent) : level(1)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 600, 520);
    setScene(scene);
    endGame = 0;
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600, 520);

    setBackgroundBrush(QBrush(QImage(":/pictures/bombermanPic/bg.png")));

    map = new Map(level, scene);

    //health = new Health();
    //health->setPos(health->x() + 400, health->y() + 25);
    //scene->addItem(health);

    player1 = new Player(0);
    player1->setPos(275, 200);
    //player1->setFlag(QGraphicsItem::ItemIsFocusable);
    //player1->setFocus();

    scene->addItem(player1);

    player2 = new Player(1);
    player2->setPos(275, 350);
    //player2->setFlag(QGraphicsItem::ItemIsFocusable);
    //player2->setFocus();

    scene->addItem(player2);

    /*
    QMediaPlayer * player=new QMediaPlayer();
    QAudioOutput * audioOutput = new QAudioOutput();
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/sound_effects/sound_effects/bgm.mp3"));
    player->setLoops(-1);
    audioOutput->setVolume(0.45);
    player->play();
    */

    show();

}

void Game::reStart() {
    timerOver->stop();
    delete player1;
    delete player2;
    delete map;
    delete scene;
    endGame = 0;
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 600, 520);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600, 520);

    setBackgroundBrush(QBrush(QImage(":/pictures/bombermanPic/bg.png")));

    map = new Map(level, scene);


    player1 = new Player(0);
    player1->setPos(275, 200);

    scene->addItem(player1);

    player2 = new Player(1);
    player2->setPos(275, 350);

    scene->addItem(player2);

    show();
    setUpGameLinks();
}

void Game::setUpGameLinks()
{
    map->setGame(this);
    player1->setGame(this);
    player2->setGame(this);
   // enemyUpDown->setGame(this);
   // enemyLeftRight->setGame(this);

}

void Game :: keyPressEvent(QKeyEvent *event) {
    setFocus();
    if (event->key() == Qt::Key_A)
        player1->keyPressEvent('l');
    else if (event->key() == Qt::Key_D)
        player1->keyPressEvent('r');
    else if (event->key() == Qt::Key_W)
        player1->keyPressEvent('u');
    else if (event->key() == Qt::Key_S)
        player1->keyPressEvent('d');
    else if (event->key() == Qt::Key_Space)
        player1->keyPressEvent('s');
    else if (event->key() == Qt::Key_Left)
        player2->keyPressEvent('l');
    else if (event->key() == Qt::Key_Right)
        player2->keyPressEvent('r');
    else if (event->key() == Qt::Key_Up)
        player2->keyPressEvent('u');
    else if (event->key() == Qt::Key_Down)
        player2->keyPressEvent('d');
    else if (event->key() == Qt::Key_L)
        player2->keyPressEvent('s');
}

void Game :: keyReleaseEvent(QKeyEvent *event) {
    setFocus();
    if (event->key() == Qt::Key_A)
        player1->keyReleaseEvent('l');
    else if (event->key() == Qt::Key_D)
        player1->keyReleaseEvent('r');
    else if (event->key() == Qt::Key_W)
        player1->keyReleaseEvent('u');
    else if (event->key() == Qt::Key_S)
        player1->keyReleaseEvent('d');
    else if (event->key() == Qt::Key_Left)
        player2->keyReleaseEvent('l');
    else if (event->key() == Qt::Key_Right)
        player2->keyReleaseEvent('r');
    else if (event->key() == Qt::Key_Up)
        player2->keyReleaseEvent('u');
    else if (event->key() == Qt::Key_Down)
        player2->keyReleaseEvent('d');
}

//void Game ::goToTheNextLevel()
//{
//    level++;
////    connect(this, SIGNAL(this->level > 2),this,SLOT(gameIsOver()));
//    if (level > 2)
//    {
//        endGame = new GameIsWin();
//        endGame->setPos(endGame->x() + 180, endGame->y() + 240);
//        scene->addItem(endGame);
//        timer = new QTimer(this);
//        connect(timer,SIGNAL(timeout()),this,SLOT(gameIsOver()));
//        timer->start(3000);

//        return;
//    }

//    clearFocus();

//    delete scene;

//    scene = new QGraphicsScene();
//    scene->setSceneRect(0, 0, 800, 600);
//    setScene(scene);
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setFixedSize(800, 600);

//    setBackgroundBrush(QBrush(QImage(":/pictures/bombermanPic/groundLevel2.png")));
////    if (!enemyLeftRight.isNull())
////    {
////        scene->removeItem(enemyLeftRight);
////        delete enemyLeftRight;
////    }
////    if (!enemyUpDown.isNull())
////    {
////        scene->removeItem(enemyUpDown);
////        delete enemyUpDown;
////    }


////    enemyUpDown = new EnemyMoveUpDown(UP_DOWN, 410, 110);
////    enemyLeftRight = new EnemyMoveLeftRight(LEFT_TO_RIGHT, 100, 400);

////    scene->addItem(enemyLeftRight);
////    scene->addItem(enemyUpDown);

//    scene->removeItem(map);
//    delete map;
//    map = new Map(level, scene);
//    scene->addItem(map);

//    scene->removeItem(health);
//    delete health;
//    health = new Health();
//    health->setPos(health->x() + 600, health->y() + 25);
//    scene->addItem(health);

//    delete player;
//    player = new Player();

//    player->setPos(0, 0);
//    player->setFlag(QGraphicsItem::ItemIsFocusable);
//    player->setFocus();

//    scene->addItem(player);

//    this->setUpGameLinks();
//    show();
//}
