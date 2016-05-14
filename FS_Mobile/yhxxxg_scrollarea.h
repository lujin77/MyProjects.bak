#ifndef YHXXXG_SCROLLAREA_H
#define YHXXXG_SCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class yhxxxg_ScrollArea;
}

class yhxxxg_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit yhxxxg_ScrollArea(QWidget *parent = 0);
    ~yhxxxg_ScrollArea();
    void init();
    void reset();
    void submit();

private slots:
    void on_btnSubmit_clicked();

    void on_btnReset_clicked();

private:
    Ui::yhxxxg_ScrollArea *ui;
};

#endif // YHXXXG_SCROLLAREA_H
