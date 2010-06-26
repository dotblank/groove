#ifndef GROOVEPROGRESSBAR_H
#define GROOVEPROGRESSBAR_H

#include <QDialog>
#include <QtGui>
#include "qmaemo5rotator.h"

class grooveProgressBar : public QDialog
{
    Q_OBJECT
public:
    explicit grooveProgressBar(QWidget *parent = 0);
    void setMaximum(int maximum);
    void setValue(int position);
    int maximum();
    QMaemo5Rotator *rot;

signals:

public slots:

private:
    QProgressBar *bar;
    QHBoxLayout  *lay;
};

#endif // GROOVEPROGRESSBAR_H
