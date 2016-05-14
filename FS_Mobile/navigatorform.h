#ifndef NAVIGATORFORM_H
#define NAVIGATORFORM_H

#include <QWidget>
#include <QResizeEvent>
#include <QThread>
#include <jf_scrollarea.h>
#include <jfrb_scrollarea.h>
#include <jfyb_scrollarea.h>
#include <ydxh_scrollarea.h>
#include <skcx_scrollarea.h>
#include <skjx_scrollarea.h>
#include <kcxk_scrollarea.h>
#include <tczfcx_scrollarea.h>
#include <ywbl_scrollarea.h>
#include <ywslcx_scrollarea.h>
#include <zhye_scrollarea.h>
#include <zhcz_scrollarea.h>
#include <xkkk_scrollarea.h>
#include <xgmm_scrollarea.h>
#include <yhxxxg_scrollarea.h>
#include <zxgg_scrollarea.h>
#include <gszh_scrollarea.h>
#include <jymx_scrollarea.h>
#include <kdcz_tabwidget.h>
#include <gmjp_scrollarea.h>
#include <klxs_tabwidget.h>
#include <drjytj_ScrollArea.h>
#include <dbfjs_scrollarea.h>
#include <newsalertdialog.h>
#include <yxcz_tabwidget.h>

namespace Ui {
    class NavigatorForm;
}

class NewsAlertThread;
class GetCompanyTelThread;

class NavigatorForm : public QWidget
{
    Q_OBJECT

public:
    explicit NavigatorForm(QWidget *parent = 0);
    ~NavigatorForm();
    Ui::NavigatorForm *ui;
    void creatSubFrame();
    void initSignalSlot();
    void reset();
    void testNewsAlert();
    void showNewsAlert();
    void hideNewsAlert();
    void init();

signals:
    void loggout();

public slots:
    void changeMainFrame(int index);
    void setMoney();
    void setName();
    void isShowNewsAlert();

protected:
    void resizeEvent(QResizeEvent *event);
    void resizeMainframe(int extraWidth);

private:
    NewsAlertThread *_newsAlertThread;
    GetCompanyTelThread *_getCompanyTelThread;

private slots:
    void on_btn_ydjf_clicked();

    void on_btn_jfrb_clicked();

    void on_btn_jfyb_clicked();

    void on_btn_skcx_clicked();

    void on_btn_ydxh_clicked();

    void on_btn_skjs_clicked();

    void on_btn_kcxk_clicked();

    void on_btn_tczfcx_clicked();

    void on_btn_ywsl_clicked();

    void on_btn_ywslcx_clicked();

    void on_btn_zhye_clicked();

    void on_btn_zhcz_clicked();

    void on_btn_xkkk_clicked();

    void on_btn_xgmm_clicked();

    void on_btn_yhxxxg_clicked();

    void on_btn_zxgg_clicked();

    void on_btn_gszh_clicked();

    void on_btn_drjjtj_clicked();

    void on_btn_gmjp_clicked();

    void on_btn_gmczk_clicked();

    void on_btn_drjymx_clicked();

    void on_btn_dbfjs_clicked();

    void on_btnLoggout_clicked();

    void on_btn_kdjf_clicked();

    void on_btn_yxcz_clicked();

    void on_btnMoney_clicked();

public:
    QImage top_image;
    jf_ScrollArea *jf_form;
    jfrb_ScrollArea *jfrb_form;
    jfyb_ScrollArea *jfyb_form;
    ydxh_ScrollArea *ydxh_form;
    skcx_ScrollArea *skcx_form;
    skjx_ScrollArea *skjx_form;
    kcxk_ScrollArea *kcxk_form;
    tczfcx_ScrollArea *tczfcx_form;
    ywbl_ScrollArea *ywbl_form;
    ywslcx_ScrollArea *ywslcx_form;
    zhye_ScrollArea *zhye_form;
    zhcz_ScrollArea *zhcz_form;
    xkkk_ScrollArea *xkkk_form;
    xgmm_ScrollArea *xgmm_form;
    yhxxxg_ScrollArea *yhxxxg_form;
    zxgg_ScrollArea *zxgg_form;
    gszh_ScrollArea *gszh_form;
    jymx_ScrollArea *jymx_form;
    kdcz_TabWidget *kdcz_form;
    gmjp_ScrollArea *gmjp_form;
    klxs_TabWidget *klxs_form;
    drjytj_ScrollArea *drjytj_form;
    dbfjs_ScrollArea *dbfjs_form;
    yxcz_TabWidget *yxcz_form;
    NewsAlertDialog *news_alert_dialog;

};

class NewsAlertThread : public  QThread
{
Q_OBJECT

public:
    NavigatorForm *_ref;
    NewsAlertThread(NavigatorForm *navigatorForm_ptr);
    bool isNetworkConnected;
signals:
    void getDataComplete();
protected:
    void run();
private:
    int waitTime;

};

//提取账户信息thread
class GetCompanyTelThread : public  QThread
{
public:
    NavigatorForm *_ref;
    GetCompanyTelThread(NavigatorForm *navigatorForm_ptr);
protected:
    void run();
};

#endif // NAVIGATORFORM_H
