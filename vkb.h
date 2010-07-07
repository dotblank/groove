#ifndef VKB_H
#define VKB_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
    class vkb;
}

class vkb : public QDialog
{
    Q_OBJECT

public:
    explicit vkb(QWidget *parent = 0);
    void setText(QString);

    ~vkb();
signals:
    void submitText(QString);
protected:
    void closeEvent(QCloseEvent *);
    void changeEvent(QEvent *e);
private slots:
    void on_aB_clicked();
    void on_bB_clicked();
    void on_cB_clicked();
    void on_dB_clicked();
    void on_eB_clicked();
    void on_fB_clicked();
    void on_gB_clicked();
    void on_hB_clicked();
    void on_iB_clicked();
    void on_jB_clicked();
    void on_kB_clicked();
    void on_lB_clicked();
    void on_mB_clicked();
    void on_nB_clicked();
    void on_oB_clicked();
    void on_pB_clicked();
    void on_qB_clicked();
    void on_rB_clicked();
    void on_sB_clicked();
    void on_tB_clicked();
    void on_uB_clicked();
    void on_vB_clicked();
    void on_wB_clicked();
    void on_xB_clicked();
    void on_yB_clicked();
    void on_zB_clicked();
    void on_delB_clicked();
    void on_spaceB_clicked();



private:
    Ui::vkb *ui;
    void addText(QString);
};

#endif // VKB_H
