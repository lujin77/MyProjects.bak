#ifndef JFYB_SCROLLAREA_H
#define JFYB_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>

namespace Ui {
    class jfyb_ScrollArea;
}

class GetJfybCondtionThread;
class GetJfybListThread;

class jfyb_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit jfyb_ScrollArea(QWidget *parent = 0);
    ~jfyb_ScrollArea();
    Ui::jfyb_ScrollArea *ui;
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
    GetJfybCondtionThread *_getJfybCondtionThread;
    GetJfybListThread *_getJfybListThread;
};

//提取下拉框
class GetJfybCondtionThread : public  QThread
{
public:
    jfyb_ScrollArea *_ref;
    GetJfybCondtionThread(jfyb_ScrollArea *jfyb_ScrollArea_ptr);
protected:
    void run();
};

//提取列表
class GetJfybListThread : public  QThread
{
public:
    jfyb_ScrollArea *_ref;
    GetJfybListThread(jfyb_ScrollArea *jfyb_ScrollArea_ptr);
    QString currentCondition;
protected:
    void run();
};

#endif // JFYB_SCROLLAREA_H
