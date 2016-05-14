#ifndef NOTICEDIALOG_H
#define NOTICEDIALOG_H

#include <QDialog>

namespace Ui {
    class NoticeDialog;
}

class NoticeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoticeDialog(QWidget *parent = 0);
    ~NoticeDialog();
    void init(QString title, QString date, QString content);
    void reset();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::NoticeDialog *ui;
};

#endif // NOTICEDIALOG_H
