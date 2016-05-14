#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QtNetwork/QNetworkInterface>

namespace Ui {
    class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();
    bool readPsw();
    bool savePsw();

signals:
    void loggingSuccess();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void logging();
    void reset();
    void showRegisterBox();

private:
    Ui::LoginForm *ui;
    QString _ip;


};

#endif // LOGINFORM_H
