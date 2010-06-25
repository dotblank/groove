#include "splayer.h"
#include <QFile>
sPlayer::sPlayer(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager();
    buffer = new QBuffer();
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory,this);
    media = new Phonon::MediaObject(this);
    Phonon::createPath(media, audioOutput);
    playing = false;
    //reply = new QNetworkReply();
    internal = parent;
    //buffer->open(QIODevice::ReadWrite);
    connect(media,SIGNAL(finished()),this,SLOT(markComplete()));
}
void sPlayer::setPlaylist(playlist *playList)
{
    this->pl = playList;
    connect(pl,SIGNAL(bufferReady(int)),this,SLOT(start(int)));
    connect(pl,SIGNAL(downloadProgress(int,qint64,qint64)),this,SLOT(putb(int,qint64,qint64)));
    //connect(pl,SIGNAL(downloadComplete(int)),this,SLOT(start(int)));

}
void sPlayer::markComplete()
{
    pl->markPlayed(pl->currentplaying());
    pl->setCurrentPlaying(-1);
}

sPlayer::~sPlayer()
{
    manager->~QNetworkAccessManager();
    //reply->~QIODevice();
    media->~MediaNode();
}
void sPlayer::abortDownload()
{
    //pd->hide();
    //reply->abort();
}

void sPlayer::start(int p)
{
    qDebug() << "got start play";
    if(p == pl->currentplaying())
        {
            playing = true;
            media->setCurrentSource(Phonon::MediaSource(pl->getBuffer(p)));
            media->play();
            qDebug() << "Playing";
        }

}
void sPlayer::play()
{
    if(pl->currentplaying() != -1)
    {
        //pl->setCurrentPlaying(pl->findFirstNotPlayed());
    }
    else
        return;
}
void sPlayer::play(int p)
{
    pl->setCurrentPlaying(p);
    //pl->beginDownload(p);
}

void sPlayer::stop()
{
    pl->setCurrentPlaying(-1);
    media->stop();
    playing = false;
}

void sPlayer::putb(int p, qint64 b, qint64 t)
{
    //qDebug() << "Download: " << b << "Total: " << t;
    if(p == pl->currentplaying())
    {
        if(pl->bReady(p))
        {
            StreamIO* stream = (StreamIO*) media->currentSource().stream();
            stream->setStreamSize(pl->getBuffer(p)->size());
        }
    }
}
