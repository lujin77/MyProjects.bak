#ifndef YDXH_SCROLLAREA_H
#define YDXH_SCROLLAREA_H

#include <QScrollArea>
#include <QModelIndex>
#include <QThread>
#include <QTableWidgetItem>

namespace Ui {
    class ydxh_ScrollArea;
}

class GetNoListThread;
class GetYdxhCondtionThread;

class NoInfo
{
public:
    QString No;
    double price;
    QString area;
    QString value;
    QString NoSection;
};

class ydxh_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit ydxh_ScrollArea(QWidget *parent = 0);
    ~ydxh_ScrollArea();
    void refresh(int pageSize, int pageIndex);
    void init();
    void getSearchCondition();
    void reset();
    void submit();
    void resetPhoneNo();
    void showNewMoney();
    NoInfo phones[20][3];
    Ui::ydxh_ScrollArea *ui;

signals:
    void updateMoney();

private slots:
    void on_txi_no1_textChanged(const QString &arg1);

    void on_txi_no2_textChanged(const QString &arg1);

    void on_txi_no3_textChanged(const QString &arg1);

    void on_txi_no4_textChanged(const QString &arg1);

    void on_txi_no5_textChanged(const QString &arg1);

    void on_txi_no6_textChanged(const QString &arg1);

    void on_txi_no7_textChanged(const QString &arg1);

    void on_txi_no8_textChanged(const QString &arg1);

    void on_txi_no9_textChanged(const QString &arg1);

    void on_txi_no10_textChanged(const QString &arg1);

    void on_txi_no11_textChanged(const QString &arg1);

    void on_btn_search_clicked();

    void on_btn_reset_clicked();

    void on_btn_front_clicked();

    void on_btn_pre_clicked();

    void on_ben_next_clicked();

    void on_btn_tail_clicked();

    void on_spinBox_editingFinished();

    void on_txi_no1_editingFinished();

    void on_txi_no2_editingFinished();

    void on_txi_no3_editingFinished();

    void on_txi_no4_editingFinished();

    void on_txi_no5_editingFinished();

    void on_txi_no6_editingFinished();

    void on_txi_no7_editingFinished();

    void on_txi_no8_editingFinished();

    void on_txi_no9_editingFinished();

    void on_txi_no10_editingFinished();

    void on_txi_no11_editingFinished();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_rdo_all_clicked();

    void on_rdo_1_clicked();

    void on_rdo_2_clicked();

    void on_rdo_3_clicked();

    void on_rdo_4_clicked();

    void on_rdo_5_clicked();

    void on_rdo_6_clicked();

    void on_tableWidget_cellPressed(int row, int column);

private:
    int totalItem;
    int totalPage;
    int currentPage;
    int initPageSize;
    QString searchCondition;
    GetNoListThread *_getNoListThread;
    GetYdxhCondtionThread *_getYdxhCondtionThread;
};

//提取下拉框
class GetYdxhCondtionThread : public  QThread
{
public:
    ydxh_ScrollArea *_ref;
    GetYdxhCondtionThread(ydxh_ScrollArea *ydxh_ScrollArea_ptr);
protected:
    void run();
};

//提取号码
class GetNoListThread : public  QThread
{
public:
    ydxh_ScrollArea *_ref;
    GetNoListThread(ydxh_ScrollArea *ydxh_ScrollArea_ptr);
    QString currentCondition;
protected:
    void run();
};



#endif // YDXH_SCROLLAREA_H
