#include "playlist.h"

playlist::playlist(QObject *parent) :
    QObject(parent)
{
   manager = new QNetworkAccessManager();
   this->currentdownloaditem = -1;
   pList = new QList<songElement *>;
}
void playlist::beginDownload(int position)
{
    startStreamT = QTime::currentTime();
    this->currentdownloaditem = position;
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
}

void playlist::addSong(QStandardItem item)
{

    playlist::songElement *newelement = new playlist::songElement;
    newelement->buffer = new QBuffer();
    newelement->downloaded =false;
    newelement->songId = new QString(item.text());
    newelement->played = false;
    newelement->server = new QUrl();
    newelement->streamkey = new QString("noneatm");
    newelement->bufferready = false;
    newelement->type = playlist::EStream;
    pList->append(newelement);
    gs->getSong(item.text());
    emit this->freeze();
    //this->currentdownloaditem = pList->size()-1;
}

void playlist::downloadDone(int position)
{
    if(pList->size() < position+1)
        beginDownload(position+1);
    else
        this->currentdownloaditem = -1;
    pList->at(position)->downloaded = true;
}

void playlist::downloadSlot(qint64 b, qint64 t)
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
            startStreamT = QTime::currentTime();
            //connect(reply,SIGNAL(finished()),this,SLOT(start()));
            connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadSlot(qint64,qint64)));
        }
        else
        {
            //buffer->close();
            emit this->sFailure(this->currentdownloaditem,playlist::Other);
            reply->close();
        }
    }
    else
    {
        emit this->downloadProgress(this->currentdownloaditem,b,t);
        pList->at(this->currentdownloaditem)->buffer->buffer().append(reply->readAll());
        //qDebug() << buffer->bytesAvailable();

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
        if ( b >= t*0.05 && !pList->at(currentdownloaditem)->bufferready && b/(startStreamT.msecsTo(QTime::currentTime()) + 1)*100/1024 >= 10)
        {
            emit this->bufferReady(this->currentdownloaditem);
            qDebug() << "Buffer Ready";
        }
        if (b==t)
        {
            emit this->downloadComplete(this->currentdownloaditem);
        }
    }
}
