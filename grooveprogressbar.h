#ifndef GROOVEPROGRESSBAR_H
#define GROOVEPROGRESSBAR_H

#include <QDialog>
#include <QtGui>
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HILDON)
#include "qmaemo5rotator.h"
#endif
class grooveProgressBar : public QDialog
{
    Q_OBJECT
public:
    explicit grooveProgressBar(QWidget *parent = 0);
    void setMaximum(int maximum);
    void setValue(int position);
    int maximum();
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HILDON)
    QMaemo5Rotator *rot;
#endif

signals:

public slots:

private:
    QProgressBar *bar;
    QHBoxLayout  *lay;
};

#endif // GROOVEPROGRESSBAR_H
