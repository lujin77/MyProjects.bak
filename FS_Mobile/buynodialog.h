#ifndef BUYNODIALOG_H
#define BUYNODIALOG_H

#include <QDialog>
#include <QThread>
#include "ydxh_scrollarea.h"

namespace Ui {
    class BuyNoDialog;
}

class GetBuyNoConditionThread;

class BuyNoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyNoDialog(QWidget *parent = 0);
    ~BuyNoDialog();
    void init(QString No, QString price, QString NoSection);
    void reset();
    void getCondition();
    void submit();
    Ui::BuyNoDialog *ui;
    void unlockNo();

protected:
    void changeEvent(QEvent *e);

private slots:

    void on_btn_submit_clicked();

    void on_btn_close_clicked();

    void on_cbx_service_currentIndexChanged(const QString &arg1);

    void on_rdo_service_type_on_clicked();

    void on_rdo_service_type_off_clicked();

private:
    GetBuyNoConditionThread *_getBuyNoConditionThread;
    ydxh_ScrollArea *_ref_ydxh_ScrollArea;
};

//提取条件
class GetBuyNoConditionThread : public  QThread
{
public:
    BuyNoDialog *_ref;
    GetBuyNoConditionThread(BuyNoDialog *BuyNoDialog_ptr);
    QString NoSection;
protected:
    void run();
};

#endif // BUYNODIALOG_H
