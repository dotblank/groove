#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>
#include <QDesktopWidget>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

namespace Ui {
    class bottomBar;
}

class bottomBar : public QWidget
{
    Q_OBJECT

public:
    explicit bottomBar(QWidget *parent = 0);
    ~bottomBar();
public slots:
    void setPlaybackProgress(qint64 min,qint64 max);
signals:
    void addB();
    void nextB();
    void pause();
    void back();
    void list();
    void settings();
protected:
    void changeEvent(QEvent *e);
private slots:
    void on_addButton_clicked();
    void on_nextB_clicked();
    void on_pauseB_clicked();
    void on_backB_clicked();
    void on_list_clicked();
    void on_settingsB_clicked();


private:
    Ui::bottomBar *ui;
    QGraphicsRectItem *playbackProgress;
    QGraphicsScene *main;
};

#endif // BOTTOMBAR_H
