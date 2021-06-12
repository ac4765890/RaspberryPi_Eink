#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QKeyEvent>
#include <QProcess>
#include <QTimer>
#include <string>

#include "common.h"

namespace Ui {
class Timer;
}

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();

    void keyEvent(QKeyEvent *event);
    void getSystemTime();

signals:
    void changeInterface(int interface);
    void changeTime(int, int);

private:
    Ui::Timer *ui;
    int hour, min;
    int place;
    QTimer* timer;

    void setSystemTime();
};

#endif // TIMER_H
