#ifndef DBFJS_SCROLLAREA_H
#define DBFJS_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>



namespace Ui {
    class dbfjs_ScrollArea;
}

class GetReturnInfoThread;

class dbfjs_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit dbfjs_ScrollArea(QWidget *parent = 0);
    ~dbfjs_ScrollArea();
    void init();
    void reset();
    void refresh();
    void submit();
    Ui::dbfjs_ScrollArea *ui;

signals:
    void updateMoney();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_btnSubmit_clicked();

private:
    GetReturnInfoThread *_getReturnInfoThread;
};

class GetReturnInfoThread : public  QThread
{
public:
    dbfjs_ScrollArea *_ref;
    GetReturnInfoThread(dbfjs_ScrollArea *dbfjs_ScrollArea_ptr);
protected:
    void run();
};

#endif // DBFJS_SCROLLAREA_H
