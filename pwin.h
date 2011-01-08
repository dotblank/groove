#ifndef PWIN_H
#define PWIN_H

#include <QWidget>
#include <QtGui>

namespace Ui {
    class pWin;
}

class pWin : public QWidget
{
    Q_OBJECT

public:
    void setModel(QAbstractItemModel *name);
    explicit pWin(QWidget *parent = 0);
    ~pWin();

private:
    void resizeEvent(QResizeEvent *);
    Ui::pWin *ui;
};

#endif // PWIN_H
