#ifndef YWSLCX_SCROLLAREA_H
#define YWSLCX_SCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class ywslcx_ScrollArea;
}

class GetYwblcxCondtionThread;
class GetYwblcxListThread;

class ywslcx_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit ywslcx_ScrollArea(QWidget *parent = 0);
    ~ywslcx_ScrollArea();
    Ui::ywslcx_ScrollArea *ui;
    void refresh();
    void init();
    void getSearchCondition();
    void reset();

private slots:
    void on_btn_search_clicked();

private:
    GetYwblcxCondtionThread *_getYwblcxCondtionThread;
    GetYwblcxListThread *_getYwblcxListThread;
};


//��ȡ������
class GetYwblcxCondtionThread : public  QThread
{
public:
    ywslcx_ScrollArea *_ref;
    GetYwblcxCondtionThread(ywslcx_ScrollArea *ywslcx_ScrollArea_ptr);
protected:
    void run();
};

//��ȡ�б�
class GetYwblcxListThread : public  QThread
{
public:
    ywslcx_ScrollArea *_ref;
    GetYwblcxListThread(ywslcx_ScrollArea *ywslcx_ScrollArea_ptr);
    QString currentCondition;
protected:
    void run();
};

#endif // YWSLCX_SCROLLAREA_H
