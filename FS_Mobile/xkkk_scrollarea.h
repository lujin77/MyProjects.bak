#ifndef XKKK_SCROLLAREA_H
#define XKKK_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>
#include <QStringListModel>

namespace Ui {
    class xkkk_ScrollArea;
}

class GetXkkkCondtionThread;

class xkkk_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit xkkk_ScrollArea(QWidget *parent = 0);
    ~xkkk_ScrollArea();
    Ui::xkkk_ScrollArea *ui;
    void init();
    void reset();
    void submit();
    float cardPrice;

signals:
    void updateMoney();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_btn_generate_clicked();

    void on_bent_delete_clicked();

    void on_btn_clear_clicked();

    void on_btn_submit_clicked();

    void on_btn_reset_clicked();

private:
    GetXkkkCondtionThread *_getXkkkCondtionThread;
    QStringList cardNoList;
    QStringListModel cardListModel;

};

//提取下拉框
class GetXkkkCondtionThread : public  QThread
{
public:
    xkkk_ScrollArea *_ref;
    GetXkkkCondtionThread(xkkk_ScrollArea *xkkk_ScrollArea_ptr);
protected:
    void run();
};

#endif // XKKK_SCROLLAREA_H
