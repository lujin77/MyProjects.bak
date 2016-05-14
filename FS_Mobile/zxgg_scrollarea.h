#ifndef ZXGG_SCROLLAREA_H
#define ZXGG_SCROLLAREA_H

#include <QScrollArea>
#include <QModelIndex>
#include <noticedialog.h>

namespace Ui {
    class zxgg_ScrollArea;
}

class zxgg_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit zxgg_ScrollArea(QWidget *parent = 0);
    ~zxgg_ScrollArea();
    void init();
    void reset();
    void refresh(int pageSize, int pageIndex);

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_btnFront_clicked();

    void on_btnPre_clicked();

    void on_btnNext_clicked();

    void on_btnTail_clicked();

    void on_spinBox_editingFinished();

    void on_txi_line_num_editingFinished();

    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::zxgg_ScrollArea *ui;
    int totalPage;
    int currentPage;
    int initPageSize;
    NoticeDialog *_notice_dialog;
};

#endif // ZXGG_SCROLLAREA_H
