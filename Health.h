#ifndef BOMBERMANQT_HEALTH_H
#define BOMBERMANQT_HEALTH_H


#include <QGraphicsTextItem>
#include "GameIsOver.h"
#include <QTimer>
#include <iostream>
class Health: public QGraphicsTextItem
{
    Q_OBJECT
public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    int getHealth();
private:
    int health;
public slots:
    void gameIsOver();
};

#endif
