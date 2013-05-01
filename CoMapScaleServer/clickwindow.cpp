#include "clickwindow.h"
#include "ui_clickwindow.h"
#include <QImage>
#include <QTimer>
#include <QPixmap>
#include <QEventLoop>

#define SLEEP_FOR 200

ClickWindow::ClickWindow(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ClickWindow)
{
    ui->setupUi(this);



    QImage globButImage;
    globButImage.load(":/Icons/globalButton");

    ui->globBut->setPixmap(QPixmap::fromImage(globButImage));
    ui->globBut->show();

    QImage wedgeButImage;
    wedgeButImage.load(":/Icons/peerBlue");

    ui->wedgeBut->setPixmap(QPixmap::fromImage(wedgeButImage));
    ui->wedgeBut->show();

    QImage scaleButImage;
    scaleButImage.load(":/Icons/scaleButton");

    ui->scaleBut->setPixmap(QPixmap::fromImage(scaleButImage));
    ui->scaleBut->show();



}

ClickWindow::~ClickWindow()
{
    delete ui;
}

void ClickWindow::showGlobBut(){
    ui->globBut->hide();
    sleepFor(SLEEP_FOR);
    ui->globBut->show();

    ui->globButCount->setValue((ui->globButCount->value()+ 1));
}

void ClickWindow::showWedgeBut(){
    ui->wedgeBut->hide();
    sleepFor(SLEEP_FOR);
    ui->wedgeBut->show();

    ui->wedgePresCount->setValue((ui->wedgePresCount->value()+1));
}

void ClickWindow::showScaleBut(){
    ui->scaleBut->hide();
    sleepFor(SLEEP_FOR);
    ui->scaleBut->show();

    ui->scaleButCount->setValue((ui->scaleButCount->value()+1));
}


void ClickWindow::sleepFor(int timeToWait){
        //sleeping for x msecs
        QTimer timer;
        timer.start(timeToWait);
        QEventLoop loop;
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        loop.exec();
}
