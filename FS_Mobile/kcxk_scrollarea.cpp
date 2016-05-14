#include "kcxk_scrollarea.h"
#include "ui_kcxk_scrollarea.h"
#include "gsoap/soapBusinessFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "printer.h"
#include "EncryptUtil.h"
#include "config.h"

GetKcxkCondtionThread::GetKcxkCondtionThread(kcxk_ScrollArea *kcxk_ScrollArea_ptr)
{
    this->_ref = kcxk_ScrollArea_ptr;
}

void GetKcxkCondtionThread::run()
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
    queryStr = "[Category]='小卡状态' and [Enabled]=1 ";
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
        qDebug()<<"服务器出错，无法提取小卡状态下拉列表";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='号段' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_noSection->addItem(name,value);
        }
    } else {
        qDebug()<<"服务器出错，无法提取客户端缴费状态下拉列表";
    }
}

GetKcxkListThread::GetKcxkListThread(kcxk_ScrollArea *kcxk_ScrollArea_ptr)
{
    this->_ref = kcxk_ScrollArea_ptr;
    this->currentCondition = "";
}

void GetKcxkListThread::run()
{
    int total = 0;

    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetMiniCardRecord req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [网点用户Id]='"+Singleton::GetInstance()->getUser().Id+"' "+currentCondition+" order by [销售时间] desc";
    qDebug()<<"查询条件:"+queryStr;
    std::string condition = NetSecurity::encrypt(queryStr);
    qDebug()<<"查询条件:"+QString::fromStdString(condition);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    qDebug()<<"session:"+Singleton::GetInstance()->session_id;
    req.sessionId = buffer2;

    _ns1__GetMiniCardRecordResponse res;
    if (soap.__ns13__GetMiniCardRecord(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetMiniCardRecordResult->__sizeMiniCardItem;
        _ref->ui->tableWidget->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<8; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetMiniCardRecordResult->MiniCardItem[i]->userName);
                        break;
                    case 1:
                        content = QString::fromUtf8(res.GetMiniCardRecordResult->MiniCardItem[i]->cardNo);
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetMiniCardRecordResult->MiniCardItem[i]->noSection);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetMiniCardRecordResult->MiniCardItem[i]->SP);
                        break;
                    case 4:
                        content = QString::fromUtf8(res.GetMiniCardRecordResult->MiniCardItem[i]->state);
                        break;
                    case 5:
                        content = QString::fromUtf8(res.GetMiniCardRecordResult->MiniCardItem[i]->workerName);
                        break;
                    case 6:
                        qDebug()<<"销售时间:"+QString::number(res.GetMiniCardRecordResult->MiniCardItem[i]->sellDate);
                        if (-1 == res.GetMiniCardRecordResult->MiniCardItem[i]->sellDate) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetMiniCardRecordResult->MiniCardItem[i]->sellDate)));
                        content = QString(cTime);
                        break;
                    case 7:
                        qDebug()<<"分配时间:"+QString::number(res.GetMiniCardRecordResult->MiniCardItem[i]->usedDate);
                        if (-1 == res.GetMiniCardRecordResult->MiniCardItem[i]->usedDate) continue;
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetMiniCardRecordResult->MiniCardItem[i]->usedDate)));
                        content = QString(cTime);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget->setItem(i, j, item);
            }
        }
        QString countStr = "共:【"+QString::number(total)+"】张";
        _ref->ui->txt_rpt_total->setText(countStr);
    } else {
        qDebug()<<"服务器出错，无法提取库存小卡信息";
    }
}

kcxk_ScrollArea::kcxk_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::kcxk_ScrollArea)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "用户名" << "小卡号" << "号段" << "运营商" << "使用状态" << "业务员名称" << "购买时间" << "使用时间" ;
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,70);
    ui->tableWidget->setColumnWidth(5,100);
    ui->tableWidget->setColumnWidth(6,150);

    _getKcxkCondtionThread = new GetKcxkCondtionThread(this);
    _getKcxkListThread = new GetKcxkListThread(this);
}

kcxk_ScrollArea::~kcxk_ScrollArea()
{
    if (_getKcxkCondtionThread != NULL) {
        _getKcxkCondtionThread->terminate();
        _getKcxkCondtionThread->exit();
        delete _getKcxkCondtionThread;
    }
    if (_getKcxkListThread != NULL) {
        _getKcxkListThread->terminate();
        _getKcxkListThread->exit();
        delete _getKcxkListThread;
    }
    delete ui;
}

void kcxk_ScrollArea::refresh()
{
    _getKcxkListThread->currentCondition = "";
    if (ui->cbx_sp->currentText() != "不区分") {
        _getKcxkListThread->currentCondition += "and [运营商] like '%"+ui->cbx_sp->currentText()+"%' ";
    } else {
        if ((Config::GetInstance()->_client_type == "移动客户端")) {
            _getKcxkListThread->currentCondition += "and [运营商] like '%移动%' ";
        } else {
             _getKcxkListThread->currentCondition += "and ([运营商] like '%联通%' or [运营商] like '%电信%')";
        }
    }
    if (ui->cbx_state->currentText() != "不区分") {
        _getKcxkListThread->currentCondition += "and [使用状态] like '%"+ui->cbx_state->currentText()+"%' ";
    }
    if (ui->cbx_noSection->currentText() != "不区分") {
        _getKcxkListThread->currentCondition += "and [号段] like '%"+ui->cbx_noSection->currentText()+"%' ";
    }

    if (_getKcxkListThread->isRunning()) {
        _getKcxkListThread->terminate();
    }
    _getKcxkListThread->start();
}

void kcxk_ScrollArea::init()
{
    reset();
    getSearchCondition();
    refresh();
}

void kcxk_ScrollArea::reset()
{
    ui->cbx_sp->setCurrentIndex(0);
    ui->cbx_state->setCurrentIndex(0);
    ui->cbx_noSection->setCurrentIndex(0);
    ui->tableWidget->clearContents();
    //表头信息
    QString countStr = "共:【0】张";
    ui->txt_rpt_total->setText(countStr);
}

void kcxk_ScrollArea::getSearchCondition()
{
    ui->cbx_sp->clear();
    ui->cbx_state->clear();
    ui->cbx_noSection->clear();
    ui->cbx_sp->addItem("不区分","不区分");
    ui->cbx_state->addItem("不区分","不区分");
    ui->cbx_noSection->addItem("不区分","不区分");

    if (_getKcxkCondtionThread->isRunning()) {
        _getKcxkCondtionThread->terminate();
    }
     _getKcxkCondtionThread->start();
}

void kcxk_ScrollArea::on_btn_search_clicked()
{
    refresh();
}
