#include "yxcz_tabwidget.h"
#include "ui_yxcz_tabwidget.h"
#include "gsoap/soapPaymentFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include "config.h"
#include <QMessageBox>
#include <QDebug>
#include "printer.h"
#include "EncryptUtil.h"

yxcz_TabWidget::yxcz_TabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::yxcz_TabWidget)
{
    ui->setupUi(this);
    //表头信息
    QString countStr = "最新缴费:【0】笔";
    QString totalPayString = "缴费金额:【0】元";
    ui->txt_rpt_count->setText(countStr);
    ui->txt_rpt_money->setText(totalPayString);

    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "Id" << "网点用户" << "游戏类型" << "游戏账号" << "缴费金额" << "缴费状态" << "缴费时间";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,200);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,100);
    ui->tableWidget->setColumnWidth(5,100);
    QRegExp regx_int("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx_int, this);
    //ui->txi_gameAccount->setValidator(validator);
    ui->txi_money->setValidator(validator);

    //日报
    QString countStr1 = "缴费:【0】笔";
    QString totalPayStr1 = "缴费金额:【0】元";
    QString totalRepayStr1 = "返款:【0】元";
    ui->txt_rpt_total_rb->setText(countStr1);
    ui->txt_rpt_money_rb->setText(totalPayStr1);
    ui->txt_rpt_repay_rb->setText(totalRepayStr1);
    ui->tableWidget_rb->setColumnCount(8);
    ui->tableWidget_rb->setRowCount(20);
    ui->tableWidget_rb->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_rb->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget_rb->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_rb->setAlternatingRowColors(true);
    QStringList list1;
    list1 << "Id" << "网点用户" << "游戏类型" << "游戏账号" << "缴费金额" << "缴费状态" << "返款金额" << "缴费时间";
    ui->tableWidget_rb->setHorizontalHeaderLabels(list1);
    //ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget_rb->hideColumn(0);
    ui->tableWidget_rb->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget_rb->setColumnWidth(1,100);
    ui->tableWidget_rb->setColumnWidth(2,200);
    ui->tableWidget_rb->setColumnWidth(3,150);
    ui->tableWidget_rb->setColumnWidth(4,100);
    ui->tableWidget_rb->setColumnWidth(5,100);
    ui->tableWidget_rb->setColumnWidth(6,100);
    //ui->txi_gameAccount_rb->setValidator( validator );

    //月报
    QString countStr2 = "缴费:【0】笔";
    QString totalPayStr2 = "缴费金额:【0】元";
    QString totalRepayStr2 = "返款:【0】元";
    ui->txt_rpt_total_yb->setText(countStr2);
    ui->txt_rpt_money_yb->setText(totalPayStr2);
    ui->txt_rpt_repay_yb->setText(totalRepayStr2);
    ui->tableWidget_yb->setColumnCount(8);
    ui->tableWidget_yb->setRowCount(20);
    ui->tableWidget_yb->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_yb->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget_yb->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_yb->setAlternatingRowColors(true);
    QStringList list2;
    list2 << "Id" << "网点用户" << "游戏类型" << "游戏账号" << "缴费金额" << "缴费状态" << "返款金额" << "缴费时间";
    ui->tableWidget_yb->setHorizontalHeaderLabels(list2);
    //ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget_yb->hideColumn(0);
    ui->tableWidget_yb->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget_yb->setColumnWidth(1,100);
    ui->tableWidget_yb->setColumnWidth(2,200);
    ui->tableWidget_yb->setColumnWidth(3,150);
    ui->tableWidget_yb->setColumnWidth(4,100);
    ui->tableWidget_yb->setColumnWidth(5,100);
    ui->tableWidget_yb->setColumnWidth(6,100);
    //ui->txi_gameAccount_yb->setValidator( validator );

    _getYxczCurrThread = new GetYxczCurrThread(this);
    _getYxczCondtionThread = new GetYxczCondtionThread(this);
    _getYxczRbListThread = new GetYxczRbListThread(this);
    _getYxczYbListThread = new GetYxczYbListThread(this);

    _game_account_size = 0;
    _game_money_size = 0;

    ui->groupBox->hide();
}

yxcz_TabWidget::~yxcz_TabWidget()
{
    if (_getYxczCurrThread != NULL) {
        _getYxczCurrThread->terminate();
        _getYxczCurrThread->exit();
        delete _getYxczCurrThread;
    }
    if (_getYxczCondtionThread != NULL) {
        _getYxczCondtionThread->terminate();
        _getYxczCondtionThread->exit();
        delete _getYxczCondtionThread;
    }
    if (_getYxczRbListThread != NULL) {
        _getYxczRbListThread->terminate();
        _getYxczRbListThread->exit();
        delete _getYxczRbListThread;
    }
    if (_getYxczYbListThread != NULL) {
        _getYxczYbListThread->terminate();
        _getYxczYbListThread->exit();
        delete _getYxczYbListThread;
    }

    delete ui;
}

void yxcz_TabWidget::changeEvent(QEvent *e)
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

void yxcz_TabWidget::resetAll()
{
    resetJF();
    resetRB();
    resetYB();
}

void yxcz_TabWidget::initAll()
{
    initJF();
    initRB();
    initYB();
    getSearchCondition();
}

void yxcz_TabWidget::resetJF()
{
    ui->txi_gameAccount->clear();
    ui->txi_money->clear();
    ui->cbx_gameType->setCurrentIndex(0);
    ui->txi_content->clear();
    ui->txi_gameAccount->setFocus();

    _game_account_size = 0;
    _game_money_size = 0;
}

void yxcz_TabWidget::initJF()
{
    resetJF();
    refreshJF();
}

void yxcz_TabWidget::refreshJF()
{
    if (!_getYxczCurrThread->isRunning())
        _getYxczCurrThread->start();
}

void yxcz_TabWidget::resetRB()
{
    ui->cbx_gameType_rb->setCurrentIndex(0);
    ui->cbx_state_rb->setCurrentIndex(0);
    ui->txi_gameAccount_rb->clear();

    ui->tableWidget_rb->clearContents();
    //表头信息
    QString countStr = "缴费:【0】笔";
    QString totalPayStr = "缴费金额:【0】元";
    QString totalRepayStr = "返款:【0】元";
    ui->txt_rpt_total_rb->setText(countStr);
    ui->txt_rpt_money_rb->setText(totalPayStr);
    ui->txt_rpt_repay_rb->setText(totalRepayStr);
}

void yxcz_TabWidget::initRB()
{
    resetRB();
    refreshRB();
}

void yxcz_TabWidget::refreshRB()
{
    _getYxczRbListThread->currentCondition = "";
    if (ui->cbx_gameType_rb->currentText() != "不区分") {
        _getYxczRbListThread->currentCondition += "and [游戏类型名称] like '%"+ui->cbx_gameType_rb->currentText()+"%' ";
    }
    if (ui->cbx_state_rb->currentText() != "不区分") {
        _getYxczRbListThread->currentCondition += "and [状态] like '%"+ui->cbx_state_rb->currentText()+"%' ";
    }
    if (ui->txi_gameAccount_rb->text() != "") {
        _getYxczRbListThread->currentCondition += "and [游戏账号] like '%"+ui->txi_gameAccount_rb->text()+"%' ";
    }

    if (!_getYxczRbListThread->isRunning())
        _getYxczRbListThread->start();
}

void yxcz_TabWidget::resetYB()
{
    ui->cbx_gameType_yb->setCurrentIndex(0);
    ui->cbx_state_yb->setCurrentIndex(0);
    ui->txi_gameAccount_yb->clear();

    ui->tableWidget_yb->clearContents();
    //表头信息
    QString countStr = "缴费:【0】笔";
    QString totalPayStr = "缴费金额:【0】元";
    QString totalRepayStr = "返款:【0】元";
    ui->txt_rpt_total_yb->setText(countStr);
    ui->txt_rpt_money_yb->setText(totalPayStr);
    ui->txt_rpt_repay_yb->setText(totalRepayStr);
    //时间
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());
}

void yxcz_TabWidget::initYB()
{
    resetYB();
    refreshYB();
}

void yxcz_TabWidget::refreshYB()
{
    _getYxczYbListThread->currentCondition = "";

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

    _getYxczYbListThread->currentCondition += " and [提交日期] between '"+datetime1+"' and '"+datetime2+ "'";

    if (ui->cbx_gameType_yb->currentText() != "不区分") {
        _getYxczYbListThread->currentCondition += "and [游戏类型名称] like '%"+ui->cbx_gameType_yb->currentText()+"%' ";
    }
    if (ui->cbx_state_yb->currentText() != "不区分") {
        _getYxczYbListThread->currentCondition += "and [状态] like '%"+ui->cbx_state_yb->currentText()+"%' ";
    }
    if (ui->txi_gameAccount_yb->text() != "") {
        _getYxczYbListThread->currentCondition += "and [游戏账号] like '%"+ui->txi_gameAccount_yb->text()+"%' ";
    }

    if (!_getYxczYbListThread->isRunning())
        _getYxczYbListThread->start();
}

void yxcz_TabWidget::submit()
{
    if (ui->txi_gameAccount->text() == "") {
        QMessageBox::warning(this,tr("警告"),tr("游戏账号不能为空!"),QMessageBox::Ok);
        ui->txi_gameAccount->setFocus();
        return;
    }

    if (ui->txi_money->text() == "") {
        QMessageBox::warning(this,tr("警告"),tr("充值金额不能为空!"),QMessageBox::Ok);
        ui->txi_money->setFocus();
        return;
    } else {
        if (ui->txi_money->text().toDouble() < 1) {
            QMessageBox::warning(this,tr("警告"),tr("游戏最低只能缴费1元!"),QMessageBox::Ok);
            ui->txi_money->setFocus();
            return;
        }
    }

    if (ui->cbx_gameType->currentText() == "") {
        QMessageBox::warning(this,tr("警告"),tr("游戏类型不能为空!"),QMessageBox::Ok);
        ui->cbx_gameType->setFocus();
        return;
    }

    QString str = "确定要为<" +ui->cbx_gameType->currentText()+ ">的账号:" + ui->txi_gameAccount->text() + "进行充值吗？";
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "缴费", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        //TODO 提交服务器处理
        PaymentFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__PayGame req;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        std::string gameAccount = NetSecurity::encrypt(ui->txi_gameAccount->text());
        strcpy(buffer1, gameAccount.data());
        req.gameAccount = buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        std::string money = NetSecurity::encrypt(ui->txi_money->text());
        strcpy(buffer2, money.data());
        req.money = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        std::string gameType = NetSecurity::encrypt(ui->cbx_gameType->currentText());
        strcpy(buffer3, gameType.data());
        req.gameType = buffer3;

        char buffer4[255];
        memset(buffer4,0,255*sizeof(char));
        strcpy(buffer4, Singleton::GetInstance()->session_id.toUtf8().data());
        req.sessionId = buffer4;

        char buffer5[255];
        memset(buffer5,0,255*sizeof(char));
        std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
        strcpy(buffer5, clientType.data());
        req.clientType = buffer5;

        char buffer6[255];
        memset(buffer6,0,255*sizeof(char));
        std::string content = NetSecurity::encrypt(ui->txi_content->toPlainText());
        strcpy(buffer6, content.data());
        req.content = buffer6;

        char buffer7[255];
        memset(buffer7,0,255*sizeof(char));
        std::string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        strcpy(buffer7, userId.data());
        req.userId = buffer7;

        char _buffer7[255];
        memset(_buffer7,0,255*sizeof(char));
        std::string userName = NetSecurity::encrypt(Singleton::GetInstance()->getUser().loggingName);
        strcpy(_buffer7, userName.data());
        req.userName = _buffer7;

        _ns1__PayGameResponse res;
        this->setCursor(Qt::BusyCursor);
        ui->btn_submit->setEnabled(false);
        ui->txi_gameAccount->setEnabled(false);
        ui->txi_money->setEnabled(false);
        if (soap.__ns3__PayGame(&req,&res) == SOAP_OK) {
            QString result = QString::fromUtf8(res.PayGameResult);
            QMessageBox::warning(this,tr("提示"),result,QMessageBox::Ok);
            if (result.contains("成功")) {
                //更新缓存在客户端的money
                double newMoney = Singleton::GetInstance()->getUser().money;
                newMoney -= ui->txi_money->text().toDouble();
                UserVO user = Singleton::GetInstance()->getUser();
                user.money = newMoney;
                Singleton::GetInstance()->setUser(user);
                emit updateMoney();
                refreshJF();
                /*
                if (ui->rdo_print_on->isChecked() == true) {
                    rb = QMessageBox::warning(NULL, "打印", "是否要打印单据？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    if (rb == QMessageBox::Yes) {
                        currentPaymentCondition = "[缴费客户号码]='"+ui->txi_PhoneNo->text()+"' and 缴费金额='"+ui->txi_money->text()+"' order by [缴费时间] desc";
                        if (!_print_jf_Thread->isRunning())
                            _print_jf_Thread->start();
                    }
                }
                */
                resetJF();
            }
            ui->txi_gameAccount->setFocus();
        }
        else {
            QMessageBox::warning(this,tr("提示"),"服务器出错！",QMessageBox::Ok);
        }

        this->setCursor(Qt::ArrowCursor);
        ui->btn_submit->setEnabled(true);
        ui->txi_gameAccount->setEnabled(true);
        ui->txi_money->setEnabled(true);
    }
}

void yxcz_TabWidget::getSearchCondition()
{
    ui->cbx_gameType->clear();
    ui->cbx_gameType_rb->clear();
    ui->cbx_gameType_yb->clear();
    ui->cbx_gameType->addItem("","");
    ui->cbx_gameType_rb->addItem("不区分","不区分");
    ui->cbx_gameType_yb->addItem("不区分","不区分");
    ui->cbx_state_rb->clear();
    ui->cbx_state_yb->clear();
    ui->cbx_state_rb->addItem("不区分","不区分");
    ui->cbx_state_yb->addItem("不区分","不区分");

    if (!_getYxczCondtionThread->isRunning()) {
        _getYxczCondtionThread->start();
    }
}

GetYxczCurrThread::GetYxczCurrThread(yxcz_TabWidget *yxcz_TabWidget_ptr)
{
    _ref = yxcz_TabWidget_ptr;
}

void GetYxczCurrThread::run()
{
    qDebug()<<"进入提取当前游戏充值列表的线程";
    int total = 0;
    float totalPay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPayGameByCondition req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [网点用户Id]='"+Singleton::GetInstance()->getUser().Id+"' order by [提交日期] desc";
    qDebug()<<queryStr;
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetPayGameByConditionResponse res;
    if (soap.__ns3__GetPayGameByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetPayGameByConditionResult->__sizePayGameItem;
        for (int i=0; i<total; ++i) {
            for (int j=0; j<7; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPayGameByConditionResult->PayGameItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPayGameByConditionResult->PayGameItem[i]->gameType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetPayGameByConditionResult->PayGameItem[i]->gameAccount);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPayGameByConditionResult->PayGameItem[i]->money,'f',2);
                        totalPay += res.GetPayGameByConditionResult->PayGameItem[i]->money;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPayGameByConditionResult->PayGameItem[i]->state);
                        break;
                    case 6:
                        if (-1 == res.GetPayGameByConditionResult->PayGameItem[i]->addDateTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPayGameByConditionResult->PayGameItem[i]->addDateTime)));
                        content = QString(cTime);
                        break;
                }
                if (i < 10) {
                    QTableWidgetItem *item = new QTableWidgetItem (content);
                    _ref->ui->tableWidget->setItem(i, j, item);
                }
            }
        }
        QString countStr = "最新缴费:【" + QString::number(total) +"】笔";
        QString totalPayString = "缴费金额:【" + QString::number(totalPay,'f',2) +"】元";
        _ref->ui->txt_rpt_count->setText(countStr);
        _ref->ui->txt_rpt_money->setText(totalPayString);
    }
    else {
        qDebug()<<"服务器出错！不能获取游戏充值列表";
    }
    qDebug()<<"提取当前游戏充值列表完成";
}

GetYxczCondtionThread::GetYxczCondtionThread(yxcz_TabWidget *yxcz_TabWidget_ptr)
{
    _ref = yxcz_TabWidget_ptr;
}

void GetYxczCondtionThread::run()
{
    qDebug()<<"进入提取游戏充值查询条件线程...";
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetDicContentByCondition req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='游戏类型' and [Enabled]=1 ";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            _ref->ui->cbx_gameType->addItem(name,name);
            _ref->ui->cbx_gameType_rb->addItem(name,name);
            _ref->ui->cbx_gameType_yb->addItem(name,name);
        }
        qDebug()<<"提取游戏类型下拉列表完成";
    } else {
        qDebug()<<"服务器出错，无法提取游戏类型下拉列表";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='查询状态' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_state_rb->addItem(name,value);
            _ref->ui->cbx_state_yb->addItem(name,value);
        }
        qDebug()<<"提取游戏充值状态下拉列表完成";
    } else {
        qDebug()<<"服务器出错，无法提取游戏充值状态下拉列表";
    }
    qDebug()<<"提取游戏充值查询条件完成";
}

GetYxczRbListThread::GetYxczRbListThread(yxcz_TabWidget *yxcz_TabWidget_ptr)
{
    this->_ref = yxcz_TabWidget_ptr;
    this->currentCondition = "";
}

void GetYxczRbListThread::run()
{
    qDebug()<<"进入提取游戏充值日报信息线程...";
    int total = 0;
    float totalPay = 0;
    float totalRepay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPayGameByCondition req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [网点用户Id]='"+Singleton::GetInstance()->getUser().Id+"'"+currentCondition+"order by [提交日期] desc";
    qDebug()<<queryStr;
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetPayGameByConditionResponse res;
    if (soap.__ns3__GetPayGameByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget_rb->clearContents();
        QString content = "";
        total = res.GetPayGameByConditionResult->__sizePayGameItem;
        _ref->ui->tableWidget_rb->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<8; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPayGameByConditionResult->PayGameItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPayGameByConditionResult->PayGameItem[i]->gameType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetPayGameByConditionResult->PayGameItem[i]->gameAccount);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPayGameByConditionResult->PayGameItem[i]->money,'f',2);
                        totalPay += res.GetPayGameByConditionResult->PayGameItem[i]->money;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPayGameByConditionResult->PayGameItem[i]->state);
                        break;
                    case 6:
                        content = QString::number(res.GetPayGameByConditionResult->PayGameItem[i]->returnMoney,'f',2);
                        totalRepay += res.GetPayGameByConditionResult->PayGameItem[i]->returnMoney;
                        break;
                    case 7:
                        if (-1 == res.GetPayGameByConditionResult->PayGameItem[i]->addDateTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPayGameByConditionResult->PayGameItem[i]->addDateTime)));
                        content = QString(cTime);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget_rb->setItem(i, j, item);
            }
        }
        QString countStr = "缴费:【"+QString::number(total)+"】笔";
        QString totalPayStr = "缴费金额:【"+QString::number(totalPay,'f',2)+"】元";
        QString totalRepayStr = "返款:【"+QString::number(totalRepay,'f',2)+"】元";
        _ref->ui->txt_rpt_total_rb->setText(countStr);
        _ref->ui->txt_rpt_money_rb->setText(totalPayStr);
        _ref->ui->txt_rpt_repay_rb->setText(totalRepayStr);
    } else {
        qDebug()<<"服务器出错，无法提取游戏充值日报信息";
    }
    qDebug()<<"提取游戏充值日报信息完成";
}

GetYxczYbListThread::GetYxczYbListThread(yxcz_TabWidget *yxcz_TabWidget_ptr)
{
    this->_ref = yxcz_TabWidget_ptr;
    this->currentCondition = "";
}

void GetYxczYbListThread::run()
{
    qDebug()<<"今天入提取游戏充值月报信息线程...";
    int total = 0;
    float totalPay = 0;
    float totalRepay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPayGameHistoryByCondition req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [网点用户Id]='"+Singleton::GetInstance()->getUser().Id+"'"+currentCondition+"order by [提交日期] desc";
    qDebug()<<queryStr;
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetPayGameHistoryByConditionResponse res;
    if (soap.__ns3__GetPayGameHistoryByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget_yb->clearContents();
        QString content = "";
        total = res.GetPayGameHistoryByConditionResult->__sizePayGameItem;
        _ref->ui->tableWidget_yb->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<8; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPayGameHistoryByConditionResult->PayGameItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPayGameHistoryByConditionResult->PayGameItem[i]->gameType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetPayGameHistoryByConditionResult->PayGameItem[i]->gameAccount);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPayGameHistoryByConditionResult->PayGameItem[i]->money,'f',2);
                        totalPay += res.GetPayGameHistoryByConditionResult->PayGameItem[i]->money;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPayGameHistoryByConditionResult->PayGameItem[i]->state);
                        break;
                    case 6:
                        content = QString::number(res.GetPayGameHistoryByConditionResult->PayGameItem[i]->returnMoney,'f',2);
                        totalRepay += res.GetPayGameHistoryByConditionResult->PayGameItem[i]->returnMoney;
                        break;
                    case 7:
                        if (-1 == res.GetPayGameHistoryByConditionResult->PayGameItem[i]->addDateTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPayGameHistoryByConditionResult->PayGameItem[i]->addDateTime)));
                        content = QString(cTime);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget_yb->setItem(i, j, item);
            }
        }
        QString countStr = "缴费:【"+QString::number(total)+"】笔";
        QString totalPayStr = "缴费金额:【"+QString::number(totalPay,'f',2)+"】元";
        QString totalRepayStr = "返款:【"+QString::number(totalRepay,'f',2)+"】元";

        if (totalRepay >-0.0000001 && totalRepay< 0.000001) {
            totalRepayStr = "返款:【0】元";;
        }

        _ref->ui->txt_rpt_total_yb->setText(countStr);
        _ref->ui->txt_rpt_money_yb->setText(totalPayStr);
        _ref->ui->txt_rpt_repay_yb->setText(totalRepayStr);
    } else {
        qDebug()<<"服务器出错，无法提取游戏充值月报信息";
    }
    qDebug()<<"提取游戏充值月报信息完成";
}


void yxcz_TabWidget::on_btn_submit_clicked()
{
    submit();
}

void yxcz_TabWidget::on_btn_reset_clicked()
{
    resetJF();
}

void yxcz_TabWidget::on_btn_refresh_clicked()
{
    refreshJF();
}

void yxcz_TabWidget::on_btn_search_rb_clicked()
{
    refreshRB();
}

void yxcz_TabWidget::on_btn_refresh_rb_clicked()
{
    refreshRB();
}

void yxcz_TabWidget::on_btn_search_yb_clicked()
{
    refreshYB();
}

void yxcz_TabWidget::on_btn_refresh_yb_clicked()
{
    refreshYB();
}

void yxcz_TabWidget::on_btn_print_yb_clicked()
{
    if (ui->tableWidget_yb->currentRow() >= 0) {
        int index = ui->tableWidget_yb->currentRow();
        if (ui->tableWidget_yb->item(index, 0) != NULL && ui->tableWidget_yb->item(index, 0)->text() != "") {
            Printer::GetInstance()->printGame(Singleton::GetInstance()->getUser().shopName,
                                              ui->tableWidget_yb->item(index, 2)->text(),
                                              ui->tableWidget_yb->item(index, 3)->text(),
                                              ui->tableWidget_yb->item(index, 4)->text(),
                                              ui->tableWidget_yb->item(index, 5)->text(),
                                              ui->tableWidget_yb->item(index, 7)->text());
            QModelIndex _QModelIndex;
            ui->tableWidget_yb->setCurrentIndex(_QModelIndex);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"当前没有选中打印项！",QMessageBox::Ok);
    }
}

void yxcz_TabWidget::on_btn_print_rb_clicked()
{
    if (ui->tableWidget_rb->currentRow() >= 0) {
        int index = ui->tableWidget_rb->currentRow();
        if (ui->tableWidget_rb->item(index, 0) != NULL && ui->tableWidget_rb->item(index, 0)->text() != "") {
            Printer::GetInstance()->printGame(Singleton::GetInstance()->getUser().shopName,
                                              ui->tableWidget_rb->item(index, 2)->text(),
                                              ui->tableWidget_rb->item(index, 3)->text(),
                                              ui->tableWidget_rb->item(index, 4)->text(),
                                              ui->tableWidget_rb->item(index, 5)->text(),
                                              ui->tableWidget_rb->item(index, 7)->text());
            QModelIndex _QModelIndex;
            ui->tableWidget_rb->setCurrentIndex(_QModelIndex);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"当前没有选中打印项！",QMessageBox::Ok);
    }
}

void yxcz_TabWidget::on_btn_print_clicked()
{
    if (ui->tableWidget->currentRow() >= 0) {
        int index = ui->tableWidget->currentRow();
        if (ui->tableWidget->item(index, 0) != NULL && ui->tableWidget->item(index, 0)->text() != "") {
            Printer::GetInstance()->printGame(Singleton::GetInstance()->getUser().shopName,
                                              ui->tableWidget->item(index, 2)->text(),
                                              ui->tableWidget->item(index, 3)->text(),
                                              ui->tableWidget->item(index, 4)->text(),
                                              ui->tableWidget->item(index, 5)->text(),
                                              ui->tableWidget->item(index, 6)->text());
            QModelIndex _QModelIndex;
            ui->tableWidget->setCurrentIndex(_QModelIndex);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"当前没有选中打印项！",QMessageBox::Ok);
    }
}
void yxcz_TabWidget::on_txi_gameAccount_textChanged(const QString &arg1)
{
    //新输入则发声
    if (arg1.size() > _game_account_size) {
        QString lastLetter = arg1.right(1);
        //QMessageBox::warning(this,tr("警告"),lastLetter,QMessageBox::Ok);
        if (lastLetter == "1") {
            QSound::play("sound/1.wav");
        } else if (lastLetter == "2") {
            QSound::play("sound/2.wav");
        } else if (lastLetter == "3") {
            QSound::play("sound/3.wav");
        } else if (lastLetter == "4") {
            QSound::play("sound/4.wav");
        } else if (lastLetter == "5") {
            QSound::play("sound/5.wav");
        } else if (lastLetter == "6") {
            QSound::play("sound/6.wav");
        } else if (lastLetter == "7") {
            QSound::play("sound/7.wav");
        } else if (lastLetter == "8") {
            QSound::play("sound/8.wav");
        } else if (lastLetter == "9") {
            QSound::play("sound/9.wav");
        } else if (lastLetter == "0") {
            QSound::play("sound/0.wav");
        }
    }

    _game_account_size = arg1.size();
}

void yxcz_TabWidget::on_txi_money_textChanged(const QString &arg1)
{
    //新输入则发声
    if (arg1.size() > _game_money_size) {
        QString lastLetter = arg1.right(1);
        //QMessageBox::warning(this,tr("警告"),lastLetter,QMessageBox::Ok);
        if (lastLetter == "1") {
            QSound::play("sound/1.wav");
        } else if (lastLetter == "2") {
            QSound::play("sound/2.wav");
        } else if (lastLetter == "3") {
            QSound::play("sound/3.wav");
        } else if (lastLetter == "4") {
            QSound::play("sound/4.wav");
        } else if (lastLetter == "5") {
            QSound::play("sound/5.wav");
        } else if (lastLetter == "6") {
            QSound::play("sound/6.wav");
        } else if (lastLetter == "7") {
            QSound::play("sound/7.wav");
        } else if (lastLetter == "8") {
            QSound::play("sound/8.wav");
        } else if (lastLetter == "9") {
            QSound::play("sound/9.wav");
        } else if (lastLetter == "0") {
            QSound::play("sound/0.wav");
        }
    }

    _game_money_size = arg1.size();
}

void yxcz_TabWidget::keyPressEvent(QKeyEvent *event)
{
    //QMessageBox::warning(this,tr("警告"),QString::number(event->key()),QMessageBox::Ok);
    switch (event->key()) {
        case 16777220:
            {
                if (ui->tab->isVisible()) {
                    //QMessageBox::warning(this,tr("警告"),"yx click enter",QMessageBox::Ok);
                    submit();
                }
                break;
            }
        case 16777221:
            {
                if (ui->tab->isVisible()) {
                    //QMessageBox::warning(this,tr("警告"),"yx click enter",QMessageBox::Ok);
                    submit();
                }
                break;
            }
    }
}
