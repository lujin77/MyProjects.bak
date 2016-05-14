#ifndef JFRB_SCROLLAREA_H
#define JFRB_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>

namespace Ui {
    class jfrb_ScrollArea;
}

class GetJfrbCondtionThread;
class GetJfrbListThread;

class jfrb_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit jfrb_ScrollArea(QWidget *parent = 0);
    ~jfrb_ScrollArea();
    Ui::jfrb_ScrollArea *ui;
    void refresh();
    void init();
    void getSearchCondition();
    void reset();

private slots:
    void on_btn_refresh_clicked();

    void on_btn_fx_clicked();

    void on_btn_cx_clicked();

    void on_btn_search_clicked();

    void on_btn_print_clicked();

private:
    GetJfrbCondtionThread *_getJfrbCondtionThread;
    GetJfrbListThread *_getJfrbListThread;

};

//提取下拉框
class GetJfrbCondtionThread : public  QThread
{
public:
    jfrb_ScrollArea *_ref;
    GetJfrbCondtionThread(jfrb_ScrollArea *jfrb_ScrollArea_ptr);
protected:
    void run();
};

//提取列表
class GetJfrbListThread : public  QThread
{
public:
    jfrb_ScrollArea *_ref;
    GetJfrbListThread(jfrb_ScrollArea *jfrb_ScrollArea_ptr);
    QString currentCondition;
protected:
    void run();
};

#endif // JFRB_SCROLLAREA_H
