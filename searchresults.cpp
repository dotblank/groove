#include "searchresults.h"
#include "ui_searchresults.h"

SearchResults::SearchResults(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchResults)
{
    ui->setupUi(this);
}

SearchResults::~SearchResults()
{
    delete ui;
}

void SearchResults::changeEvent(QEvent *e)
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
