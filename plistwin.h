#ifndef PLISTWIN_H
#define PLISTWIN_H

#include <QWidget>
#include <QtGui>
#include "playlist.h"

class pListWin : public QWidget
{
    Q_OBJECT
public:
    explicit pListWin(QWidget *parent = 0);
    bool setPlaylist(playlist*);
    void updateList();

signals:

public slots:

private:
    QTableView *pview;
    QList<playlist::songElement *> *plist;
    QStandardItemModel *model;

};

#endif // PLISTWIN_H
