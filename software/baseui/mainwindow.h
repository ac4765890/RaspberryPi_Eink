#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QProcess>

#include "desktop.h"
#include "timer.h"
#include "wifi.h"
#include "sleep.h"
#include "common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateInterface(int interface);

private:
    QGraphicsScene* scene;
    QGraphicsProxyWidget* proxy;
    Desktop* desktop;
    Timer* timer;
    Wifi* wifi;
    Sleep* sleep;

    int currentInterface;


protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif
