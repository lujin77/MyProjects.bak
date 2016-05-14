#include "gszh_scrollarea.h"
#include "ui_gszh_scrollarea.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "config.h"
#include "singleton.h"
#include "EncryptUtil.h"

GetAccountListThread::GetAccountListThread(gszh_ScrollArea *gszh_ScrollArea_ptr)
{
    _ref = gszh_ScrollArea_ptr;
}

void GetAccountListThread::run()
{
    qDebug()<<"进入提取公司账户的线程...";
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetCompanyAccount req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[客户端类型]='"+Config::GetInstance()->_client_type+"'";
    qDebug()<<queryStr;
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetCompanyAccountResponse res;
    if (soap.__ns7__GetCompanyAccount(&req,&res) == SOAP_OK) {
        QString content = "";
        for (int i=0; i<res.GetCompanyAccountResult->__sizeCompanyAccount; ++i) {
            for (int j=0; j<3; ++j) {
                content = "";
                switch (j) {
                    case 0:
                         content = QString::fromUtf8(res.GetCompanyAccountResult->CompanyAccount[i]->Bank);
                         break;
                    case 1:
                        content = QString::fromUtf8(res.GetCompanyAccountResult->CompanyAccount[i]->AccountNo);
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetCompanyAccountResult->CompanyAccount[i]->userName);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget->setItem(i, j, item);
            }
        }
    } else {
        qDebug()<<"提取公司账户信息失败！";
    }
    qDebug()<<"提取公司账户的线程处理完成";
}

gszh_ScrollArea::gszh_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::gszh_ScrollArea)
{
    ui->setupUi(this);
    //表头信息
    QString str1 = "移动客户端专用账号";
    QString str2 = "联通电信客户端专用账号";

    if (Config::GetInstance()->_client_type == "移动客户端") {
        ui->txt_title->setText(str1);
    } else {
        ui->txt_title->setText(str2);
    }

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "开户银行" << "账号" << "户主";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    //ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget->setColumnWidth(0,180);
    ui->tableWidget->setColumnWidth(1,450);


    _getAccountListThread = new GetAccountListThread(this);
}

gszh_ScrollArea::~gszh_ScrollArea()
{
    if (_getAccountListThread != NULL) {
        _getAccountListThread->terminate();
        _getAccountListThread->exit();
        delete _getAccountListThread;
    }

    delete ui;
}

void gszh_ScrollArea::init()
{
    _getAccountListThread->start();
}
