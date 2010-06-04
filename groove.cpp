#include "groove.h"



groove::groove(QWidget *parent) :
    QWidget(parent)
{
    mBar = new QMenuBar();
    //mBar->addAction("test");
    sMethod = new QPushButton("Song:");
    lineEdit = new QLineEdit("");
    player = new sPlayer();
    QHBoxLayout *layout = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout();
    button = new QPushButton("Search");
    QPushButton *dButton = new QPushButton("Play");
    resultView = new QTableView();
    QMenu *pushMenu = new QMenu();
    //showFullScreen();
    lineEdit->insert("");
    lineEdit->setDisabled(true);
    pushMenu->addAction("Song:");
    pushMenu->addAction("Artist:");
    pushMenu->addAction("Album:");

    //sMethod->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Maximum);
    sMethod->setMaximumWidth(sMethod->sizeHint().rwidth());
    sMethod->setMenu(pushMenu);
    model = new  QStandardItemModel();
    model->setHorizontalHeaderLabels(
        QStringList() << "Please wait for initialization"
                      /*<< "Artist"*/);
    resultView->setModel(model);
    resultView->verticalHeader()->hide();
    resultView->horizontalHeader()->setStretchLastSection(true);
    resultView->setSelectionBehavior(QAbstractItemView::SelectRows);
    resultView->setSelectionMode(QAbstractItemView::SingleSelection);
    resultView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resultView->setColumnHidden(2,true);
    resultView->setAutoScroll(false);

    layout->addWidget(sMethod);
    layout->addWidget(lineEdit);
    layout->addWidget(button);
    vlayout->addLayout(layout);
    vlayout->addWidget(resultView);
    vlayout->addWidget(dButton);
    vlayout->setMenuBar(mBar);
    setLayout(vlayout);
    setWindowTitle("GrooveShark");
    //Create New Grooveshark connection
    gs = new gscom();
    //Connections
    connect(button, SIGNAL(clicked()), this, SLOT(search()));
    connect(gs, SIGNAL(finishedSearch()), this, SLOT(finishedS()));
    connect(lineEdit,SIGNAL(returnPressed()),this, SLOT(search()));
    connect(pushMenu,SIGNAL(triggered(QAction*)),this,SLOT(changeS(QAction*)));
    connect(dButton,SIGNAL(clicked()),this, SLOT(play()));
    connect(gs,SIGNAL(sKeyFound()),this,SLOT(startP()));
}
void groove::search()
{
    if(!lineEdit->text().isEmpty())
    {
    if(lineEdit->isEnabled())
    {

        if(sMethod->text().compare("Song:")==0)
            resultView->setModel(gs->getSongModel(lineEdit->text()));
        else if(sMethod->text().compare("Artist:")==0)
            resultView->setModel(gs->getArtistModel(lineEdit->text()));
        else if(sMethod->text().compare("Album")==0)
            resultView->setModel(gs->getAlbumModel(lineEdit->text()));
        else
            return;


        button->setText("Stop");
        lineEdit->setDisabled(true);
    }
    else
    {
        resultView->setModel(model);
        button->setText("Search");
        resultView->setColumnWidth(0,resultView->viewport()->width()/2);
        resultView->setColumnWidth(1,resultView->viewport()->width()/2);
        lineEdit->setDisabled(false);
    }
    }
}
void groove::finishedS()
{
    model = gs->getModel();
    resultView->setModel(model);
    button->setText("Search");
    resultView->setColumnWidth(0,resultView->viewport()->width()/2);
    resultView->setColumnWidth(1,resultView->viewport()->width()/2);
    lineEdit->setDisabled(false);
    resultView->setColumnHidden(2,true);
}
void groove::changeS( QAction * action)
{
    sMethod->setText(action->text());
    sMethod->setMaximumWidth(sMethod->sizeHint().rwidth());
}
void groove::play()
{
    QModelIndexList selected = resultView->selectionModel()->selectedRows(0);
    if(!selected.isEmpty())
    {
        QStandardItem *item = model->item(selected.first().row(),2);
        if(item == 0)
            return;
        //gs->getSong();
        gs->getSong(item->text());
    }
    //selected.
    //if
}
void groove::startP()
{
    if(!gs->sku.isValid())
        return;
    player->~sPlayer();
    player = new sPlayer();
    player->play(gs->streamID,gs->sku);

}