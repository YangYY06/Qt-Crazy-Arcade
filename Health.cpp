#include <QFont>

#include "Health.h"
#include <QGraphicsScene>

void Health::gameIsOver() {
    std::exit(0);
}

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    health = 3;

    // draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::decrease(){
    health--;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 2
    if (health == 0)
    {
        GameIsOver* end = new GameIsOver();
        end->setPos(end->x() + 180, end->y() + 240);
        scene()->addItem(end);
        QTimer* timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(gameIsOver()));
        timer->start(3000);
    }
}

int Health::getHealth(){
    return health;
}
