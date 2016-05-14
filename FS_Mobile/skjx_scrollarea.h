#ifndef SKJX_SCROLLAREA_H
#define SKJX_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>

namespace Ui {
    class skjx_ScrollArea;
}

class GetSkjxCondtionThread;
class GetSkjxListThread;

class skjx_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit skjx_ScrollArea(QWidget *parent = 0);
    ~skjx_ScrollArea();
    Ui::skjx_ScrollArea *ui;
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
    GetSkjxCondtionThread *_getSkjxCondtionThread;
    GetSkjxListThread *_getSkjxListThread;
};

//提取下拉框
class GetSkjxCondtionThread : public  QThread
{
public:
    skjx_ScrollArea *_ref;
    GetSkjxCondtionThread(skjx_ScrollArea *skjx_ScrollArea_ptr);
protected:
    void run();
};

//提取列表
class GetSkjxListThread : public  QThread
{
public:
    skjx_ScrollArea *_ref;
    GetSkjxListThread(skjx_ScrollArea *skjx_ScrollArea_ptr);
    QString currentCondition;
protected:
    void run();
};

#endif // SKJX_SCROLLAREA_H
