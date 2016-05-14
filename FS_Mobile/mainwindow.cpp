#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "EncryptUtil.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isLogged = false;

    //设置背景图片和默认窗口大小
    _image.load("images/bg/background.png");
    setAutoFillBackground(true);
    this->showMaximized();

    scrollArea = new QScrollArea;
    gridLayout = new QGridLayout;
    scrollArea->setLayout(gridLayout);
    setCentralWidget(scrollArea);

    //显示登录框
    loginForm = new LoginForm(this);
    loginForm->show();
    gridLayout->addWidget(loginForm);


    //解决登陆框背景不显示的问题
    loginForm->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = loginForm->palette();
    palette.setBrush(QPalette::Window,
    QBrush(QPixmap("images/bg/loginBox.png").scaled( // 缩放背景图.
                    loginForm->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation))); // 使用平滑的缩放方式
    loginForm->setPalette(palette); // 至此, 已给widget加上了背景图.


    connect(loginForm, SIGNAL(loggingSuccess()), this, SLOT(change2Logged()));
    navigatorForm = new NavigatorForm(this);
    connect(navigatorForm, SIGNAL(loggout()), this, SLOT(change2Loggout()));


}

MainWindow::~MainWindow()
{
    //如果不是正常退出，先清空session
    if (Singleton::GetInstance()->getUser().Id != "") {
        UserFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__loggout req;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        string user_id = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        strcpy(buffer1, user_id.data());
        req.userId = buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
        req.sessionId = buffer2;

        _ns1__loggoutResponse res;
        this->setCursor(Qt::BusyCursor);
        if (soap.__ns5__loggout(&req,&res) == SOAP_OK) {
            //清空客户端缓存
            Singleton::GetInstance()->clear();
            //成功退出
            //QMessageBox::warning(this,tr("警告"),"成功退出",QMessageBox::Ok);
        } else {
            QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
        }
        this->setCursor(Qt::ArrowCursor);
    }
    delete loginForm;
    delete navigatorForm;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(!isLogged) {
        QWidget::resizeEvent(event);
        QPalette pal(palette());
        pal.setBrush(QPalette::Window,
                    QBrush(_image.scaled(event->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
        setPalette(pal);
    }
    else { 
        QWidget::resizeEvent(event);
        QPalette pal(palette());
        pal.setColor(QPalette::Window,QColor(255,255,255));
        setPalette(pal);

    }
}

void MainWindow::change2Logged()
{

    isLogged = true;

    loginForm->hide();

    navigatorForm->show();
    navigatorForm->init();

    //navigatorForm->setAutoFillBackground(true);
    //QScrollArea *scrollArea = new QScrollArea;
    //QGridLayout *gridLayout = new QGridLayout;
    gridLayout->removeWidget(loginForm);
    gridLayout->addWidget(navigatorForm);
    //scrollArea->setLayout(gridLayout);
    //setCentralWidget(scrollArea);

    //设置背景色
    QPalette pal(palette());
    pal.setColor(QPalette::Window,QColor(255,255,255));
    setPalette(pal);

    navigatorForm->setMoney();
    navigatorForm->setName();

    navigatorForm->zxgg_form->init();
    navigatorForm->testNewsAlert();

}


void MainWindow::change2Loggout()
{

    isLogged = false;

    //清空缓存的数据和界面信息
    navigatorForm->reset();
    navigatorForm->hide();
    Singleton::GetInstance()->clear();


    //显示登录框
    loginForm->show();
    gridLayout->removeWidget(navigatorForm);
    gridLayout->addWidget(loginForm);

    QPalette pal(palette());
    pal.setBrush(QPalette::Window,
                QBrush(_image.scaled(this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));
    setPalette(pal);
}

