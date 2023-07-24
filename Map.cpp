

#include "IndestructibleBlock.h"
#include <iostream>
#include <stdlib.h>
#include <QGraphicsScene>

#include "Map.h"
#include "prop.h"
Map :: Map(int level, QGraphicsScene* scene, QGraphicsItem* parent): QGraphicsPixmapItem(parent)
{
    LEVEL = level;
    outputField(scene);
}


Map :: Map() {}

void Map::setGame(Game* game)
{

    this->game = game;
}

void Map::outputField(QGraphicsScene *scene)
{
    int x0 = 40;
    int y0 = 160;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 13; j++) {
            if (initializationsTable[i][j] == DESTRUCTIBLE_BLOCK_A) {
                DestructibleBlock *destroyedBlock = new DestructibleBlock(j, i, DESTRUCTIBLE_BLOCK, 0, game);
                destroyedBlock->setPos(j * 40 + x0, i * 40 + y0);
                scene->addItem(destroyedBlock);
                table[i][j] = destroyedBlock;
            }
            else if (initializationsTable[i][j] == DESTRUCTIBLE_BLOCK_B) {
                DestructibleBlock *destroyedBlock = new DestructibleBlock(j, i, DESTRUCTIBLE_BLOCK, 1, game);
                destroyedBlock->setPos(j * 40 + x0, i * 40 + y0);
                scene->addItem(destroyedBlock);
                table[i][j] = destroyedBlock;
            }
            else {
                EmptyBlock *emptyBlock = new EmptyBlock(EMPTY);
                table[i][j] = emptyBlock;
            }
        }
    }
//    if (LEVEL == 1) {
//        for (int i = 0; i < 6; i++) {
//            for (int j = 0; j < 8; j++) {
//                if (initializationsTable[i][j] == DESTRUCTIBLE_BLOCK) {
//                    DestructibleBlock *destroyedBlock = new DestructibleBlock(j, i, DESTRUCTIBLE_BLOCK);
//                    destroyedBlock->setPos(j * 100, i * 100);
//                    scene->addItem(destroyedBlock);
//                    table[i][j] = destroyedBlock;
//                } else if (initializationsTable[i][j] == INDESTRUCTIBLE_BLOCK) {
//                    IndestructibleBlock *indestrictableBlock = new IndestructibleBlock(j, i, INDESTRUCTIBLE_BLOCK);
//                    indestrictableBlock->setPos(j * 100, i * 100);
//                    scene->addItem(indestrictableBlock);
//                    table[i][j] = indestrictableBlock;
//                } /*else if (initializationsTable[i][j] == EXIT) {
//                    ExitBlock *exit = new ExitBlock(EXIT);
//                    table[i][j] = exit;
//                    exit->setPos(j * 100, i * 100);
//                    scene->addItem(exit);
//                } */else {
//                    EmptyBlock *emptyBlock = new EmptyBlock(EMPTY);
//                    table[i][j] = emptyBlock;

//                }
//            }
//        }
//    } else if (LEVEL == 2)
//    {
//        for (int i = 0; i < 6; i++) {
//            for (int j = 0; j < 8; j++) {
//                if (initializationsTableLevel2[i][j] == DESTRUCTIBLE_BLOCK) {
//                    DestructibleBlock *destroyedBlock = new DestructibleBlock(j, i, DESTRUCTIBLE_BLOCK);
//                    destroyedBlock->setPos(j * 100, i * 100);
//                    scene->addItem(destroyedBlock);
//                    table[i][j] = destroyedBlock;
//                } else if (initializationsTableLevel2[i][j] == INDESTRUCTIBLE_BLOCK) {
//                    IndestructibleBlock *indestrictableBlock = new IndestructibleBlock(j, i, INDESTRUCTIBLE_BLOCK);
//                    indestrictableBlock->setPos(j * 100, i * 100);
//                    scene->addItem(indestrictableBlock);
//                    table[i][j] = indestrictableBlock;
//                } else if (initializationsTableLevel2[i][j] == EXIT) {
//                    ExitBlock *exit = new ExitBlock(EXIT);
//                    exit->setPos(j * 100, i * 100);
//                    table[i][j] = exit;
//                    scene->addItem(exit);
//                } else {
//                    EmptyBlock *emptyBlock = new EmptyBlock(EMPTY);
//                    table[i][j] = emptyBlock;
//                }
//            }
//        }
//    }
//    EnemyMoveUpDown* enemyUpDown = new EnemyMoveUpDown(UP_DOWN);
//        scene->addItem(enemyUpDown);
}
void Map::setEmptyTriger(int i, int j)
{
    QTimer * t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [this, i, j]() {
        setEmptyCell(i, j);
    });
    t->start(5);
}
void Map::setEmptyCell(int i, int j)
{
    if (this->table[i][j]->type != EMPTY) {
        this->table[i][j]->type = EMPTY;
        this->table[i][j]->removeItem();
        int random_number = std::rand() % 100 + 1;
        if (random_number <= 5) {
            Prop* item = new Prop(i, j, 0, this->game);
            this->table[i][j]->item = item;
        }
        else if (random_number <= 13) {
            Prop* item = new Prop(i, j, 1, this->game);
            this->table[i][j]->item = item;
        }
        else if (random_number <= 18) {
            Prop* item = new Prop(i, j, 2, this->game);
            this->table[i][j]->item = item;
        }
    }
}



//void Map :: setCellValue(int i, int j, int value)
//{
//    initializationsTable[i][j] = value;
//}



//void Map :: outputCTable()
//{
//    system("cls");
//    for (int i = 0; i < 9; i++)
//        {
//            for (int j = 0; j < 9; j++)
//            {
//                if (initializationsTable[i][j] == INDESTRUCTIBLE_BLOCK)
//                {
//                    std::cout << "#";
//                }else if(initializationsTable[i][j] == DESTRUCTIBLE_BLOCK)
//                {
//                    std::cout << "0";
//                }else if(initializationsTable[i][j] == EMPTY)
//                {
//                    std::cout << ' ';
//                }else if(initializationsTable[i][j] == Eplayer)
//                {
//                    std::cout << '4';
//                }else if(initializationsTable[i][j] == Eenemies)
//                {
//                    std::cout << '5';
//                }
//            }
//         std::cout << "\n";
//        }
//}


//для доступа к блокам надо их куда-то записывать
//создать переменную класса map которая будет хранить созданные объекты
