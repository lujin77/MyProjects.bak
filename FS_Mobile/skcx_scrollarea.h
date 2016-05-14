#ifndef SKCX_SCROLLAREA_H
#define SKCX_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>

namespace Ui {
    class skcx_ScrollArea;
}

class GetSkcxCondtionThread;
class GetSkcxListThread;

class skcx_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit skcx_ScrollArea(QWidget *parent = 0);
    ~skcx_ScrollArea();
    Ui::skcx_ScrollArea *ui;
    void refresh();
    void init();
    void getSearchCondition();
    void reset();
    void printPayment(QString shop_name, QString tel, QString location, QString name, QString brand,
               QString before_money, QString pay_money, QString after_money, QString state, QString datetime);

private slots:
    void on_btn_search_clicked();

    void on_btn_refresh_clicked();

    void on_btn_print_clicked();

private:
    GetSkcxCondtionThread *_getSkcxCondtionThread;
    GetSkcxListThread *_getSkcxListThread;
};

//提取下拉框
class GetSkcxCondtionThread : public  QThread
{
public:
    skcx_ScrollArea *_ref;
    GetSkcxCondtionThread(skcx_ScrollArea *skcx_ScrollArea_ptr);
protected:
    void run();
};

//提取列表
class GetSkcxListThread : public  QThread
{
public:
    skcx_ScrollArea *_ref;
    GetSkcxListThread(skcx_ScrollArea *skcx_ScrollArea_ptr);
    QString currentCondition;
protected:
    void run();
};

#endif // SKCX_SCROLLAREA_H
