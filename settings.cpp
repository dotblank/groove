#include "settings.h"
#include "ui_settings.h"


settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    config = new QSettings("Maemo.org","Groove");
    if(config->value("buffer-pcnt").isNull())
        config->setValue("buffer-pcnt",5);
    if(config->value("playlist-precache").isNull())
        config->setValue("playlist-precache",3);
    ui->setupUi(this);
    ui->spinBox->setValue(config->value("buffer-pcnt").toInt());
    ui->spinBox_2->setValue(config->value("playlist-precache").toInt());
    config->sync();
}

settings::~settings()
{
    delete ui;
}
void settings::close()
{
    QWidget::close();
    emit this->closed();
}
void settings::populate()
{
    emit this->settingsChange("buffer-percentage",ui->spinBox->value());
    emit this->settingsChange("playlist-precache",ui->spinBox_2->value());
}
void settings::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void settings::on_pushButton_clicked()
{
    config->setValue("buffer-pcnt",ui->spinBox->value());
    config->setValue("playlist-precache",ui->spinBox_2->value());
    config->sync();
    populate();
    ui->pushButton->setText("Applied");
    ui->pushButton->setEnabled(false);

    //ui->pushButton
    //this->close();
}

void settings::on_pushButton_3_clicked()
{
    //restore values from configuration
    ui->spinBox->setValue(config->value("buffer-pcnt").toInt());
    ui->spinBox_2->setValue(config->value("playlist-precache").toInt());
    ui->pushButton->setEnabled(false);
    //populate();
}

void settings::on_pushButton_2_clicked()
{
    ui->spinBox->setValue(5);
    ui->spinBox_2->setValue(3);
    //populate();
}
void settings::enableapplied()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton->setText("Apply");
}

void settings::on_spinBox_valueChanged(int )
{
    enableapplied();
}
void settings::on_spinBox_2_valueChanged(int )
{
    enableapplied();
}
