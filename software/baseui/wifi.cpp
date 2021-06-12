#include "wifi.h"
#include "ui_wifi.h"
#include "common.h"
#include <QDebug>

#define WIDGET_LIST     0
#define WIDGET_PSD      1

Wifi::Wifi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wifi)
{
    ui->setupUi(this);

    button[0] = &(ui->btn0);
    button[1] = &(ui->btn1);
    button[2] = &(ui->btn2);
    button[3] = &(ui->btn3);
    button[4] = &(ui->btn4);
    button[5] = &(ui->btn5);
    button[6] = &(ui->btn6);
    button[7] = &(ui->btn7);
    button[8] = &(ui->btn8);
    button[9] = &(ui->btn9);
    button[10] = &(ui->btnq);
    button[11] = &(ui->btnw);
    button[12] = &(ui->btne);
    button[13] = &(ui->btnr);
    button[14] = &(ui->btnt);
    button[15] = &(ui->btny);
    button[16] = &(ui->btnu);
    button[17] = &(ui->btni);
    button[18] = &(ui->btno);
    button[19] = &(ui->btnp);
    button[20] = &(ui->btncap);
    button[21] = &(ui->btna);
    button[22] = &(ui->btns);
    button[23] = &(ui->btnd);
    button[24] = &(ui->btnf);
    button[25] = &(ui->btng);
    button[26] = &(ui->btnh);
    button[27] = &(ui->btnj);
    button[28] = &(ui->btnk);
    button[29] = &(ui->btnl);
    button[30] = &(ui->btnok);
    button[31] = &(ui->btnz);
    button[32] = &(ui->btnx);
    button[33] = &(ui->btnc);
    button[34] = &(ui->btnv);
    button[35] = &(ui->btnb);
    button[36] = &(ui->btnn);
    button[37] = &(ui->btnm);



    for (int i = 0; i < 38; i++){
        (*button[i])->setStyleSheet("border-style: outset;"
                                    "border-width: 2px;"
                                    "border-color: black;"
                                    "border-radius: 10px;"
                                    "font: bold 20px;");
    }

    ui->titleLab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->titleLab->setText("Wifi Setting");
    ui->titleLab->setStyleSheet("border-style: outset;"
                                "font: bold 35px;");

    ui->pwdLab->setText("Scanning");

    scanWifi();
    currentWidget = WIDGET_LIST;


}

void Wifi::displayView()
{
    scanWifi();
    checkConnect();
    apendListToView();
}

bool Wifi::scanWifi()
{
    QProcess process;
    process.start("nmcli d wifi list");
    process.waitForFinished(10000);

    QString stdout = process.readAllStandardOutput();

    wifiList.clear();
    wifiList = stdout.split('\n', QString::SkipEmptyParts);
    ui->pwdLab->setText("Scan finish");

    return true;
}

void Wifi::checkConnect()
{
    for (const auto& i : wifiList){
        if (i.startsWith('*')){
            connectStatus = true;
            emit changeWifiStatus(true);
            return;
        }
    }
    emit changeWifiStatus(false);
}

void Wifi::apendListToView()
{
    ui->headerLab->setText(wifiList.at(0));
    ui->listWidget->clear();
    for (int i = 1; i < wifiList.size(); i++){
        ui->listWidget->addItem(wifiList.at(i));
    }
    ui->listWidget->setCurrentRow(0);
    ui->listWidget->setFocus();
}

void Wifi::keyEvent(QKeyEvent *event)
{
    auto funEnterPSD = [this](){
        wifiSSID.clear();
        wifiPSD.clear();

        QStringList temp = wifiList.at(ui->listWidget->currentRow()+1)
                                   .split(QRegExp("\\s+"), QString::SkipEmptyParts);

        if (temp.at(0) == '*')
            return;
        wifiSSID = temp.at(0);

        currentWidget = WIDGET_PSD;
        ui->pwdLab->setText("Password:");
        btnPlace = 0;
        (*button[btnPlace])->setFocus();
        isUper = false;
    };

    auto funKey = [this, event](){
        if (currentWidget == WIDGET_PSD){
            (*button[btnPlace])->setStyleSheet("border-style: outset;"
                                               "border-width: 2px;"
                                               "border-color: black;"
                                               "border-radius: 10px;"
                                               "font: bold 20px;");

            switch (event->key()){
            case Qt::Key_Left:
                btnPlace -= 1;
                btnPlace = (btnPlace < 0) ? 37 : btnPlace;
                break;
            case Qt::Key_Right:
                btnPlace += 1;
                btnPlace %= 38;
                break;
            case Qt::Key_Up:
                btnPlace -= 10;
                btnPlace = (btnPlace%37+37)%37;
                break;
            case Qt::Key_Down:
                btnPlace += 10;
                btnPlace %= 37;
                break;
            }

            (*button[btnPlace])->setStyleSheet("border-style: outset;"
                                               "border-width: 4px;"
                                               "border-color: black;"
                                               "border-radius: 10px;"
                                               "font: bold 20px;");
        }
    };

    QString temp;

    switch(event->key()){
    case Qt::Key_Left:
        funKey();
        break;
    case Qt::Key_Right:
        funKey();
        break;
    case Qt::Key_Up:
        funKey();
        break;
    case Qt::Key_Down:
        funKey();
        break;
    case Qt::Key_Return:
        switch (currentWidget){
        case WIDGET_LIST:
            funEnterPSD();
            break;
        case WIDGET_PSD:
            switch (btnPlace){
            case 20:
                isUper = !isUper;
                break;
            case 30:
                currentWidget = WIDGET_LIST;
                (*button[btnPlace])->setStyleSheet("border-style: outset;"
                                                   "border-width: 2px;"
                                                   "border-color: black;"
                                                   "border-radius: 10px;"
                                                   "font: bold 20px;");
                ui->pwdLab->setText("connecting...");
                connetcWifi();
                break;
            default:
                temp = (*button[btnPlace])->text();
                if (!isUper)
                    temp = temp.toLower();
                wifiPSD.append(temp);
                temp = ui->pwdLab->text();
                temp.append(isUper ? (*button[btnPlace])->text() : (*button[btnPlace])->text().toLower());
                ui->pwdLab->setText(temp);
                break;
            }
            break;
        }
        break;
    case Qt::Key_Escape:
        if (currentWidget == WIDGET_PSD){
            currentWidget = WIDGET_LIST;
            ui->pwdLab->clear();
            (*button[btnPlace])->setStyleSheet("border-style: outset;"
                                               "border-width: 2px;"
                                               "border-color: black;"
                                               "border-radius: 10px;"
                                               "font: bold 20px;");
            ui->listWidget->setFocus();
        } else {
            emit changeInterface(INTERFACE_MAIN);
        }
        break;
    }
}

bool Wifi::connetcWifi()
{
    QProcess process;
    process.start(QString("nmcli d wifi connect %1 password %2").arg(wifiSSID)
                                                                .arg(wifiPSD));
    process.waitForFinished(10000);

    QString stderr = process.readAllStandardError();
    if (stderr.isEmpty()){
        emit changeWifiStatus(true);
        ui->pwdLab->setText("Connect success!");
        return true;
    } else {
        emit changeWifiStatus(false);
        ui->pwdLab->setText("Connect failed, please try again");
        return false;
    }
}

Wifi::~Wifi()
{
    delete ui;
}
