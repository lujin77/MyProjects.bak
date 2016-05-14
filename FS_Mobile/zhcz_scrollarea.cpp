#include "zhcz_scrollarea.h"
#include "ui_zhcz_scrollarea.h"
#include "singleton.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include <QMessageBox>
#include <config.h>
#include "EncryptUtil.h"

using namespace std;

zhcz_ScrollArea::zhcz_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::zhcz_ScrollArea)
{
    ui->setupUi(this);

    //QRegExp regx("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$");
    QRegExp regx("^[0-9]+(\.[0-9]{1,3})?$");
    QValidator *validator = new QRegExpValidator(regx, this );
    ui->txiStoredMoney->setValidator( validator );

    ui->txiDatetime->setDateTime(QDateTime::currentDateTime());

    ui->label_time->hide();
    ui->txiDatetime->hide();
}

zhcz_ScrollArea::~zhcz_ScrollArea()
{
    delete ui;
}

void zhcz_ScrollArea::init()
{
    ui->txiAccountName->setText(Singleton::GetInstance()->getUser().loggingName);
    ui->txiAccountMoney->setText(QString::number(Singleton::GetInstance()->getUser().money,'f',2));
    ui->txiAccountTail->setText(Singleton::GetInstance()->getUser().moneyTail);
    reset();
    getSearchCondition();
}

void zhcz_ScrollArea::getSearchCondition()
{
    ui->cbxBankName->clear();
    ui->cbxStoredType->clear();
    ui->cbxBankName->addItem("","");
    ui->cbxStoredType->addItem("","");

    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetDicContentByCondition req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='银行'";
    string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            ui->cbxBankName->addItem(name,value);
        }
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='存款方式'";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            ui->cbxStoredType->addItem(name,value);
        }
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
}

void zhcz_ScrollArea::reset()
{
    ui->cbxBankName->setCurrentIndex(0);
    ui->cbxStoredType->setCurrentIndex(0);
    ui->txiStoredMoney->clear();
    ui->txiSubBankName->clear();
    ui->txiContent->clear();
    ui->txiDatetime->setDateTime(QDateTime::currentDateTime());
}

void zhcz_ScrollArea::submit()
{
    if (ui->txiStoredMoney->text() == "") {
        QMessageBox::warning(this,tr("警告"),tr("充值金额不能为空!"),QMessageBox::Ok);
        ui->txiStoredMoney->setFocus();
        return;
    } else {
        if (ui->txiStoredMoney->text().contains("。")
                || ui->txiStoredMoney->text().contains("，")
                || ui->txiStoredMoney->text().contains(",")) {
            QMessageBox::warning(this,tr("警告"),tr("您输入的充值金额包含非法字符！请重新检查"),QMessageBox::Ok);
            ui->txiStoredMoney->setFocus();
            return;
        }

        if (ui->txiStoredMoney->text().toDouble() <= 0) {
            QMessageBox::warning(this,tr("警告"),tr("充值金额不能为0!"),QMessageBox::Ok);
            ui->txiStoredMoney->setFocus();
            return;
        }
    }

    if (ui->cbxBankName->currentText() == "") {
        QMessageBox::warning(this,tr("警告"),tr("银行不能为空!"),QMessageBox::Ok);
        ui->cbxBankName->setFocus();
        return;
    }

    if (ui->txiSubBankName->text() == "") {
        QMessageBox::warning(this,tr("警告"),tr("支行名称不能为空!"),QMessageBox::Ok);
        ui->txiSubBankName->setFocus();
        return;
    }

    if (ui->cbxStoredType->currentText() == "") {
        QMessageBox::warning(this,tr("警告"),tr("存款方式不能为空!"),QMessageBox::Ok);
        ui->cbxStoredType->setFocus();
        return;
    }

    if (ui->txiContent->toPlainText() == "") {
        QMessageBox::warning(this,tr("警告"),tr("备注信息不能为空!"),QMessageBox::Ok);
        ui->txiContent->setFocus();
        return;
    }

    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "账户充值", "确定提交该条充值信息?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb != QMessageBox::Yes) {
        return;
    }

    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__AddAcountPayment req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    string username = NetSecurity::encrypt(Singleton::GetInstance()->getUser().loggingName);
    strcpy(buffer0, username.data());
    req.username = buffer0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer1, userId.data());
    req.userId = buffer1;

    req.money = ui->txiStoredMoney->text().toFloat();

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    string bankName = NetSecurity::encrypt(ui->cbxBankName->currentText());
    strcpy(buffer2, bankName.data());
    req.bankName = buffer2;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    string payType = NetSecurity::encrypt(ui->cbxStoredType->currentText());
    strcpy(buffer3, payType.data());
    req.payType = buffer3;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    string subBankName = NetSecurity::encrypt(ui->txiSubBankName->text());
    strcpy(buffer4, subBankName.data());
    req.subBankName = buffer4;

    req.payTime = ui->txiDatetime->dateTime().toTime_t();

    char buffer6[255];
    memset(buffer6,0,255*sizeof(char));
    string content = NetSecurity::encrypt(ui->txiContent->toPlainText());
    strcpy(buffer6, content.data());
    req.content = buffer6;

    char buffer7[255];
    memset(buffer7,0,255*sizeof(char));
    strcpy(buffer7, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer7;

    char buffer8[255];
    memset(buffer8,0,255*sizeof(char));
    string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
    strcpy(buffer8, clientType.data());
    req.clientType = buffer8;

    _ns1__AddAcountPaymentResponse res;
    this->setCursor(Qt::BusyCursor);
    ui->btnSubmit->setEnabled(false);
    if (soap.__ns5__AddAcountPayment(&req,&res) == SOAP_OK) {
        QString result = QString::fromUtf8(res.AddAcountPaymentResult);
        QMessageBox::warning(this,tr("警告"),result,QMessageBox::Ok);
        reset();
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
    ui->btnSubmit->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void zhcz_ScrollArea::on_btnSubmit_clicked()
{
    submit();
}

void zhcz_ScrollArea::on_btnReset_clicked()
{
    reset();
}
