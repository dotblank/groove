#include "grooveprogressbar.h"

grooveProgressBar::grooveProgressBar(QDialog *parent) :
    QDialog(parent)
{
    bar = new QProgressBar();
    bar->setMaximum(100);
    bar->setValue(0);
    lay = new QHBoxLayout();
    lay->addWidget(bar);
    this->setLayout(lay);
    this->setWindowTitle("Downloading /  Buffering");
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
