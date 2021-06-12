#include "sleep.h"
#include "ui_sleep.h"
#include "common.h"

Sleep::Sleep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sleep)
{
    ui->setupUi(this);
    QPixmap pixmap;
    pixmap.load(":/pic/sleepPic");
    QTransform tran;
    tran.rotate(270);
    ui->imageLab->setPixmap(pixmap.transformed(tran));

}

void Sleep::keyEvent(QKeyEvent *event)
{
    emit changeInterface(INTERFACE_MAIN);
}

Sleep::~Sleep()
{
    delete ui;
}
