#include "vkb.h"
#include "ui_vkb.h"
#include <QMouseEvent>
vkb::vkb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vkb)
{
    ui->setupUi(this);
}
void vkb::setText(QString s)
{
    ui->tBox->setText(s);
}
void vkb::closeEvent(QCloseEvent *)
{
    emit this->submitText(ui->tBox->text());
}

vkb::~vkb()
{
    delete ui;
}
void vkb::addText(QString s)
{
    ui->tBox->setText(ui->tBox->text().append(s));
}
void vkb::on_delB_clicked()
{
    QString a = ui->tBox->text();
    a.chop(1);
    ui->tBox->setText(a);
}
void vkb::on_spaceB_clicked()
{
    this->addText(" ");
}

void vkb::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void vkb::on_aB_clicked()
{
    this->addText("a");
}
void vkb::on_bB_clicked()
{
    this->addText("b");
}
void vkb::on_cB_clicked()
{
    this->addText("c");
}
void vkb::on_dB_clicked()
{
    this->addText("d");
}
void vkb::on_eB_clicked()
{
    this->addText("e");
}
void vkb::on_fB_clicked()
{
    this->addText("f");
}
void vkb::on_gB_clicked()
{
    this->addText("g");
}
void vkb::on_hB_clicked()
{
    this->addText("h");
}
void vkb::on_iB_clicked()
{
    this->addText("i");
}
void vkb::on_jB_clicked()
{
    this->addText("j");
}
void vkb::on_kB_clicked()
{
    this->addText("k");
}
void vkb::on_lB_clicked()
{
    this->addText("l");
}
void vkb::on_mB_clicked()
{
    this->addText("m");
}
void vkb::on_nB_clicked()
{
    this->addText("n");
}
void vkb::on_oB_clicked()
{
    this->addText("o");
}
void vkb::on_pB_clicked()
{
    this->addText("p");
}
void vkb::on_qB_clicked()
{
    this->addText("q");
}
void vkb::on_rB_clicked()
{
    this->addText("r");
}
void vkb::on_sB_clicked()
{
    this->addText("s");
}
void vkb::on_tB_clicked()
{
    this->addText("t");
}
void vkb::on_uB_clicked()
{
    this->addText("u");
}
void vkb::on_vB_clicked()
{
    this->addText("v");
}
void vkb::on_wB_clicked()
{
    this->addText("w");
}
void vkb::on_xB_clicked()
{
    this->addText("x");
}
void vkb::on_yB_clicked()
{
    this->addText("y");
}
void vkb::on_zB_clicked()
{
    this->addText("z");
}

