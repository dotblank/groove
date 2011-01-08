#include "pwin.h"
#include "playlist.h"
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
void pWin::setModel(QAbstractItemModel *m)
{
    ui->tabv->setModel(m);
    //By Default hide all columns
    for(int i = 0; i < PLAYLISTENUMS; i++)
    {
        ui->tabv->hideColumn(i);
    }
    //Only show the song name column
    ui->tabv->showColumn(playlist::sName);
}
