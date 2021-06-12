#ifndef SLEEP_H
#define SLEEP_H

#include <QWidget>

namespace Ui {
class Sleep;
}

class Sleep : public QWidget
{
    Q_OBJECT

public:
    explicit Sleep(QWidget *parent = nullptr);
    ~Sleep();

    void keyEvent(QKeyEvent *event);

signals:

    void changeInterface(int);

private:
    Ui::Sleep *ui;
};

#endif // SLEEP_H
