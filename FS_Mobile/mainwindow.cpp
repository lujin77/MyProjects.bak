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

    //���ñ���ͼƬ��Ĭ�ϴ��ڴ�С
    _image.load("images/bg/background.png");
    setAutoFillBackground(true);
    this->showMaximized();

    scrollArea = new QScrollArea;
    gridLayout = new QGridLayout;
    scrollArea->setLayout(gridLayout);
    setCentralWidget(scrollArea);

    //��ʾ��¼��
    loginForm = new LoginForm(this);
    loginForm->show();
    gridLayout->addWidget(loginForm);


    //�����½�򱳾�����ʾ������
    loginForm->setAutoFillBackground(true); // ���Ҫ����, ���������ʾ��������ͼ.
    QPalette palette = loginForm->palette();
    palette.setBrush(QPalette::Window,
    QBrush(QPixmap("images/bg/loginBox.png").scaled( // ���ű���ͼ.
                    loginForm->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation))); // ʹ��ƽ�������ŷ�ʽ
    loginForm->setPalette(palette); // ����, �Ѹ�widget�����˱���ͼ.


    connect(loginForm, SIGNAL(loggingSuccess()), this, SLOT(change2Logged()));
    navigatorForm = new NavigatorForm(this);
    connect(navigatorForm, SIGNAL(loggout()), this, SLOT(change2Loggout()));


}

MainWindow::~MainWindow()
{
    //������������˳��������session
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
            //��տͻ��˻���
            Singleton::GetInstance()->clear();
            //�ɹ��˳�
            //QMessageBox::warning(this,tr("����"),"�ɹ��˳�",QMessageBox::Ok);
        } else {
            QMessageBox::warning(this,tr("����"),"��������������ϵ����Ա",QMessageBox::Ok);
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

    //���ñ���ɫ
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

    //��ջ�������ݺͽ�����Ϣ
    navigatorForm->reset();
    navigatorForm->hide();
    Singleton::GetInstance()->clear();


    //��ʾ��¼��
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

