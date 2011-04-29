#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QStandardItem>
#include <QBuffer>
#include <QNetworkReply>
#include <QList>
#include <QSignalMapper>
#include <gscom.h>
class playlist : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum elementType
    {
        EStream = 1,
        EFile = 2,
    };
    enum failType
    {
        none = 0,
        Aborted = 1,
        Other =2
    };
    //this Enum MUST BE sequantial
    //And when changed must update the length
#define PLAYLISTENUMS 9
    enum coulmnStruct
    {
        sPlaying,
        sName,
        sID,
        sKey,
        sURL,
        sBuff,
        sDownloaded,
        sPlayed,
        sReady
    };

    struct songElement
    {
        QString *name;
        QString *songId;
        QString *streamkey;
        QUrl *server;
        QBuffer *buffer;
        QIODevice *data;
        elementType type;
        bool downloaded;
        bool played;
        bool bufferready;
    };
    int prefetch;
    QList<songElement *>* getList();
    explicit playlist(QObject *parent = 0);
    int addSong(QStandardItem *item,QString name);
    void removeSong(int position);
    void getSong(int position);
    QIODevice * getBuffer(int position);
    bool isStream(int position);
    void markPlayed(int position);
    void deleteSong(int position);
    void setGscom(gscom *comm);
    void freeMemory(int position);
    int currentplaying();
    void setCurrentPlaying(int position);
    bool bReady(int b);
    int findFirstNotPlayed();
    void beginDownload(int position);
    bool existAt(int position);

    //Implemented virtual classes for Model View
    QVariant data(const QModelIndex &index, int role) const;
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;

signals:
    void downloadProgress(int position, qint64 d, qint64 t);
    void bufferReady(int position);
    void sFailure(int position,failType);
    void downloadComplete(int position);
    void freeze(bool);
    //void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void rowsInserted ( const QModelIndex & parent, int start, int end );

public slots:
    void setSettings(QString key, QVariant Val);
private slots:
    void downloadSlot(qint64 d, qint64 t);
    void networkReplyFinish();
    void downloadDone(int position);
    void skeyFound();
    void setBufferRdy(int b);
    void getNError(QNetworkReply::NetworkError);
private:
    int currentplayingitem;
    int currentSkeyItem;
    QList<songElement *> *pList;
    QSignalMapper *mapper;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    int currentdownloaditem;
    gscom *gs;
    QTime startStreamT;
    QVariant *icon;
    QVariant *invalid;
    double bufferpcnt;

};

#endif // PLAYLIST_H
