//
// Created by gaydi on 23.12.2021.
//

#include "GameIsWin.h"
#include <QFont>
GameIsWin::GameIsWin(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    setPlainText(QString("You win!"));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",60));
}

