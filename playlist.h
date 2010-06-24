#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QStandardItem>
#include <QBuffer>
#include <QNetworkReply>
#include <QList>
#include <QSignalMapper>
#include <gscom.h>
class playlist : public QObject
{
    Q_OBJECT
public:
    enum failType
    {
        none = 0,
        Aborted = 1,
        Other =2
    };
    explicit playlist(QObject *parent = 0);
    void addSong(QStandardItem item);
    void addSong(QString songid);
    void addsong(QString streamkey, QUrl server);
    QList<QStandardItem *> getPlaylist();
    void removeSong(int position);
    void getSong(int position);
    QIODevice * getBuffer(int position);
    bool isStream(int position);
    void markComplete(int position);
    void deleteSong(int position);
    void setGscom(gscom *comm);

signals:
    void downloadProgress(int position, qint64 d, qint64 t);
    void bufferReady(int position);
    void sFailure(int position,failType);
    void downloadComplete(int position);
    void freeze();
    void unfreeze();

public slots:
private slots:
    void downloadSlot(qint64 d, qint64 t);
    void downloadDone(int position);
    void skeyFound();
private:
    void beginDownload(int position);
    enum elementType
    {
        EStream = 1,
        EFile = 2,
    };

    struct songElement
    {
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
    int currentSkeyItem;
    QList<songElement *> *pList;
    QSignalMapper *mapper;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    int currentdownloaditem;
    gscom *gs;
    QTime startStreamT;
};

#endif // PLAYLIST_H
