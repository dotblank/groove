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
}
sPlayer::~sPlayer()
{
    manager->~QNetworkAccessManager();
    //reply->~QIODevice();
    buffer->~QBuffer();
    media->~MediaNode();
}
void sPlayer::abortDownload()
{
    //pd->hide();
    //reply->abort();
}

void sPlayer::play(QString StreamKey,QUrl server)
{
    if(playing)
    {
        //reply->abort();
    }
    pd = new grooveProgressBar();
    //pd->setAttribute();

#ifdef Q_WS_MAEMO_5
    pd->setAttribute(Qt::WA_Maemo5AutoOrientation,true);
    //pd->setModal(false);
#endif
    pd->show();
    pd->setValue(0);
    QNetworkRequest req;
    req.setUrl(server);
    qDebug() << server;
    req.setHeader(req.ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    reply = manager->post(req,QString("streamKey=" + StreamKey.toAscii()).toAscii());
    buffer->open(buffer->ReadWrite | buffer->Truncate);
    connect(reply,SIGNAL(finished()),this,SLOT(start()));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(putb(qint64,qint64)));
    //connect(pd,SIGNAL(canceled()),this,SLOT(abortDownload()));
    media->stop();
    playing = false;
    startStreamT = QTime::currentTime();
}
void sPlayer::start()
{
    QVariant url = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(url.toUrl().isValid())
    {
        QNetworkRequest req;
        req.setUrl(url.toUrl());
        qDebug() << url;
        reply = manager->get(req);
        connect(reply,SIGNAL(finished()),this,SLOT(start()));
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(putb(qint64,qint64)));
    }
    else
    {
        if(!playing)
        {
            playing = true;
            media->setCurrentSource(Phonon::MediaSource(buffer));
            media->play();
            qDebug() << "Playing";
        }
    }
    /*else
    {
        media->stop();
        buffer->close();
        buffer->open(QIODevice::ReadWrite | QIODevice::Truncate);
        buffer->write(reply->readAll());
        reply->close();
        media->setCurrentSource(Phonon::MediaSource(buffer));
        media->play();
    }*/
}
void sPlayer::stop()
{
    media->stop();
}

void sPlayer::putb(qint64 b, qint64 t)
{
    //qDebug() << "Download: " << b << "Total: " << t;
    if(b == 0 && t == 0)
    {
        QVariant url = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        if(url.toUrl().isValid())
        {
            QNetworkRequest req;
            req.setUrl(url.toUrl());
            qDebug() << url;
            reply = manager->get(req);
            connect(reply,SIGNAL(finished()),this,SLOT(start()));
            connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(putb(qint64,qint64)));
        }
        else
        {
            //buffer->close();
            reply->close();
        }
    }
    else
    {
        if(pd->maximum() != t)
            pd->setMaximum(t);
        pd->setValue(b);

        buffer->buffer().append(reply->readAll());
        //qDebug() << buffer->bytesAvailable();
        if(playing)
        {
            StreamIO* stream = (StreamIO*) media->currentSource().stream();
            stream->setStreamSize(buffer->size());
        }

        /*
        //buffer->seek(b);
        qint64 last = buffer->pos();
        buffer->seek(buffer->bytesAvailable()+buffer->pos());
        qDebug() << buffer->write(reply->readAll());
        qDebug() << buffer->pos();
        //buffer->putChar()
        buffer->seek(last);
        //buffer->data().append(reply->readAll());*/
        //qDebug() << "Download speed (KB/S): " << b/(startStreamT.msecsTo(QTime::currentTime()) + 1)*100/1024;
        if ( b >= t*0.05 && !playing && b/(startStreamT.msecsTo(QTime::currentTime()) + 1)*100/1024 >= 25)
        {
            pd->hide();
            playing = true;
            //Start playback at 25% download
            media->setCurrentSource(Phonon::MediaSource(buffer));
            media->play();
            qDebug() << "Playing";
        }
    }
}
