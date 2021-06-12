#ifndef DESKTOP_H
#define DESKTOP_H

#include <QWidget>
#include <QPixmap>
#include <QTransform>
#include <QFont>
#include <QPushButton>
#include <QKeyEvent>
#include <QProcess>

#include "common.h"

namespace Ui {
class Desktop;
}

class Desktop : public QWidget
{
    Q_OBJECT

public:
    explicit Desktop(QWidget *parent = nullptr);
    ~Desktop();

    void setWifiIconStatus(bool isConnect);
    void setTimerBtnNum(int hour, int min);
    void keyEvent(QKeyEvent *event);

signals:
    void changeInterface(int interface);

private:
    Ui::Desktop *ui;

    int btnSize;
    int btnSelect;
    bool btnWifiStatus;
    int btnTimeHour;
    int btnTimeMin;
    QPushButton** btnGroup[4];

    void setBtnSelect(int place);

};

#endif // DESKTOP_H
