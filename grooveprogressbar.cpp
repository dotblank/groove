#include "grooveprogressbar.h"
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HILDON)
#include "qmaemo5rotator.h"
#endif
grooveProgressBar::grooveProgressBar(QWidget *parent) :
    QDialog(parent)
{
    bar = new QProgressBar();
    bar->setMaximum(100);
    bar->setValue(0);
    lay = new QHBoxLayout();
    lay->addWidget(bar);
    this->setLayout(lay);
    this->setWindowTitle("Downloading /  Buffering");
    //rot = new QMaemo5Rotator(QMaemo5Rotator::AutomaticBehavior,this);
}
void grooveProgressBar::setMaximum(int maximum)
{
    bar->setMaximum(maximum);
}
int grooveProgressBar::maximum()
{
   return bar->maximum();
}

void grooveProgressBar::setValue(int position)
{
    bar->setValue(position);
}
