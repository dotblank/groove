#ifndef STREAMIO_H
#define STREAMIO_H
#include <QBuffer>
#include <QWidget>
#include <phonon>
#include "splayer.h"

class StreamIO : public Phonon::AbstractMediaStream
{
    Q_OBJECT

    /*
public:
    explicit StreamIO(Phonon::MediaSource *parent = 0);
    void setSizeOfStream(qint64);
    //qint64 bytesAvailable();
    //qint64 size();
    //bool isSequential();
signals:

public slots:
private:
    Phonon::MediaSource *internal;
    //qint64 readData(char * data, qint64 maxsize);*/
    friend class sPlayer;

};

#endif // STREAMIO_H
