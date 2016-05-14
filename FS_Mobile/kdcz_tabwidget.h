#ifndef KDCZ_TABWIDGET_H
#define KDCZ_TABWIDGET_H

#include <QTabWidget>
#include <QThread>

namespace Ui {
    class kdcz_TabWidget;
}

class GetKdInfoThread;
class GetKdczCurrThread;
class GetKdczCondtionThread;
class GetKdczRbListThread;
class GetKdczYbListThread;

class GetGhczCurrThread;
class GetGhczCondtionThread;
class GetGhczRbListThread;
class GetGhczYbListThread;

class kdcz_TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit kdcz_TabWidget(QWidget *parent = 0);
    ~kdcz_TabWidget();
    Ui::kdcz_TabWidget *ui;
    //宽带
    void resetAll();
    void initAll();
    void resetJF();
    void initJF();
    void refreshJF();
    void resetRB();
    void initRB();
    void refreshRB();
    void resetYB();
    void initYB();
    void refreshYB();
    void submit();
    void getSearchCondition();
    void getKdInfo();
    //公话
    void resetJF2();
    void initJF2();
    void refreshJF2();
    void resetRB2();
    void initRB2();
    void refreshRB2();
    void resetYB2();
    void initYB2();
    void refreshYB2();
    void submit2();
    void getSearchCondition2();

protected:
    void keyPressEvent(QKeyEvent *event);
    void changeEvent(QEvent *e);

signals:
    void updateMoney();

private slots:
    void on_btn_submit_clicked();

    void on_btn_reset_clicked();

    void on_btn_refresh_clicked();

    void on_btn_search_rb_clicked();

    void on_btn_refresh_rb_clicked();

    void on_btn_search_yb_clicked();

    void on_btn_refresh_yb_clicked();

    void on_btn_print_yb_clicked();

    void on_btn_print_rb_clicked();

    void on_btn_print_clicked();

    void on_btn_submit_tel_clicked();

    void on_btn_reset_tel_clicked();

    void on_btn_refresh_tel_clicked();

    void on_btn_search_rb_tel_clicked();

    void on_btn_refresh_rb_tel_clicked();

    void on_btn_search_yb_2_clicked();

    void on_btn_refresh_yb_tel_clicked();

    void on_btn_print_yb_tel_clicked();

    void on_btn_print_rb_tel_clicked();

    void on_btn_print_tel_clicked();

    void on_txi_internetAccount_textChanged(const QString &arg1);

    void on_txi_money_textChanged(const QString &arg1);

    void on_txi_telAccount_textChanged(const QString &arg1);

    void on_txi_money_tel_textChanged(const QString &arg1);

    void on_btn_search_kd_clicked();

    void on_txi_internetAccount_lostFocus();

    void on_btn_kd_fx_clicked();

    void on_btnPayWithList_clicked();

private:
    GetKdInfoThread *_getKdInfoThread;
    GetKdczCurrThread *_getKdczCurrThread;
    GetKdczCondtionThread *_getKdczCondtionThread;
    GetKdczRbListThread *_getKdczRbListThread;
    GetKdczYbListThread *_getKdczYbListThread;

    GetGhczCurrThread *_getGhczCurrThread;
    GetGhczCondtionThread *_getGhczCondtionThread;
    GetGhczRbListThread *_getGhczRbListThread;
    GetGhczYbListThread *_getGhczYbListThread;

    int _kd_account_size;
    int _kd_money_size;
    int _gh_account_size;
    int _gh_money_size;
};

//提取提取宽带详细信息
class GetKdInfoThread : public  QThread
{
public:
    kdcz_TabWidget *_ref;
    GetKdInfoThread(kdcz_TabWidget *kdcz_TabWidget_ptr);
protected:
    void run();
};

//提取最新宽带充值记录
class GetKdczCurrThread : public  QThread
{
public:
    kdcz_TabWidget *_ref;
    GetKdczCurrThread(kdcz_TabWidget *kdcz_TabWidget_ptr);
protected:
    void run();
};

//提取下拉框
class GetKdczCondtionThread : public  QThread
{
public:
    kdcz_TabWidget *_ref;
    GetKdczCondtionThread(kdcz_TabWidget *kdcz_TabWidget_ptr);
protected:
    void run();
};

//提取列表
class GetKdczRbListThread : public  QThread
{
public:
    kdcz_TabWidget *_ref;
    GetKdczRbListThread(kdcz_TabWidget *kdcz_TabWidget_ptr);
    QString currentCondition;
protected:
    void run();
};

//提取列表
class GetKdczYbListThread : public  QThread
{
public:
    kdcz_TabWidget *_ref;
    GetKdczYbListThread(kdcz_TabWidget *kdcz_TabWidget_ptr);
    QString currentCondition;
protected:
    void run();
};

//提取最新公话充值记录
class GetGhczCurrThread : public  QThread
{
    Q_OBJECT

public:
    kdcz_TabWidget *_ref;
    GetGhczCurrThread(kdcz_TabWidget *kdcz_TabWidget_ptr);
protected:
    void run();
};

//提取下拉框
class GetGhczCondtionThread : public  QThread
{
public:
    kdcz_TabWidget *_ref;
    GetGhczCondtionThread(kdcz_TabWidget *kdcz_TabWidget_ptr);
protected:
    void run();
};

//提取列表
class GetGhczRbListThread : public  QThread
{
public:
    kdcz_TabWidget *_ref;
    GetGhczRbListThread(kdcz_TabWidget *kdcz_TabWidget_ptr);
    QString currentCondition;
protected:
    void run();
};

//提取列表
class GetGhczYbListThread : public  QThread
{
public:
    kdcz_TabWidget *_ref;
    GetGhczYbListThread(kdcz_TabWidget *kdcz_TabWidget_ptr);
    QString currentCondition;
protected:
    void run();
};

#endif // KDCZ_TABWIDGET_H
