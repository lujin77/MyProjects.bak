#include "navigatorform.h"
#include "ui_navigatorform.h"
#include "jf_scrollarea.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include <QGridLayout>
#include "singleton.h"
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QtNetwork/QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include "config.h"
#include "EncryptUtil.h"

int const topFrameWidth = 10006;
int const topFrameHeight = 100;
int const leftFrameWidth = 221;
int const leftFrameHeight = 592;

int const mainFrameX = 220;
int const mainFrameY = 100;
int const mainFrameWidth = 791;
int const mainFrameHeight = 601;


NewsAlertThread::NewsAlertThread(NavigatorForm *navigatorForm_ptr)
{
    this->_ref = navigatorForm_ptr;
    //Ĭ�ϵȴ�10������ȡһ����Ϣ
    waitTime = 600;
    isNetworkConnected = false;
}

void NewsAlertThread::run()
{
    //�ȼ��ػ�����Ϣ
    _ref->news_alert_dialog->readFile();
    QNetworkInterface localInterface;

    //qDebug() << "��notice�� time here";
    while (true) {

        //�ȼ�������Ƿ�����
        if (localInterface.allInterfaces().first().addressEntries().size() >0) {
            if (!localInterface.allInterfaces().first().addressEntries().first().ip().isNull()) {
                isNetworkConnected = true;
            }
        } else if (localInterface.allInterfaces().at(1).addressEntries().size() > 0) {
            if (!localInterface.allInterfaces().at(1).addressEntries().first().ip().isNull()) {
                isNetworkConnected = true;
            }
        } else {
            if (isNetworkConnected == false) return;
            else isNetworkConnected = false;
        }

        qDebug()<<"������ȡ�����Զ����ʱ����߳�...";

        UtilFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__GetDicContentByCondition req0;

        char buffer0[255];
        memset(buffer0,0,255*sizeof(char));
        strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
        req0.sessionId = buffer0;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        QString queryStr = "[Category]='�ͻ�������' and [Name]='������ʱ��' and [Enabled]=1 ";
        std::string condition = NetSecurity::encrypt(queryStr);
        strcpy(buffer1, condition.data());
        req0.condition = buffer1;

        _ns1__GetDicContentByConditionResponse res0;
        if (soap.__ns7__GetDicContentByCondition(&req0,&res0) == SOAP_OK) {
            if (res0.GetDicContentByConditionResult->__sizeDIC_USCOREContent >= 1) {
                waitTime = QString(res0.GetDicContentByConditionResult->DIC_USCOREContent[0]->Code).toInt();
                qDebug()<<"������ʱ�䣺"+QString::number(waitTime);
            }
        } else {
            qDebug()<<"�����������޷���ǰ��ʱ��Ϣ";
        }

        qDebug()<<"������ȡ��ʱ��Ϣ���߳�";

        //UtilFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__GetAlertNoticeList req;

        char buffer[255];
        memset(buffer,0,255*sizeof(char));
        std::string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        strcpy(buffer, userId.data());
        qDebug()<<"userId:"+QString::fromStdString(userId);
        req.userId = buffer;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
        qDebug()<<"sessionId:"+Singleton::GetInstance()->session_id;
        req.sessionId = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
        strcpy(buffer3, clientType.data());
        qDebug()<<"clientType:"+QString::fromStdString(clientType);
        req.clientType = buffer3;

        _ns1__GetAlertNoticeListResponse res;
        if (soap.__ns7__GetAlertNoticeList(&req,&res) == SOAP_OK) {
            qDebug()<<"�鵽"+QString::number(res.GetAlertNoticeListResult->total)+"����ʱ��¼:";
            //��տͻ��˻������Ϣ
            _ref->news_alert_dialog->_news_list.clear();
            for (int i=0; i<res.GetAlertNoticeListResult->listOfNotice->__sizeNoticeItem; ++i) {
                QString id = QString::fromUtf8(res.GetAlertNoticeListResult->listOfNotice->NoticeItem[i]->Id);
                //������Ѿ������ļ�¼����ͳ��
                if (!_ref->news_alert_dialog->_already_read_list.contains(id)) {
                    qDebug()<<"��⵽һ��δ����¼";
                    AlertNews alertNews;
                    alertNews.id = id;
                    char cTime[50];
                    memset(cTime,0,50);
                    strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetAlertNoticeListResult->listOfNotice->NoticeItem[i]->publishDatetime)));
                    alertNews.date = QString(cTime);
                    alertNews.title = QString::fromUtf8(res.GetAlertNoticeListResult->listOfNotice->NoticeItem[i]->title);
                    alertNews.content = QString::fromUtf8(res.GetAlertNoticeListResult->listOfNotice->NoticeItem[i]->content);
                    alertNews.isRead = false;

                    _ref->news_alert_dialog->_news_list.append(alertNews);
                    /*
                    //�����ظ���ȡ
                    bool isExist = false;
                    for (int k=0; k<_ref->news_alert_dialog->_news_list.length(); ++k) {
                        if (_ref->news_alert_dialog->_news_list.at(k).id == id)
                            isExist = true;
                    }
                    if (!isExist) {
                        _ref->news_alert_dialog->_news_list.append(alertNews);
                    }
                    */
                }
            }
        } else {
            qDebug()<<"�����������޷���ǰ��ʱ��Ϣ";
        }

        qDebug()<<"Ӧ����ʾ"+QString::number(_ref->news_alert_dialog->_news_list.length())+"����ʱ��¼";

        //_ref->news_alert_dialog->testShow();
        //qDebug()<<"�����ǰ��ʱ��Ϣ���̣߳���ʾ��Ϣ��ʾ";
        emit getDataComplete();
        qDebug()<<"�������߳����ߣ�"+QString::number(waitTime)+"��";
        sleep(waitTime);
    }
    _ref->news_alert_dialog->saveFile();
}

GetCompanyTelThread::GetCompanyTelThread(NavigatorForm *navigatorForm_ptr)
{
    _ref = navigatorForm_ptr;
}

void GetCompanyTelThread::run()
{
    qDebug()<<"������ȡ��˾�ͷ��绰�߳�...";
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetCompanyInfo req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
    strcpy(buffer1, clientType.data());
    req.clientType = buffer1;

   _ns1__GetCompanyInfoResponse res;
    if (soap.__ns7__GetCompanyInfo(&req,&res) == SOAP_OK) {
        _ref->ui->txtTel1->setText(QString::fromUtf8(res.GetCompanyInfoResult->tel_USCORE1));
        _ref->ui->txtTel2->setText(QString::fromUtf8(res.GetCompanyInfoResult->tel_USCORE2));
    } else {
        qDebug()<<"��ȡ��˾�ͻ��绰ʧ�ܣ�";
    }
    qDebug()<<"��ȡ��˾�ͷ��绰�̴߳������";
}


NavigatorForm::NavigatorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigatorForm)
{
    ui->setupUi(this);

    //���ɶ����ı���ͼ
    top_image.load("images/bg/top.png");

    //�����ӽ���
    creatSubFrame();

    ui->topFrame->setAutoFillBackground(true); // ���Ҫ����, ���������ʾ��������ͼ.
    QPalette palette = ui->topFrame->palette();
    palette.setBrush(ui->topFrame->backgroundRole(),QBrush(QPixmap("images/bg/top.png"))); // ʹ��ƽ�������ŷ�ʽ
    ui->topFrame->setPalette(palette); // ����, �Ѹ�widget�����˱���ͼ.
    ui->topFrame->show();

    ui->leftFrame->setAutoFillBackground(true); // ���Ҫ����, ���������ʾ��������ͼ.
    QPalette palette2 = ui->leftFrame->palette();
    palette2.setBrush(QPalette::Window,QBrush(QPixmap("images/bg/btnList.png")));
    ui->leftFrame->setPalette(palette2);

    connect(this->jf_form, SIGNAL(updateMoney()), this, SLOT(setMoney()));
    connect(this->zhye_form, SIGNAL(updateMoney()), this, SLOT(setMoney()));
    connect(this->dbfjs_form, SIGNAL(updateMoney()), this, SLOT(setMoney()));
    connect(this->yxcz_form, SIGNAL(updateMoney()), this, SLOT(setMoney()));
    connect(this->kdcz_form, SIGNAL(updateMoney()), this, SLOT(setMoney()));
    connect(this->xkkk_form, SIGNAL(updateMoney()), this, SLOT(setMoney()));
    connect(this->ydxh_form, SIGNAL(updateMoney()), this, SLOT(setMoney()));
    connect(this->klxs_form, SIGNAL(updateMoney()), this, SLOT(setMoney()));
    //��ʼ���߳�
    _newsAlertThread = new NewsAlertThread(this);
    connect(_newsAlertThread,SIGNAL(getDataComplete()), this, SLOT(isShowNewsAlert()));
    _getCompanyTelThread = new GetCompanyTelThread(this);

    //�ƶ��ͻ������ΰ�ť
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        ui->btn_gmjp->hide();
        ui->btn_yxcz->hide();
        ui->btn_kdjf->hide();
    } else {
        ui->btn_ydjf->setToolTip("�ֻ��ɷ�");
        ui->btn_ydjf->setStatusTip("�ֻ��ɷ�");
        ui->btn_ydjf->setWhatsThis("�ֻ��ɷ�");
        ui->btn_ydxh->setToolTip("�ֻ�ѡ��");
        ui->btn_ydxh->setStatusTip("�ֻ�ѡ��");
        ui->btn_ydxh->setWhatsThis("�ֻ�ѡ��");
        ui->btn_ydjf->setStyleSheet("background-image: url(:/btn_main/images/btnList/btn_sjjf.png);");
        ui->btn_ydxh->setStyleSheet("background-image: url(:/btn_main/images/btnList/btn_sjxh.png);");
    }

    //���ñ���
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {

    } else {
        ui->topFrame->setStyleSheet("background-image: url(:/bg/images/bg/top2.png);");
        ui->leftFrame->setStyleSheet("background-image: url(:/border/images/bg/btnList2.png);");
    }

    //���ñ���
    ui->txtSysName->setText(Config::GetInstance()->_sysTitle);
}

NavigatorForm::~NavigatorForm()
{
    qDebug()<<"�����浼����������";
    if (_newsAlertThread != NULL) {
        _newsAlertThread->terminate();
        _newsAlertThread->exit();
        delete _newsAlertThread;
    }
    if (_getCompanyTelThread != NULL) {
        _getCompanyTelThread->terminate();
        _getCompanyTelThread->exit();
        delete _getCompanyTelThread;
    }

    //this->news_alert_dialog->saveFile();
    delete news_alert_dialog;

    delete jf_form;
    delete jfrb_form;
    delete jfyb_form;
    delete ydxh_form;
    delete skcx_form;
    delete skjx_form;
    delete kcxk_form;
    delete tczfcx_form;
    delete ywbl_form;
    delete ywslcx_form;
    delete zhye_form;
    delete zhcz_form;
    delete xkkk_form;
    delete xgmm_form;
    delete yhxxxg_form;
    delete zxgg_form;
    delete gszh_form;
    delete jymx_form;
    delete yxcz_form;
    delete gmjp_form;
    delete klxs_form;
    delete drjytj_form;
    delete dbfjs_form;
    delete kdcz_form;
    delete ui;
}

void NavigatorForm::resizeEvent(QResizeEvent *event)
{
    //int extraWidth = width() - topFrameWidth;
    //ui->top_bg_frame->resize(181 + extraWidth, 88);
    /*
    QPalette pal(ui->topWidget->palette());
    pal.setBrush(QPalette::Background,
                 QBrush(top_image.scaledToWidth("10006 + extraWidth")));
    ui->topWidget->setPalette(pal);
    */
}

void NavigatorForm::resizeMainframe(int extraWidth)
{
}

void NavigatorForm::creatSubFrame()
{
    jf_form = new jf_ScrollArea(this);
    ui->mainStack->addWidget(jf_form);

    jfrb_form = new jfrb_ScrollArea(this);
    ui->mainStack->addWidget(jfrb_form);

    jfyb_form = new jfyb_ScrollArea(this);
    ui->mainStack->addWidget(jfyb_form);

    ydxh_form = new ydxh_ScrollArea(this);
    ui->mainStack->addWidget(ydxh_form);

    skcx_form = new skcx_ScrollArea(this);
    ui->mainStack->addWidget(skcx_form);

    skjx_form = new skjx_ScrollArea(this);
    ui->mainStack->addWidget(skjx_form);

    kcxk_form = new kcxk_ScrollArea(this);
    ui->mainStack->addWidget(kcxk_form);

    tczfcx_form = new tczfcx_ScrollArea(this);
    ui->mainStack->addWidget(tczfcx_form);

    ywbl_form = new ywbl_ScrollArea(this);
    ui->mainStack->addWidget(ywbl_form);

    ywslcx_form = new ywslcx_ScrollArea(this);
    ui->mainStack->addWidget(ywslcx_form);

    zhye_form = new zhye_ScrollArea(this);
    ui->mainStack->addWidget(zhye_form);

    zhcz_form = new zhcz_ScrollArea(this);
    ui->mainStack->addWidget(zhcz_form);

    xkkk_form = new xkkk_ScrollArea(this);
    ui->mainStack->addWidget(xkkk_form);

    xgmm_form = new xgmm_ScrollArea(this);
    ui->mainStack->addWidget(xgmm_form);

    yhxxxg_form = new yhxxxg_ScrollArea(this);
    ui->mainStack->addWidget(yhxxxg_form);

    zxgg_form = new zxgg_ScrollArea(this);
    ui->mainStack->addWidget(zxgg_form);

    gszh_form = new gszh_ScrollArea(this);
    ui->mainStack->addWidget(gszh_form);

    jymx_form = new jymx_ScrollArea(this);
    ui->mainStack->addWidget(jymx_form);

    yxcz_form = new yxcz_TabWidget(this);
    ui->mainStack->addWidget(yxcz_form);

    gmjp_form = new gmjp_ScrollArea(this);
    ui->mainStack->addWidget(gmjp_form);

    klxs_form = new klxs_TabWidget(this);
    ui->mainStack->addWidget(klxs_form);

    drjytj_form = new drjytj_ScrollArea(this);
    ui->mainStack->addWidget(drjytj_form);

    dbfjs_form = new dbfjs_ScrollArea(this);
    ui->mainStack->addWidget(dbfjs_form);

    kdcz_form = new kdcz_TabWidget(this);
    ui->mainStack->addWidget(kdcz_form);

    //������Ϣ��ʾ
    news_alert_dialog = new NewsAlertDialog(this);
    news_alert_dialog->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    news_alert_dialog->hide();
    news_alert_dialog->move(this->parentWidget()->width()-250,this->parentWidget()->height()-250);

}

void NavigatorForm::reset()
{
    _newsAlertThread->terminate();
    //this->news_alert_dialog->saveFile();
    //this->news_alert_dialog->reset();

    this->jf_form->reset();
    this->jfrb_form->reset();
}

void NavigatorForm::testNewsAlert()
{
    //qDebug()<<"����testNewsAlert";
    this->news_alert_dialog->reset();
    if (!_newsAlertThread->isRunning())
        _newsAlertThread->start();

    /*
    //�ȼ��ػ�����Ϣ
    news_alert_dialog->readFile();
    //qDebug()<< "��:" + QString::number(this->parentWidget()->width()) + ",��:" + QString::number(this->parentWidget()->height());
    //_newsAlertThread->start();
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetAlertNoticeList req;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetAlertNoticeListResponse res;
    if (soap.__ns7__GetAlertNoticeList(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetAlertNoticeListResult->listOfNotice->__sizeNoticeItem; ++i) {
            QString id = QString::fromUtf8(res.GetAlertNoticeListResult->listOfNotice->NoticeItem[i]->Id);
            //������Ѿ������ļ�¼����ͳ��
            if (!news_alert_dialog->_already_read_list.contains(id)) {
                AlertNews alertNews;
                alertNews.id = id;
                char cTime[50];
                memset(cTime,0,50);
                strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetAlertNoticeListResult->listOfNotice->NoticeItem[i]->publishDatetime)));
                alertNews.date = QString(cTime);
                alertNews.title = QString::fromUtf8(res.GetAlertNoticeListResult->listOfNotice->NoticeItem[i]->title);
                alertNews.content = QString::fromUtf8(res.GetAlertNoticeListResult->listOfNotice->NoticeItem[i]->content);
                alertNews.isRead = false;
                news_alert_dialog->_news_list.append(alertNews);
            } else {
                news_alert_dialog->_new_already_read_list += id;
            }
        }
    } else {
        qDebug()<<"�����������޷���ǰ��ʱ��Ϣ";
    }

    qDebug()<<"��ȡ��"+QString::number(news_alert_dialog->_news_list.length())+"����¼";

    news_alert_dialog->testShow();
    */

}

void NavigatorForm::showNewsAlert()
{
    news_alert_dialog->show();
}

void NavigatorForm::hideNewsAlert()
{
    news_alert_dialog->hide();
}

void NavigatorForm::init()
{
    //����Ĭ����ʾ����
    ui->mainStack->setCurrentIndex(17);
    //ui->mainStack->setCurrentIndex(9);
    //this->tczfcx_form->init();
    //ui->mainStack->setCurrentIndex(5);
    //this->ydxh_form->init();
    //��ȡ��˾�˻���Ϣ
    gszh_form->init();
    //��ȡ��˾�ͷ��绰
    _getCompanyTelThread->start();
}

void NavigatorForm::initSignalSlot()
{
    connect(ui->btn_ydjf, SIGNAL(clicked()), this, SLOT(changeMainFrame(int)));
}

void NavigatorForm::changeMainFrame(int index)
{
    ui->mainStack->setCurrentIndex(index);
}

void NavigatorForm::on_btn_ydjf_clicked()
{
    //QMessageBox::warning(this,tr("����"),Singleton::GetInstance()->getUser().btnList,QMessageBox::Ok);
    qDebug()<<"Ȩ���б�"+Singleton::GetInstance()->getUser().btnList;
    if (!Singleton::GetInstance()->getUser().btnList.contains("�ֻ��ɷ�")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_ydjf->setEnabled(false);
    ui->mainStack->setCurrentIndex(2);
    this->jf_form->init();
    ui->btn_ydjf->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_jfrb_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�ɷ��ձ�")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_jfrb->setEnabled(false);
    ui->mainStack->setCurrentIndex(3);
    this->jfrb_form->init();
    ui->btn_jfrb->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_jfyb_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�ɷ��±�")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_jfyb->setEnabled(false);
    ui->mainStack->setCurrentIndex(4);
    this->jfyb_form->init();
    ui->btn_jfyb->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_ydxh_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�ֻ�ѡ��")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_ydxh->setEnabled(false);
    this->ydxh_form->init();
    ui->mainStack->setCurrentIndex(5);
    ui->btn_ydxh->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_skcx_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�ۿ���ѯ")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_skcx->setEnabled(false);
    this->skcx_form->init();
    ui->mainStack->setCurrentIndex(6);
    ui->btn_skcx->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}


void NavigatorForm::on_btn_skjs_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�ۿ�����")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_skjs->setEnabled(false);
    this->skjx_form->init();
    ui->mainStack->setCurrentIndex(7);
    ui->btn_skjs->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_kcxk_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("���С��")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->kcxk_form->init();
    ui->mainStack->setCurrentIndex(8);
}


void NavigatorForm::on_btn_tczfcx_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�ײ��ʷѲ�ѯ")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_tczfcx->setEnabled(false);
    this->tczfcx_form->init();
    ui->mainStack->setCurrentIndex(9);
    ui->btn_tczfcx->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_ywsl_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("ҵ������")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }

    this->setCursor(Qt::BusyCursor);
    ui->btn_ywsl->setEnabled(false);
    this->ywbl_form->init();
    ui->mainStack->setCurrentIndex(10);
    ui->btn_ywsl->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_ywslcx_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("ҵ�������ѯ")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_ywslcx->setEnabled(false);
    this->ywslcx_form->init();
    ui->mainStack->setCurrentIndex(11);
    ui->btn_ywslcx->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_zhye_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("��ֵ��ϸ")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_zhye->setEnabled(false);
    this->zhye_form->init();
    ui->mainStack->setCurrentIndex(12);
    ui->btn_zhye->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_zhcz_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�˻���ֵ")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_zhcz->setEnabled(false);
    this->zhcz_form->init();
    ui->mainStack->setCurrentIndex(13);
    ui->btn_zhcz->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_xkkk_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("С���ۿ�")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->xkkk_form->init();
    ui->mainStack->setCurrentIndex(14);
}

void NavigatorForm::on_btn_xgmm_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�����޸�")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_xgmm->setEnabled(false);
    this->xgmm_form->init();
    ui->mainStack->setCurrentIndex(15);
    ui->btn_xgmm->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_yhxxxg_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�û���Ϣ�޸�")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_yhxxxg->setEnabled(false);
    this->yhxxxg_form->init();
    ui->mainStack->setCurrentIndex(16);
    ui->btn_yhxxxg->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_zxgg_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("���¹���")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_zxgg->setEnabled(false);
    this->zxgg_form->init();
    ui->mainStack->setCurrentIndex(17);
    ui->btn_zxgg->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_gszh_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("��˾�˻�")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    ui->mainStack->setCurrentIndex(18);
}

void NavigatorForm::on_btn_drjymx_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("���ս�����ϸ")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_drjymx->setEnabled(false);
    this->jymx_form->init();
    ui->mainStack->setCurrentIndex(19);
    ui->btn_drjymx->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_drjjtj_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("���ս���ͳ��")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_drjjtj->setEnabled(false);
    this->drjytj_form->init();
    ui->mainStack->setCurrentIndex(23);
    ui->btn_drjjtj->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_yxcz_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("��Ϸ��ֵ")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }

    this->setCursor(Qt::BusyCursor);
    ui->btn_yxcz->setEnabled(false);
    yxcz_form->initAll();
    ui->mainStack->setCurrentIndex(20);
    ui->btn_yxcz->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);

}

void NavigatorForm::on_btn_gmjp_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�����Ʊ")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    ui->mainStack->setCurrentIndex(21);
}

void NavigatorForm::on_btn_gmczk_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("��������")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_gmczk->setEnabled(false);
    this->klxs_form->init();
    ui->mainStack->setCurrentIndex(22);
    ui->btn_gmczk->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}


void NavigatorForm::on_btn_dbfjs_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("����ѽ���")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }
    this->setCursor(Qt::BusyCursor);
    ui->btn_dbfjs->setEnabled(false);
    this->dbfjs_form->init();
    ui->mainStack->setCurrentIndex(24);
    ui->btn_dbfjs->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btn_kdjf_clicked()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�������")) {
        QMessageBox::warning(this,tr("����"),tr("��û��ʹ�øù��ܵ�Ȩ��!"),QMessageBox::Ok);
        return;
    }

    this->setCursor(Qt::BusyCursor);
    ui->btn_kdjf->setEnabled(false);
    this->kdcz_form->initAll();
    ui->mainStack->setCurrentIndex(25);
    ui->btn_kdjf->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void NavigatorForm::on_btnLoggout_clicked()
{
    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__loggout req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    qDebug()<<"user_id:"+QString::fromStdString(userId);
    strcpy(buffer1, userId.data());
    req.userId = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    qDebug()<<"session:"+Singleton::GetInstance()->session_id;
    req.sessionId = buffer2;

    _ns1__loggoutResponse res;
    this->setCursor(Qt::BusyCursor);
    ui->btnLoggout->setEnabled(false);
    if (soap.__ns5__loggout(&req,&res) == SOAP_OK) {
        //�ɹ��˳�
        //QMessageBox::warning(this,tr("����"),"�ɹ��˳�",QMessageBox::Ok);
    } else {
        QMessageBox::warning(this,tr("����"),"��������������ϵ����Ա",QMessageBox::Ok);
    }
    ui->btnLoggout->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);

    //���������ʾ��
    this->news_alert_dialog->saveFile();
    this->news_alert_dialog->reset();
    this->_newsAlertThread->terminate();
    emit loggout();
}

void NavigatorForm::setMoney()
{
    //QMessageBox::warning(this,tr("����"),QString::number(Singleton::GetInstance()->getUser().money),QMessageBox::Ok);
    ui->btnMoney->setText(QString::number(Singleton::GetInstance()->getUser().money));
}

void NavigatorForm::setName()
{
    ui->txtName->setText(Singleton::GetInstance()->getUser().loggingName);
}

void NavigatorForm::isShowNewsAlert()
{
    news_alert_dialog->testShow();
    if (this->_newsAlertThread->isNetworkConnected == false) {
        QMessageBox::warning(this,tr("����"),"û���������磡",QMessageBox::Ok);
    }
}

void NavigatorForm::on_btnMoney_clicked()
{
    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetUserInfo req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string username = NetSecurity::encrypt(Singleton::GetInstance()->getUser().loggingName);
    strcpy(buffer1, username.data());
    req.username = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    std::string password = NetSecurity::encrypt(Singleton::GetInstance()->getUser().password);
    strcpy(buffer2, password.data());
    req.password = buffer2;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer3;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
    strcpy(buffer4, clientType.data());
    req.clientType = buffer4;

    _ns1__GetUserInfoResponse res;
    this->setCursor(Qt::BusyCursor);
    ui->btnMoney->setEnabled(false);
    if (soap.__ns5__GetUserInfo(&req,&res) == SOAP_OK) {
        //���»����ڿͻ��˵�money
        double newMoney = res.GetUserInfoResult->money;
        UserVO user = Singleton::GetInstance()->getUser();
        user.money = newMoney;
        Singleton::GetInstance()->setUser(user);
        ui->btnMoney->setText(QString::number(Singleton::GetInstance()->getUser().money));
    } else {
        QMessageBox::warning(this,tr("����"),"��������������ϵ����Ա",QMessageBox::Ok);
    }
    this->setCursor(Qt::ArrowCursor);
    ui->btnMoney->setEnabled(true);
}
