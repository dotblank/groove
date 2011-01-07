#include "pwin.h"
#include "ui_pwin.h"

pWin::pWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pWin)
{
    ui->setupUi(this);
}

pWin::~pWin()
{
    delete ui;
}
void pWin::addSong(QString name)
{
    ui->listWidget->addItem(name);
}
