#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "Game.h"
Game* bomberman;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/pictures/bombermanPic/Cover1.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);

    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    //
    n++;
    if (n == 1) {
        QPixmap bkgnd(":/pictures/bombermanPic/Cover2.png");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
    if (n == 2) {
        this->close();
        bomberman = new Game(1);
        bomberman->setUpGameLinks();
    }


    //bomberman->show();

}


//void MainWindow::on_pushButton_clicked()
//{
//    bombermanLevel2 = new Game(2);
//    bombermanLevel2->show();
//}



