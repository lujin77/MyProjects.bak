#include "jfyb_scrollarea.h"
#include "ui_jfyb_scrollarea.h"
#include "gsoap/soapPaymentFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "printer.h"
#include "EncryptUtil.h"
#include "config.h"

GetJfybCondtionThread::GetJfybCondtionThread(jfyb_ScrollArea *jfyb_ScrollArea_ptr)
{
    this->_ref = jfyb_ScrollArea_ptr;
}

void GetJfybCondtionThread::run()
{
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetDicContentByCondition req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='运营商' and [Enabled]=1 ";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            if ((Config::GetInstance()->_client_type == "移动客户端")) {
                if (name == "移动") {
                    _ref->ui->cbx_sp->addItem(name,value);
                }
            } else {
                if (name != "移动") {
                    _ref->ui->cbx_sp->addItem(name,value);
                }
            }
        }
    } else {
        qDebug()<<"服务器出错，无法提取运营商下拉列表";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='缴费状态_客户端' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_state->addItem(name,value);
        }
    } else {
        qDebug()<<"服务器出错，无法提取客户端缴费状态下拉列表";
    }
}

GetJfybListThread::GetJfybListThread(jfyb_ScrollArea *jfyb_ScrollArea_ptr)
{
    _ref = jfyb_ScrollArea_ptr;
    currentCondition = "";
}

void GetJfybListThread::run()
{
    int total = 0;
    float totalPay = 0;
    float totalRepay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPaymentOrPaymentHistoryByCondition req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [网点用户Id]='"+Singleton::GetInstance()->getUser().Id+"' "+currentCondition+"order by [缴费时间] desc";
    qDebug()<<"query str:"+queryStr;
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetPaymentOrPaymentHistoryByConditionResponse res;
    if (soap.__ns3__GetPaymentOrPaymentHistoryByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetPaymentOrPaymentHistoryByConditionResult->__sizePaymentItem;
        _ref->ui->tableWidget->setRowCount(total);
        for (int i=0; i<res.GetPaymentOrPaymentHistoryByConditionResult->__sizePaymentItem; ++i) {
            for (int j=0; j<10; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->Id);
                         break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->telNo);
                        break;
                    case 3:
                        content = QString::number(res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->customerBeforeMoney,'f',2);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->chargeMoney,'f',2);
                        float payMoney = res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->chargeMoney;
                        totalPay += payMoney;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->state);
                        break;

                    case 6:
                        content = QString::fromUtf8(res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->SP);
                        break;
                    case 7:
                    {
                        content = QString::number(res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->repay,'f',2);
                        float repayMoney = res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->repay;
                        totalRepay += repayMoney;
                        continue;
                        break;
                    }
                    case 8:
                        content = QString::fromUtf8(res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->area);
                        break;
                    case 9:
                        if (-1 == res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->chargeTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPaymentOrPaymentHistoryByConditionResult->PaymentItem[i]->chargeTime)));
                        content = QString(cTime);
                        break;

                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget->setItem(i, j, item);
            }
        }
        QString countStr = "缴费:【"+QString::number(total)+"】笔";
        QString totalPayStr = "缴费金额:【"+QString::number(totalPay,'f',2)+"】元";
        QString totalRepayStr = "返款:【"+QString::number(totalRepay,'f',2)+"】元";

        if (totalRepay >-0.0000001 && totalRepay< 0.000001) {
            totalRepayStr = "返款:【0】元";;
        }

        _ref->ui->txt_rpt_total->setText(countStr);
        _ref->ui->txt_rpt_money->setText(totalPayStr);
        _ref->ui->txt_rpt_repay->setText(totalRepayStr);
    } else {
        qDebug()<<"服务器出错，无法提取缴费日报信息";
    }
}

jfyb_ScrollArea::jfyb_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::jfyb_ScrollArea)
{
    ui->setupUi(this);
    //表头信息
    QString countStr = "缴费:【0】笔";
    QString totalPayStr = "缴费金额:【0】元";
    QString totalRepayStr = "返款:【0】元";
    ui->txt_rpt_total->setText(countStr);
    ui->txt_rpt_money->setText(totalPayStr);
    ui->txt_rpt_repay->setText(totalRepayStr);

    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "Id" << "网点用户" << "缴费号码" << "缴前余额" << "缴费金额"
         << "缴费状态" << "运营商" << "返款金额" << "号码归属" << "缴费时间";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    //ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget->setColumnWidth(1,80);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,70);
    ui->tableWidget->setColumnWidth(5,70);
    ui->tableWidget->setColumnWidth(6,70);
    ui->tableWidget->setColumnWidth(7,70);
    ui->tableWidget->hideColumn(7);
    ui->tableWidget->setColumnWidth(8,70);

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this );
    ui->txi_phone_no->setValidator( validator );

    _getJfybCondtionThread = new GetJfybCondtionThread(this);
    _getJfybListThread = new GetJfybListThread(this);
}

jfyb_ScrollArea::~jfyb_ScrollArea()
{
    if (_getJfybCondtionThread != NULL) {
        _getJfybCondtionThread->terminate();
        _getJfybCondtionThread->exit();
        delete _getJfybCondtionThread;
    }
    if (_getJfybListThread != NULL) {
        _getJfybListThread->terminate();
        _getJfybListThread->exit();
        delete _getJfybListThread;
    }
    delete ui;
}

void jfyb_ScrollArea::refresh()
{
    _getJfybListThread->currentCondition = "";
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

    _getJfybListThread->currentCondition += " and [缴费时间] between '"+datetime1+"' and '"+datetime2+ "'";

    if (ui->cbx_sp->currentText() != "不区分") {
        _getJfybListThread->currentCondition += " and [运营商] like '%"+ui->cbx_sp->currentText()+"%' ";
    } else {
        if ((Config::GetInstance()->_client_type == "移动客户端")) {
            _getJfybListThread->currentCondition += " and [运营商] like '%移动%' ";
        } else {
             _getJfybListThread->currentCondition += " and ([运营商] like '%联通%' or [运营商] like '%电信%')";
        }
    }
    if (ui->cbx_state->currentText() != "不区分") {
        _getJfybListThread->currentCondition += " and [缴费状态] like '%"+ui->cbx_state->currentText()+"%' ";
    }
    if (ui->txi_phone_no->text() != "") {
        _getJfybListThread->currentCondition += " and [缴费客户号码] like '%"+ui->txi_phone_no->text()+"%' ";
    }
    //
    if (!this->_getJfybListThread->isRunning()) {
        _getJfybListThread->start();
    } else {
        return;
    }
}

void jfyb_ScrollArea::init()
{
    reset();
    getSearchCondition();
    refresh();
}

void jfyb_ScrollArea::getSearchCondition()
{
    ui->cbx_sp->clear();
    ui->cbx_state->clear();
    ui->cbx_sp->addItem("不区分","不区分");
    ui->cbx_state->addItem("不区分","不区分");

    if (!this->_getJfybCondtionThread->isRunning()) {
        _getJfybCondtionThread->start();
    }
}

void jfyb_ScrollArea::reset()
{
    ui->cbx_sp->setCurrentIndex(0);
    ui->cbx_state->setCurrentIndex(0);
    ui->txi_phone_no->setText("");
    ui->tableWidget->clearContents();
    //表头信息
    QString countStr = "缴费:【0】笔";
    QString totalPayStr = "缴费金额:【0】元";
    QString totalRepayStr = "返款:【0】元";
    ui->txt_rpt_total->setText(countStr);
    ui->txt_rpt_money->setText(totalPayStr);
    ui->txt_rpt_repay->setText(totalRepayStr);
    //时间
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());
}

void jfyb_ScrollArea::on_btn_search_clicked()
{
    refresh();
}

void jfyb_ScrollArea::on_btn_refresh_clicked()
{
    refresh();
}

void jfyb_ScrollArea::on_btn_print_clicked()
{
    if (ui->tableWidget->currentRow() >= 0) {
        int index = ui->tableWidget->currentRow();
        if (ui->tableWidget->item(index, 0) != NULL && ui->tableWidget->item(index, 0)->text() != "") {
            Printer::GetInstance()->printJF("[Id]='"+ui->tableWidget->item(index, 0)->text()+"'");
            QModelIndex _QModelIndex;
            ui->tableWidget->setCurrentIndex(_QModelIndex);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"当前没有选中打印项！",QMessageBox::Ok);
    }
}
