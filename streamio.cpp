#include "streamio.h"
/*
StreamIO::StreamIO(Phonon::MediaSource *parent) :
    Phonon::MediaSource(parent)
{
    internal = parent;
}
void StreamIO::setSizeOfStream(qint64 s)
{
    internal->stream()->setStreamSize(s);
}
/*qint64 StreamIO::size()
{
    return sized;
}
qint64 StreamIO::bytesAvailable()
{
    return this->size();
}
bool StreamIO::isSequential()
{
    return true;
}/*
qint64 StreamIO::readData(char* data, qint64 maxsize)
{
    internal->data().at(rpos);
    data = this->data().at(rpos);
    rpos += 1;
    return 1;
}

*/
