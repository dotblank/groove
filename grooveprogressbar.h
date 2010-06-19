#ifndef GROOVEPROGRESSBAR_H
#define GROOVEPROGRESSBAR_H

#include <QDialog>
#include <QtGui>

class grooveProgressBar : public QDialog
{
    Q_OBJECT
public:
    explicit grooveProgressBar(QDialog *parent = 0);
    void setMaximum(int maximum);
    void setValue(int position);
    int maximum();

signals:

public slots:

private:
    QProgressBar *bar;
    QHBoxLayout  *lay;
};

#endif // GROOVEPROGRESSBAR_H
