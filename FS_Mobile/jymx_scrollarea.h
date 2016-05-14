#ifndef JYMX_SCROLLAREA_H
#define JYMX_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>

namespace Ui {
    class jymx_ScrollArea;
}

class GetJymxCondtionThread;
class GetJymxListThread;

class jymx_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit jymx_ScrollArea(QWidget *parent = 0);
    ~jymx_ScrollArea();
    Ui::jymx_ScrollArea *ui;
    void refresh();
    void init();
    void getSearchCondition();
    void reset();

private slots:
    void on_btnSearch_clicked();

    void on_btnExport_clicked();

private:
    GetJymxCondtionThread *_getJymxCondtionThread;
    GetJymxListThread *_getJymxListThread;
};

//提取下拉框
class GetJymxCondtionThread : public  QThread
{
public:
    jymx_ScrollArea *_ref;
    GetJymxCondtionThread(jymx_ScrollArea *jfyb_ScrollArea_ptr);
protected:
    void run();
};

//提取列表
class GetJymxListThread : public  QThread
{
public:
    jymx_ScrollArea *_ref;
    GetJymxListThread(jymx_ScrollArea *jfyb_ScrollArea_ptr);
    QString currentCondition;
protected:
    void run();
};

#endif // JYMX_SCROLLAREA_H
