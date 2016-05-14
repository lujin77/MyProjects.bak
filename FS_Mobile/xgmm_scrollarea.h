#ifndef XGMM_SCROLLAREA_H
#define XGMM_SCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class xgmm_ScrollArea;
}

class xgmm_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit xgmm_ScrollArea(QWidget *parent = 0);
    ~xgmm_ScrollArea();
    void init();
    void reset();
    void submit();

private slots:
    void on_btnSubmit_clicked();

    void on_btnReset_clicked();

private:
    Ui::xgmm_ScrollArea *ui;
};

#endif // XGMM_SCROLLAREA_H
