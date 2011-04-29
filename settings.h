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
    void populate();
signals:
    void settingsChange(QString key, QVariant value);
    void closed();
public slots:
    void close();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::settings *ui;
    QSettings *config;
    void enableapplied();

private slots:
    void on_spinBox_valueChanged(int );
    void on_spinBox_2_valueChanged(int );
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
};

#endif // SETTINGS_H
