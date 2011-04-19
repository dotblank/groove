#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSettings>

namespace Ui {
    class settings;
}

class settings : public QWidget
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::settings *ui;
    QSettings *config;

private slots:
    void on_buttonBox_accepted();
};

#endif // SETTINGS_H
