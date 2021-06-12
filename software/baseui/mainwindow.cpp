#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    currentInterface = INTERFACE_MAIN;
    desktop = new Desktop();
    timer = new Timer();
    wifi = new Wifi();
    sleep = new Sleep();

    QObject::connect(desktop, &Desktop::changeInterface,
                     this, &MainWindow::updateInterface);

    QObject::connect(timer, &Timer::changeInterface,
                     this, &MainWindow::updateInterface);
    QObject::connect(timer, &Timer::changeTime,
                     desktop, &Desktop::setTimerBtnNum);

    QObject::connect(wifi, &Wifi::changeInterface,
                     this, &MainWindow::updateInterface);
    QObject::connect(wifi, &Wifi::changeWifiStatus,
                     desktop, &Desktop::setWifiIconStatus);
    wifi->displayView();

    QObject::connect(sleep, &Sleep::changeInterface,
                     this, &MainWindow::updateInterface);

    scene = new QGraphicsScene(this);
    proxy = new QGraphicsProxyWidget();

    proxy->setWidget(desktop);
    proxy->setRotation(90);
    proxy->setPos(720, -60);

    scene->addItem(proxy);
    scene->setSceneRect(0, 0, static_cast<QWidget*>(scene->parent())->size().width(), static_cast<QWidget*>(scene->parent())->size().height());
    scene->setFocusItem(proxy);


    timer->getSystemTime();
    this->setScene(scene);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (currentInterface){
    case INTERFACE_MAIN:
        desktop->keyEvent(event);
        break;
    case INTERFACE_WIFI:
        wifi->keyEvent(event);
        break;
    case INTERFACE_TIMER:
        timer->keyEvent(event);
        break;
    case INTERFACE_READER:
        break;
    case INTERFACE_SLEEP:
        sleep->keyEvent(event);
        break;
    }
    QGraphicsView::keyPressEvent(event);
}

void MainWindow::updateInterface(int interface)
{
    switch (interface){
    case INTERFACE_WIFI:
        proxy->setWidget(wifi);
        wifi->displayView();
        break;
    case INTERFACE_TIMER:
        proxy->setWidget(timer);
        break;
    case INTERFACE_READER:
        break;
    case INTERFACE_SLEEP:
        proxy->setWidget(sleep);
        break;
    case INTERFACE_MAIN:
        proxy->setWidget(desktop);
        break;
    }

    if (interface != INTERFACE_READER)
        currentInterface = interface;
    proxy->setPos(720, -60);
    this->update();
}

MainWindow::~MainWindow()
{

}
