#include "yhxxxg_scrollarea.h"
#include "ui_yhxxxg_scrollarea.h"
#include "singleton.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include <QMessageBox>
#include "EncryptUtil.h"

yhxxxg_ScrollArea::yhxxxg_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::yhxxxg_ScrollArea)
{
    ui->setupUi(this);
}

yhxxxg_ScrollArea::~yhxxxg_ScrollArea()
{
    delete ui;
}

void yhxxxg_ScrollArea::init()
{
    ui->txi_LoggingName->setText(Singleton::GetInstance()->getUser().loggingName);
    ui->txi_phone->setText(Singleton::GetInstance()->getUser().tel);
    ui->txi_address->setText(Singleton::GetInstance()->getUser().address);
    ui->txi_shop_name->setText(Singleton::GetInstance()->getUser().shopName);
    ui->txi_real_name->setText(Singleton::GetInstance()->getUser().realName);
    ui->txi_mobile_phone->setText(Singleton::GetInstance()->getUser().mobilePhone);
    ui->txi_identify_no->setText(Singleton::GetInstance()->getUser().indentityNo);
    ui->txi_worker_name->setText(Singleton::GetInstance()->getUser().managerName);
}

void yhxxxg_ScrollArea::reset()
{
    ui->txi_phone->setText("");
    ui->txi_address->setText("");
    ui->txi_shop_name->setText("");
    ui->txi_real_name->setText("");
    ui->txi_mobile_phone->setText("");
    ui->txi_identify_no->setText("");
    ui->txi_worker_name->setText("");
}

void yhxxxg_ScrollArea::submit()
{
    if (ui->txi_phone->text() == "") {
        QMessageBox::warning(this,tr("警告"),"固定电话不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txi_address->text() == "") {
        QMessageBox::warning(this,tr("警告"),"地址不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txi_shop_name->text() == "") {
        QMessageBox::warning(this,tr("警告"),"店名不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txi_real_name->text() == "") {
        QMessageBox::warning(this,tr("警告"),"真实姓名不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txi_mobile_phone->text() == "") {
        QMessageBox::warning(this,tr("警告"),"移动电话号码不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txi_identify_no->text() == "") {
        QMessageBox::warning(this,tr("警告"),"身份证号不能为空",QMessageBox::Ok);
        return;
    }

    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "用户信息修改", "确定修改当前的用户信息吗?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb != QMessageBox::Yes) {
        return;
    }

    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__AlterUserInfo req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer1, userId.data());
    req.user_USCOREid = buffer1;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    std::string address = NetSecurity::encrypt(ui->txi_address->text());
    strcpy(buffer4, address.data());
    req.address = buffer4;

    char buffer5[255];
    memset(buffer5,0,255*sizeof(char));
    std::string adrTel = NetSecurity::encrypt(ui->txi_phone->text());
    strcpy(buffer5, adrTel.data());
    req.adrTel = buffer5;

    char buffer6[255];
    memset(buffer6,0,255*sizeof(char));
    std::string shopName = NetSecurity::encrypt(ui->txi_shop_name->text());
    strcpy(buffer6, shopName.data());
    req.shopName = buffer6;

    char buffer7[255];
    memset(buffer7,0,255*sizeof(char));
    std::string realName = NetSecurity::encrypt(ui->txi_real_name->text());
    strcpy(buffer7, realName.data());
    req.realName = buffer7;

    char buffer8[255];
    memset(buffer8,0,255*sizeof(char));
    std::string identifyNo = NetSecurity::encrypt(ui->txi_identify_no->text());
    strcpy(buffer8, identifyNo.data());
    req.identifyNo = buffer8;

    char buffer9[255];
    memset(buffer9,0,255*sizeof(char));
    std::string workerName = NetSecurity::encrypt(ui->txi_worker_name->text());
    strcpy(buffer9, workerName.data());
    req.workerName = buffer9;

    char buffer11[255];
    memset(buffer11,0,255*sizeof(char));
    std::string mobilePhone = NetSecurity::encrypt(ui->txi_mobile_phone->text());
    strcpy(buffer11, mobilePhone.data());
    req.mobilePhone = buffer11;

    char buffer12[255];
    memset(buffer12,0,255*sizeof(char));
    std::string moneyTail = NetSecurity::encrypt(Singleton::GetInstance()->getUser().moneyTail);
    strcpy(buffer12, moneyTail.data());
    req.moneyTail = buffer12;

    char buffer10[255];
    memset(buffer10,0,255*sizeof(char));
    strcpy(buffer10, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer10;

    _ns1__AlterUserInfoResponse res;
    this->setCursor(Qt::BusyCursor);
    ui->btnSubmit->setEnabled(false);
    if (soap.__ns5__AlterUserInfo(&req,&res) == SOAP_OK) {
        QString str = QString::fromUtf8(res.AlterUserInfoResult);
        QMessageBox::warning(this,tr("结果"),str,QMessageBox::Ok);
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
    this->setCursor(Qt::ArrowCursor);
    ui->btnSubmit->setEnabled(true);
}

void yhxxxg_ScrollArea::on_btnSubmit_clicked()
{
    submit();
}

void yhxxxg_ScrollArea::on_btnReset_clicked()
{
    reset();
}
