#include "playlist.h"

playlist::playlist(QObject *parent) :
    QObject(parent)
{
   manager = new QNetworkAccessManager();
   this->currentdownloaditem = -1;
   pList = new QList<songElement *>;
   this->currentplayingitem = -1;
   this->currentSkeyItem = -1;
}
void playlist::markPlayed(int position)
{
    pList->at(position)->played = true;
    this->freeMemory(position);
}
void playlist::freeMemory(int position)
{
   pList->at(position)->buffer->~QBuffer();
   pList->at(position)->buffer = new QBuffer();
}

int playlist::currentplaying()
{
    return this->currentplayingitem;
}
bool playlist::bReady(int b)
{
    return pList->at(b)->bufferready;
}
void playlist::setBufferRdy(int b)
{
    pList->at(b)->bufferready = true;
}
bool playlist::setCurrentPlaying(int position)
{
    if(pList->size() > position)
    {
        this->currentplayingitem = position;
        /*if(pList->at(position)->bufferready == false &&)
        {
            if(!pList->at(position)->downloaded)
                this->beginDownload(position);
        }
        else
            emit this->bufferReady(position);
        */
        return true;
    }
    else
        return false;
}
QIODevice * playlist::getBuffer(int position)
{
    return pList->at(position)->buffer;
}

void playlist::beginDownload(int position)
{
    this->currentdownloaditem = position;
    qDebug() << "StartDownlaod:" << pList->at(position)->songId;
    QNetworkRequest req;
    req.setUrl(*pList->at(currentdownloaditem)->server);
    qDebug() << pList->at(currentdownloaditem)->server;
    req.setHeader(req.ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    if(reply)
        reply->~QNetworkReply();
    reply = manager->post(req,QString("streamKey=" + pList->at(this->currentdownloaditem)->streamkey->toAscii()).toAscii());
    pList->at(this->currentdownloaditem)->buffer->open(QBuffer::ReadWrite | QBuffer::Truncate);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadSlot(qint64,qint64)));
    connect(reply,SIGNAL(finished()),this,SLOT(networkReplyFinish()));
    connect(this,SIGNAL(downloadComplete(int)),this,SLOT(downloadDone(int)));
    startStreamT = QTime::currentTime();
}

void playlist::setGscom(gscom *comm)
{
    gs = comm;
    connect(gs,SIGNAL(sKeyFound()),this,SLOT(skeyFound()));
}
void playlist::skeyFound()
{
    emit this->unfreeze();
    pList->at(this->currentSkeyItem)->streamkey = new QString(gs->streamID);
    pList->at(this->currentSkeyItem)->server = new QUrl(gs->sku);
    if(this->currentdownloaditem == -1)
        this->beginDownload(this->currentSkeyItem);
    else
        if(this->currentplaying() == this->currentSkeyItem)
            this->beginDownload(this->currentSkeyItem);
}

int playlist::addSong(QStandardItem *item)
{
    playlist::songElement *newelement = new playlist::songElement;
    newelement->buffer = new QBuffer();
    newelement->downloaded =false;
    newelement->songId = new QString(item->text());
    newelement->played = false;
    newelement->server = new QUrl();
    newelement->streamkey = new QString("noneatm");
    newelement->bufferready = false;
    newelement->type = playlist::EStream;
    pList->append(newelement);
    gs->getSong(item->text());
    emit this->freeze();
    this->currentSkeyItem = pList->size()-1;
    return pList->size()-1;
}

void playlist::downloadDone(int position)
{
    if(pList->size() < position+1)
        beginDownload(position+1);
    else
        this->currentdownloaditem = -1;
    pList->at(position)->downloaded = true;
}
void playlist::networkReplyFinish()
{
    qDebug() << "finish";
    QVariant url = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(url.toUrl().isValid())
    {
        QNetworkRequest req;
        req.setUrl(url.toUrl());
        qDebug() << url;
        reply = manager->get(req);
        startStreamT = QTime::currentTime();
        //connect(reply,SIGNAL(finished()),this,SLOT(start()));
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadSlot(qint64,qint64)));
    }
}

void playlist::downloadSlot(qint64 b, qint64 t)
{
    //qDebug() << "Download: " << b << "Total: " << t;
    if(t != 0)
    {
        emit this->downloadProgress(this->currentdownloaditem,b,t);
        pList->at(this->currentdownloaditem)->buffer->buffer().append(reply->readAll());
        //qDebug() << !pList->at(this->currentdownloaditem)->bufferready << this->currentdownloaditem;
        if ( b >= t*0.05 && !pList->at(this->currentdownloaditem)->bufferready)
            //if(!pList->at(currentdownloaditem)->bufferready && b/(startStreamT.msecsTo(QTime::currentTime()) + 1)*100/1024 >= 10)
        {
            this->setBufferRdy(this->currentdownloaditem);
            emit this->bufferReady(this->currentdownloaditem);

            qDebug() << "Buffer Ready";
        }
        if (b==t)
        {
            emit this->downloadComplete(this->currentdownloaditem);
            //emit this->bufferReady(this->currentdownloaditem);
        }
    }
}
