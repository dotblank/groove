#include "topbar.h"
#include "ui_topbar.h"

topBar::topBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::topBar)
{
    ui->setupUi(this);
    kb = NULL;
    ui->sBox->installEventFilter(this);
}

topBar::~topBar()
{
    delete ui;
}
void topBar::on_taskSwitch_clicked()
{
    emit this->changeTask();
}
void topBar::on_sButton_clicked()
{
    emit this->searchRequest(ui->sBox->text());
}
void topBar::on_closeButton_clicked()
{
    emit this->closeApp();
}

void topBar::changeEvent(QEvent *e)
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
void topBar::resizeEvent(QResizeEvent *e)
{
    if(e->type() == QEvent::Resize)
    {
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HILDON)
        if(((QWidget *)this->parent())->testAttribute(Qt::WA_Maemo5PortraitOrientation))
        {
            ui->sBox->setReadOnly(true);
            //ui->sBox->setText("Portrait");
        }
        else
            ui->sBox->setReadOnly(false);
#endif
    }
}

bool topBar::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->sBox && ui->sBox->isReadOnly() && e->type() == QEvent::MouseButtonRelease)
    {
        if(!kb)
        {
            this->kb = new vkb(this);
            connect(kb,SIGNAL(submitText(QString)),ui->sBox,SLOT(setText(QString)));
        }
        kb->setText(ui->sBox->text());
        kb->show();
    }
    else
        return QWidget::eventFilter(obj,e);
    return true;
}
