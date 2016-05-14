#include "registerbox.h"
#include "ui_registerbox.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "stdlib.h"
#include "time.h"
#include <qglobal.h>
#include "config.h"
#include "EncryptUtil.h"

GetWorkerListThread::GetWorkerListThread(RegisterBox *registerBox_ptr)
{
    _ref = registerBox_ptr;
}

void GetWorkerListThread::run()
{
    _ref->ui->cbxWorkList->clear();
    _ref->ui->cbxWorkList->addItem("","");

    qDebug()<<"进入获取业务员的线程";
    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetWorkNameList req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [员工类型]='业务员' ";
    string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetWorkNameListResponse res;
    if (soap.__ns5__GetWorkNameList(&req,&res) == SOAP_OK) {
        qDebug()<<"提取到条数:"+QString::number(res.GetWorkNameListResult->__sizeWorker);
        for (int i = 0; i < res.GetWorkNameListResult->__sizeWorker; ++i) {
            QString name = QString::fromUtf8(res.GetWorkNameListResult->Worker[i]->WorkerName);
            QString worker_id = QString::fromUtf8(res.GetWorkNameListResult->Worker[i]->Id);
            _ref->ui->cbxWorkList->addItem(name,worker_id);
        }
    } else {
        qDebug()<<"服务器出错！不能获取业务员列表";
    }
    qDebug()<<"获取业务员的线程，处理完成";
}

RegisterBox::RegisterBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterBox)
{
    ui->setupUi(this);

    QNetworkInterface localInterface;
    QString MAC =localInterface.allInterfaces().first().hardwareAddress();
    ui->txiMac->setText(MAC);
    //float rand = (qrand()% 101) * 0.01f;
    srand((int)time(NULL));
    int rand_int = 999 - rand()%899;
    QString randStr = QString::number(rand_int);
    ui->txiAcountTail->setText(randStr);
    //connect(ui->txiRePassword, SIGNAL(editingFinished()), this, SLOT(on_txiRePassword_editingFinished()));
    //connect(ui->btnReset, SIGNAL(clicked()), this, SLOT(on_btnReset_clicked()));
    //connect(ui->btnSubmit, SIGNAL(clicked()), this, SLOT(on_btnSubmit_clicked()));
    _getWorkerListThread = new GetWorkerListThread(this);
    _getWorkerListThread->start();
}

RegisterBox::~RegisterBox()
{
    if (_getWorkerListThread != NULL) {
        _getWorkerListThread->terminate();
        _getWorkerListThread->exit();
        delete _getWorkerListThread;
    }

    delete ui;
}

void RegisterBox::changeEvent(QEvent *e)
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

void RegisterBox::on_txiRePassword_editingFinished()
{
    if (ui->txiPassword->text() == "") {
        ui->txtPswAlert->setText("请先输入密码");
        ui->txiPassword->setFocus();
    }
    else if (ui->txiPassword->text() != ui->txiRePassword->text()) {
        ui->txtPswAlert->setText("两次输入的密码不一致");
        ui->txiRePassword->setFocus();
    }
    else {
        ui->txtPswAlert->clear();
    }
}

void RegisterBox::on_btnReset_clicked()
{
    ui->txiUsername->clear();
    ui->txiPassword->clear();
    ui->txiRePassword->clear();
    ui->txtPswAlert->clear();
    ui->txiAdrTel->clear();
    ui->txiAddress->clear();
    ui->txiShopName->clear();
    ui->txiRealName->clear();
    ui->txiMobilePhone->clear();
    ui->txiIdentityNo->clear();
    ui->cbxWorkList->clear();
    ui->cbxWorkList->addItem("","");
}

void RegisterBox::on_btnSubmit_clicked()
{
    if (ui->txiUsername->text() == "") {
        QMessageBox::warning(this,tr("警告"),"用户名不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txiPassword->text() == "") {
        QMessageBox::warning(this,tr("警告"),"密码不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txiRePassword->text() == "") {
        QMessageBox::warning(this,tr("警告"),"确认密码不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txiRePassword->text() != ui->txiPassword->text()) {
        QMessageBox::warning(this,tr("警告"),"两次输入的密码不一致",QMessageBox::Ok);
        return;
    }
    if (ui->txiAdrTel->text() == "") {
        QMessageBox::warning(this,tr("警告"),"固定电话不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txiAddress->text() == "") {
        QMessageBox::warning(this,tr("警告"),"地址不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txiShopName->text() == "") {
        QMessageBox::warning(this,tr("警告"),"店名不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txiRealName->text() == "") {
        QMessageBox::warning(this,tr("警告"),"真实姓名不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txiMobilePhone->text() == "") {
        QMessageBox::warning(this,tr("警告"),"移动电话号码不能为空",QMessageBox::Ok);
        return;
    }
    if (ui->txiIdentityNo->text() == "") {
        QMessageBox::warning(this,tr("警告"),"身份证号不能为空",QMessageBox::Ok);
        return;
    }

    if (ui->cbxWorkList->currentText() == "") {
        QMessageBox::warning(this,tr("警告"),"业务员不能为空",QMessageBox::Ok);
        return;
    }

    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__RegisterUser req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    //注册名删除空白字符
    std::string username = NetSecurity::encrypt(ui->txiUsername->text().simplified());
    strcpy(buffer1, username.data());
    req.username = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    std::string password = NetSecurity::encrypt(ui->txiPassword->text());
    strcpy(buffer2, password.data());
    req.password = buffer2;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    std::string mac = NetSecurity::encrypt(ui->txiMac->text());
    strcpy(buffer3, mac.data());
    req.mac = buffer3;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    std::string address = NetSecurity::encrypt(ui->txiAddress->text());
    strcpy(buffer4, address.data());
    req.address = buffer4;

    char buffer5[255];
    memset(buffer5,0,255*sizeof(char));
    std::string adrTel = NetSecurity::encrypt(ui->txiAdrTel->text());
    strcpy(buffer5, adrTel.data());
    req.adrTel = buffer5;

    char buffer6[255];
    memset(buffer6,0,255*sizeof(char));
    std::string shopName = NetSecurity::encrypt(ui->txiShopName->text());
    strcpy(buffer6, shopName.data());
    req.shopName = buffer6;

    char buffer7[255];
    memset(buffer7,0,255*sizeof(char));
    std::string realName = NetSecurity::encrypt(ui->txiRealName->text());
    strcpy(buffer7, realName.data());
    req.realName = buffer7;

    char buffer8[255];
    memset(buffer8,0,255*sizeof(char));
    std::string identifyNo = NetSecurity::encrypt(ui->txiIdentityNo->text());
    strcpy(buffer8, identifyNo.data());
    req.identifyNo = buffer8;

    char buffer9[255];
    memset(buffer9,0,255*sizeof(char));
    std::string workerName = NetSecurity::encrypt(ui->cbxWorkList->currentText());
    strcpy(buffer9, workerName.data());
    req.workerName = buffer9;

    char _buffer9[255];
    memset(_buffer9,0,255*sizeof(char));
    QString work_id = ui->cbxWorkList->itemData(ui->cbxWorkList->currentIndex()).toString();
    std::string workerId = NetSecurity::encrypt(work_id);
    strcpy(_buffer9, workerId.data());
    req.workerId = _buffer9;

    char buffer10[255];
    memset(buffer10,0,255*sizeof(char));
    std::string moneyTail = NetSecurity::encrypt(ui->txiAcountTail->text());
    strcpy(buffer10, moneyTail.data());
    req.moneyTail = buffer10;

    char buffer11[255];
    memset(buffer11,0,255*sizeof(char));
    std::string mobilePhone = NetSecurity::encrypt(ui->txiMobilePhone->text());
    strcpy(buffer11, mobilePhone.data());
    req.mobilePhone = buffer11;

    char buffer12[255];
    memset(buffer12,0,255*sizeof(char));
    std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
    strcpy(buffer12, clientType.data());
    req.clientType = buffer12;

    _ns1__RegisterUserResponse res;
    this->setCursor(Qt::BusyCursor);
    ui->btnSubmit->setEnabled(false);
    if (soap.__ns5__RegisterUser(&req,&res) == SOAP_OK) {
        QString str = QString::fromUtf8(res.RegisterUserResult);
        if (str == "注册成功") {
            on_btnReset_clicked();
            this->close();
        }
        QMessageBox::warning(this,tr("结果"),str,QMessageBox::Ok);
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
    this->setCursor(Qt::ArrowCursor);
    ui->btnSubmit->setEnabled(true);
}
