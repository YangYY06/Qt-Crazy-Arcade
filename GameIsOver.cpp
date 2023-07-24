//
// Created by gaydi on 23.12.2021.
//

#include "GameIsOver.h"
#include <QFont>
GameIsOver::GameIsOver(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    setPlainText(QString("Game is over!"));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",60));
}
