#ifndef REGISTERBOX_H
#define REGISTERBOX_H

#include <QDialog>
#include <QtNetwork/QNetworkInterface>
#include <QThread>

namespace Ui {
    class RegisterBox;
}

class GetWorkerListThread;

class RegisterBox : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterBox(QWidget *parent = 0);
    ~RegisterBox();
    Ui::RegisterBox *ui;

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_txiRePassword_editingFinished();

    void on_btnReset_clicked();

    void on_btnSubmit_clicked();

private:
    GetWorkerListThread *_getWorkerListThread;
};

//提取业务员
class GetWorkerListThread : public  QThread
{
public:
    RegisterBox *_ref;
    GetWorkerListThread(RegisterBox *registerBox_ptr);
protected:
    void run();
};

#endif // REGISTERBOX_H
