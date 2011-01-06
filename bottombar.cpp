#include "bottombar.h"
#include "ui_bottombar.h"


bottomBar::bottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bottomBar)
{
    ui->setupUi(this);
    main = new QGraphicsScene(0,0,this->width(),15);
    ui->graphicsView->setScene(main);
    ui->graphicsView->setSceneRect(0,0,this->width(),15);
    //ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
    main->setBackgroundBrush(this->palette().window());
    main->setSceneRect(0,0,this->width(),15);
    this->playbackProgress = main->addRect(0,0,this->width()/2,15,QPen(Qt::white),QBrush(Qt::white));
#ifndef Q_WS_MAEMO_5
    ui->stopButton->setIcon(QIcon::fromTheme("media-playback-stop"));
    ui->pauseB->setIcon(QIcon::fromTheme("media-playback-pause"));
    ui->nextB->setIcon(QIcon::fromTheme("media-skip-forward"));
    ui->backB->setIcon(QIcon::fromTheme("media-skip-backward"));
    ui->settingsB->setIcon(QIcon::fromTheme("document-properties"));

#endif
}

bottomBar::~bottomBar()
{
    delete ui;
}
void bottomBar::setPlaybackProgress(qint64 min,qint64 max)
{

    this->playbackProgress->setRect(0,0,((float)min/(float)max)*this->width(),15);
    //ui->graphicsView->update();
}

void bottomBar::on_nextB_clicked()
{
    emit this->nextB();
}
void bottomBar::on_pauseB_clicked()
{
    emit this->pause();
}

void bottomBar::on_addButton_clicked()
{
    emit this->addB();
}
void bottomBar::on_backB_clicked()
{
    emit this->back();
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
