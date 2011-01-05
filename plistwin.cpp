#include "plistwin.h"
#include <QStandardItemModel>

pListWin::pListWin(QWidget *parent) :
    QWidget(parent)
{
    pview = new QTableView();
    QVBoxLayout *vlay = new QVBoxLayout();
    this->setLayout(vlay);
    vlay->addWidget(pview);
}
bool pListWin::setPlaylist(playlist *p)
{
    if(p==0)
        return false;
    plist = p->getList();
    return true;
}
void pListWin::updateList()
{
    if(!plist)
        return;
    if(!model)
        model = new QStandardItemModel(0,1);
    for(int i = 0; i < plist->count(); i++)
    {
        model->appendRow(new QStandardItem("test"));
    }
    pview->setModel(model);

}

