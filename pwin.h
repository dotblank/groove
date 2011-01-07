#ifndef PWIN_H
#define PWIN_H

#include <QWidget>

namespace Ui {
    class pWin;
}

class pWin : public QWidget
{
    Q_OBJECT

public:
    void addSong(QString name);
    explicit pWin(QWidget *parent = 0);
    ~pWin();

private:
    Ui::pWin *ui;
};

#endif // PWIN_H
