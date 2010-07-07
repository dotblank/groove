#include "groove.h"
#include <parser.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Groove");
    groove gs; //create Groove!
#ifdef Q_WS_MAEMO_5
    //setAttribute(Qt::WA_Maemo5AutoOrientation,true);
    //a.setAttribute(Qt::WA_Maemo5AutoOrientation,true);
    gs.showFullScreen();
#endif
#if defined(Q_WS_S60)
    gs.showMaximized();
#else
    gs.show();
#endif
    return a.exec();
}
