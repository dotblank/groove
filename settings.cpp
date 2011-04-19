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
        config->setValue("playlist-precache",1);
    ui->setupUi(this);
    ui->spinBox->setValue(config->value("buffer-pcnt").toInt());
    ui->spinBox_2->setValue(config->value("playlist-precache").toInt());
    config->sync();
}

settings::~settings()
{
    delete ui;
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

void settings::on_buttonBox_accepted()
{
    config->setValue("buffer-pcnt",ui->spinBox->value());
    config->setValue("playlist-precache",ui->spinBox_2->value());
    config->sync();
    this->close();
}
