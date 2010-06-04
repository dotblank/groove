#include "groove.h"
#include <parser.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Groove");
    groove gs;
#if defined(Q_WS_S60)
    gs.showMaximized();
#else
    gs.show();
#endif
    return a.exec();
}
