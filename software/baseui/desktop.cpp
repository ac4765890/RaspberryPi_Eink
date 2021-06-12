#include "desktop.h"
#include "ui_desktop.h"
#include <QDebug>

Desktop::Desktop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Desktop)
{
    ui->setupUi(this);

    btnSelect = 0;
    btnWifiStatus = false;
    btnTimeHour = 0;
    btnTimeMin = 0;

    QPixmap image;
    image.load(":/pic/logo");
    QTransform tran;
    tran.rotate(270);
    ui->imageLab->setPixmap(image.transformed(tran));
    ui->imageLab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->messageLab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->messageLab->setText(QString("Wifi Setting | Status: %1").arg(btnWifiStatus ? "Online" : "Offline"));
    ui->messageLab->setStyleSheet("font: bold 26px;");

    btnSize = 120;
    image.load(":/pic/wifiOff");
    QIcon icon(image);
    ui->wifiBtn->setIcon(icon);
    ui->wifiBtn->setIconSize(QSize(btnSize - 10, btnSize - 10));
    ui->wifiBtn->setFocus();
    ui->wifiBtn->setStyleSheet("border-style: outset;"
                               "border-width: 4px;"
                               "border-color: black;"
                               "border-radius: 10px;");

    ui->timerBtn->setText("00:00");
    ui->timerBtn->setStyleSheet("border-style: outset;"
                                "border-width: 2px;"
                                "border-color: black;"
                                "border-radius: 10px;"
                                "font: bold 26px;");

    image.load(":/pic/koreader");
    icon.addPixmap(image);
    ui->readerBtn->setIcon(icon);
    ui->readerBtn->setIconSize(QSize(btnSize - 10, btnSize - 10));
    ui->readerBtn->setStyleSheet("border-style: outset;"
                                 "border-width: 2px;"
                                 "border-color: black;"
                                 "border-radius: 10px;");

    image.load(":/pic/sleep");
    icon.addPixmap(image);
    ui->sleepBtn->setIcon(icon);
    ui->sleepBtn->setIconSize(QSize(btnSize - 10, btnSize - 10));
    ui->sleepBtn->setStyleSheet("border-style: outset;"
                                "border-width: 2px;"
                                "border-color: black;"
                                "border-radius: 10px;");

    btnGroup[0] = &(ui->wifiBtn);
    btnGroup[1] = &(ui->timerBtn);
    btnGroup[2] = &(ui->readerBtn);
    btnGroup[3] = &(ui->sleepBtn);
}

void Desktop::setTimerBtnNum(int hour, int min)
{
    this->btnTimeHour = hour;
    this->btnTimeMin = min;
    ui->timerBtn->setText(QString("%1:%2").arg(btnTimeHour, 2, 10, QChar('0'))
                                          .arg(btnTimeMin, 2, 10, QChar('0')));
    ui->messageLab->setText(QString("Clock Setting | Current: %1:%2").arg(btnTimeHour, 2, 10, QChar('0'))
                                                                     .arg(btnTimeMin, 2, 10, QChar('0')));
    this->update();
}

void Desktop::setBtnSelect(int place)
{
    (*(btnGroup[btnSelect]))->setStyleSheet("border-style: outset;"
                                            "border-width: 2px;"
                                            "border-color: black;"
                                            "border-radius: 10px;"
                                            "font: bold 26px;");
    (*(btnGroup[place]))->setStyleSheet("border-style: outset;"
                                        "border-width: 4px;"
                                        "border-color: black;"
                                        "border-radius: 10px;"
                                        "font: bold 26px;");
    switch (place){
    case 0:
        ui->messageLab->setText(QString("Wifi Setting | Status: %1").arg(btnWifiStatus ? "Online" : "Offline"));
        break;
    case 1:
        ui->messageLab->setText(QString("Clock Setting | Current: %1:%2").arg(btnTimeHour, 2, 10, QChar('0'))
                                                                         .arg(btnTimeMin, 2, 10, QChar('0')));
        break;
    case 2:
        ui->messageLab->setText("Open eReader GUI");
        break;
    case 3:
        ui->messageLab->setText("Display screen save picture and sleep");
        break;
    }

    btnSelect = place;
}

void Desktop::keyEvent(QKeyEvent *event)
{
    //qDebug() << "KeyPress enter" << event->text() << event->key();
    QProcess process;
    switch(event->key()){
    case Qt::Key_Left:
        setBtnSelect(((btnSelect-1)%4 + 4)%4);
        break;
    case Qt::Key_Right:
        setBtnSelect((btnSelect+1) % 4);
        break;
    case Qt::Key_Return:
        if (btnSelect == 2){
            process.start("bash /home/pi/script/koreader.sh");
            process.waitForFinished(-1);
        }
        emit changeInterface(btnSelect);
        break;
    }
}

void Desktop::setWifiIconStatus(bool isConnect)
{
    btnWifiStatus = isConnect;
    QPixmap image;
    if (btnWifiStatus){
        ui->messageLab->setText(QString("Wifi Setting | Status: Online"));
        image.load(":/pic/wifiOn");
    } else {
        ui->messageLab->setText(QString("Wifi Setting | Status: Offline"));
        image.load(":/pic/wifiOff");
    }

    QIcon icon(image);
    ui->wifiBtn->setIcon(icon);
}

Desktop::~Desktop()
{
    delete ui;
}
