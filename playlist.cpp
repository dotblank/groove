#include "playlist.h"

playlist::playlist(QObject *parent) :
    QAbstractTableModel(parent)
{
   manager = new QNetworkAccessManager();
   this->currentdownloaditem = -1;
   pList = new QList<songElement *>;
   this->currentplayingitem = -1;
   this->currentSkeyItem = -1;
   this->reply = NULL;
   invalid = new QVariant();
   icon = new QVariant(QIcon(":/groove/icons/general_forward.png"));
}

//Implemented model class information
QVariant playlist::data(const QModelIndex &index, int role) const
{

    playlist* play = (playlist *)index.model();
    QVariant dat = *play->invalid;
    if(play->existAt(index.row()))
    {
        if (!index.isValid())
            return *play->invalid;
        if (role == Qt::TextAlignmentRole) {
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        } else if (role == Qt::DecorationRole) {
            switch(index.column())
            {
            case sName:
                if(play->currentplaying()==index.row())
                    //dat = *play->icon;
                    dat = *play->invalid;
                else
                    dat = *play->invalid;
                break;
            default:
                dat = *play->invalid;
            }
        } else if (role == Qt::ForegroundRole) {
            switch(index.column())
            {
            case sName:
                if(!play->pList->at(index.row())->downloaded)
                    dat = QVariant(Qt::gray);
                else
                    dat = *play->invalid;
                break;
            default:
                dat = *play->invalid;
            }
        } else if (role == Qt::DisplayRole) {
            switch(index.column())
            {
            case sName:
                dat = QVariant(*play->pList->at(index.row())->name);
                break;
            case sID:
                dat = QVariant(*play->pList->at(index.row())->songId);
                break;
            case sKey:
                dat = QVariant(*play->pList->at(index.row())->streamkey);
                break;
            case sDownloaded:
                dat = QVariant(play->pList->at(index.row())->downloaded);
                break;
            case sReady:
                dat = QVariant(play->pList->at(index.row())->bufferready);
                break;
            case sURL:
                dat = QVariant(play->pList->at(index.row())->server->toString());
                break;
            case sPlayed:
                dat = QVariant(play->pList->at(index.row())->played);
                break;
            default:
                dat = *play->invalid;
            }
        } else
            dat = *play->invalid;
    }
    else
        dat = *play->invalid;
    return dat;
}
int playlist::rowCount(const QModelIndex &) const
{
    return pList->size();
}
int playlist::columnCount(const QModelIndex &) const
{
    return PLAYLISTENUMS;
}


QList<playlist::songElement *>* playlist::getList()
{
    return pList;
}

void playlist::markPlayed(int position)
{
    if(0 <= position && position < pList->size())
    {
        pList->at(position)->played = true;
        this->freeMemory(position);
    }
}
void playlist::freeMemory(int position)
{
   pList->at(position)->downloaded = false;
   pList->at(position)->bufferready = false;
   delete pList->at(position)->buffer;
   pList->at(position)->buffer = new QBuffer();
}
bool playlist::existAt(int position)
{
    if(position < 0)
        return false;
    return (pList->size() > position);
}

int playlist::currentplaying()
{
    return this->currentplayingitem;
}
bool playlist::bReady(int b)
{
    if(pList->size() > b)
        return pList->at(b)->bufferready;
    else
        return false;
}
void playlist::setBufferRdy(int b)
{
    pList->at(b)->bufferready = true;
}
void playlist::setCurrentPlaying(int position)
{
    if(this->existAt(position))
    {
        this->currentplayingitem = position;
        if(!pList->at(position)->downloaded && this->currentdownloaditem != this->currentplayingitem)
            this->beginDownload(position);
        /*if(pList->at(position)->bufferready == false &&)
        {
            if(!pList->at(position)->downloaded)
                this->beginDownload(position);
        }
        else
            emit this->bufferReady(position);
        */
        return;
    }
    else
    {
    if(position == -1)
        {
        this->currentplayingitem = -1;
    }
    else
        return;
    }
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
    {
        reply->disconnect();
        reply->deleteLater();
    }
    reply = manager->post(req,QString("streamKey=" + pList->at(this->currentdownloaditem)->streamkey->toAscii()).toAscii());
    pList->at(this->currentdownloaditem)->buffer->open(QBuffer::ReadWrite | QBuffer::Truncate);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadSlot(qint64,qint64)));
    connect(reply,SIGNAL(finished()),this,SLOT(networkReplyFinish()));
    connect(this,SIGNAL(downloadComplete(int)),this,SLOT(downloadDone(int)));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(getNError(QNetworkReply::NetworkError)));
    startStreamT = QTime::currentTime();
}
void playlist::getNError(QNetworkReply::NetworkError error)
{
    qDebug() << "Network Error (if this is 99 then it will retry" << error;
    if(error == QNetworkReply::UnknownNetworkError && this->currentdownloaditem != -1)
        beginDownload(this->currentdownloaditem);

}

void playlist::setGscom(gscom *comm)
{
    gs = comm;
    connect(gs,SIGNAL(sKeyFound()),this,SLOT(skeyFound()));
}
void playlist::skeyFound()
{
    emit this->freeze(false);
    pList->at(this->currentSkeyItem)->streamkey = new QString(gs->streamID);
    pList->at(this->currentSkeyItem)->server = new QUrl(gs->sku);
    if(this->currentdownloaditem == -1)
        this->beginDownload(this->currentSkeyItem);
    else
        if(this->currentplaying() == this->currentSkeyItem)
            this->beginDownload(this->currentSkeyItem);
    this->currentSkeyItem = -1;
}

int playlist::addSong(QStandardItem *item, QString name)
{
    playlist::songElement *newelement = new playlist::songElement;
    newelement->name = new QString(name);
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
    emit this->rowsInserted(QModelIndex(),pList->size(),pList->size());
    this->currentSkeyItem = pList->size()-1;
    emit this->freeze(true);
    return pList->size()-1;
}

void playlist::downloadDone(int position)
{
    if(this->existAt(position+1) && this->currentSkeyItem == -1 && !pList->at(position+1)->downloaded && this->currentdownloaditem != position+1)
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
        if(reply)
        {
            reply->disconnect();
            reply->deleteLater();
        }
        reply = manager->get(req);
        startStreamT = QTime::currentTime();
        //connect(reply,SIGNAL(finished()),this,SLOT(start()));
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadSlot(qint64,qint64)));
        connect(reply,SIGNAL(finished()),this,SLOT(networkReplyFinish()));
        connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(getNError(QNetworkReply::NetworkError)));
    }
}

void playlist::downloadSlot(qint64 b, qint64 t)
{
    //qDebug() << "Download: " << b << "Total: " << t;
    if(t != 0)
    {
        emit this->downloadProgress(this->currentdownloaditem,b,t);
        if(existAt(this->currentdownloaditem))
        {
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
}
