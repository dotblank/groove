#ifndef SPLAYER_H
#define SPLAYER_H
#include <QtNetwork>
//#include <parser.h>
#include <QObject>
#include <phonon>
#include "streamio.h"
#include <QProgressDialog>

class sPlayer : public QObject
{
    Q_OBJECT
public:
    explicit sPlayer(QObject *parent = 0);
    void play(QString StreamKey, QUrl server);
    void stop();
    ~sPlayer();

signals:
    void finishedPlaying();
    void downloadComplete();
public slots:
    void start();
    void putb(qint64,qint64);
    void abortDownload();
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
    QProgressDialog *pd;
};
#endif // SPLAYER_H
