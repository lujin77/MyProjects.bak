#ifndef GMQB_SCROLLAREA_H
#define GMQB_SCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class gmqb_ScrollArea;
}

class gmqb_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit gmqb_ScrollArea(QWidget *parent = 0);
    ~gmqb_ScrollArea();

private:
    Ui::gmqb_ScrollArea *ui;
};

#endif // GMQB_SCROLLAREA_H
