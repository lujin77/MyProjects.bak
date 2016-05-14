#ifndef YXCZ_TABWIDGET_H
#define YXCZ_TABWIDGET_H

#include <QTabWidget>
#include <QThread>

namespace Ui {
    class yxcz_TabWidget;
}

class GetYxczCurrThread;
class GetYxczCondtionThread;
class GetYxczRbListThread;
class GetYxczYbListThread;

class yxcz_TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit yxcz_TabWidget(QWidget *parent = 0);
    ~yxcz_TabWidget();
    Ui::yxcz_TabWidget *ui;
    void resetAll();
    void initAll();
    void resetJF();
    void initJF();
    void refreshJF();
    void resetRB();
    void initRB();
    void refreshRB();
    void resetYB();
    void initYB();
    void refreshYB();
    void submit();
    void getSearchCondition();

signals:
    void updateMoney();

protected:
    void keyPressEvent(QKeyEvent *event);
    void changeEvent(QEvent *e);

private slots:
    void on_btn_submit_clicked();

    void on_btn_reset_clicked();

    void on_btn_refresh_clicked();

    void on_btn_search_rb_clicked();

    void on_btn_refresh_rb_clicked();

    void on_btn_search_yb_clicked();

    void on_btn_refresh_yb_clicked();

    void on_btn_print_yb_clicked();

    void on_btn_print_rb_clicked();

    void on_btn_print_clicked();

    void on_txi_gameAccount_textChanged(const QString &arg1);

    void on_txi_money_textChanged(const QString &arg1);

private:
    GetYxczCurrThread *_getYxczCurrThread;
    GetYxczCondtionThread *_getYxczCondtionThread;
    GetYxczRbListThread *_getYxczRbListThread;
    GetYxczYbListThread *_getYxczYbListThread;
    int _game_account_size;
    int _game_money_size;
};

//��ȡ������Ϸ��ֵ��¼
class GetYxczCurrThread : public  QThread
{
    Q_OBJECT

public:
    yxcz_TabWidget *_ref;
    GetYxczCurrThread(yxcz_TabWidget *yxcz_TabWidget_ptr);
protected:
    void run();
};

//��ȡ������
class GetYxczCondtionThread : public  QThread
{
public:
    yxcz_TabWidget *_ref;
    GetYxczCondtionThread(yxcz_TabWidget *yxcz_TabWidget_ptr);
protected:
    void run();
};

//��ȡ�б�
class GetYxczRbListThread : public  QThread
{
public:
    yxcz_TabWidget *_ref;
    GetYxczRbListThread(yxcz_TabWidget *yxcz_TabWidget_ptr);
    QString currentCondition;
protected:
    void run();
};

//��ȡ�б�
class GetYxczYbListThread : public  QThread
{
public:
    yxcz_TabWidget *_ref;
    GetYxczYbListThread(yxcz_TabWidget *yxcz_TabWidget_ptr);
    QString currentCondition;
protected:
    void run();
};

#endif // YXCZ_TABWIDGET_H
