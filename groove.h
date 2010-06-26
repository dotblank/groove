#ifndef GROOVE_H
#define GROOVE_H
#include <QtGui>
#include "gscom.h"
#include "splayer.h"
#include "qmaemo5rotator.h"
#include <QMenuBar>
#include "playlist.h"
#include "grooveprogressbar.h"

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
private slots:
    void progressUpdate(int,qint64,qint64);
    void addSongPlaylist();
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
    QMaemo5Rotator *rot;
    playlist *pl;
    grooveProgressBar *pd;

};

#endif // GROOVE_H
