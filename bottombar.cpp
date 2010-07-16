#include "bottombar.h"
#include "ui_bottombar.h"

bottomBar::bottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bottomBar)
{
    ui->setupUi(this);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    QGraphicsScene *main = new QGraphicsScene(0,0,screenGeometry.width(),15);
    ui->graphicsView->setScene(main);
    ui->graphicsView->setSceneRect(0,0,screenGeometry.width(),15);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
    main->setBackgroundBrush(this->palette().window());
    main->setSceneRect(0,0,screenGeometry.width(),15);
    main->addRect(0,0,screenGeometry.width()/2,15,QPen(Qt::white),QBrush(Qt::white));
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
