//
// Created by gaydi on 05.12.2021.
//

#ifndef BOMBERMANQT_EMPTYBLOCK_H
#define BOMBERMANQT_EMPTYBLOCK_H
#include "MapCell.h"

class EmptyBlock : public MapCell
{
public:

    EmptyBlock(CellType type): MapCell(type)
    {

    }
};


#endif