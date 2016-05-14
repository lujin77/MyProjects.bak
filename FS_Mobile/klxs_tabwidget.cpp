#include "klxs_tabwidget.h"
#include "ui_klxs_tabwidget.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include "gsoap/soapBusinessFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include "printer.h"
#include <QMessageBox>
#include "EncryptUtil.h"
#include "config.h"

GetKlxsListThread::GetKlxsListThread(klxs_TabWidget *klxs_TabWidget_ptr)
{
    this->_ref = klxs_TabWidget_ptr;
}

void GetKlxsListThread::run()
{
    qDebug()<<"进入提取卡类销售前10条列表的线程";
    int total = 0;

    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetSellOtherCardRecordByCondition req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [网点用户Id]='"+Singleton::GetInstance()->getUser().Id+"' order by [购买时间] desc";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    qDebug()<<"condition:"+QString::fromStdString(condition);
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    qDebug()<<"sessionId:"+Singleton::GetInstance()->session_id;
    req.sessionId = buffer2;

    _ns1__GetSellOtherCardRecordByConditionResponse res;
    if (soap.__ns13__GetSellOtherCardRecordByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetSellOtherCardRecordByConditionResult->__sizeSellOtherCardItem;
         _ref->ui->tableWidget->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<8; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetSellOtherCardRecordByConditionResult->SellOtherCardItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetSellOtherCardRecordByConditionResult->SellOtherCardItem[i]->cardType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetSellOtherCardRecordByConditionResult->SellOtherCardItem[i]->cardName);
                        break;
                    case 4:
                        content = QString::fromUtf8(res.GetSellOtherCardRecordByConditionResult->SellOtherCardItem[i]->cardSeq);
                        break;
                    case 5:
                        content = QString::fromUtf8(res.GetSellOtherCardRecordByConditionResult->SellOtherCardItem[i]->cardPsw);
                        break;
                    case 6:
                        content = QString::fromUtf8(res.GetSellOtherCardRecordByConditionResult->SellOtherCardItem[i]->state);
                        break;
                    case 7:
                        if (-1 == res.GetSellOtherCardRecordByConditionResult->SellOtherCardItem[i]->datetime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetSellOtherCardRecordByConditionResult->SellOtherCardItem[i]->datetime)));
                        content = QString(cTime);
                        break;
                }
                if (i < 10) {
                    QTableWidgetItem *item = new QTableWidgetItem (content);
                    _ref->ui->tableWidget->setItem(i, j, item);
                }
            }
        }
        QString countStr = "购买记录:【" + QString::number(total) +"】笔";
        _ref->ui->txt_rpt_count->setText(countStr);
    }
    else {
        qDebug()<<"服务器出错！不能获取卡类销售前10条列表";
    }
    qDebug()<<"卡类销售前10条提取成功";
}

GetKlxsCxCondtionThread::GetKlxsCxCondtionThread(klxs_TabWidget *klxs_TabWidget_ptr)
{
    this->_ref = klxs_TabWidget_ptr;
}

void GetKlxsCxCondtionThread::run()
{
    //提取状态下拉列表
    qDebug()<<"进入提取卡类销售状态线程...";
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetDicContentByCondition req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='查询状态' and [Enabled]=1 ";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_state->addItem(name,value);
        }
    } else {
        qDebug()<<"服务器出错，无法提取卡类销售状态下拉列表";
    }

    qDebug()<<"进入提取卡类列表的线程";

    BusinessFunctionWebServiceSoap soap1;
    soap_set_mode(soap1.soap, SOAP_C_UTFSTRING);
    _ns1__GetOtherCardList req1;

    req1.condition = "";

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    qDebug()<<"session:"+Singleton::GetInstance()->session_id;
    req1.sessionId = buffer2;

    _ns1__GetOtherCardListResponse res1;
    if (soap1.__ns13__GetOtherCardList(&req1,&res1) == SOAP_OK) {
        _ref->ui->tableWidget_cardlist->clearContents();
        QString name = "";
        QString type = "";
        int total = res1.GetOtherCardListResult->__sizeOtherCardItem;
        for (int i=0; i<total; ++i) {
            type = QString::fromUtf8(res1.GetOtherCardListResult->OtherCardItem[i]->cardType);
            name = QString::fromUtf8(res1.GetOtherCardListResult->OtherCardItem[i]->cardName);
            if (type == "通信类") _ref->arrCardListTx.append(name);
            if (type == "游戏类") _ref->arrCardListYx.append(name);
            if (type == "其他类") _ref->arrCardListQt.append(name);
            //qDebug()<<"获取卡类"+name;
        }
        //根据单选按钮更新界面
        QStringList *arrCardList;
        if (_ref->ui->rdo_tx->isChecked() == true) {
            arrCardList = &_ref->arrCardListTx;
        }
        if (_ref->ui->rdo_yx->isChecked() == true) {
            arrCardList = &_ref->arrCardListYx;
        }
        if (_ref->ui->rdo_qt->isChecked() == true) {
            arrCardList = &_ref->arrCardListQt;
        }

        int count = arrCardList->size();
        int row = (count / 4) + 1;
        _ref->ui->tableWidget_cardlist->setRowCount(row);
        QString content = "";
        int i = 0;
        int j = 0;
        for (int n = 0; n < count; ++n) {
            i = n / 4;
            j = n % 4;
            content = arrCardList->at(n);
            QTableWidgetItem *item = new QTableWidgetItem (content);
            _ref->ui->tableWidget_cardlist->setItem(i, j, item);
            qDebug()<<"添加一个卡类"+content;
        }
        qDebug()<<"卡类列表提取成功";
    }
    else {
        qDebug()<<"服务器出错！不能获取卡类列表";
    }

}

GetKlxsCxListThread::GetKlxsCxListThread(klxs_TabWidget *klxs_TabWidget_ptr)
{
    this->_ref = klxs_TabWidget_ptr;
}

void GetKlxsCxListThread::run()
{
    qDebug()<<"进入提取卡类销售查询的线程";
    int total = 0;

    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GettSellOtherCardRecordHistoryByCondition req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [网点用户Id]='"+Singleton::GetInstance()->getUser().Id+"' "+currentCondition+" order by [购买时间] desc";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    qDebug()<<"condition:"+QString::fromStdString(condition);
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    qDebug()<<"sessionId:"+Singleton::GetInstance()->session_id;
    req.sessionId = buffer2;

    _ns1__GettSellOtherCardRecordHistoryByConditionResponse res;
    if (soap.__ns13__GettSellOtherCardRecordHistoryByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget_cx->clearContents();
        QString content = "";
        total = res.GettSellOtherCardRecordHistoryByConditionResult->__sizeSellOtherCardItem;
         _ref->ui->tableWidget_cx->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<9; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GettSellOtherCardRecordHistoryByConditionResult->SellOtherCardItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GettSellOtherCardRecordHistoryByConditionResult->SellOtherCardItem[i]->cardType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GettSellOtherCardRecordHistoryByConditionResult->SellOtherCardItem[i]->cardName);
                        break;
                    case 4:
                        content = QString::fromUtf8(res.GettSellOtherCardRecordHistoryByConditionResult->SellOtherCardItem[i]->cardSeq);
                        break;
                    case 5:
                        content = QString::fromUtf8(res.GettSellOtherCardRecordHistoryByConditionResult->SellOtherCardItem[i]->cardPsw);
                        break;
                    case 6:
                        content = QString::fromUtf8(res.GettSellOtherCardRecordHistoryByConditionResult->SellOtherCardItem[i]->state);
                        break;
                    case 7:
                        content = QString::number(res.GettSellOtherCardRecordHistoryByConditionResult->SellOtherCardItem[i]->chargeMoney,'f',2);
                        break;
                    case 8:
                        if (-1 == res.GettSellOtherCardRecordHistoryByConditionResult->SellOtherCardItem[i]->datetime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GettSellOtherCardRecordHistoryByConditionResult->SellOtherCardItem[i]->datetime)));
                        content = QString(cTime);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget_cx->setItem(i, j, item);
            }
        }
        QString countStr = "购买记录:【" + QString::number(total) +"】笔";
        _ref->ui->txt_rpt_count_cx->setText(countStr);
    }
    else {
        qDebug()<<"服务器出错！不能获取卡类销售查询列表";
    }
    qDebug()<<"提取成功";
}


klxs_TabWidget::klxs_TabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::klxs_TabWidget)
{
    ui->setupUi(this);
    //卡类列表
    ui->tableWidget_cardlist->setColumnCount(4);
    ui->tableWidget_cardlist->setRowCount(0);
    ui->tableWidget_cardlist->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_cardlist->setAlternatingRowColors(true);
    ui->tableWidget_cardlist->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    //卡类销售结果
    QString count = "购买记录:【0】笔";
    ui->txt_rpt_count->setText(count);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "Id" << "网点用户" << "卡类型" << "卡名称" << "序列号" << "卡密" << "状态" << "办理时间";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget->setColumnWidth(1,80);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,200);
    ui->tableWidget->setColumnWidth(5,200);
    ui->tableWidget->setColumnWidth(6,80);
    ui->txt_rpt_count->setText(count);

    //卡类销售查询结果
    ui->txt_rpt_count->setText(count);
    ui->tableWidget_cx->setColumnCount(9);
    ui->tableWidget_cx->setRowCount(0);
    ui->tableWidget_cx->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_cx->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget_cx->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_cx->setAlternatingRowColors(true);
    list << "Id" << "网点用户" << "卡类型" << "卡名称" << "序列号" << "卡密" << "状态" << "扣款金额" << "办理时间";
    ui->tableWidget_cx->setHorizontalHeaderLabels(list);
    ui->tableWidget_cx->hideColumn(0);
    ui->tableWidget_cx->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget_cx->setColumnWidth(1,80);
    ui->tableWidget_cx->setColumnWidth(2,80);
    ui->tableWidget_cx->setColumnWidth(3,150);
    ui->tableWidget_cx->setColumnWidth(4,200);
    ui->tableWidget_cx->setColumnWidth(5,200);
    ui->tableWidget_cx->setColumnWidth(6,80);
    ui->tableWidget_cx->setColumnWidth(7,80);
    ui->txt_rpt_count_cx->setText(count);

    ui->cbx_state->addItem("不区分","不区分");
    ui->cbx_card_type->addItem("不区分","不区分");
    ui->cbx_card_type->addItem("通信类","通信类");
    ui->cbx_card_type->addItem("游戏类","游戏类");
    ui->cbx_card_type->addItem("其他类","其他类");
    ui->cbx_card_name->addItem("不区分","不区分");

    _getKlxsListThread = new GetKlxsListThread(this);
    _getKlxsCxCondtionThread = new GetKlxsCxCondtionThread(this);
    _getKlxsCxListThread = new GetKlxsCxListThread(this);

    //时间
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());

    ui->rdo_tx->setChecked(true);

}

klxs_TabWidget::~klxs_TabWidget()
{
    if (_getKlxsListThread != NULL) {
        _getKlxsListThread->terminate();
        _getKlxsListThread->exit();
        delete _getKlxsListThread;
    }
    if (_getKlxsCxCondtionThread != NULL) {
        _getKlxsCxCondtionThread->terminate();
        _getKlxsCxCondtionThread->exit();
        delete _getKlxsCxCondtionThread;
    }
    if (_getKlxsCxListThread != NULL) {
        _getKlxsCxListThread->terminate();
        _getKlxsCxListThread->exit();
        delete _getKlxsCxListThread;
    }
    delete ui;
}

void klxs_TabWidget::changeEvent(QEvent *e)
{
    QTabWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void klxs_TabWidget::refreshAll()
{
    refreshCardList();
    refresh();
    refreshCx();
}

void klxs_TabWidget::refreshCardList()
{
    resetCardList();
    if (!_getKlxsCxCondtionThread->isRunning())
        _getKlxsCxCondtionThread->start();
}

void klxs_TabWidget::refresh()
{
    if (!_getKlxsListThread->isRunning())
        _getKlxsListThread->start();
}

void klxs_TabWidget::refreshCx()
{
    _getKlxsCxListThread->currentCondition = "";
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

    _getKlxsCxListThread->currentCondition = " and [购买时间] between '"+datetime1+"' and '"+datetime2+ "' ";

    if (ui->cbx_card_type->currentText() != "不区分") {
        _getKlxsCxListThread->currentCondition += "and [卡类型] like '%"+ui->cbx_card_type->currentText()+"%' ";
    }
    if (ui->cbx_card_name->currentText() != "不区分") {
        _getKlxsCxListThread->currentCondition += "and [卡名称] like '%"+ui->cbx_card_name->currentText()+"%' ";
    }
    if (ui->cbx_state->currentText() != "不区分") {
        _getKlxsCxListThread->currentCondition += "and [状态] like '%"+ui->cbx_state->currentText()+"%' ";
    }

    //启动线程
    if (!_getKlxsCxListThread->isRunning())
        _getKlxsCxListThread->start();
}

void klxs_TabWidget::init()
{
    resetAll();
    getSearchCondition();
    refreshAll();
}

void klxs_TabWidget::getSearchCondition()
{
    resetCardList();
    ui->cbx_state->clear();
    ui->cbx_card_type->clear();
    ui->cbx_card_name->clear();
    ui->cbx_state->addItem("不区分","不区分");
    ui->cbx_card_type->addItem("不区分","不区分");
    ui->cbx_card_type->addItem("通信类","通信类");
    ui->cbx_card_type->addItem("游戏类","游戏类");
    ui->cbx_card_type->addItem("其他类","其他类");
    ui->cbx_card_name->addItem("不区分","不区分");
    if (!_getKlxsCxCondtionThread->isRunning())
        _getKlxsCxCondtionThread->start();
}

void klxs_TabWidget::resetAll()
{
    resetCardList();
    reset();
    resetCx();
}

void klxs_TabWidget::resetCardList()
{
    ui->tableWidget_cardlist->clearContents();
    arrCardListTx.clear();
    arrCardListYx.clear();
    arrCardListQt.clear();
}

void klxs_TabWidget::reset()
{
    ui->tableWidget->clearContents();
    ui->txt_rpt_count->setText(QString("购买记录:【0】笔"));
}

void klxs_TabWidget::resetCx()
{
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());
    ui->cbx_state->clear();
    ui->cbx_card_type->clear();
    ui->cbx_card_name->clear();
    ui->cbx_state->addItem("不区分","不区分");
    ui->cbx_card_type->addItem("不区分","不区分");
    ui->cbx_card_type->addItem("通信类","通信类");
    ui->cbx_card_type->addItem("游戏类","游戏类");
    ui->cbx_card_type->addItem("其他类","其他类");
    ui->cbx_card_name->addItem("不区分","不区分");
    ui->tableWidget_cx->clearContents();
    ui->txt_rpt_count_cx->setText(QString("购买记录:【0】笔"));
}

void klxs_TabWidget::printKlxs()
{
    if (ui->tableWidget->currentRow() >= 0) {
        int index = ui->tableWidget->currentRow();
        if (ui->tableWidget->item(index, 0) != NULL && ui->tableWidget->item(index, 0)->text() != "") {
            Printer::GetInstance()->printKlxs(Singleton::GetInstance()->getUser().shopName,
                                              ui->tableWidget->item(index, 2)->text(),
                                              ui->tableWidget->item(index, 3)->text(),
                                              ui->tableWidget->item(index, 4)->text(),
                                              ui->tableWidget->item(index, 5)->text(),
                                              ui->tableWidget->item(index, 6)->text(),
                                              ui->tableWidget->item(index, 7)->text());
            QModelIndex _QModelIndex;
            ui->tableWidget->setCurrentIndex(_QModelIndex);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"当前没有选中打印项！",QMessageBox::Ok);
    }
}

void klxs_TabWidget::on_btn_refresh_clicked()
{
    refresh();
}

void klxs_TabWidget::on_btn_print_klsx_clicked()
{
    printKlxs();
}

void klxs_TabWidget::on_btn_search_cx_clicked()
{
    refreshCx();
}

void klxs_TabWidget::on_btn_refresh_cx_clicked()
{
    refreshCx();
}

void klxs_TabWidget::on_tableWidget_cardlist_clicked(const QModelIndex &index)
{


    //有效性验证
    if (ui->tableWidget_cardlist->item(index.row(),index.column()) == NULL) {
        return;
    }
    QString cardName = ui->tableWidget_cardlist->item(index.row(),index.column())->text();
    if (cardName == "" || cardName == NULL)
    {
       return;
    }
    //QString result = "("+QString::number(index.row())+","+QString::number(index.column())+")"+"当前卡名称:"+cardName;
    //QMessageBox::warning(this,tr("警告"),result,QMessageBox::Ok);


    QString str = "确定要购买<" + cardName + ">吗？";
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "卡类销售", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb != QMessageBox::Yes) {
        return;
    }

    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__SellOhterCard req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    QString cardType = "";
    if (ui->rdo_tx->isChecked() == true) {
        cardType = "通信类";
    }
    if (ui->rdo_yx->isChecked() == true) {
        cardType = "游戏类";
    }
    if (ui->rdo_qt->isChecked() == true) {
        cardType = "其他类";
    }
    std::string type = NetSecurity::encrypt(cardType);
    strcpy(buffer0, type.data());
    qDebug()<<"cardType:"+QString::fromStdString(type);
    req.cardType = buffer0;

    char buffer[255];
    memset(buffer,0,255*sizeof(char));
    std::string name = NetSecurity::encrypt(cardName);
    strcpy(buffer, name.data());
    qDebug()<<"cardName:"+QString::fromStdString(name);
    req.cardName = buffer;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString userId = Singleton::GetInstance()->getUser().Id;
    std::string id = NetSecurity::encrypt(userId);
    strcpy(buffer1, id.data());
    qDebug()<<"userId:"+QString::fromStdString(id);
    req.userId = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__SellOhterCardResponse res;
    if (soap.__ns13__SellOhterCard(&req,&res) == SOAP_OK) {
        QString result = QString::fromUtf8(res.SellOhterCardResult);
        QMessageBox::warning(this,tr("警告"),result,QMessageBox::Ok);
        if (result.contains("成功")) {

            //更新最新显示列表
            refresh();

            //更新客户端显示的金钱数量
            UserFunctionWebServiceSoap soap;
            soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
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
                //更新缓存在客户端的money
                double newMoney = res1.GetUserInfoResult->money;
                UserVO user = Singleton::GetInstance()->getUser();
                user.money = newMoney;
                Singleton::GetInstance()->setUser(user);
            } else {
                QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
            }

            emit updateMoney();
        }
    } else {
        QMessageBox::warning(this,tr("警告"),tr("服务器出错！不能获取卡类销售查询列表"),QMessageBox::Ok);
    }

}

void klxs_TabWidget::on_cbx_card_type_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "不区分") {
        ui->cbx_card_name->clear();
        ui->cbx_card_name->addItem("不区分","不区分");
    }

    QString str;
    if (arg1 == "通信类") {
        ui->cbx_card_name->clear();
        ui->cbx_card_name->addItem("不区分","不区分");
        foreach(str, arrCardListTx) {
            ui->cbx_card_name->addItem(str, str);
        }
    }
    if (arg1 == "游戏类") {
        ui->cbx_card_name->clear();
        ui->cbx_card_name->addItem("不区分","不区分");
        foreach(str, arrCardListYx) {
            ui->cbx_card_name->addItem(str, str);
        }
    }
    if (arg1 == "其他类") {
        ui->cbx_card_name->clear();
        ui->cbx_card_name->addItem("不区分","不区分");
        foreach(str, arrCardListQt) {
            ui->cbx_card_name->addItem(str, str);
        }
    }
}

void klxs_TabWidget::on_rdo_tx_clicked()
{
    refreshCardList();
}

void klxs_TabWidget::on_rdo_yx_clicked()
{
    refreshCardList();
}

void klxs_TabWidget::on_rdo_qt_clicked()
{
    refreshCardList();
}


