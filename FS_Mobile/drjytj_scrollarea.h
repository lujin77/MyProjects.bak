#ifndef DRJYTJ_SCROLLAREA_H
#define DRJYTJ_SCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class drjytj_ScrollArea;
}

class GetJytjListThread;

class drjytj_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit drjytj_ScrollArea(QWidget *parent = 0);
    ~drjytj_ScrollArea();
    Ui::drjytj_ScrollArea *ui;
    void refresh();
    void init();
    void reset();

private slots:
    void on_btn_submit_clicked();

private:
    GetJytjListThread *_getJytjListThread;
};

//提取列表
class GetJytjListThread : public  QThread
{
public:
    drjytj_ScrollArea *_ref;
    GetJytjListThread(drjytj_ScrollArea *drjytj_ScrollArea_ptr);
    QString currentCondition;
protected:
    void run();
};

#endif // DRJYTJ_SCROLLAREA_H
