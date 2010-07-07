#include "bottombar.h"
#include "ui_bottombar.h"

bottomBar::bottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bottomBar)
{
    ui->setupUi(this);
}

bottomBar::~bottomBar()
{
    delete ui;
}
void bottomBar::on_addButton_clicked()
{
    emit this->addB();
}

void bottomBar::changeEvent(QEvent *e)
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
