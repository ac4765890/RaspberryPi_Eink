#include "timer.h"
#include "ui_timer.h"
#include <QDebug>

Timer::Timer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    place = 0;
    hour = min = 0;
    timer = new QTimer(this);
    getSystemTime();

    ui->titleLab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->clockLab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->expLab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->titleLab->setStyleSheet("border-style: outset;"
                                "font: bold 35px;");

    ui->clockLab->setText(QString("<p><u>%1</u>%2:%3<p>").arg(hour/10)
                                                         .arg(hour%10)
                                                         .arg(min, 2, 10, QChar('0')));
    ui->clockLab->setStyleSheet("border-style: outset;"
                                "border-width: 4px;"
                                "border-color: black;"
                                "font: bold 50px;");

    ui->expLab->setText("Esc: return to main and save | ArrowKey: move and adjust");
    ui->expLab->setStyleSheet("border-style: outset;"
                              "font: bold 16px;");

    QObject::connect(timer, &QTimer::timeout, this, &Timer::getSystemTime);
    timer->start(1*1000*20);
}

void Timer::getSystemTime()
{
    QProcess process;
    process.start("date +\"%H %M\"");
    process.waitForFinished(1000);
    QString stdout = process.readAllStandardOutput();
    QStringList list = stdout.split(' ');
    hour = list.at(0).toInt();
    min = list.at(1).toInt();
    emit changeTime(hour, min);
}

void Timer::setSystemTime()
{
    QProcess process;
    char temp[50];
    sprintf(temp, "date +%T -s \"%d:%d:00\"", hour, min);
    process.start(QString(temp));
    process.waitForFinished(1000);
    emit changeTime(hour, min);
}


void Timer::keyEvent(QKeyEvent *event)
{
    //qDebug() << "KeyPress enter" << event->text() << event->key();
    auto funPlace = [this](int place){
        switch (place){
        case 0:
            ui->clockLab->setText(QString("<p><u>%1</u>%2:%3<p>").arg(hour/10)
                                                                 .arg(hour%10)
                                                                 .arg(min, 2, 10, QChar('0')));
            break;
        case 1:
            ui->clockLab->setText(QString("<p>%1<u>%2</u>:%3<p>").arg(hour/10)
                                                                 .arg(hour%10)
                                                                 .arg(min, 2, 10, QChar('0')));
            break;
        case 2:
            ui->clockLab->setText(QString("<p>%1:<u>%2</u>%3<p>").arg(hour, 2, 10, QChar('0'))
                                                                 .arg(min/10)
                                                                 .arg(min%10));
            break;
        case 3:
            ui->clockLab->setText(QString("<p>%1:%2<u>%3</u><p>").arg(hour, 2, 10, QChar('0'))
                                                                 .arg(min/10)
                                                                 .arg(min%10));
            break;
        }
    };

    auto funClock = [this](int place, bool isUp){
        int temp;
        switch (place){
        case 0:
            temp = hour%10;
            hour = isUp ? (hour+10)%24 : (((hour-10)%24)+24)%24;
            hour /= 10;
            hour *= 10;
            hour += temp;
            break;
        case 1:
            hour = isUp ? (hour+1)%24 : (((hour-1)%24)+24)%24;
            break;
        case 2:
            min = isUp ? (min+10)%60 : (((min-10)%60)+60)%60;
            break;
        case 3:
            min = isUp ? (min+1)%60 : (((min-1)%60)+60)%60;
            break;
        }
    };

    switch(event->key()){
    case Qt::Key_Left:
        place = ((place-1)%4 + 4)%4;
        funPlace(place);
        break;
    case Qt::Key_Right:
        place = (place+1)%4;
        funPlace(place);
        break;
    case Qt::Key_Up:
        funClock(place, true);
        funPlace(place);
        break;
    case Qt::Key_Down:
        funClock(place, false);
        funPlace(place);
        break;
    case Qt::Key_Escape:
        setSystemTime();
        emit changeInterface(INTERFACE_MAIN);
        break;
    }
}

Timer::~Timer()
{
    delete ui;
}
