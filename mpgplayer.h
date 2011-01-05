#ifndef MPGPLAYER_H
#define MPGPLAYER_H

#include <QtNetwork>
//#include <parser.h>
#include <QObject>
#include "streamio.h"
#include <QProgressDialog>
#include "grooveprogressbar.h"
#include "playlist.h"
#include <mpg123.h>

class mpgplayer : public QThread
{
    Q_OBJECT
public:
    explicit mpgplayer(QObject *parent = 0);
    void play(int p);
    void run();

    void play();
    void stop();
    void pause();
    void setPlaylist(playlist *playList);
    ~mpgplayer();

signals:
    void finishedPlaying();
    void downloadComplete();
public slots:
    void playNext();
    void putb(int p,qint64,qint64);
    void abortDownload();
    void back();
private slots:
    void markComplete();
    void updatePlayPosition(qint64 time);
private:
    enum status {TWait, TAbort, TFinish, TData};
    status net;
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
    static const long samplerate = 44100;

};

#endif // MPGPLAYER_H
