#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>
#include <QString>
#include "vkb.h"
#include <QResizeEvent>

namespace Ui {
    class topBar;
}

class topBar : public QWidget
{
    Q_OBJECT

public:
    explicit topBar(QWidget *parent = 0);
    ~topBar();
signals:
    void changeTask();
    void searchRequest(QString);
    void closeApp();
protected:
    void changeEvent(QEvent *e);
    bool eventFilter(QObject *, QEvent *);
    void resizeEvent(QResizeEvent *);

private slots:
    void on_taskSwitch_clicked();
    void on_sButton_clicked();
    void on_closeButton_clicked();
private:
    Ui::topBar *ui;
    vkb *kb;
};

#endif // TOPBAR_H
