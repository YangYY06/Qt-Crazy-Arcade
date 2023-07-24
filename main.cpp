#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "mainwindow.h"

#include "Game.h"

//Game* bomberman;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
//    bomberman = new Game();
//    bomberman->setUpGameLinks();
//    bomberman->show();
    return a.exec();
}
