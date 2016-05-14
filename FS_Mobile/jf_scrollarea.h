#ifndef JF_SCROLLAREA_H
#define JF_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>
#include <QWriteLocker>

namespace Ui {
    class jf_ScrollArea;
}

class GetLocationThread;
class GetNoInfoThread;
class GetNoServiceThread;
class GetPayment_jf_Thread;
class Print_jf_Thread;

class jf_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit jf_ScrollArea(QWidget *parent = 0);
    ~jf_ScrollArea();
    Ui::jf_ScrollArea *ui;
    void init();
    void refresh();
    void reset();

    bool _auto_get_location;
    //查询覆盖互斥
    QReadWriteLock _getNoInfolock;
    int _getNoInfoSign; // 0代表初始化，1表示获取到接口的，2表示获取到BOSs的

signals:
    void updateMoney();

protected:
    void keyPressEvent(QKeyEvent *event);
    void pay();

private slots:
    void on_btn_submit_clicked();
    void on_btn_search_clicked();
    void on_btn_reset_clicked();
    void on_txi_PhoneNo_textChanged(const QString &arg1);
    void on_btn_refresh_clicked();
    void on_txi_money_textChanged(const QString &arg1);
    void on_btn_print_clicked();
    void on_btnPayWithList_clicked();

private:
    GetLocationThread *_getLocationThread;
    GetNoInfoThread *_getNoInfoThread;
    GetNoServiceThread *_getNoServiceThread;
    GetPayment_jf_Thread *_getPayment_jf_Thread;
    int _tel_size;
    int _money_size;
};

//提取号码地区
class GetLocationThread : public  QThread
{
public:
    jf_ScrollArea *_ref;
    GetLocationThread(jf_ScrollArea *jf_ScrollArea_ptr);
protected:
    void run();
};

//提取号码详细信息
class GetNoInfoThread : public  QThread
{
public:
    jf_ScrollArea *_ref;
    GetNoInfoThread(jf_ScrollArea *jf_ScrollArea_ptr);
protected:
    void run();
};

//提取号码套餐信息
class GetNoServiceThread : public  QThread
{
public:
    jf_ScrollArea *_ref;
    GetNoServiceThread(jf_ScrollArea *jf_ScrollArea_ptr);
protected:
    void run();
};

//提取缴费记录
class GetPayment_jf_Thread : public  QThread
{
    Q_OBJECT

public:
    jf_ScrollArea *_ref;
    GetPayment_jf_Thread(jf_ScrollArea *jf_ScrollArea_ptr);
protected:
    void run();
};


#endif // JF_SCROLLAREA_H
