#ifndef ZHCZ_SCROLLAREA_H
#define ZHCZ_SCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class zhcz_ScrollArea;
}

class zhcz_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit zhcz_ScrollArea(QWidget *parent = 0);
    ~zhcz_ScrollArea();
    void init();
    void getSearchCondition();
    void reset();
    void submit();

private slots:
    void on_btnSubmit_clicked();
    void on_btnReset_clicked();

private:
    Ui::zhcz_ScrollArea *ui;
};

#endif // ZHCZ_SCROLLAREA_H
