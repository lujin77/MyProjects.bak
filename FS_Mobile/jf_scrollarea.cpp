#include "jf_scrollarea.h"
#include "ui_jf_scrollarea.h"
#include <QStringList>
#include <QMessageBox>
#include "gsoap/soapPaymentFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "gsoap/soapHttpServiceSoapProxy.h"
#include "gsoap/soapMobileWebServiceSoapProxy.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include <QSound>
#include <QPrinter>
#include <QTextDocument>
#include <config.h>
#include <QFileDialog>
#include <exception>
#include <QAxObject>
#include "printer.h"
#include "EncryptUtil.h"

GetLocationThread::GetLocationThread(jf_ScrollArea *jf_ScrollArea_ptr)
{
    _ref = jf_ScrollArea_ptr;
}

void GetLocationThread::run()
{
    qDebug()<<"�����ȡ����������߳�";
    //TODO �ύ��������ѯ������
    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetLocation req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string phoneNo = NetSecurity::encrypt(_ref->ui->txi_PhoneNo->text());
    strcpy(buffer1, phoneNo.data());
    //qDebug()<<"phoneNo:"+QString::fromStdString(phoneNo);
    req.phoneNo = buffer1;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
    strcpy(buffer3, clientType.data());
    //qDebug()<<"clientType:"+QString::fromStdString(clientType);
    req.clientType = buffer3;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    //qDebug()<<"session:"+QString::fromStdString(phoneNo);
    req.sessionId = buffer2;

    _ns1__GetLocationResponse res;
    if (soap.__ns3__GetLocation(&req,&res) == SOAP_OK) {
        QString str = QString::fromUtf8(res.GetLocationResult);
        if (str == "") {
            _ref->ui->txt_area->setText("δ֪");
        } else {
            _ref->ui->txt_area->setText(str);
        }
    } else {
        qDebug()<<"�������������ܻ�ȡ��������";
    }
    qDebug()<<"��ȡ����������̣߳��������";

    //��ѯ��־λ��ȷ���Ƿ��Զ���ȡ
    UtilFunctionWebServiceSoap util_soap;
    soap_set_mode(util_soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetDicContentByCondition util_req;

    char util_buffer0[255];
    memset(util_buffer0,0,255*sizeof(char));
    strcpy(util_buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    util_req.sessionId = util_buffer0;

    char util_buffer1[255];
    memset(util_buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='�ͻ�������' and [Name]='�Զ���ѯ������' and [Enabled]=1 ";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    util_req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse util_res;
    if (util_soap.__ns7__GetDicContentByCondition(&util_req,&util_res) == SOAP_OK) {
        qDebug()<<"�Զ���ȡ������Ϣ��־:"+QString::fromUtf8(util_res.GetDicContentByConditionResult->DIC_USCOREContent[0]->Code);
        if (QString::fromUtf8(util_res.GetDicContentByConditionResult->DIC_USCOREContent[0]->Code) == "��") {
            _ref->_auto_get_location = true;
        } else {
            _ref->_auto_get_location = false;
        }
    } else {
        qDebug()<<"�������������ܻ�ȡ�Զ���ȡ�����صı�־λ";
    }
}


GetNoInfoThread::GetNoInfoThread(jf_ScrollArea *jf_ScrollArea_ptr)
{
    _ref = jf_ScrollArea_ptr;
}

void GetNoInfoThread::run()
{

    qDebug()<<"�����ȡ��ͨ������ϸ��Ϣ���߳�";
    HttpServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__queryPhoneNOInfo req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    //std::string phoneNO = NetSecurity::encrypt(_ref->ui->txi_PhoneNo->text());
    strcpy(buffer1, _ref->ui->txi_PhoneNo->text().toUtf8().data());
    req.phoneNO = buffer1;

    _ns1__queryPhoneNOInfoResponse res;
    if (soap.__ns9__queryPhoneNOInfo(&req,&res) == SOAP_OK) {
        if (QString::fromUtf8(res.queryPhoneNOInfoResult->UserName) == "") {
            _ref->ui->txt_name->setText("δ֪");
            _ref->ui->txt_now_money->setText("δ֪");
            _ref->ui->txt_brand->setText("δ֪");
        } else {
            QString name = QString::fromUtf8(res.queryPhoneNOInfoResult->UserName);
            QString money = QString::fromUtf8(res.queryPhoneNOInfoResult->Balance);
            QString brand = QString::fromUtf8(res.queryPhoneNOInfoResult->PhoneType);
            qDebug()<<"Ʒ��:"+brand;

            if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
                //���˷��ƶ��ĺ���
                if (brand.contains("���еش�") || brand.contains("ȫ��ͨ") || brand.contains("������")) {

                    //��ѯ���ǻ���
                    _ref->_getNoInfolock.lockForWrite();
                    if (_ref->_getNoInfoSign == 0) {
                        _ref->ui->txt_name->setText(name);
                        _ref->ui->txt_now_money->setText(money);
                        _ref->ui->txt_brand->setText(brand);
                        _ref->_getNoInfoSign == 1;
                    }
                    _ref->_getNoInfolock.unlock();
                } else {
                    _ref->_getNoInfolock.lockForWrite();
                    _ref->ui->txt_name->setText("δ֪");
                    _ref->ui->txt_now_money->setText("δ֪");
                    _ref->ui->txt_brand->setText("δ֪");
                    _ref->_getNoInfoSign == 3;
                    _ref->_getNoInfolock.unlock();
                }
            } else {
                //���˷���ͨ���ŵĺ���
                if (brand.contains("���еش�") || brand.contains("ȫ��ͨ") || brand.contains("������")) {

                    _ref->_getNoInfolock.lockForWrite();
                    _ref->ui->txt_name->setText("δ֪");
                    _ref->ui->txt_now_money->setText("δ֪");
                    _ref->ui->txt_brand->setText("δ֪");
                    _ref->_getNoInfoSign == 3;
                    _ref->_getNoInfolock.unlock();

                } else {
                    //��ѯ���ǻ���
                    _ref->_getNoInfolock.lockForWrite();
                    if (_ref->_getNoInfoSign == 0) {
                        _ref->ui->txt_name->setText(name);
                        _ref->ui->txt_now_money->setText(money);
                        _ref->ui->txt_brand->setText(brand);
                        _ref->_getNoInfoSign == 1;
                    }
                    _ref->_getNoInfolock.unlock();
                }
            }
        }
    }
    else {
        qDebug()<<"�������������ܻ�ȡ������ϸ��Ϣ";
    }
    qDebug()<<"��ȡ������ϸ��Ϣ���̣߳��������";

}

GetNoServiceThread::GetNoServiceThread(jf_ScrollArea *jf_ScrollArea_ptr)
{
    _ref = jf_ScrollArea_ptr;
}

void GetNoServiceThread::run()
{

    qDebug()<<"�����ȡ�ƶ������ײ͵��߳�";
    MobileWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__queryPhoneNOInfo req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    //std::string phoneNO = NetSecurity::encrypt(_ref->ui->txi_PhoneNo->text());
    strcpy(buffer1, _ref->ui->txi_PhoneNo->text().toUtf8().data());
    req.phoneNO = buffer1;

    _ns1__queryPhoneNOInfoResponse res;
    if (soap.__ns11__queryPhoneNOInfo(&req,&res) == SOAP_OK) {
        if (QString::fromUtf8(res.queryPhoneNOInfoResult->UserName) != "") {
            QString name = QString::fromUtf8(res.queryPhoneNOInfoResult->UserName);
            QString money = QString::fromUtf8(res.queryPhoneNOInfoResult->Balance);
            QString brand = QString::fromUtf8(res.queryPhoneNOInfoResult->PhoneType);

            //��ѯ���ǻ���
            _ref->_getNoInfolock.lockForWrite();
            if (_ref->_getNoInfoSign == 0 || _ref->_getNoInfoSign == 1) {
                _ref->ui->txt_name->setText(name);
                _ref->ui->txt_now_money->setText(money);
                _ref->ui->txt_brand->setText(brand);
                _ref->_getNoInfoSign == 2;
            }
            _ref->_getNoInfolock.unlock();
        }
    }
    else {
        qDebug()<<"�������������ܻ�ȡ������ϸ��Ϣ";
    }
    qDebug()<<"��ȡ������ϸ��Ϣ���̣߳��������";

}

//��ȡ�ɷѼ�¼
GetPayment_jf_Thread::GetPayment_jf_Thread(jf_ScrollArea *jf_ScrollArea_ptr)
{
    _ref = jf_ScrollArea_ptr;
}

void GetPayment_jf_Thread::run()
{
    qDebug()<<"������ȡ�ɷ��б���߳�";
    int total = 0;
    float totalPay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPaymentRecord req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [�����û�Id]='"+Singleton::GetInstance()->getUser().Id+"' order by [�ɷ�ʱ��] desc";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    qDebug()<<"condition:"+QString::fromStdString(condition);
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetPaymentRecordResponse res;
    if (soap.__ns3__GetPaymentRecord(&req,&res) == SOAP_OK) {
        _ref->ui->tbl_detail->clearContents();
        QString content = "";
        total = res.GetPaymentRecordResult->__sizePaymentItem;
        for (int i=0; i<total; ++i) {
            for (int j=0; j<9; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->telNo);
                        break;
                    case 3:
                        content = QString::number(res.GetPaymentRecordResult->PaymentItem[i]->customerBeforeMoney,'f',2);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPaymentRecordResult->PaymentItem[i]->chargeMoney,'f',2);
                        float payMoney = res.GetPaymentRecordResult->PaymentItem[i]->chargeMoney;
                        totalPay += payMoney;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->state);
                        break;

                    case 6:
                        content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->SP);
                        break;
                    case 7:
                        content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->area);
                        break;
                    case 8:
                        if (-1 == res.GetPaymentRecordResult->PaymentItem[i]->chargeTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPaymentRecordResult->PaymentItem[i]->chargeTime)));
                        content = QString(cTime);
                        break;
                }
                if (i < 10) {
                    QTableWidgetItem *item = new QTableWidgetItem (content);
                    _ref->ui->tbl_detail->setItem(i, j, item);
                }
            }
        }
        QString countStr = "���½ɷ�:��" + QString::number(total) +"����";
        QString totalPayString = "�ɷѽ��:��" + QString::number(totalPay,'f',2) +"��Ԫ";
        _ref->ui->txt_rpt_count->setText(countStr);
        _ref->ui->txt_rpt_money->setText(totalPayString);
    }
    else {
        qDebug()<<"�������������ܻ�ȡ�ɷ��б�";
    }
    qDebug()<<"��ȡ�ɹ�";
}

jf_ScrollArea::jf_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::jf_ScrollArea)
{
    ui->setupUi(this);
    //��ͷ��Ϣ
    QString countStr = "���½ɷ�:��0����";
    QString totalPayString = "�ɷѽ��:��0��Ԫ";
    ui->txt_rpt_count->setText(countStr);
    ui->txt_rpt_money->setText(totalPayString);

    ui->tbl_detail->setColumnCount(9);
    ui->tbl_detail->setRowCount(10);
    ui->tbl_detail->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ��һ��
    ui->tbl_detail->setSelectionMode(QAbstractItemView::SingleSelection); //����ֻ��ѡ��һ�У����ܶ���ѡ��
    ui->tbl_detail->setEditTriggers(QAbstractItemView::AllEditTriggers);   //����ÿ�����ݲ��ɸ���
    ui->tbl_detail->setAlternatingRowColors(true);
    QStringList list;
    list << "Id" << "�����û�" << "�ɷѺ���" << "�ɷ�ǰ���" << "�ɷѽ��"
         << "�ɷ�״̬" << "��Ӫ��" << "�������" << "�ɷ�ʱ��";
    ui->tbl_detail->setHorizontalHeaderLabels(list);
    ui->tbl_detail->horizontalHeader()->setStretchLastSection(true); //��������ط�
    ui->tbl_detail->hideColumn(0);
    ui->tbl_detail->setColumnWidth(1,80);
    ui->tbl_detail->setColumnWidth(2,100);
    ui->tbl_detail->setColumnWidth(3,80);
    ui->tbl_detail->setColumnWidth(4,80);
    ui->tbl_detail->setColumnWidth(5,80);
    ui->tbl_detail->setColumnWidth(6,80);
    ui->tbl_detail->setColumnWidth(7,80);
    //ui->tbl_detail->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    QRegExp regx_int("[0-9]+$");
    //QRegExp regx_float("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$");
    QValidator *validator_num = new QRegExpValidator(regx_int, this);
    //QValidator *validator_float = new QRegExpValidator(regx_float, this);
    ui->txi_PhoneNo->setValidator(validator_num);
    ui->txi_money->setValidator(validator_num);

    //ע���¼�
    //this->connect(ui->btn_submit,SIGNAL(clicked()),this,SLOT(on_btn_submit_clicked()));
    //this->connect(ui->txi_PhoneNo,SIGNAL(textChanged(QString)),this,SLOT(on_txi_PhoneNo_textChanged(QString)));

    //�߳�
    _getLocationThread = new GetLocationThread(this);
    _getNoInfoThread = new GetNoInfoThread(this);
    _getNoServiceThread = new GetNoServiceThread(this);
    _getPayment_jf_Thread = new GetPayment_jf_Thread(this);

    _auto_get_location = false;

    //��ѯ������Ϣ����
    _getNoInfoSign = 0;

    //���ػ�
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        ui->txt_title->setText("      �ƶ��ɷ�");
    } else {
        ui->txt_title->setText("      �ֻ��ɷ�");
    }

    _tel_size = 0;
    _money_size = 0;
}

jf_ScrollArea::~jf_ScrollArea()
{
    qDebug()<<"�ɷѴ�������";
    if (_getLocationThread != NULL) {
        _getLocationThread->terminate();
        _getLocationThread->exit();
        delete _getLocationThread;
    }
    if (_getNoInfoThread != NULL) {
        _getNoInfoThread->terminate();
        _getNoInfoThread->exit();
        delete _getNoInfoThread;
    }
    if (_getNoServiceThread != NULL) {
        _getNoServiceThread->terminate();
        _getNoServiceThread->exit();
        delete _getNoServiceThread;
    }
    if (_getPayment_jf_Thread != NULL) {
        _getPayment_jf_Thread->terminate();
        _getPayment_jf_Thread->exit();
        delete _getPayment_jf_Thread;
    }
    delete ui;
}

void jf_ScrollArea::init()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("�����ɷ�")) {
        ui->btnPayWithList->setEnabled(false);
    } else {
        ui->btnPayWithList->setEnabled(true);
    }
    reset();
    refresh();
}

void jf_ScrollArea::refresh()
{
    if (!_getPayment_jf_Thread->isRunning())
        _getPayment_jf_Thread->start();
}


void jf_ScrollArea::on_btn_submit_clicked()
{
    pay();
}

void jf_ScrollArea::on_btn_search_clicked()
{
    if (ui->txi_PhoneNo->text().at(0) == '0') {
        //�����л��͵���
        if (ui->txi_PhoneNo->text().at(1) == '8'
                && ui->txi_PhoneNo->text().at(2) == '7'
                && ui->txi_PhoneNo->text().at(3) == '1') {
            //�̻�
            if (ui->txi_PhoneNo->text().length() != 12) {
                QMessageBox::warning(this,tr("����"),"����ѯ����������λ��������������Ӧ��Ϊ12λ",QMessageBox::Ok);
                return;
            }
        } else {
            //�̻�
            if (ui->txi_PhoneNo->text().length() != 11) {
                QMessageBox::warning(this,tr("����"),"����ѯ����������λ������",QMessageBox::Ok);
                return;
            }
        }
    } else if (ui->txi_PhoneNo->text().at(0) == '1') {
        //�ֻ�
        if (ui->txi_PhoneNo->text().length() != 11) {
            QMessageBox::warning(this,tr("����"),"����ѯ���ֻ���������",QMessageBox::Ok);
            return;
        }
    }

    //����
    _getNoInfolock.lockForWrite();
    _getNoInfoSign = 0;
    _getNoInfolock.unlock();

    ui->txt_name->clear();
    ui->txt_now_money->clear();
    ui->txt_brand->clear();

    //�������ͨ���ſͻ��ˣ��߽ӿ�
    if (Config::GetInstance()->_client_type == "��ͨ���ſͻ���") {
        if (_getNoInfoThread->isRunning()) {
            _getNoInfoThread->terminate();
        }
        _getNoInfoThread->start();
    }

    //������ƶ��ͻ��ˣ���ѯ����
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        if (_getNoServiceThread->isRunning()) {
            _getNoServiceThread->terminate();
        }
        _getNoServiceThread->start();
    }
}

void jf_ScrollArea::on_btn_reset_clicked()
{
    reset();
}

void jf_ScrollArea::on_txi_PhoneNo_textChanged(const QString &arg1)
{
    if (arg1.length() == 7) {
        //TODO �ύ��������ѯ������
        if (_getLocationThread->isRunning()) {
            _getLocationThread->terminate();
        }
        _getLocationThread->start();
    }

    if (ui->txi_PhoneNo->text().at(0) == '1' && arg1.length() == 11) {
        ui->txi_money->setFocus();
        if (this->_auto_get_location == true) {
            qDebug()<<"�Զ���ѯ������ϸ��Ϣ";

            //����
            _getNoInfolock.lockForWrite();
            _getNoInfoSign = 0;
            _getNoInfolock.unlock();

            ui->txt_name->clear();
            ui->txt_now_money->clear();
            ui->txt_brand->clear();

            //�������ͨ���ſͻ��ˣ��߽ӿ�
            if (Config::GetInstance()->_client_type == "��ͨ���ſͻ���") {
                if (_getNoInfoThread->isRunning()) {
                    _getNoInfoThread->terminate();
                }
                _getNoInfoThread->start();
            }

            //������ƶ��ͻ��ˣ���ѯ����
            if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
                if (_getNoServiceThread->isRunning()) {
                    _getNoServiceThread->terminate();
                }
                _getNoServiceThread->start();
            }
        }
    } else if (ui->txi_PhoneNo->text().at(0) == '0'
                && ui->txi_PhoneNo->text().at(1) == '8'
                && ui->txi_PhoneNo->text().at(2) == '7'
                && ui->txi_PhoneNo->text().at(3) == '1'
                && arg1.length() == 12) {
        ui->txi_money->setFocus();
        if (this->_auto_get_location == true) {
            qDebug()<<"�Զ���ѯ������ϸ��Ϣ";

            //����
            _getNoInfolock.lockForWrite();
            _getNoInfoSign = 0;
            _getNoInfolock.unlock();

            ui->txt_name->clear();
            ui->txt_now_money->clear();
            ui->txt_brand->clear();

            //�������ͨ���ſͻ��ˣ��߽ӿ�
            if (Config::GetInstance()->_client_type == "��ͨ���ſͻ���") {
                if (_getNoInfoThread->isRunning()) {
                    _getNoInfoThread->terminate();
                }
                _getNoInfoThread->start();
            }

            //������ƶ��ͻ��ˣ���ѯ����
            if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
                if (_getNoServiceThread->isRunning()) {
                    _getNoServiceThread->terminate();
                }
                _getNoServiceThread->start();
            }
        }
    } else if (ui->txi_PhoneNo->text().at(0) == '0'
               && (ui->txi_PhoneNo->text().at(1) != '8'
                   || ui->txi_PhoneNo->text().at(2) != '7'
                   || ui->txi_PhoneNo->text().at(3) != '1')
               && arg1.length() == 11) {
        ui->txi_money->setFocus();
        if (this->_auto_get_location == true) {
            qDebug()<<"�Զ���ѯ������ϸ��Ϣ";

            //����
            _getNoInfolock.lockForWrite();
            _getNoInfoSign = 0;
            _getNoInfolock.unlock();

            ui->txt_name->clear();
            ui->txt_now_money->clear();
            ui->txt_brand->clear();

            //�������ͨ���ſͻ��ˣ��߽ӿ�
            if (Config::GetInstance()->_client_type == "��ͨ���ſͻ���") {
                if (_getNoInfoThread->isRunning()) {
                    _getNoInfoThread->terminate();
                }
                _getNoInfoThread->start();
            }

            //������ƶ��ͻ��ˣ���ѯ����
            if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
                if (_getNoServiceThread->isRunning()) {
                    _getNoServiceThread->terminate();
                }
                _getNoServiceThread->start();
            }
        }
    }

    //����������
    if (arg1.size() > _tel_size) {
        QString lastLetter = arg1.right(1);
        //QMessageBox::warning(this,tr("����"),lastLetter,QMessageBox::Ok);
        if (lastLetter == "1") {
            QSound::play("sound/1.wav");
        } else if (lastLetter == "2") {
            QSound::play("sound/2.wav");
        } else if (lastLetter == "3") {
            QSound::play("sound/3.wav");
        } else if (lastLetter == "4") {
            QSound::play("sound/4.wav");
        } else if (lastLetter == "5") {
            QSound::play("sound/5.wav");
        } else if (lastLetter == "6") {
            QSound::play("sound/6.wav");
        } else if (lastLetter == "7") {
            QSound::play("sound/7.wav");
        } else if (lastLetter == "8") {
            QSound::play("sound/8.wav");
        } else if (lastLetter == "9") {
            QSound::play("sound/9.wav");
        } else if (lastLetter == "0") {
            QSound::play("sound/0.wav");
        }
    }

    _tel_size = arg1.size();

}

void jf_ScrollArea::keyPressEvent(QKeyEvent *event)
{    
    //QMessageBox::warning(this,tr("����"),QString::number(event->key()),QMessageBox::Ok);
    switch (event->key()) {
        case 16777220:
            pay();
            break;
        case 16777221:
            pay();
            break;
    }
}

//�ɷ�
void jf_ScrollArea::pay()
{
    if (ui->txi_PhoneNo->text() == "") {
        QMessageBox::warning(this,tr("����"),tr("�绰���벻��Ϊ��!"),QMessageBox::Ok);
        ui->txi_PhoneNo->setFocus();
        return;
    } else {
        if (ui->txi_PhoneNo->text().at(0) == '0' && Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
            QMessageBox::warning(this,tr("����"),tr("�ƶ��ͻ��˲���Ϊ�����ɷ�!"),QMessageBox::Ok);
            ui->txi_PhoneNo->setFocus();
            return;
        }
    }

    if (ui->txi_PhoneNo->text().at(0) == '0') {
        //�����л��͵���
        if (ui->txi_PhoneNo->text().at(1) == '8'
                && ui->txi_PhoneNo->text().at(2) == '7'
                && ui->txi_PhoneNo->text().at(3) == '1') {
            //�̻�
            if (ui->txi_PhoneNo->text().length() != 12) {
                QMessageBox::warning(this,tr("����"),"����ѯ����������λ��������������Ӧ��Ϊ12λ",QMessageBox::Ok);
                return;
            }
        } else {
            //�̻�
            if (ui->txi_PhoneNo->text().length() != 11) {
                QMessageBox::warning(this,tr("����"),"����ѯ����������λ������",QMessageBox::Ok);
                return;
            }
        }

    } else if (ui->txi_PhoneNo->text().at(0) == '1') {
        //�ֻ�
        if (ui->txi_PhoneNo->text().length() != 11) {
            QMessageBox::warning(this,tr("����"),"����ѯ���ֻ�����λ������",QMessageBox::Ok);
            return;
        }
    }

    if (ui->txi_money->text() == "") {
        QMessageBox::warning(this,tr("����"),tr("�ɷѽ���Ϊ��!"),QMessageBox::Ok);
        ui->txi_money->setFocus();
        return;
    } else {
        if (ui->txi_money->text().toDouble() < 10 && Config::GetInstance()->_client_type == "��ͨ���ſͻ���") {
            QMessageBox::warning(this,tr("����"),tr("��ͨ����ź������ֻ�ܽɷ�10Ԫ!"),QMessageBox::Ok);
            ui->txi_money->setFocus();
            return;
        }
        if (ui->txi_money->text().toDouble() < 1 && Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
            QMessageBox::warning(this,tr("����"),tr("�ƶ��������ֻ�ܽɷ�1Ԫ!"),QMessageBox::Ok);
            ui->txi_money->setFocus();
            return;
        }
    }

    QString str = "ȷ��Ҫ��" + ui->txi_PhoneNo->text() + "���нɷ���";
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "�ɷ�", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        //TODO �ύ����������
        PaymentFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__PayMoney req;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        std::string phoneNo = NetSecurity::encrypt(ui->txi_PhoneNo->text());
        qDebug()<<"phoneNo:"+QString::fromStdString(phoneNo);
        strcpy(buffer1, phoneNo.data());
        req.phoneNo = buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        std::string money = NetSecurity::encrypt(ui->txi_money->text());
        qDebug()<<"money:"+QString::fromStdString(money);
        strcpy(buffer2, money.data());
        req.money = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        qDebug()<<"userId:"+QString::fromStdString(userId);
        strcpy(buffer3, userId.data());
        req.userId = buffer3;

        char _buffer3[255];
        memset(_buffer3,0,255*sizeof(char));
        string userName = NetSecurity::encrypt(Singleton::GetInstance()->getUser().loggingName);
        qDebug()<<"userName:"+QString::fromStdString(userName);
        strcpy(_buffer3, userName.data());
        req.userName = _buffer3;

        char buffer4[255];
        memset(buffer4,0,255*sizeof(char));
        strcpy(buffer4, Singleton::GetInstance()->session_id.toUtf8().data());
        qDebug()<<"session_id:"+Singleton::GetInstance()->session_id;
        req.sessionId = buffer4;

        char buffer5[255];
        memset(buffer5,0,255*sizeof(char));
        std::string SP = NetSecurity::encrypt(Config::GetInstance()->_sp);
        qDebug()<<"SP:"+QString::fromStdString(SP);
        strcpy(buffer5, SP.data());
        req.SP = buffer5;

        _ns1__PayMoneyResponse res;
        this->setCursor(Qt::BusyCursor);
        ui->btn_submit->setEnabled(false);
        ui->txi_PhoneNo->setEnabled(false);
        ui->txi_money->setEnabled(false);
        if (soap.__ns3__PayMoney(&req,&res) == SOAP_OK) {
            QString result = QString::fromUtf8(res.PayMoneyResult);
            QMessageBox::warning(this,tr("��ʾ"),result,QMessageBox::Ok);
            if (result.contains("�ɹ�")) {
                //���»����ڿͻ��˵�money
//                double newMoney = Singleton::GetInstance()->getUser().money;
//                newMoney -= ui->txi_money->text().toDouble();
//                UserVO user = Singleton::GetInstance()->getUser();
//                user.money = newMoney;
//                Singleton::GetInstance()->setUser(user);

                UserFunctionWebServiceSoap soap;
                soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
                _ns1__GetUserInfo req1;

                char buffer1[255];
                memset(buffer1,0,255*sizeof(char));
                std::string username = NetSecurity::encrypt(Singleton::GetInstance()->getUser().loggingName);
                strcpy(buffer1, username.data());
                req1.username = buffer1;

                char buffer2[255];
                memset(buffer2,0,255*sizeof(char));
                std::string password = NetSecurity::encrypt(Singleton::GetInstance()->getUser().password);
                strcpy(buffer2, password.data());
                req1.password = buffer2;

                char buffer3[255];
                memset(buffer3,0,255*sizeof(char));
                strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
                req1.sessionId = buffer3;

                char buffer4[255];
                memset(buffer4,0,255*sizeof(char));
                std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
                strcpy(buffer4, clientType.data());
                req1.clientType = buffer4;

                _ns1__GetUserInfoResponse res1;
                if (soap.__ns5__GetUserInfo(&req1,&res1) == SOAP_OK) {
                    //���»����ڿͻ��˵�money
                    double newMoney = res1.GetUserInfoResult->money;
                    UserVO user = Singleton::GetInstance()->getUser();
                    user.money = newMoney;
                    Singleton::GetInstance()->setUser(user);
                } else {
                    QMessageBox::warning(this,tr("����"),"��������������ϵ����Ա",QMessageBox::Ok);
                }

                emit updateMoney();
                refresh();
                if (ui->rdo_print_on->isChecked() == true) {
                    rb = QMessageBox::warning(NULL, "��ӡ", "�Ƿ�Ҫ��ӡ���ݣ�", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    if (rb == QMessageBox::Yes) {
                        Printer::GetInstance()->printJF("[�ɷѿͻ�����]='"+ui->txi_PhoneNo->text()+"' and �ɷѽ��='"+ui->txi_money->text()+"' order by [�ɷ�ʱ��] desc");
                    }
                }
                reset();
            }
            ui->txi_PhoneNo->setFocus();
        }
        else {
            QMessageBox::warning(this,tr("��ʾ"),"����������",QMessageBox::Ok);
        }
        this->setCursor(Qt::ArrowCursor);
        ui->btn_submit->setEnabled(true);
        ui->txi_PhoneNo->setEnabled(true);
        ui->txi_money->setEnabled(true);

    }
}

void jf_ScrollArea::reset()
{
    ui->txi_PhoneNo->clear();
    ui->txi_money->clear();
    ui->txt_area->clear();
    ui->txt_name->clear();
    ui->txt_now_money->clear();
    ui->txt_brand->clear();
    ui->txi_PhoneNo->setFocus();
    _tel_size = 0;
    _money_size = 0;
}

void jf_ScrollArea::on_btn_refresh_clicked()
{
    refresh();
}

void jf_ScrollArea::on_txi_money_textChanged(const QString &arg1)
{
    if (ui->txi_money->text().length() == 0) {
        ui->txi_PhoneNo->setFocus();
    }

    //����������
    if (arg1.size() > _money_size) {
        QString lastLetter = arg1.right(1);
        //QMessageBox::warning(this,tr("����"),lastLetter,QMessageBox::Ok);
        if (lastLetter == "1") {
            QSound::play("sound/1.wav");
        } else if (lastLetter == "2") {
            QSound::play("sound/2.wav");
        } else if (lastLetter == "3") {
            QSound::play("sound/3.wav");
        } else if (lastLetter == "4") {
            QSound::play("sound/4.wav");
        } else if (lastLetter == "5") {
            QSound::play("sound/5.wav");
        } else if (lastLetter == "6") {
            QSound::play("sound/6.wav");
        } else if (lastLetter == "7") {
            QSound::play("sound/7.wav");
        } else if (lastLetter == "8") {
            QSound::play("sound/8.wav");
        } else if (lastLetter == "9") {
            QSound::play("sound/9.wav");
        } else if (lastLetter == "0") {
            QSound::play("sound/0.wav");
        }
    }

    _money_size = arg1.size();
}

void jf_ScrollArea::on_btn_print_clicked()
{
    qDebug()<<"��ǰѡ����У�"+QString::number(ui->tbl_detail->currentRow());
    if (ui->tbl_detail->currentRow() >= 0) {
        int index = ui->tbl_detail->currentRow();
        if (ui->tbl_detail->item(index, 0) != NULL && ui->tbl_detail->item(index, 0)->text() != "") {
            Printer::GetInstance()->printJF("[Id]='"+ui->tbl_detail->item(index, 0)->text()+"'");
            QModelIndex _QModelIndex;
            ui->tbl_detail->setCurrentIndex(_QModelIndex);
            return;
        }
    } else {
        QMessageBox::warning(this,tr("��ʾ"),"��ǰû��ѡ�д�ӡ�",QMessageBox::Ok);
    }
}


void jf_ScrollArea::on_btnPayWithList_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,"ѡ���ļ�", QDir::currentPath(),QString::fromUtf8("Excel(*.xls *.xlsx)"));
    qDebug()<<file;
    //��ʱ����
    //QString data = "13087145772,10|12887869241,7|1357706194,5|";
    QString data = "";

    if (!file.isEmpty()) {
        //��ȡexcel
        try {
            QAxObject* excel = new QAxObject("Excel.Application");
            excel->setProperty("Visible", false);
            QAxObject* workbooks = excel->querySubObject("WorkBooks");
            qDebug()<<"׼����excel:"+file;
            workbooks->dynamicCall("Open (const QString&)", file);
            QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
            QAxObject* worksheets = workbook->querySubObject("WorkSheets");
            QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1);
            QAxObject* usedrange = worksheet->querySubObject("UsedRange");
            QAxObject* rows = usedrange->querySubObject("Rows");
            QAxObject* columns = usedrange->querySubObject("Columns");
            int intRowStart = usedrange->property("Row").toInt();
            int intColStart = usedrange->property("Column").toInt();
            int intCols = columns->property("Count").toInt();
            int intRows = rows->property("Count").toInt();
            QAxObject * cell;
            for (int i = intRowStart; i < intRowStart + intRows; i++)
             {
                    bool isFirst = true;
                    for (int j = intColStart; j < intColStart + intCols; j++)
                    {
                        cell = worksheet->querySubObject("Cells(int,int)", i, j);
                        qDebug() << i << j << cell->property("Value");
                        data += cell->property("Value").toString();
                        if (isFirst) {
                            data += ",";
                            isFirst = false;
                        }
                    }
                    data += "|";
            }
            excel->setProperty("DisplayAlerts", 0);
            //workbook->dynamicCall("Save(void)");
            workbook->dynamicCall("Close (Boolean)", false);
            excel->dynamicCall("Quit (void)");
            delete excel;
        } catch(QString ex) {
            QMessageBox::warning(this,tr("��ʾ"),"��ȡexcel����"+ex,QMessageBox::Ok);
        }
        qDebug()<<"�����ɷ�:"<<data;
        //�ύ�ɷ�
        PaymentFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__PayMoneyWithList req;

        std::string _data = NetSecurity::encrypt(data);
        char buffer[_data.length()];
        memset(buffer,0,_data.length()*sizeof(char));
        strcpy(buffer, _data.data());
        req.data = buffer;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        strcpy(buffer1,  userId.data());
        req.userId = buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
        req.sessionId = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        std::string SP = NetSecurity::encrypt(Config::GetInstance()->_sp);
        strcpy(buffer3, SP.data());
        req.SP = buffer3;

        _ns1__PayMoneyWithListResponse res;
        this->setCursor(Qt::BusyCursor);
        ui->btnPayWithList->setEnabled(false);
        if (soap.__ns3__PayMoneyWithList(&req,&res) == SOAP_OK) {
            QString result = QString::fromUtf8(res.PayMoneyWithListResult->result);
            QMessageBox::warning(this,tr("��ʾ"),result,QMessageBox::Ok);
            if (result.contains("�ɹ�")) {
                //���»����ڿͻ��˵�money
                double newMoney = Singleton::GetInstance()->getUser().money;
                newMoney -= res.PayMoneyWithListResult->totalMoney;
                UserVO user = Singleton::GetInstance()->getUser();
                user.money = newMoney;
                Singleton::GetInstance()->setUser(user);
                emit updateMoney();
                refresh();
                reset();
            }
            //����д���ļ�¼��д���ļ�
            if (res.PayMoneyWithListResult->failedCount > 0) {
                QFile file("fail.txt");
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream stream(&file);
                    //stream.setCodec(code);//�����������--------������
                    for (int i=0; i<res.PayMoneyWithListResult->list->__sizePayWithListItem; ++i) {
                        stream << res.PayMoneyWithListResult->list->PayWithListItem[i]->phoneNo
                               << "\t" << QString::number(res.PayMoneyWithListResult->list->PayWithListItem[i]->money,'f',2) << "\n";
                    }
                    file.close();
                }
            }
        }
        else {
            QMessageBox::warning(this,tr("��ʾ"),"����������",QMessageBox::Ok);
        }
        this->setCursor(Qt::ArrowCursor);
        ui->btnPayWithList->setEnabled(true);
    }
}
