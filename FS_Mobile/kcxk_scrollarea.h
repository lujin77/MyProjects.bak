#ifndef KCXK_SCROLLAREA_H
#define KCXK_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>

namespace Ui {
    class kcxk_ScrollArea;
}

class GetKcxkCondtionThread;
class GetKcxkListThread;

class kcxk_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit kcxk_ScrollArea(QWidget *parent = 0);
    ~kcxk_ScrollArea();
    Ui::kcxk_ScrollArea *ui;
    void refresh();
    void init();
    void getSearchCondition();
    void reset();

private slots:
    void on_btn_search_clicked();

private:
    GetKcxkCondtionThread *_getKcxkCondtionThread;
    GetKcxkListThread *_getKcxkListThread;
};

//提取下拉框
class GetKcxkCondtionThread : public  QThread
{
public:
    kcxk_ScrollArea *_ref;
    GetKcxkCondtionThread(kcxk_ScrollArea *kcxk_ScrollArea_ptr);
protected:
    void run();
};

//提取列表
class GetKcxkListThread : public  QThread
{
public:
    kcxk_ScrollArea *_ref;
    GetKcxkListThread(kcxk_ScrollArea *kcxk_ScrollArea_ptr);
    QString currentCondition;
protected:
    void run();
};


#endif // KCXK_SCROLLAREA_H
