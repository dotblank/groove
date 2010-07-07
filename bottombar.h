#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>

namespace Ui {
    class bottomBar;
}

class bottomBar : public QWidget
{
    Q_OBJECT

public:
    explicit bottomBar(QWidget *parent = 0);
    ~bottomBar();
signals:
    void addB();
protected:
    void changeEvent(QEvent *e);
private slots:
    void on_addButton_clicked();

private:
    Ui::bottomBar *ui;
};

#endif // BOTTOMBAR_H
