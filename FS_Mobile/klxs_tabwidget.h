#ifndef KLXS_TABWIDGET_H
#define KLXS_TABWIDGET_H

#include <QTabWidget>

namespace Ui {
    class klxs_TabWidget;
}

class GetKlxsListThread;
class GetKlxsCxCondtionThread;
class GetKlxsCxListThread;

class klxs_TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit klxs_TabWidget(QWidget *parent = 0);
    ~klxs_TabWidget();
    Ui::klxs_TabWidget *ui;
    QStringList arrCardListTx;
    QStringList arrCardListYx;
    QStringList arrCardListQt;
    void refreshAll();
    void refreshCardList();
    void refresh();
    void refreshCx();
    void init();
    void getSearchCondition();
    void resetAll();
    void resetCardList();
    void reset();
    void resetCx();
    void printKlxs();

signals:
    void updateMoney();

protected:
    void changeEvent(QEvent *e);

private slots:

    void on_btn_print_klsx_clicked();

    void on_btn_search_cx_clicked();

    void on_btn_refresh_cx_clicked();

    void on_tableWidget_cardlist_clicked(const QModelIndex &index);

    void on_cbx_card_type_currentIndexChanged(const QString &arg1);

    void on_rdo_tx_clicked();

    void on_rdo_yx_clicked();

    void on_rdo_qt_clicked();

    void on_btn_refresh_clicked();

private:
    GetKlxsListThread *_getKlxsListThread;
    GetKlxsCxCondtionThread *_getKlxsCxCondtionThread;
    GetKlxsCxListThread *_getKlxsCxListThread;

};

//提取卡类销售查询列表
class GetKlxsListThread : public  QThread
{
public:
    klxs_TabWidget *_ref;
    GetKlxsListThread(klxs_TabWidget *klxs_TabWidget_ptr);
protected:
    void run();
};


//提取下拉框
class GetKlxsCxCondtionThread : public  QThread
{
public:
    klxs_TabWidget *_ref;
    GetKlxsCxCondtionThread(klxs_TabWidget *klxs_TabWidget_ptr);
protected:
    void run();
};

//提取卡类销售查询列表
class GetKlxsCxListThread : public  QThread
{
public:
    klxs_TabWidget *_ref;
    GetKlxsCxListThread(klxs_TabWidget *klxs_TabWidget_ptr);
    QString currentCondition;
protected:
    void run();
};


#endif // KLXS_TABWIDGET_H
