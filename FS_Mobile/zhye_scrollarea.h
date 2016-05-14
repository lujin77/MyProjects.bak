#ifndef ZHYE_SCROLLAREA_H
#define ZHYE_SCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class zhye_ScrollArea;
}

class zhye_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit zhye_ScrollArea(QWidget *parent = 0);
    ~zhye_ScrollArea();
    void init();
    void reset();
    void getSearchCondition();
    void search();

signals:
    void updateMoney();

private slots:
    void on_btnSearch_clicked();

private:
    Ui::zhye_ScrollArea *ui;
};

#endif // ZHYE_SCROLLAREA_H
