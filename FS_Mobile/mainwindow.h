#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QScrollArea>
#include <QGridLayout>
#include "loginform.h"
#include "navigatorform.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    bool isLogged;
    QImage _image;
    QImage _logged_image;
    Ui::MainWindow *ui;
    QScrollArea *scrollArea;
    QGridLayout *gridLayout;
    LoginForm *loginForm;
    NavigatorForm *navigatorForm;

public slots:
    void change2Logged();
    void change2Loggout();
};

#endif // MAINWINDOW_H
