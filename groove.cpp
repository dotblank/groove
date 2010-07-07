#include "groove.h"
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HILDON)
#include "qmaemo5rotator.h"
#endif
#include <QtDBus>
#include "bottombar.h"

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
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    button = new QPushButton("Search");
    QPushButton *dButton = new QPushButton("Queue");
    QPushButton *stopButton = new QPushButton("Pause");
    QPushButton *moreButton = new QPushButton("...");
    QPushButton *nextB = new QPushButton("->");
    topBar *ok = new topBar(this);
    resultView = new QTableView();
    QMenu *pushMenu = new QMenu();
    //showFullScreen();
    lineEdit->insert("");
    lineEdit->setDisabled(true);
    pushMenu->addAction("Song:");
    //pushMenu->addAction("Artist:");
    //pushMenu->addAction("Album:");
    pd = new grooveProgressBar(this);
    pd->hide();
    QMenu *moreAction = new QMenu();
    //moreAction->addAction("Playlist");
    connect(moreAction->addAction("Play Now"),SIGNAL(triggered()),this,SLOT(play()));
    connect(moreAction->addAction("Show download Progress"),SIGNAL(triggered()),pd,SLOT(show()));
    moreButton->setMenu(moreAction);

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
    resultView->setColumnHidden(3,true);
    resultView->setAutoScroll(false);
    /*QPalette pal = resultView->palette();
    pal.setBrush(QPalette::Highlight,QBrush(Qt::transparent,Qt::NoBrush));
    resultView->setPalette(pal);*/
    portrait = false;
    layout->addWidget(sMethod);
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HILDON)
    rot = new QMaemo5Rotator(QMaemo5Rotator::AutomaticBehavior,this);
#endif
    //this->setAttribute(Qt::WA_Maemo5AutoOrientation);
    layout->addWidget(lineEdit);
    layout->addWidget(button);
    vlayout->addWidget(ok);
    //vlayout->addLayout(layout);
    vlayout->addWidget(resultView);
    //vlayout->addLayout(bottomLayout);
    bottomBar *bBar = new bottomBar();
    vlayout->addWidget(bBar);
    vlayout->setSpacing(0);
    bottomLayout->addWidget(dButton);
    bottomLayout->addWidget(stopButton);
    bottomLayout->addWidget(nextB);
    bottomLayout->addWidget(moreButton);
    vlayout->setMenuBar(mBar);
    vlayout->setContentsMargins(QMargins());
    setLayout(vlayout);
    setWindowTitle("Groove");
    //Create New Grooveshark connection
    gs = new gscom();
    //Connections
    connect(button, SIGNAL(clicked()), this, SLOT(search()));
    connect(gs, SIGNAL(finishedSearch()), this, SLOT(finishedS()));
    connect(lineEdit,SIGNAL(returnPressed()),this, SLOT(search()));
    connect(pushMenu,SIGNAL(triggered(QAction*)),this,SLOT(changeS(QAction*)));
    connect(dButton,SIGNAL(clicked()),this, SLOT(addSongPlaylist()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stop()));
    connect(moreButton,SIGNAL(clicked()),this,SLOT(moreB()));
    //connect(rotator,SIGNAL(orientationChanged(Orientation)),this,SLOT(orientationChanged()));
    pl = new playlist();
    pl->setGscom(gs);
    player->setPlaylist(pl);
    connect(pl,SIGNAL(downloadProgress(int,qint64,qint64)),this,SLOT(progressUpdate(int,qint64,qint64)));
    connect(pl,SIGNAL(bufferReady(int)),pd,SLOT(close()));
    connect(pl,SIGNAL(freeze(bool)),resultView,SLOT(setDisabled(bool)));
    connect(pl,SIGNAL(freeze(bool)),pushMenu,SLOT(setDisabled(bool)));
    connect(pl,SIGNAL(freeze(bool)),dButton,SLOT(setDisabled(bool)));
    connect(nextB,SIGNAL(clicked()),player,SLOT(playNext()));
    connect(ok,SIGNAL(changeTask()),this,SLOT(showOthers()));
    connect(ok,SIGNAL(searchRequest(QString)),this,SLOT(performSearch(QString)));
    connect(ok,SIGNAL(closeApp()),this,SLOT(close()));
    connect(bBar,SIGNAL(addB()),this,SLOT(addSongPlaylist()));
}
void groove::performSearch(QString s)
{
    qDebug() << s;
    resultView->setModel(gs->getSongModel(s));
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
void groove::showOthers()
{
    QDBusConnection c = QDBusConnection::sessionBus();
    QDBusMessage m = QDBusMessage::createSignal("/", "com.nokia.hildon_desktop", "exit_app_view");
    c.send(m);
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
        player->play(pl->addSong(item));
        pd->setMaximum(100);
        pd->setValue(0);
        pd->show();
    }
    //selected.
    //if
}
void groove::addSongPlaylist()
{
    QModelIndexList selected = resultView->selectionModel()->selectedRows(0);
    if(!selected.isEmpty())
    {
        QStandardItem *item = model->item(selected.first().row(),2);
        if(item == 0)
            return;
        //gs->getSong();
        if(pl->currentplaying() == -1)
        {
            player->play(pl->addSong(item));
        }
        else
            pl->addSong(item);
        pd->setMaximum(100);
        pd->setValue(0);
        pd->show();
        model->item(selected.first().row(),1)->setText("Added to Playlist");;
    }
}

void groove::stop()
{
    player->pause();
}
void groove::moreB()
{
    qDebug() << "He pressed the button";
}
void groove::progressUpdate(int p, qint64 d, qint64 t)
{
    //if(!pd->isHidden())
    //{


        pd->setMaximum(t);
        pd->setValue(d);
    //}
}

void groove::orientationChanged()
{
#ifdef Q_WS_MAEMO_5
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    if (screenGeometry.width() > screenGeometry.height())
        portrait = false;
    else
        portrait = true;
#endif
}
