#ifndef GSCOM_H
#define GSCOM_H
#include <QString>
#include <QStandardItemModel>
#include <QtNetwork>
//#include <parser.h>
#define GSPASS "**********"
#define GSIP "grooveshark.com"
#define GS_LISTEN "listen.grooveshark.com"
#define GS_GUTS "guts.grroveshark.com"
class gscom : public QObject
{
    Q_OBJECT;
public:
    QUrl sku;
    QString streamID;
    gscom();
    QStandardItemModel* getSongModel(QString song);
    QStandardItemModel* getArtistModel(QString artist);
    QStandardItemModel* getAlbumModel(QString Album);
    QStandardItemModel* getModel();
    void getSong(QString songid);


signals:
    void finishedSearch();
    void sKeyFound();

public slots:
    void replyFinished(QNetworkReply*);



private:
    enum gMETHOD {
        getCommunicationToken,
        getSearchResults,
        getStreamKeyFromSongIDEx,
        getPHP,
        none
    };
    gMETHOD currentaction;
    QString *sessionKey;
    void getSessionKey();
    QString* getStreamKey();
    QString* getToken(gMETHOD m);
    QStandardItemModel *model;
    QString *phpSession;
    QNetworkAccessManager *manager;
    QNetworkCookieJar *cookies;
    void addDebugMsg(QString debug);
    bool firstR;
    QByteArray *postdata;
};

#endif // GSCOM_H
