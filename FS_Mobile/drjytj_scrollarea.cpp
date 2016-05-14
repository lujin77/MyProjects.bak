#include "drjytj_scrollarea.h"
#include "ui_drjytj_scrollarea.h"
#include "gsoap/soapPaymentFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "EncryptUtil.h"

GetJytjListThread::GetJytjListThread(drjytj_ScrollArea *drjytj_ScrollArea_ptr)
{
    currentCondition = "";
    this->_ref = drjytj_ScrollArea_ptr;
}

void GetJytjListThread::run()
{
    int total = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetTransactionStaticsByCondition req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [网点用户Id]='"+Singleton::GetInstance()->getUser().Id+"' "+currentCondition;
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetTransactionStaticsByConditionResponse res;
    if (soap.__ns3__GetTransactionStaticsByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetTransactionStaticsByConditionResult->__sizeTransStaticsItem;
        _ref->ui->tableWidget->setRowCount(total);

        for (int i=0; i<res.GetTransactionStaticsByConditionResult->__sizeTransStaticsItem; ++i) {
            for (int j=0; j<5; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetTransactionStaticsByConditionResult->TransStaticsItem[i]->transName);
                        break;
                    case 1:
                        content = QString::number(res.GetTransactionStaticsByConditionResult->TransStaticsItem[i]->count);
                        break;
                    case 2:
                        content = QString::number(res.GetTransactionStaticsByConditionResult->TransStaticsItem[i]->totalPay,'f',2);
                        break;
                    case 3:
                        content = QString::number(res.GetTransactionStaticsByConditionResult->TransStaticsItem[i]->totalCharge,'f',2);
                        break;
                    case 4:
                        content = QString::number(res.GetTransactionStaticsByConditionResult->TransStaticsItem[i]->totalReturn,'f',2);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget->setItem(i, j, item);
            }
        }
    } else {
        qDebug()<<"服务器出错，无法提取缴费日报信息";
    }
}

drjytj_ScrollArea::drjytj_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::drjytj_ScrollArea)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "业务类型" << "办理笔数" << "办理总额" << "扣款总额" << "利润";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    _getJytjListThread = new GetJytjListThread(this);

    //时间
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());
}

drjytj_ScrollArea::~drjytj_ScrollArea()
{
    if (_getJytjListThread != NULL) {
        _getJytjListThread->terminate();
        _getJytjListThread->exit();
        delete _getJytjListThread;
    }

    delete ui;
}

void drjytj_ScrollArea::on_btn_submit_clicked()
{
    refresh();
}

void drjytj_ScrollArea::init()
{
    reset();
    refresh();
}

void drjytj_ScrollArea::reset()
{
    ui->tableWidget->clearContents();
    //时间
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());
}

void drjytj_ScrollArea::refresh()
{
    _getJytjListThread->currentCondition = "";
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

     _getJytjListThread->currentCondition += " and [办理时间] between '"+datetime1+"' and '"+datetime2+ "'";

    //启动线程
    if (!this->_getJytjListThread->isRunning()) {
        _getJytjListThread->start();
    } else {
        return;
    }
}
