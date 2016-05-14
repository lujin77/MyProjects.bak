#include "businessdialog.h"
#include "ui_businessdialog.h"
#include "config.h"
#include "EncryptUtil.h"
#include "singleton.h"
#include "gsoap/soapBusinessFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include <QMessageBox>

GetYwblConditionThread::GetYwblConditionThread(BusinessDialog *BusinessDialog_ptr)
{
    _ref = BusinessDialog_ptr;
    type = "更改套餐窗口";
}

void GetYwblConditionThread::run()
{
    if (type == "更改套餐窗口") {
        BusinessFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

        _ns1__GetCardService req2;

        req2.top = 0;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        QString queryStr = "";
        if (Config::GetInstance()->_client_type == "移动客户端") {
            queryStr += " [运营商]='移动'";
        } else {
            queryStr += " [运营商]<>'移动'";
        }
        if (_ref->ui->rdo_service_type_on->isChecked()) {
            queryStr += " and [是否常用]=1";
        }
        queryStr += " order by [套餐名称]";
        string condition = NetSecurity::encrypt(queryStr);
        strcpy(buffer3, condition.data());
        qDebug()<<"condition："+QString::fromStdString(condition);
        req2.condition = buffer3;

        char buffer4[255];
        memset(buffer4,0,255*sizeof(char));
        strcpy(buffer4, Singleton::GetInstance()->session_id.toUtf8().data());
        qDebug()<<"session:"+Singleton::GetInstance()->session_id;
        req2.sessionId = buffer4;

        _ns1__GetCardServiceResponse res2;
        if (soap.__ns13__GetCardService(&req2,&res2) == SOAP_OK) {
            _ref->ui->cbx_service->clear();
            _ref->ui->cbx_service->addItem("","");
            _ref->ui->cbx_service->setMaxVisibleItems(15);
            for (int i=0; i<res2.GetCardServiceResult->__sizeCardService; ++i) {
                QString name = QString::fromUtf8(res2.GetCardServiceResult->CardService[i]->serviceName);
                _ref->ui->cbx_service->addItem(name, name);
            }
            qDebug()<<"获取套餐列表成功";
        } else {
            qDebug()<<"服务器出错！不能获取套餐列表";
        }
    } else if (type == "更改姓名窗口") {
         qDebug()<<"准备获取证件类型";
        //获取证件类型
        UtilFunctionWebServiceSoap util_soap;
        soap_set_mode(util_soap.soap, SOAP_C_UTFSTRING);
        _ns1__GetDicContentByCondition util_req;

        char util_buffer0[255];
        memset(util_buffer0,0,255*sizeof(char));
        strcpy(util_buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
        qDebug()<<"session:"+Singleton::GetInstance()->session_id;
        util_req.sessionId = util_buffer0;

        char util_buffer1[255];
        memset(util_buffer1,0,255*sizeof(char));
        QString queryStr = "[Category]='证件类型' and [Enabled]=1 ";
        string condition = NetSecurity::encrypt(queryStr);
        qDebug()<<"condition："+QString::fromStdString(condition);
        strcpy(util_buffer1, condition.data());
        util_req.condition = util_buffer1;

        _ns1__GetDicContentByConditionResponse util_res;
        if (util_soap.__ns7__GetDicContentByCondition(&util_req,&util_res) == SOAP_OK) {
            _ref->ui->cbx_card_type->clear();
            _ref->ui->cbx_card_type->addItem("","");
            for(int i=0; i<util_res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
                QString name = QString::fromUtf8(util_res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
                QString value = QString::fromUtf8(util_res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
                _ref->ui->cbx_card_type->addItem(name,value);
            }
            qDebug()<<"获取证件类型成功";
        } else {
            qDebug()<<"服务器出错！不能获取证件类型列表";
        }
    }
}

BusinessDialog::BusinessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BusinessDialog)
{
    ui->setupUi(this);

    _getYwblConditionThread = new GetYwblConditionThread(this);
}

BusinessDialog::~BusinessDialog()
{
    if (_getYwblConditionThread != NULL) {
        _getYwblConditionThread->terminate();
        _getYwblConditionThread->exit();
        delete _getYwblConditionThread;
    }
    delete ui;
}

void BusinessDialog::changeEvent(QEvent *e)
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

void BusinessDialog::init(QString type, QString name)
{
    reset();

    if (type == "更改套餐窗口") {
        if (_getYwblConditionThread->isRunning()) {
            _getYwblConditionThread->terminate();
        }
        _getYwblConditionThread->type = type;
        _getYwblConditionThread->start();
        ui->stackedWidget->setCurrentIndex(2);

    } else if (type == "更改姓名窗口") {
        if (_getYwblConditionThread->isRunning()) {
            _getYwblConditionThread->terminate();
        }
        _getYwblConditionThread->type = type;
        _getYwblConditionThread->start();
        ui->stackedWidget->setCurrentIndex(3);
    } else if (type == "亲情业务窗口") {
        ui->stackedWidget->setCurrentIndex(4);
    } else if (type == "高级窗口") {
        ui->stackedWidget->setCurrentIndex(1);
    } else {    //对于不合法的输入，默认是简单窗口
        type = "简单窗口";
        ui->stackedWidget->setCurrentIndex(0);
    }
    winType = type;
    businessName = name;

    this->setWindowTitle(businessName);
}

void BusinessDialog::submit()
{
    if (ui->txi_no->text() == "") {
        QMessageBox::warning(this,tr("警告"),"电话号码不能为空",QMessageBox::Ok);
        return;
    }

    if (ui->txi_no->text().length() != 11) {
        QMessageBox::warning(this,tr("警告"),"电话号码长度不对",QMessageBox::Ok);
        return;
    }

    if (ui->txi_passwd->text() == "") {
        QMessageBox::warning(this,tr("警告"),"密码不能为空",QMessageBox::Ok);
        return;
    }

    QString content = "";
    QString comment = "";

    if (winType == "更改套餐窗口") {
        if (ui->cbx_service->currentText() == "") {
            QMessageBox::warning(this,tr("警告"),"套餐不能为空",QMessageBox::Ok);
            return;
        }
        content = "变更套餐为：\n"+ui->cbx_service->currentText();
    } else if (winType == "更改姓名窗口") {
        if (ui->txi_name->text() == "") {
            QMessageBox::warning(this,tr("警告"),"客户姓名不能为空",QMessageBox::Ok);
            return;
        }
        if (ui->cbx_card_type->currentText() == "") {
            QMessageBox::warning(this,tr("警告"),"证件类型不能为空",QMessageBox::Ok);
            return;
        } else {
            if (ui->txi_card_no->text() == "") {
                QMessageBox::warning(this,tr("警告"),"证件号码不能为空",QMessageBox::Ok);
                return;
            }
        }
        content = "更改姓名业务：\n客户姓名："+ui->txi_name->text();
        content += "\n证件类型:"+ui->cbx_card_type->currentText();
        content += "\n证件号码:"+ui->txi_card_no->text();
    } else if (winType == "亲情业务窗口") {
        if (ui->txi_add_no->toPlainText() == "" && ui->txi_delete_no->toPlainText() == "") {
            QMessageBox::warning(this,tr("警告"),"办理的亲情号码不能为空\n必须输入至少一类",QMessageBox::Ok);
            return;
        }
        content = "办理亲情业务：\n新增号码："+ui->txi_add_no->toPlainText();
        content += "\n删除号码："+ui->txi_delete_no->toPlainText();
    } else if (winType == "高级窗口") {
        content = ui->txi_content->toPlainText();
        comment = ui->txi_comment->toPlainText();
    }

    QString str = "确定要对" + ui->txi_no->text() + "办理业务吗？";
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "业务受理", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {

        BusinessFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

        _ns1__SubmitBusiness req;

        char buffer0[255];
        memset(buffer0,0,255*sizeof(char));
        string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        strcpy(buffer0, userId.data());
        qDebug()<<"userId:"+QString::fromStdString(userId);
        req.userId = buffer0;

        char buffer[255];
        memset(buffer,0,255*sizeof(char));
        string name = NetSecurity::encrypt(businessName);
        strcpy(buffer, name.data());
        qDebug()<<"businessName:"+QString::fromStdString(name);
        req.businessName = buffer;

        char buffer2[255];
        memset(buffer2,0,content.size()*sizeof(char));
        string businessSpec = NetSecurity::encrypt(content);
        strcpy(buffer2, businessSpec.data());
        qDebug()<<"businessSpec:"+QString::fromStdString(businessSpec);
        req.businessSpec = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        string No = NetSecurity::encrypt(ui->txi_no->text());
        strcpy(buffer3, No.data());
        qDebug()<<"No:"+QString::fromStdString(No);
        req.No = buffer3;

        char buffer4[255];
        memset(buffer4,0,255*sizeof(char));
        string passwd = NetSecurity::encrypt(ui->txi_passwd->text());
        strcpy(buffer4, passwd.data());
        qDebug()<<"passwd:"+QString::fromStdString(passwd);
        req.passwd = buffer4;

        char buffer5[255];
        memset(buffer5,0,comment.size()*sizeof(char));
        string bz = NetSecurity::encrypt(comment);
        strcpy(buffer5, bz.data());
        qDebug()<<"comment:"+QString::fromStdString(bz);
        req.content = buffer5;

        char buffer6[255];
        memset(buffer6,0,255*sizeof(char));
        strcpy(buffer6, Singleton::GetInstance()->session_id.toUtf8().data());
        qDebug()<<"session:"+Singleton::GetInstance()->session_id;
        req.sessionId = buffer6;

        req.sp = "";

        char buffer7[255];
        memset(buffer7,0,255*sizeof(char));
        string userLevel = NetSecurity::encrypt(Singleton::GetInstance()->getUser().level);
        strcpy(buffer7, userLevel.data());
        qDebug()<<"userLevel:"+QString::fromStdString(userLevel);
        req.userLevel = buffer7;

        _ns1__SubmitBusinessResponse res;
        if (soap.__ns13__SubmitBusiness(&req,&res) == SOAP_OK) {
            QMessageBox::warning(this,tr("提示"),QString::fromUtf8(res.SubmitBusinessResult),QMessageBox::Ok);
            if (QString::fromUtf8(res.SubmitBusinessResult).contains("成功")) this->close();
        } else {
            QMessageBox::warning(this,tr("提示"),"服务器出错！不能进行业务办理",QMessageBox::Ok);
        }
    }

}

void BusinessDialog::reset()
{
    ui->txi_no->setText("");
    ui->txi_passwd->setText("");
    ui->cbx_service->setCurrentIndex(0);
    ui->cbx_card_type->setCurrentIndex(0);
    ui->txi_name->setText("");
    ui->txi_card_no->setText("");
    ui->txi_add_no->setText("");
    ui->txi_delete_no->setText("");
    ui->txi_content->setText("");
    ui->txi_comment->setText("");
}

void BusinessDialog::on_btn_reset_clicked()
{
    reset();
}

void BusinessDialog::on_btn_submit_clicked()
{
    submit();
}

void BusinessDialog::on_rdo_service_type_on_clicked()
{
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

    _ns1__GetCardService req2;

    req2.top = 0;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    QString queryStr = "";
    if (Config::GetInstance()->_client_type == "移动客户端") {
        queryStr += " [运营商]='移动'";
    } else {
        queryStr += " [运营商]<>'移动'";
    }
    if (ui->rdo_service_type_on->isChecked()) {
        queryStr += " and [是否常用]=1";
    }
    queryStr += " order by [套餐名称]";
    string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer3, condition.data());
    qDebug()<<"condition："+QString::fromStdString(condition);
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
            ui->cbx_service->addItem(name, name);
        }
        qDebug()<<"获取套餐列表成功";
    } else {
        qDebug()<<"服务器出错！不能获取套餐列表";
    }
    ui->rdo_service_type_on->setEnabled(true);
    ui->rdo_service_type_off->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}

void BusinessDialog::on_rdo_service_type_off_clicked()
{
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

    _ns1__GetCardService req2;

    req2.top = 0;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    QString queryStr = "";
    if (Config::GetInstance()->_client_type == "移动客户端") {
        queryStr += " [运营商]='移动'";
    } else {
        queryStr += " [运营商]<>'移动'";
    }
    queryStr += " order by [套餐名称]";
    string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer3, condition.data());
    qDebug()<<"condition："+QString::fromStdString(condition);
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
            ui->cbx_service->addItem(name, name);
        }
        qDebug()<<"获取套餐列表成功";
    } else {
        qDebug()<<"服务器出错！不能获取套餐列表";
    }
    ui->rdo_service_type_on->setEnabled(true);
    ui->rdo_service_type_off->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}
