#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QStandardItem>

class playlist : public QObject
{
    Q_OBJECT
public:
    explicit playlist(QObject *parent = 0);
    void addSong(QStandardItem item);
    QList<QStandardItem *> getPlaylist();
    void removeSong(int position);
    void getSong(int position);


signals:

public slots:

};

#endif // PLAYLIST_H
