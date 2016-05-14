#include "buynodialog.h"
#include "ui_buynodialog.h"
#include "config.h"
#include "EncryptUtil.h"
#include "singleton.h"
#include "gsoap/soapBusinessFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include <QMessageBox>

GetBuyNoConditionThread::GetBuyNoConditionThread(BuyNoDialog *BuyNoDialog_ptr)
{
    _ref = BuyNoDialog_ptr;
}

void GetBuyNoConditionThread::run()
{
    qDebug()<<"�����ȡ�����������߳�";
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetMiniCardRecord req;

    req.top = 0;

    QString queryStr = "[�����û�Id]='"+Singleton::GetInstance()->getUser().Id+"' and [�Ŷ�]='"+NoSection+"' and [ʹ��״̬]='δʹ��' ";
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        queryStr += "and [��Ӫ��]='�ƶ�'";
    } else {
        queryStr += "and [��Ӫ��]<>'�ƶ�'";
    }

    //qDebug()<<"condition:"+QString::fromStdString(condition);
    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());  
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    //qDebug()<<"session:"+QString::fromStdString(phoneNo);
    req.sessionId = buffer2;

    _ns1__GetMiniCardRecordResponse res;
    if (soap.__ns13__GetMiniCardRecord(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetMiniCardRecordResult->__sizeMiniCardItem; ++i) {
            QString name = QString::fromUtf8(res.GetMiniCardRecordResult->MiniCardItem[i]->cardNo);
            QString value = QString::fromUtf8(res.GetMiniCardRecordResult->MiniCardItem[i]->cardNo);
            _ref->ui->cbx_mini_card->addItem(name,value);
        }
        qDebug()<<"��ȡС���б�ɹ�";
    } else {
        qDebug()<<"�������������ܻ�ȡС���б�";
    }

    _ns1__GetCardService req2;

    req2.top = 0;

    queryStr = "";
    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        queryStr += " [��Ӫ��]='�ƶ�'";
    } else {
        queryStr += " [��Ӫ��]<>'�ƶ�'";
    }
    if (_ref->ui->rdo_service_type_on->isChecked()) {
        queryStr += " and [�Ƿ���]=1";
    }
    queryStr += " order by [�ײ�����]";
    qDebug()<<"condition:"+queryStr;
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer3, condition.data());
    //qDebug()<<"condition:"+QString::fromStdString(condition);
    req2.condition = buffer3;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    strcpy(buffer4, Singleton::GetInstance()->session_id.toUtf8().data());
    //qDebug()<<"session:"+QString::fromStdString(phoneNo);
    req2.sessionId = buffer4;

    _ns1__GetCardServiceResponse res2;
    if (soap.__ns13__GetCardService(&req2,&res2) == SOAP_OK) {
        _ref->ui->cbx_service->setMaxVisibleItems(15);
        for (int i=0; i<res2.GetCardServiceResult->__sizeCardService; ++i) {
            QString name = QString::fromUtf8(res2.GetCardServiceResult->CardService[i]->serviceName);
            QString value = QString::fromUtf8(res2.GetCardServiceResult->CardService[i]->serviceSpec);
            _ref->ui->cbx_service->addItem(name,value);
        }
        qDebug()<<"��ȡ�ײ��б�ɹ�";
    } else {
        qDebug()<<"�������������ܻ�ȡ�ײ��б�";
    }

    //��ȡ֤������
    UtilFunctionWebServiceSoap util_soap;
    soap_set_mode(util_soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetDicContentByCondition util_req;

    char util_buffer0[255];
    memset(util_buffer0,0,255*sizeof(char));
    strcpy(util_buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    util_req.sessionId = util_buffer0;

    char util_buffer1[255];
    memset(util_buffer1,0,255*sizeof(char));
    queryStr = "[Category]='֤������' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    util_req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse util_res;
    if (util_soap.__ns7__GetDicContentByCondition(&util_req,&util_res) == SOAP_OK) {
        for(int i=0; i<util_res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(util_res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(util_res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_zjlx->addItem(name,value);
        }
        qDebug()<<"��ȡ֤�����ͳɹ�";
    } else {
        qDebug()<<"�������������ܻ�ȡ֤�������б�";
    }
}


BuyNoDialog::BuyNoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyNoDialog)
{
    _ref_ydxh_ScrollArea = (ydxh_ScrollArea*)parent;
    _getBuyNoConditionThread = new GetBuyNoConditionThread(this);
    ui->setupUi(this);
}

BuyNoDialog::~BuyNoDialog()
{
    unlockNo();
    if (_getBuyNoConditionThread != NULL) {
        _getBuyNoConditionThread->terminate();
        _getBuyNoConditionThread->exit();
        delete _getBuyNoConditionThread;
    }
    delete ui;
}

void BuyNoDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void BuyNoDialog::init(QString No, QString price, QString NoSection)
{
    reset();
    _getBuyNoConditionThread->NoSection = NoSection;
    getCondition();
    ui->txt_No->setText(No);
    ui->txt_price->setText(price);
}

void BuyNoDialog::reset()
{
    ui->txt_No->clear();
    ui->cbx_mini_card->clear();
    ui->cbx_mini_card->addItem("","");
    ui->cbx_service->clear();
    ui->cbx_service->addItem("","");
    ui->txt_service_spec->clear();
    ui->rdo_ld_on->setChecked(true);
    ui->rdo_cl_off->setChecked(true);
    ui->txi_name->clear();
    ui->cbx_zjlx->clear();
    ui->cbx_zjlx->addItem("","");
    ui->txi_indentifyNo->clear();
}

void BuyNoDialog::getCondition()
{
    if (_getBuyNoConditionThread->isRunning()) {
        _getBuyNoConditionThread->terminate();
    }
    _getBuyNoConditionThread->start();
}

void BuyNoDialog::unlockNo()
{
    qDebug()<<"��������...";
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__UnlockNo req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string No = NetSecurity::encrypt(ui->txt_No->text());
    strcpy(buffer1, No.data());
    req.No = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer2, userId.data());
    req.userId = buffer2;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
    //qDebug()<<"session:"+QString::fromStdString(phoneNo);
    req.sessionId = buffer3;

    _ns1__UnlockNoResponse res;
    if (soap.__ns13__UnlockNo(&req,&res) == SOAP_OK) {
        QString result = QString::fromUtf8(res.UnlockNoResult);
        if (result.contains("�ɹ�")) {
            reset();
        } else {
            //QMessageBox::warning(this,tr("��ʾ"),result,QMessageBox::Ok);
            return;
        }

    } else {
        QMessageBox::warning(this,tr("��ʾ"),"�������������ܽ�������",QMessageBox::Ok);
    }
}

void BuyNoDialog::submit()
{
    QString business1 = "";
    QString business2 = "";
    QString business3 = "";

    if (ui->cbx_mini_card->currentText() == "") {
        QMessageBox::warning(this,tr("����"),tr("С������Ϊ��!"),QMessageBox::Ok);
        ui->cbx_mini_card->setFocus();
        return;
    }

    if (ui->cbx_service->currentText() == "") {
        QMessageBox::warning(this,tr("����"),tr("�ײͲ���Ϊ��!"),QMessageBox::Ok);
        ui->cbx_mini_card->setFocus();
        return;
    }

    if (ui->txi_name->text() != "") {
        if (ui->cbx_zjlx->currentText() == "") {
            QMessageBox::warning(this,tr("����"),tr("֤�����Ͳ���Ϊ��!"),QMessageBox::Ok);
            ui->cbx_mini_card->setFocus();
            return;
        }
        if (ui->txi_indentifyNo->text() == "") {
            QMessageBox::warning(this,tr("����"),tr("֤�����벻��Ϊ��!"),QMessageBox::Ok);
            ui->cbx_mini_card->setFocus();
            return;
        }
        business3 = "��������ҵ��\n������"+ui->txi_name->text()
                    +"\n֤�����ͣ�"+ui->cbx_zjlx->currentText()
                    +"\n֤�����룺"+ui->txi_indentifyNo->text();
    }

    if (ui->rdo_ld_on->isChecked()) {
        business1 = "��ͨ������ʾ";
    }

    if (ui->rdo_cl_on->isChecked()) {
        business2 = "��ͨ����ҵ��";
    }

    QString str = "ȷ��Ҫ��ͨ���룺" + ui->txt_No->text() + "��";
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "�ֻ�����", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {

        BusinessFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__SellNo req;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        std::string No = NetSecurity::encrypt(ui->txt_No->text());
        strcpy(buffer1, No.data());
        qDebug()<<"No:"+QString::fromStdString(No);
        req.No = buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        strcpy(buffer2, userId.data());
        qDebug()<<"userId:"+QString::fromStdString(userId);
        req.userId = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
        qDebug()<<"session:"+Singleton::GetInstance()->session_id;
        req.sessionId = buffer3;

        char buffer4[255];
        memset(buffer4,0,255*sizeof(char));
        string miniCard = NetSecurity::encrypt(ui->cbx_mini_card->currentText());
        strcpy(buffer4, miniCard.data());
        qDebug()<<"miniCard:"+QString::fromStdString(miniCard);
        req.miniCard = buffer4;

        char buffer5[255];
        memset(buffer5,0,255*sizeof(char));
        string serviceName = NetSecurity::encrypt(ui->cbx_service->currentText());
        strcpy(buffer5, serviceName.data());
        qDebug()<<"serviceName:"+QString::fromStdString(serviceName);
        req.serviceName = buffer5;

        char buffer6[255];
        memset(buffer6,0,255*sizeof(char));
        string value = NetSecurity::encrypt(ui->txt_price->text());
        strcpy(buffer6, value.data());
        qDebug()<<"value:"+QString::fromStdString(value);
        req.value = buffer6;

        char buffer0[255];
        memset(buffer0,0,255*sizeof(char));
        string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
        strcpy(buffer0, clientType.data());
        qDebug()<<"value:"+QString::fromStdString(clientType);
        req.clientType = buffer0;

        if (business1 != "") {
            char buffer7[255];
            memset(buffer7,0,255*sizeof(char));
            string b1 = NetSecurity::encrypt(business1);
            strcpy(buffer7, b1.data());
            qDebug()<<"b1:"+QString::fromStdString(b1);
            req.business1 = buffer7;
        }

        if (business2 != "") {
            char buffer8[255];
            memset(buffer8,0,255*sizeof(char));
            string b2 = NetSecurity::encrypt(business2);
            strcpy(buffer8, b2.data());
            qDebug()<<"b2:"+QString::fromStdString(b2);
            req.business2 = buffer8;
        }

        if (business3 != "") {
            char buffer9[255];
            memset(buffer9,0,255*sizeof(char));
            string b3 = NetSecurity::encrypt(business3);
            strcpy(buffer9, b3.data());
            qDebug()<<"b3:"+QString::fromStdString(b3);
            req.business3 = buffer9;
        }

        _ns1__SellNoResponse res;
        if (soap.__ns13__SellNo(&req,&res) == SOAP_OK) {
            QString result = QString::fromUtf8(res.SellNoResult);
            if (result.contains("�ɹ�")) {
                QMessageBox::warning(this,tr("��ʾ"),result,QMessageBox::Ok);
                _ref_ydxh_ScrollArea->showNewMoney();
                reset();
                this->close();
            } else {
                QMessageBox::warning(this,tr("��ʾ"),result,QMessageBox::Ok);
                return;
            }

        } else {
            QMessageBox::warning(this,tr("��ʾ"),"�������������ܿ���",QMessageBox::Ok);
        }
    }
}


void BuyNoDialog::on_btn_submit_clicked()
{
    submit();
}

void BuyNoDialog::on_btn_close_clicked()
{
    this->close();
}

void BuyNoDialog::on_cbx_service_currentIndexChanged(const QString &arg1)
{
    QString tmp = ui->cbx_service->itemData(ui->cbx_service->currentIndex()).toString();
    ui->txt_service_spec->setText(tmp);
}

void BuyNoDialog::on_rdo_service_type_on_clicked()
{
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

    _ns1__GetCardService req2;

    req2.top = 0;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    QString queryStr = "";
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        queryStr += " [��Ӫ��]='�ƶ�'";
    } else {
        queryStr += " [��Ӫ��]<>'�ƶ�'";
    }
    if (ui->rdo_service_type_on->isChecked()) {
        queryStr += " and [�Ƿ���]=1";
    }
    queryStr += " order by [�ײ�����]";
    string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer3, condition.data());
    qDebug()<<"condition��"+QString::fromStdString(condition);
    req2.condition = buffer3;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    strcpy(buffer4, Singleton::GetInstance()->session_id.toUtf8().data());
    qDebug()<<"session:"+Singleton::GetInstance()->session_id;
    req2.sessionId = buffer4;

    _ns1__GetCardServiceResponse res2;
    this->setCursor(Qt::BusyCursor);
    ui->rdo_service_type_on->setEnabled(false);
    ui->rdo_service_type_off->setEnabled(false);
    if (soap.__ns13__GetCardService(&req2,&res2) == SOAP_OK) {
        ui->cbx_service->clear();
        ui->cbx_service->addItem("","");
        ui->cbx_service->setMaxVisibleItems(15);
        for (int i=0; i<res2.GetCardServiceResult->__sizeCardService; ++i) {
            QString name = QString::fromUtf8(res2.GetCardServiceResult->CardService[i]->serviceName);
            QString value = QString::fromUtf8(res2.GetCardServiceResult->CardService[i]->serviceSpec);
            ui->cbx_service->addItem(name, value);
        }
        qDebug()<<"��ȡ�ײ��б�ɹ�";
    } else {
        qDebug()<<"�������������ܻ�ȡ�ײ��б�";
    }
    ui->rdo_service_type_on->setEnabled(true);
    ui->rdo_service_type_off->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void BuyNoDialog::on_rdo_service_type_off_clicked()
{
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

    _ns1__GetCardService req2;

    req2.top = 0;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    QString queryStr = "";
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        queryStr += " [��Ӫ��]='�ƶ�'";
    } else {
        queryStr += " [��Ӫ��]<>'�ƶ�'";
    }
    queryStr += " order by [�ײ�����]";
    string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer3, condition.data());
    qDebug()<<"condition��"+QString::fromStdString(condition);
    req2.condition = buffer3;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    strcpy(buffer4, Singleton::GetInstance()->session_id.toUtf8().data());
    qDebug()<<"session:"+Singleton::GetInstance()->session_id;
    req2.sessionId = buffer4;

    _ns1__GetCardServiceResponse res2;
    this->setCursor(Qt::BusyCursor);
    ui->rdo_service_type_on->setEnabled(false);
    ui->rdo_service_type_off->setEnabled(false);
    if (soap.__ns13__GetCardService(&req2,&res2) == SOAP_OK) {
        ui->cbx_service->clear();
        ui->cbx_service->addItem("","");
        ui->cbx_service->setMaxVisibleItems(15);
        for (int i=0; i<res2.GetCardServiceResult->__sizeCardService; ++i) {
            QString name = QString::fromUtf8(res2.GetCardServiceResult->CardService[i]->serviceName);
            QString value = QString::fromUtf8(res2.GetCardServiceResult->CardService[i]->serviceSpec);
            ui->cbx_service->addItem(name, value);
        }
        qDebug()<<"��ȡ�ײ��б�ɹ�";
    } else {
        qDebug()<<"�������������ܻ�ȡ�ײ��б�";
    }
    ui->rdo_service_type_on->setEnabled(true);
    ui->rdo_service_type_off->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}
