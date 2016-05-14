#ifndef YWBL_SCROLLAREA_H
#define YWBL_SCROLLAREA_H

#include <QScrollArea>
#include <QThread>
#include <QVector>

namespace Ui {
    class ywbl_ScrollArea;
}

class GetBusinessListThread;

class BusinessInfo {
public:
    QString name;
    QString winType;
};

class ywbl_ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit ywbl_ScrollArea(QWidget *parent = 0);
    ~ywbl_ScrollArea();
    Ui::ywbl_ScrollArea *ui;
    QVector<BusinessInfo> list;
    void refresh();
    void init();
    void reset();

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);

private:
    GetBusinessListThread *_getBusinessListThread;
};


class GetBusinessListThread : public  QThread
{
public:
    ywbl_ScrollArea *_ref;
    GetBusinessListThread(ywbl_ScrollArea *ywbl_ScrollArea_ptr);
protected:
    void run();
};

#endif // YWBL_SCROLLAREA_H
