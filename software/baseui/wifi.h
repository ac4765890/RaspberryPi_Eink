#ifndef WIFI_H
#define WIFI_H

#include <QWidget>
#include <QPushButton>
#include <QProcess>
#include <QKeyEvent>
#include <QInputDialog>

namespace Ui {
class Wifi;
}

class Wifi : public QWidget
{
    Q_OBJECT

public:
    explicit Wifi(QWidget *parent = nullptr);
    ~Wifi();

    void displayView();
    void keyEvent(QKeyEvent *event);

signals:
    void changeWifiStatus(bool isConnect);
    void changeInterface(int interface);

private:
    Ui::Wifi *ui;

    QPushButton** button[38];
    QStringList wifiList;
    bool connectStatus;
    int currentWidget;
    QString wifiSSID;
    QString wifiPSD;
    int btnPlace;
    bool isUper;


    bool scanWifi();
    void checkConnect();
    void apendListToView();
    bool connetcWifi();

};

#endif // WIFI_H
