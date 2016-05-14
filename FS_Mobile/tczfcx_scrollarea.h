#ifndef TCZFCX_SCROLLAREA_H
#define TCZFCX_SCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class tczfcx_ScrollArea;
}

class GetCardServiceThread;

class tczfcx_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit tczfcx_ScrollArea(QWidget *parent = 0);
    ~tczfcx_ScrollArea();
    Ui::tczfcx_ScrollArea *ui;
    void init();
    void refresh();
    void reset();

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_tableWidget_clicked(const QModelIndex &index);

private:
    GetCardServiceThread *_getCardServiceThread;
};

//提取套餐信息
class GetCardServiceThread : public  QThread
{
public:
    tczfcx_ScrollArea *_ref;
    GetCardServiceThread(tczfcx_ScrollArea *tczfcx_ScrollArea_ptr);
protected:
    void run();
};

#endif // TCZFCX_SCROLLAREA_H
