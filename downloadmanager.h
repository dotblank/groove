#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>

class downloadmanager : public QObject
{
    Q_OBJECT
public:
    explicit downloadmanager(QObject *parent = 0);
    explicit downloadmanager(QString songid,bool start = true,QObject *parent = 0);
    void setSong(QString songid);
    void startDownload();
    void stopDownload();

signals:

public slots:

};

#endif // DOWNLOADMANAGER_H
