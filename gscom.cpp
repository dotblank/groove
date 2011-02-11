#include "gscom.h"
#include <parser.h>
#include <serializer.h>
#include <QCryptographicHash>
//#include <QApplication>
#define CVERSION "20100831"
#define CLIENT "htmlshark"

gscom::gscom()
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    cookies = manager->cookieJar();
    currentaction = getPHP;
    manager->get(QNetworkRequest(QUrl(QString("http://") + GS_LISTEN)));
    phpSession = new QString("none");
    sessionKey = new QString("none");
    firstR = true;
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(
        QStringList() << "Online");
    addDebugMsg("You may now search for a song");
    //addProgressbar("test");
    //getSessionKey();
}

QStandardItemModel* gscom::getSongModel(QString song)
{
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(
        QStringList() << "Searching..");
    addDebugMsg("Fetching Song List...");

    if(currentaction != none)
    {
        addDebugMsg("Error: communication is busy Try again later");
        return model;
    }
    else
    {
        QString *token = getToken(getSearchResults);
        qDebug() << token->toAscii();
        QNetworkRequest request;
        request.setUrl(QUrl("http://listen.grooveshark.com/more.php?getSearchResults"));
        request.setHeader(request.ContentTypeHeader,QVariant("application/json"));
        QVariantMap jlist;
        QVariantMap header;
        //header.insert("uuid","DEA8E133-2080-F666-4B38-9465187B20A9");
        header.insert("session",phpSession->toUtf8());
        header.insert("client",CLIENT);
        //header.insert("clientRevision","20100412.09");
        header.insert("clientRevision",CVERSION);
        header.insert("privacy",0);
        header.insert("token",token->toAscii());
        jlist.insert("method","getSearchResults");
        jlist.insertMulti("header",header);
        QVariantMap param;
        param.insert("type","Songs");
        param.insert("query",song);
        jlist.insertMulti("parameters",param);
        QJson::Serializer *serializer = new QJson::Serializer();
        //qDebug() << serializer->serialize(jlist);
        manager->post(request,serializer->serialize(jlist));
        currentaction = getSearchResults;
    }

    return model;
}
QStandardItemModel* gscom::getArtistModel(QString song)
{
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(
        QStringList() << "Searching..");
    addDebugMsg("Fetching Song List...");

    if(currentaction != none)
    {
        addDebugMsg("Error: communication is busy Try again later");
        return model;
    }
    else
    {
        QString *token = getToken(getSearchResults);
        qDebug() << token->toAscii();
        QNetworkRequest request;
        request.setUrl(QUrl("http://listen.grooveshark.com/more.php?getSearchResults"));
        request.setHeader(request.ContentTypeHeader,QVariant("application/json"));
        QVariantMap jlist;
        QVariantMap header;
        //header.insert("uuid","DEA8E133-2080-F666-4B38-9465187B20A9");
        header.insert("session",phpSession->toUtf8());
        header.insert("client",CLIENT);
        header.insert("clientRevision",CVERSION);
        header.insert("token",token->toAscii());
        jlist.insert("method","getSearchResults");
        jlist.insertMulti("header",header);
        QVariantMap param;
        param.insert("type","Artists");
        param.insert("query",song.toAscii());
        jlist.insertMulti("parameters",param);
        QJson::Serializer *serializer = new QJson::Serializer();
        //qDebug() << serializer->serialize(jlist);
        manager->post(request,serializer->serialize(jlist));
        currentaction = getSearchResults;
    }

    return model;
}
QStandardItemModel* gscom::getAlbumModel(QString song)
{
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(
        QStringList() << "Searching..");
    addDebugMsg("Fetching Song List...");

    if(currentaction != none)
    {
        addDebugMsg("Error: communication is busy Try again later");
        return model;
    }
    else
    {
        QString *token = getToken(getSearchResults);
        qDebug() << token->toAscii();
        QNetworkRequest request;
        request.setUrl(QUrl("http://listen.grooveshark.com/more.php?getSearchResults"));
        request.setHeader(request.ContentTypeHeader,QVariant("application/json"));
        QVariantMap jlist;
        QVariantMap header;
        //header.insert("uuid","DEA8E133-2080-F666-4B38-9465187B20A9");
        header.insert("session",phpSession->toUtf8());
        header.insert("client",CLIENT);
        header.insert("clientRevision",CVERSION);
        header.insert("token",token->toAscii());
        jlist.insert("method","getSearchResults");
        jlist.insertMulti("header",header);
        QVariantMap param;
        param.insert("type","Albums");
        param.insert("query",song.toAscii());
        jlist.insertMulti("parameters",param);
        QJson::Serializer *serializer = new QJson::Serializer();
        //qDebug() << serializer->serialize(jlist);
        manager->post(request,serializer->serialize(jlist));
        currentaction = getSearchResults;
    }

    return model;
}
void gscom::replyFinished(QNetworkReply *reply)
{
    switch (currentaction)
    {
    case getTokenForForSong:
        {
            qDebug() << "Recieved a Token Packet!";
            QJson::Parser parser;
            bool ok;
            QByteArray array = reply->readAll();
            qDebug(array);
            QVariantMap result = parser.parse (array, &ok).toMap();
            if (!ok) {
              qFatal("An error occurred during parsing");
              return;
            }
            QVariantMap results = result["result"].toMap();
            this->songToken = results["Token"].toString();
            qDebug() << this->songToken;
            currentaction = none;
            reply->close();
        }
        break;
    case getStreamKeyFromSongIDEx:
        {
            qDebug() << "Recieved a Stream Packet";
            QJson::Parser parser;
            bool ok;
            QByteArray array = reply->readAll();
            qDebug(array);
            QVariantMap result = parser.parse (array, &ok).toMap();
            if (!ok) {
              qFatal("An error occurred during parsing");
              return;
            }
            QVariantMap results = result["result"].toMap();
            this->streamID = results["streamKey"].toString();
            this->sku = QUrl(QString("http://") + results["ip"].toString() + "/stream.php");
            //qDebug() << results;
            qDebug() << sku;
            currentaction = none;
            reply->close();
            emit sKeyFound();
        }
        break;
    case getPHP:
        {
            QList<QNetworkCookie> cookieList = cookies->cookiesForUrl(QUrl(QString("http://") + GS_LISTEN));
            foreach(QNetworkCookie cookie, cookieList)
            {
                if(cookie.name() == "PHPSESSID")
                {
                    phpSession = new QString(cookie.value());
                    qDebug() << QDateTime::currentDateTime();
                    qDebug() << cookie.expirationDate();
                }
            }
            reply->readAll();
            reply->close();
            qDebug() << phpSession->toAscii();
            firstR = false;
            currentaction = getCommunicationToken;
            getSessionKey();

        }
        break;
    case getCommunicationToken:
        {
            bool ok;
            QJson::Parser parser;
            QByteArray array = reply->readAll();
            qDebug(array);
            QVariantMap result = parser.parse(array,&ok).toMap();
            if(!ok)
                qDebug("Error parsing request");
            else
            {
                sessionKey = new QString(result["result"].toString());
                qDebug() << sessionKey->toAscii();
            }
            qDebug() << result;
            currentaction = none;
            reply->close();
            emit finishedSearch();
        }
        break;
    case(getSearchResults):
        {
            QJson::Parser parser;
            bool ok;
            QVariantMap result = parser.parse (reply->readAll(), &ok).toMap();
            if (!ok) {
              qFatal("An error occurred during parsing");
              return;
            }
            if(result.contains("fault"))
            {
                currentaction = getPHP;
                manager->get(QNetworkRequest(QUrl(QString("http://") + GS_LISTEN)));
                qDebug() << reply->readAll();
                qDebug() << result;
                reply->close();
                return;
            }
            model->clear();
            model->setHorizontalHeaderLabels(
                QStringList() << "Song"
                              << "Artist"
                              << "Song Id");


            foreach (QVariant plugin, result["result"].toMap()["Songs"].toList()) {
              QList<QStandardItem *> items;
              QVariantMap nestedMap = plugin.toMap();
              items.append(new QStandardItem(nestedMap["Name"].toString()));
              items.append(new QStandardItem(nestedMap["ArtistName"].toString()));
              items.append(new QStandardItem(nestedMap["SongID"].toString()));
              model->appendRow(items);
            }
            currentaction = none;
            reply->close();
            emit finishedSearch();
        }
        break;
    default:
        qDebug() << reply->readAll();
        reply->close();
        currentaction=none;
    }

}
QStandardItemModel* gscom::getModel()
{
    return model;
}
void gscom::addDebugMsg(QString debug)
{
    QList<QStringList> rows = QList<QStringList>()
        << (QStringList() << debug);
    foreach (QStringList row, rows) {
        QList<QStandardItem *> items;
        foreach (QString text, row)
            items.append(new QStandardItem(text));
        model->appendRow(items);
    }
    return;
}
void gscom::addProgressbar(QString debug)
{
    QList<QStringList> rows = QList<QStringList>()
        << (QStringList() << debug);
    foreach (QStringList row, rows) {
        QList<QStandardItem *> items;
        foreach (QString text, row)
        {
            QLinearGradient gradient(0,0,250,0);
            gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
            gradient.setColorAt(0.9, QColor::fromRgbF(0, 1, 0, 1));
            gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
            QBrush brush(Qt::red);
            QStandardItem *pBar = new QStandardItem(text);
            pBar->setBackground(brush);
            pBar->setSelectable(false);
            items.append(pBar);
        }
        model->appendRow(items);
    }
    return;
}
QString* gscom::getToken(gMETHOD meth)
{
    QCryptographicHash *hasher = new QCryptographicHash(QCryptographicHash::Sha1);
    //generate six random numbers
    QString rnum =  QString(qrand() %9 + 48)
                    + QString(qrand() %9 + 48)
                    + QString(qrand() %9 + 48)
                    + QString(qrand() %9 + 48)
                    + QString(qrand() %9 + 48)
                    + QString(qrand() %9 + 48);
    QString *data = new QString();
    QString *string = new QString();
    switch(meth)
    {
    case(getSearchResults):
        data->append("getSearchResults");
        break;
    case(getTokenForForSong):
        data->append("getTokenForForSong");
        break;
    case(getStreamKeyFromSongIDEx):
        data->append("getStreamKeyFromSongIDEx");
        break;
    default:
        data->append("getSearchResults");
    }
    string->append(data);
    string->append(":");
    string->append(sessionKey->toAscii());
    string->append(":quitStealinMahShit:");
    string->append(rnum);
    hasher->addData(string->toAscii());
    QString *rs = new QString();
    rs->append(rnum);
    rs->append(hasher->result().toHex());
    return rs;
}
void gscom::getSong(QString songid)
{
    if(currentaction != none)
    {
        return;
    }
    else
    {
        QString *token = getToken(getStreamKeyFromSongIDEx);
        qDebug() << token->toAscii();
        QNetworkRequest request;
        request.setUrl(QUrl("http://listen.grooveshark.com/more.php?getStreamKeyFromSongIDEx"));
        request.setHeader(request.ContentTypeHeader,QVariant("application/json"));
        QVariantMap jlist;
        QVariantMap header;
        QVariantMap country;
        country.insert("CC1","0");
        country.insert("CC3","0");
        country.insert("ID","223");
        country.insert("CC2","0");
        country.insert("CC4","1073741824");
        //header.insert("uuid","DEA8E133-2080-F666-4B38-9465187B20A9");
        header.insert("session",phpSession->toUtf8());
        header.insert("client","jsqueue");
        header.insert("clientRevision","20101012.37");
        header.insert("token",token->toAscii());
        header.insertMulti("country",country);
        jlist.insert("method","getStreamKeyFromSongIDEx");
        jlist.insertMulti("header",header);
        QVariantMap param;
        param.insertMulti("country",country);
        param.insert("mobile",false);
        param.insert("songID",songid.toAscii());
        param.insert("prefetch",false);
        jlist.insertMulti("parameters",param);
        QJson::Serializer *serializer = new QJson::Serializer();
        //qDebug() << serializer->serialize(jlist);
        manager->post(request,serializer->serialize(jlist));
        currentaction = getStreamKeyFromSongIDEx;
    }
    return;
}

void gscom::getSessionKey()
{
    QNetworkRequest request; // = new QNetworkRequest(QUrl("https://listen.grooveshark.com/service.php"));
    request.setUrl(QUrl("https://listen.grooveshark.com/more.php"));
    request.setHeader(request.ContentTypeHeader,QVariant("application/json"));
    QVariantMap jlist;
    QVariantMap header;
    //header.insert("uuid","DEA8E133-2080-F666-4B38-9465187B20A9");
    //header.insert("session",phpSession->toUtf8());
    header.insert("client",CLIENT);
    header.insert("clientRevision",CVERSION);
    jlist.insert("method","getCommunicationToken");
    jlist.insertMulti("header",header);
    QVariantMap param;
    QCryptographicHash *hasher = new QCryptographicHash(QCryptographicHash::Md5);
    hasher->addData(phpSession->toUtf8());
    param.insert("secretKey",hasher->result().toHex());
    jlist.insertMulti("parameters",param);
    QJson::Serializer *serializer = new QJson::Serializer();
    manager->post(request,serializer->serialize(jlist));
}
