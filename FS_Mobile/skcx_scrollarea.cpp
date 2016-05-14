#include "skcx_scrollarea.h"
#include "ui_skcx_scrollarea.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "gsoap/soapBusinessFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "printer.h"
#include "EncryptUtil.h"
#include "config.h"

GetSkcxCondtionThread::GetSkcxCondtionThread(skcx_ScrollArea *skcx_ScrollArea_ptr)
{
    this->_ref = skcx_ScrollArea_ptr;
}

void GetSkcxCondtionThread::run()
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
    queryStr = "[Category]='查询状态' and [Enabled]=1 ";
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
        qDebug()<<"服务器出错，无法提取客户端售卡查询状态下拉列表";
    }
}

GetSkcxListThread::GetSkcxListThread(skcx_ScrollArea *skcx_ScrollArea_ptr)
{
    _ref = skcx_ScrollArea_ptr;
    currentCondition = "";
}

void GetSkcxListThread::run()
{
    int total = 0;

    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetSellCardRecordByCondition req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [销售用户ID]='"+Singleton::GetInstance()->getUser().Id+"' "+currentCondition+"order by [销售时间] desc";
    qDebug()<<"query str:"+queryStr;
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

   _ns1__GetSellCardRecordByConditionResponse res;
    if (soap.__ns13__GetSellCardRecordByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetSellCardRecordByConditionResult->__sizeSellCardItem;
        _ref->ui->tableWidget->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<8; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetSellCardRecordByConditionResult->SellCardItem[i]->Id);
                         break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetSellCardRecordByConditionResult->SellCardItem[i]->telNo);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetSellCardRecordByConditionResult->SellCardItem[i]->brand);
                        break;
                    case 4:
                        content = QString::fromUtf8(res.GetSellCardRecordByConditionResult->SellCardItem[i]->cardPrice);
                        break;
                    case 5:
                        content = QString::fromUtf8(res.GetSellCardRecordByConditionResult->SellCardItem[i]->miniNo);
                        break;

                    case 6:
                        content = QString::fromUtf8(res.GetSellCardRecordByConditionResult->SellCardItem[i]->state);
                        break;
                    case 7:
                        if (-1 == res.GetSellCardRecordByConditionResult->SellCardItem[i]->sellTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetSellCardRecordByConditionResult->SellCardItem[i]->sellTime)));
                        content = QString(cTime);
                        break;

                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget->setItem(i, j, item);
            }
        }
        QString totalStr = "共:【"+QString::number(total)+"】条售卡记录";
        _ref->ui->txt_rpt_total->setText(totalStr);
    } else {
        qDebug()<<"服务器出错，无法提取售卡信息";
    }
}

skcx_ScrollArea::skcx_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::skcx_ScrollArea)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "Id" << "网点用户" << "销售号码" << "套餐名称" << "开卡面值"
         << "绑定小卡" << "开卡状态" << "开卡时间";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget->setColumnWidth(1,70);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,200);
    ui->tableWidget->setColumnWidth(4,70);
    ui->tableWidget->setColumnWidth(5,150);
    ui->tableWidget->setColumnWidth(6,70);

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this );
    ui->txi_no->setValidator( validator );

    _getSkcxCondtionThread = new GetSkcxCondtionThread(this);
    _getSkcxListThread = new GetSkcxListThread(this);

    //表头信息
    QString totalStr = "共:【0】条售卡记录";
    ui->txt_rpt_total->setText(totalStr);
}

skcx_ScrollArea::~skcx_ScrollArea()
{
    if (_getSkcxCondtionThread != NULL) {
        _getSkcxCondtionThread->terminate();
        _getSkcxCondtionThread->exit();
        delete _getSkcxCondtionThread;
    }
    if (_getSkcxListThread != NULL) {
        _getSkcxListThread->terminate();
        _getSkcxListThread->exit();
        delete _getSkcxListThread;
    }
    delete ui;
}

void skcx_ScrollArea::refresh()
{
    _getSkcxListThread->currentCondition = "";
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

    _getSkcxListThread->currentCondition += " and [销售时间] between '"+datetime1+"' and '"+datetime2+ "'";

    if (ui->cbx_sp->currentText() != "不区分") {
        _getSkcxListThread->currentCondition += "and [运营商] like '%"+ui->cbx_sp->currentText()+"%' ";
    } else {
        if ((Config::GetInstance()->_client_type == "移动客户端")) {
            _getSkcxListThread->currentCondition += "and [运营商] like '%移动%' ";
        } else {
             _getSkcxListThread->currentCondition += "and ([运营商] like '%联通%' or [运营商] like '%电信%')";
        }
    }
    if (ui->cbx_state->currentText() != "不区分") {
        _getSkcxListThread->currentCondition += "and [处理状态] like '%"+ui->cbx_state->currentText()+"%' ";
    }
    if (ui->txi_no->text() != "") {
        _getSkcxListThread->currentCondition += "and [电话号码] like '%"+ui->txi_no->text()+"%' ";
    }

    if (!this->_getSkcxListThread->isRunning()) {
        _getSkcxListThread->start();
    }
}

void skcx_ScrollArea::init()
{
    reset();
    getSearchCondition();
    refresh();
}

void skcx_ScrollArea::getSearchCondition()
{
    ui->cbx_sp->clear();
    ui->cbx_state->clear();
    ui->cbx_sp->addItem("不区分","不区分");
    ui->cbx_state->addItem("不区分","不区分");

    if (!this->_getSkcxCondtionThread->isRunning()) {
        _getSkcxCondtionThread->start();
    }
}

void skcx_ScrollArea::reset()
{
    ui->cbx_sp->setCurrentIndex(0);
    ui->cbx_state->setCurrentIndex(0);
    ui->txi_no->setText("");
    ui->tableWidget->clearContents();
    //表头信息
    QString totalStr = "共:【0】条售卡记录";
    ui->txt_rpt_total->setText(totalStr);
    //时间
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());
}

void skcx_ScrollArea::on_btn_search_clicked()
{
    refresh();
}

void skcx_ScrollArea::on_btn_refresh_clicked()
{
    refresh();
}

void skcx_ScrollArea::on_btn_print_clicked()
{
    if (ui->tableWidget->currentRow() >= 0) {
        int index = ui->tableWidget->currentRow();
        if (ui->tableWidget->item(index, 0) != NULL && ui->tableWidget->item(index, 0)->text() != "") {
            Printer::GetInstance()->printSellCard(Singleton::GetInstance()->getUser().shopName,
                                              ui->tableWidget->item(index, 2)->text(),
                                              ui->tableWidget->item(index, 3)->text(),
                                              ui->tableWidget->item(index, 4)->text(),
                                              ui->tableWidget->item(index, 6)->text(),
                                              ui->tableWidget->item(index, 7)->text());
            QModelIndex _QModelIndex;
            ui->tableWidget->setCurrentIndex(_QModelIndex);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"当前没有选中打印项！",QMessageBox::Ok);
    }
}
