#ifndef GROOVE_H
#define GROOVE_H
#include <QtGui>
#include "gscom.h"
#include "splayer.h"
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HILDON)
#include "qmaemo5rotator.h"
#endif
#include <QMenuBar>
#include "playlist.h"
#include "grooveprogressbar.h"
#include "topbar.h"
#include "vkb.h"

class groove : public QWidget
{
    Q_OBJECT;
public:
    explicit groove(QWidget *parent = 0);

signals:

public slots:
    void search();
    void finishedS();
    void changeS( QAction * action);
    void play();
    void stop();
    void moreB();
    void orientationChanged();
    void performSearch(QString);
private slots:
    void progressUpdate(int,qint64,qint64);
    void addSongPlaylist();
    void showOthers();
private:
    sPlayer *player;
    QMenuBar *mBar;
    QPushButton *sMethod;
    QStandardItemModel *model;
    QLineEdit *lineEdit;
    QTableView *resultView;
    QPushButton *button;
    bool portrait;
    gscom *gs;
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HILDON)
    QMaemo5Rotator *rot;
#endif
    playlist *pl;
    grooveProgressBar *pd;

};

#endif // GROOVE_H
