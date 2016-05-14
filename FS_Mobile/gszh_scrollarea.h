#ifndef GSZH_SCROLLAREA_H
#define GSZH_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>

namespace Ui {
    class gszh_ScrollArea;
}

class GetAccountListThread;

class gszh_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit gszh_ScrollArea(QWidget *parent = 0);
    ~gszh_ScrollArea();
    Ui::gszh_ScrollArea *ui;
    void init();

private:
    GetAccountListThread *_getAccountListThread;
};

//提取账户信息thread
class GetAccountListThread : public  QThread
{
public:
    gszh_ScrollArea *_ref;
    GetAccountListThread(gszh_ScrollArea *gszh_ScrollArea_ptr);
protected:
    void run();
};

#endif // GSZH_SCROLLAREA_H
