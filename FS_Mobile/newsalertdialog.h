#ifndef NEWSALERTDIALOG_H
#define NEWSALERTDIALOG_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include "noticedialog.h"

namespace Ui {
    class NewsAlertDialog;
}

class AlertNews
{
public:
    QString id;
    QString title;
    QString date;
    QString content;
    bool isRead;
};

class NewsAlertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewsAlertDialog(QWidget *parent = 0);
    ~NewsAlertDialog();
    void readFile();
    void saveFile();
    void reset();
    void testShow();

    QList<AlertNews> _news_list;        //未读消息（包含详细信息）
    QStringList _already_read_list;     //已读消息的Id

//public slots:
//    void changeAlert();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_btnShow_clicked();

private:
    Ui::NewsAlertDialog *ui;
    //ShowAlertNewsDialog *showAlertNewsDialog;
    NoticeDialog *noticeDialog;
};

#endif // NEWSALERTDIALOG_H
