#ifndef SPLAYER_H
#define SPLAYER_H
#include <QtNetwork>
//#include <parser.h>
#include <QObject>
#include <phonon>
#include "streamio.h"
#include <QProgressDialog>
#include "grooveprogressbar.h"
#include "playlist.h"

class sPlayer : public QObject
{
    Q_OBJECT
public:
    explicit sPlayer(QObject *parent = 0);
    void play(int p);

    void play();
    void stop();
    void pause();
    void setPlaylist(playlist *playList);
    ~sPlayer();

signals:
    void finishedPlaying();
    void downloadComplete();
public slots:
    void start(int p);
    void playNext();
    void putb(int p,qint64,qint64);
    void abortDownload();
private slots:
    void markComplete();
private:
    QNetworkAccessManager *manager;
    Phonon::AudioOutput *audioOutput;
    Phonon::MediaObject *media;
    QNetworkReply *reply;
    QBuffer *buffer;
    Phonon::Path *path;
    bool playing;
    QObject *internal;
    QTime startStreamT;
    grooveProgressBar *pd;
    playlist *pl;
};
#endif // SPLAYER_H
