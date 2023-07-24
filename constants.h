#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdbool.h>

enum CellType
{
    EMPTY = 0,
    DESTRUCTIBLE_BLOCK_A = 1,
    DESTRUCTIBLE_BLOCK_B = 2,
    INDESTRUCTIBLE_BLOCK = 3,
    BOMB = 4,
    DESTRUCTIBLE_BLOCK = 5,
};

const int initializationsTable[8][13] =
        {
                { 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2},
                { 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2},
                { 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2},
                { 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2},
                { 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2},
                { 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2},
                { 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2},
                { 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2},
        };



#endif
