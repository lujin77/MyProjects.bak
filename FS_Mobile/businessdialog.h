#ifndef BUSINESSDIALOG_H
#define BUSINESSDIALOG_H

#include <QDialog>
#include <QThread>

namespace Ui {
    class BusinessDialog;
}

class GetYwblConditionThread;

class BusinessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BusinessDialog(QWidget *parent = 0);
    ~BusinessDialog();
    Ui::BusinessDialog *ui;
    void init(QString type, QString name);
    void submit();
    void reset();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_btn_reset_clicked();

    void on_btn_submit_clicked();

    void on_rdo_service_type_on_clicked();

    void on_rdo_service_type_off_clicked();

private:
    GetYwblConditionThread *_getYwblConditionThread;
    QString winType;
    QString businessName;
};

//提取下拉框
class GetYwblConditionThread : public  QThread
{
public:
    BusinessDialog *_ref;
    GetYwblConditionThread(BusinessDialog *BusinessDialog_ptr);
    QString type;
protected:
    void run();
};

#endif // BUSINESSDIALOG_H
