#include "jfrb_scrollarea.h"
#include "ui_jfrb_scrollarea.h"
#include "gsoap/soapPaymentFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "printer.h"
#include "EncryptUtil.h"
#include "config.h"

GetJfrbCondtionThread::GetJfrbCondtionThread(jfrb_ScrollArea *jfrb_ScrollArea_ptr)
{
    this->_ref = jfrb_ScrollArea_ptr;
}

void GetJfrbCondtionThread::run()
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
                    _ref->ui->cbx_SP->addItem(name,value);
                }
            } else {
                if (name != "移动") {
                    _ref->ui->cbx_SP->addItem(name,value);
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

GetJfrbListThread::GetJfrbListThread(jfrb_ScrollArea *jfrb_ScrollArea_ptr)
{
    this->_ref = jfrb_ScrollArea_ptr;
    this->currentCondition = "";
}

void GetJfrbListThread::run()
{
    int total = 0;
    float totalPay = 0;
    float totalRepay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPaymentRecord req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [网点用户Id]='"+Singleton::GetInstance()->getUser().Id+"' "+currentCondition+"order by [缴费时间] desc";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetPaymentRecordResponse res;
    if (soap.__ns3__GetPaymentRecord(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetPaymentRecordResult->__sizePaymentItem;
        _ref->ui->tableWidget->setRowCount(total);
        for (int i=0; i<res.GetPaymentRecordResult->__sizePaymentItem; ++i) {
            for (int j=0; j<10; ++j) {
                switch (j) {
                    case 0:
                         content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->Id);
                         break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->telNo);
                        break;
                    case 3:
                        content = QString::number(res.GetPaymentRecordResult->PaymentItem[i]->customerBeforeMoney,'f',2);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPaymentRecordResult->PaymentItem[i]->chargeMoney,'f',2);
                        float payMoney = res.GetPaymentRecordResult->PaymentItem[i]->chargeMoney;
                        totalPay += payMoney;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->state);
                        break;

                    case 6:
                        content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->SP);
                        break;
                    case 7:
                    {
                        content = QString::number(res.GetPaymentRecordResult->PaymentItem[i]->repay,'f',2);
                        float repayMoney = res.GetPaymentRecordResult->PaymentItem[i]->repay;
                        totalRepay += repayMoney;
                        break;
                    }
                    case 8:
                        content = QString::fromUtf8(res.GetPaymentRecordResult->PaymentItem[i]->area);
                        break;
                    case 9:
                        if (-1 == res.GetPaymentRecordResult->PaymentItem[i]->chargeTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPaymentRecordResult->PaymentItem[i]->chargeTime)));
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

jfrb_ScrollArea::jfrb_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::jfrb_ScrollArea)
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
    ui->txi_PhoneNo->setValidator( validator );

    //connect(ui->btn_refresh, SIGNAL(clicked()), this, SLOT(on_btn_refresh_clicked()));
    //connect(ui->btn_cx, SIGNAL(clicked()), this, SLOT(on_btn_cx_clicked()));
    //connect(ui->btn_fx, SIGNAL(clicked()), this, SLOT(on_btn_fx_clicked()));
    _getJfrbCondtionThread = new GetJfrbCondtionThread(this);
    _getJfrbListThread = new GetJfrbListThread(this);
}

jfrb_ScrollArea::~jfrb_ScrollArea()
{
    if (_getJfrbCondtionThread != NULL) {
        _getJfrbCondtionThread->terminate();
        _getJfrbCondtionThread->exit();
        delete _getJfrbCondtionThread;
    }
    if (_getJfrbListThread != NULL) {
        _getJfrbListThread->terminate();
        _getJfrbListThread->exit();
        delete _getJfrbListThread;
    }

    delete ui;
}

void jfrb_ScrollArea::refresh()
{
    _getJfrbListThread->currentCondition = "";
    if (ui->cbx_SP->currentText() != "不区分") {
        _getJfrbListThread->currentCondition += "and [运营商] like '%"+ui->cbx_SP->currentText()+"%' ";
    } else {
        if ((Config::GetInstance()->_client_type == "移动客户端")) {
            _getJfrbListThread->currentCondition += "and [运营商] like '%移动%' ";
        } else {
             _getJfrbListThread->currentCondition += "and ([运营商] like '%联通%' or [运营商] like '%电信%')";
        }
    }
    if (ui->cbx_state->currentText() != "不区分") {
        _getJfrbListThread->currentCondition += "and [缴费状态] like '%"+ui->cbx_state->currentText()+"%' ";
    }
    if (ui->txi_PhoneNo->text() != "") {
        _getJfrbListThread->currentCondition += "and [缴费客户号码] like '%"+ui->txi_PhoneNo->text()+"%' ";
    }

    if (!this->_getJfrbListThread->isRunning()) {
        _getJfrbListThread->start();
    } else {
        return;
    }
}

void jfrb_ScrollArea::init()
{
    reset();
    getSearchCondition();
    refresh();
}

void jfrb_ScrollArea::reset()
{
    ui->cbx_SP->setCurrentIndex(0);
    ui->cbx_state->setCurrentIndex(0);
    ui->txi_PhoneNo->setText("");
    ui->tableWidget->clearContents();
    //表头信息
    QString countStr = "缴费:【0】笔";
    QString totalPayStr = "缴费金额:【0】元";
    QString totalRepayStr = "返款:【0】元";
    ui->txt_rpt_total->setText(countStr);
    ui->txt_rpt_money->setText(totalPayStr);
    ui->txt_rpt_repay->setText(totalRepayStr);
}

void jfrb_ScrollArea::getSearchCondition()
{
    ui->cbx_SP->clear();
    ui->cbx_state->clear();
    ui->cbx_SP->addItem("不区分","不区分");
    ui->cbx_state->addItem("不区分","不区分");

    if (!this->_getJfrbCondtionThread->isRunning()) {
        _getJfrbCondtionThread->start();
    }
}

void jfrb_ScrollArea::on_btn_refresh_clicked()
{
    refresh();
}

void jfrb_ScrollArea::on_btn_fx_clicked()
{
    int index = ui->tableWidget->currentIndex().row();
    if (index < 0) {
        QMessageBox::warning(this,tr("警告"),"错误！您没有选中任何项目",QMessageBox::Ok);
        return;
    }

    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "缴费日报", "确定要返销该条记录?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb != QMessageBox::Yes) {
        return;
    }

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__RequstRollback req;
    QString payment_id = ui->tableWidget->item(index,0)->text();
    qDebug()<<"返销ID"+payment_id;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string paymentId = NetSecurity::encrypt(payment_id);
    strcpy(buffer1, paymentId.data());
    req.paymentId = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer2, userId.data());
    req.userId = buffer2;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer3;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    std::string type = NetSecurity::encrypt(QString("申请返销"));
    strcpy(buffer4, type.data());
    req.type = buffer4;

    _ns1__RequstRollbackResponse res;
    if (soap.__ns3__RequstRollback(&req,&res) == SOAP_OK) {
        QString result = QString::fromUtf8(res.RequstRollbackResult);
        if (result.contains("成功")) {
            refresh();
        }
        QMessageBox::warning(this,tr("提示"),result,QMessageBox::Ok);
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
}

void jfrb_ScrollArea::on_btn_cx_clicked()
{
    int index = ui->tableWidget->currentIndex().row();
    if (index < 0) {
        QMessageBox::warning(this,tr("警告"),"错误！您没有选中任何项目",QMessageBox::Ok);
        return;
    }

    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "缴费日报", "确定要撤销该条记录?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb != QMessageBox::Yes) {
        return;
    }

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__RequstRollback req;
    QString payment_id = ui->tableWidget->item(index,0)->text();
    qDebug()<<"撤销ID"+payment_id;
    //QMessageBox::warning(this,tr("警告"),payment_id,QMessageBox::Ok);

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string paymentId = NetSecurity::encrypt(payment_id);
    strcpy(buffer1, paymentId.data());
    req.paymentId = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer2, userId.data());
    req.userId = buffer2;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer3;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    std::string type = NetSecurity::encrypt(QString("申请撤销"));
    strcpy(buffer4, type.data());
    req.type = buffer4;

    _ns1__RequstRollbackResponse res;
    if (soap.__ns3__RequstRollback(&req,&res) == SOAP_OK) {
        QString result = QString::fromUtf8(res.RequstRollbackResult);
        if (result.contains("成功")) {
            refresh();
        }
        QMessageBox::warning(this,tr("提示"),result,QMessageBox::Ok);
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
}

void jfrb_ScrollArea::on_btn_search_clicked()
{
    refresh();
}

void jfrb_ScrollArea::on_btn_print_clicked()
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
