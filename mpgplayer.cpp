#include "mpgplayer.h"
#include "pulse/simple.h"
#include <QFile>
mpgplayer::mpgplayer(QObject *parent) :
    QThread(parent)
{
    net = TWait;
    playing=false;


}
void mpgplayer::run()
{
    if(mpg123_init() != MPG123_OK)
        qDebug("Error initilizing mpg123");
    const char **test = mpg123_supported_decoders();
    int error;
    mpg123_handle *mh = mpg123_new(test[0],&error);
    if(!mpg123_feature(MPG123_FEATURE_DECODE_LAYER3))
    {
        qDebug("You do not seem to have mp3 decoding support");
        return;
    }
    mpg123_format_none(mh);
    if(mpg123_format(mh,samplerate,MPG123_STEREO,MPG123_ENC_SIGNED_16)!=MPG123_OK)
        qDebug("Error in initilizing format decoder");
    qDebug(test[0]);
    mpg123_open(mh,"/home/eli/Projects/groove-evan/Animal.mp3");
    net = TData;
    pa_simple *s;
    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16NE;
    ss.rate = samplerate;
    ss.channels = 2;
    s =pa_simple_new(NULL,"Groove",PA_STREAM_PLAYBACK ,NULL,"Music",&ss,NULL,NULL,NULL);

    unsigned char bytes[1024];
    size_t bsize = 1024;
    size_t done = 0;
    bool stop = false;
    playing=true;
    while(!stop)
    {
        switch(net)
        {
        case TWait: usleep(100); break;
        case TData:
            if(mpg123_read(mh,bytes,bsize,&done)==MPG123_DONE)
            {
                net=TFinish;
            }
            pa_simple_write(s,bytes,done,&error);
            break;
        case TAbort:
            stop = true;
            break;
        case TFinish:
            pa_simple_drain(s,&error);
            stop = true;
            break;
        default: break;
        }
    }
    qDebug("Finsihed playback");
    pa_simple_free(s);

    mpg123_exit();
}

void mpgplayer::setPlaylist(playlist *playList)
{
    this->pl = playList;
    connect(pl,SIGNAL(bufferReady(int)),this,SLOT(start(int)));
    connect(pl,SIGNAL(downloadProgress(int,qint64,qint64)),this,SLOT(putb(int,qint64,qint64)));
    //connect(pl,SIGNAL(downloadComplete(int)),this,SLOT(start(int)));

}
void mpgplayer::markComplete()
{

}
void mpgplayer::updatePlayPosition(qint64 time)
{
    //qDebug() << time << ":" << media->totalTime();
}

void mpgplayer::pause()
{
    if(playing)
        net = TWait;
    else
        net = TData;
    playing = !playing;
}
void mpgplayer::playNext()
{

}

mpgplayer::~mpgplayer()
{

}
void mpgplayer::back()
{

}

void mpgplayer::abortDownload()
{
    //pd->hide();
    //reply->abort();
}

void mpgplayer::play()
{

}
void mpgplayer::play(int p)
{

}

void mpgplayer::stop()
{


}

void mpgplayer::putb(int p, qint64 b, qint64 t)
{
    //qDebug() << "Download: " << b << "Total: " << t;
    if(p == pl->currentplaying())
    {
        if(pl->bReady(p))
        {
        }
    }
}
