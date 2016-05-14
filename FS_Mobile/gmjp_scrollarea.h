#ifndef GMJP_SCROLLAREA_H
#define GMJP_SCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class gmjp_ScrollArea;
}

class gmjp_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit gmjp_ScrollArea(QWidget *parent = 0);
    ~gmjp_ScrollArea();

private:
    Ui::gmjp_ScrollArea *ui;
};

#endif // GMJP_SCROLLAREA_H
