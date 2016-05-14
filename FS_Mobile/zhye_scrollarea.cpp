#include "zhye_scrollarea.h"
#include "ui_zhye_scrollarea.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include <QDebug>
#include "config.h"
#include "EncryptUtil.h"

zhye_ScrollArea::zhye_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::zhye_ScrollArea)
{
    ui->setupUi(this);

    //表头信息
    QString countStr = "总笔数：【0】";
    QString totalPayStr = "总金额：【10】";
    QString info = "当前用户：【】的可用余额为：【0】元";
    ui->txt_rpt_total->setText(countStr);
    ui->txt_rpt_totoalMoney->setText(totalPayStr);
    ui->txt_rpt_info->setText(info);

    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "账户名称" << "充值银行名称" << "支行名称" << "存款金额"
         << "存款方式" << "存款时间" << "状态" << "备注";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    //ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setWordWrap(true);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->setColumnWidth(1,80);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,80);
    ui->tableWidget->setColumnWidth(4,100);
    ui->tableWidget->setColumnWidth(5,150);
    ui->tableWidget->setColumnWidth(6,70);
}

zhye_ScrollArea::~zhye_ScrollArea()
{
    delete ui;
}

void zhye_ScrollArea::init()
{
    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

    //获取用户详细信息
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
        ns1__User *soap_user = res1.GetUserInfoResult;
        UserVO userVO;
        userVO.Id = QString::fromUtf8(soap_user->Id);
        userVO.loggingName = QString::fromUtf8(soap_user->loggingName);
        userVO.password = QString::fromUtf8(soap_user->password);
        userVO.money = soap_user->money;
        userVO.tel = QString::fromUtf8(soap_user->tel);
        userVO.mac = QString::fromUtf8(soap_user->mac);
        userVO.address = QString::fromUtf8(soap_user->address);
        userVO.shopName = QString::fromUtf8(soap_user->shopName);
        userVO.mobilePhone = QString::fromUtf8(soap_user->mobilePhone);
        userVO.pingying = QString::fromUtf8(soap_user->pingying);
        userVO.realName = QString::fromUtf8(soap_user->realName);
        userVO.indentityNo = QString::fromUtf8(soap_user->indentityNo);
        userVO.manager_id = QString::fromUtf8(soap_user->manager_USCOREid);
        userVO.managerName = QString::fromUtf8(soap_user->managerName);
        userVO.moneyTail = QString::fromUtf8(soap_user->moneyTail);
        userVO.level = QString::fromUtf8(soap_user->level);
        userVO.registerDatetime = soap_user->registerDatetime;
        userVO.isValidate = soap_user->isValidate;
        userVO.btnList = QString::fromUtf8(soap_user->btnList);
        Singleton::GetInstance()->setUser(userVO);
        emit updateMoney();
        QString info = "当前用户：【"+Singleton::GetInstance()->getUser().loggingName+"】的可用余额为：【"+QString::number(Singleton::GetInstance()->getUser().money,'f',2)+"】元";
        ui->txt_rpt_info->setText(info);
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
    reset();
    getSearchCondition();
    search();
}

void zhye_ScrollArea::reset()
{
    ui->cbxBank->setCurrentIndex(0);
    ui->cbxStoredState->setCurrentIndex(0);
    //时间
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());
}

void zhye_ScrollArea::getSearchCondition()
{
    ui->cbxBank->clear();
    ui->cbxStoredState->clear();
    ui->cbxBank->addItem("","");
    ui->cbxStoredState->addItem("","");

    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetDicContentByCondition req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='银行' and [Enabled]=1 ";
    string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            ui->cbxBank->addItem(name,value);
        }
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='充值状态' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            ui->cbxStoredState->addItem(name,value);
        }
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
}

void zhye_ScrollArea::search()
{
    int total = 0;
    float totalPay = 0;

    if (ui->txiStartDate->date() > ui->txiEndDate->date()) {
        QMessageBox::about(this,tr("日期范围错误"),tr("开单的起始时间不能大于开单的截止时间,请点击'确定'返回重新设置日期间隔！"));
        return;
    }
    //调整日期格式
    QString datetime1,datetime2;
    datetime1=QString::number(ui->txiStartDate->date().year());
    if (ui->txiStartDate->date().month()<10) {
        datetime1=datetime1+tr("-0")+QString::number(ui->txiStartDate->date().month());
    } else {
        datetime1=datetime1+tr("-")+QString::number(ui->txiStartDate->date().month());
    }
    if (ui->txiStartDate->date().day()<10) {
        datetime1=datetime1+tr("-0")+QString::number(ui->txiStartDate->date().day());
    } else {
        datetime1=datetime1+tr("-")+QString::number(ui->txiStartDate->date().day());
    }
    datetime1 += " 00:00:00";

    datetime2=QString::number(ui->txiEndDate->date().year());
    if (ui->txiEndDate->date().month()<10) {
        datetime2=datetime2+tr("-0")+QString::number(ui->txiEndDate->date().month());
    } else {
        datetime2=datetime2+tr("-")+QString::number(ui->txiEndDate->date().month());
    }
    if (ui->txiEndDate->date().day()<10) {
        datetime2=datetime2+tr("-0")+QString::number(ui->txiEndDate->date().day());
    } else {
        datetime2=datetime2+tr("-")+QString::number(ui->txiEndDate->date().day());
    }
    datetime2 += " 23:59:59";

    QString conditon = " and [充值时间] between '"+datetime1+"' and '"+datetime2+ "'";
    //条件查询
    if (ui->cbxBank->currentText() != "") {
        conditon += "and [充值银行名称] like '%"+ui->cbxBank->currentText()+"%' ";
    }
    if (ui->cbxStoredState->currentText() != "") {
        conditon += "and [状态] like '%"+ui->cbxStoredState->currentText()+"%' ";
    }

    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetAcountPaymentRecord req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[状态]<>'锁定' and [状态]<>'异常' and [账户名称]='"+Singleton::GetInstance()->getUser().loggingName+"'"+conditon+" and [客户端类型]='"+Config::GetInstance()->_client_type+"' order by [充值时间] desc";
    //QMessageBox::warning(this,tr("警告"),queryStr,QMessageBox::Ok);
    string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;
   _ns1__GetAcountPaymentRecordResponse res;
    if (soap.__ns5__GetAcountPaymentRecord(&req,&res) == SOAP_OK) {
        ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetAcountPaymentRecordResult->__sizeAcountPaymentItem;
        ui->tableWidget->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<8; ++j) {
                switch (j) {
                    case 0:
                    content = QString::fromUtf8(res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->acountName);
                         break;
                    case 1:
                        content = QString::fromUtf8(res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->bankName);
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->subBankName);
                        break;
                    case 3:
                        content = QString::number(res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->payMoney,'f',2);
                        totalPay += res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->payMoney;
                        break;
                    case 4:
                        content = QString::fromUtf8(res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->payType);
                        break;
                    case 5:
                        if (-1 == res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->payTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->payTime)));
                        content = QString(cTime);
                        break;
                    case 6:
                        content = QString::fromUtf8(res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->state);
                        break;
                    case 7:
                        content = QString::fromUtf8(res.GetAcountPaymentRecordResult->AcountPaymentItem[i]->content);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                ui->tableWidget->setItem(i, j, item);
            }
        }
        QString countStr = "总笔数：【"+QString::number(total)+"】";
        QString totalPayStr = "总金额：【"+QString::number(totalPay,'f',2)+"】";
        ui->txt_rpt_total->setText(countStr);
        ui->txt_rpt_totoalMoney->setText(totalPayStr);
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
}


void zhye_ScrollArea::on_btnSearch_clicked()
{
    this->setCursor(Qt::BusyCursor);
    ui->btnSearch->setEnabled(false);
    search();
    ui->btnSearch->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}
