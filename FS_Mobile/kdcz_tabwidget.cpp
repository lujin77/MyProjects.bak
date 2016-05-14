#include "kdcz_tabwidget.h"
#include "ui_kdcz_tabwidget.h"
#include "gsoap/soapPaymentFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "gsoap/soapHttpServiceSoapProxy.h"
#include "singleton.h"
#include "config.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <exception>
#include <QAxObject>
#include "printer.h"
#include "EncryptUtil.h"

kdcz_TabWidget::kdcz_TabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::kdcz_TabWidget)
{
    ui->setupUi(this);
    //表头信息
    QString countStr = "最新缴费:【0】笔";
    QString totalPayString = "缴费金额:【0】元";
    ui->txt_rpt_count->setText(countStr);
    ui->txt_rpt_money->setText(totalPayString);

    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "Id" << "网点用户" << "宽带类型" << "宽带账号" << "缴费金额" << "缴费状态" << "号码归属" << "缴费时间";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,200);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,100);
    ui->tableWidget->setColumnWidth(5,100);
    ui->tableWidget->setColumnWidth(6,100);
    QRegExp regx_int("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx_int, this);
    //ui->txi_internetAccount->setValidator(validator);
    ui->txi_money->setValidator(validator);

    //日报
    QString countStr1 = "缴费:【0】笔";
    QString totalPayStr1 = "缴费金额:【0】元";
    QString totalRepayStr1 = "返款:【0】元";
    ui->txt_rpt_total_rb->setText(countStr1);
    ui->txt_rpt_money_rb->setText(totalPayStr1);
    ui->txt_rpt_repay_rb->setText(totalRepayStr1);
    ui->tableWidget_rb->setColumnCount(9);
    ui->tableWidget_rb->setRowCount(20);
    ui->tableWidget_rb->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_rb->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget_rb->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_rb->setAlternatingRowColors(true);
    QStringList list1;
    list1 << "Id" << "网点用户" << "宽带类型" << "宽带账号" << "缴费金额" << "缴费状态" << "号码归属" << "返款金额" << "缴费时间";
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
    ui->tableWidget_rb->setColumnWidth(7,100);
    //ui->txi_internetAccount_rb->setValidator( validator );

    //月报
    QString countStr2 = "缴费:【0】笔";
    QString totalPayStr2 = "缴费金额:【0】元";
    QString totalRepayStr2 = "返款:【0】元";
    ui->txt_rpt_total_yb->setText(countStr2);
    ui->txt_rpt_money_yb->setText(totalPayStr2);
    ui->txt_rpt_repay_yb->setText(totalRepayStr2);
    ui->tableWidget_yb->setColumnCount(9);
    ui->tableWidget_yb->setRowCount(20);
    ui->tableWidget_yb->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_yb->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget_yb->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_yb->setAlternatingRowColors(true);
    QStringList list2;
    list2 << "Id" << "网点用户" << "宽带类型" << "宽带账号" << "缴费金额" << "缴费状态" << "号码归属" << "返款金额" << "缴费时间";
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
    ui->tableWidget_yb->setColumnWidth(7,100);
    //ui->txi_internetAccount_yb->setValidator( validator );

    _getKdInfoThread = new GetKdInfoThread(this);
    _getKdczCurrThread = new GetKdczCurrThread(this);
    _getKdczCondtionThread = new GetKdczCondtionThread(this);
    _getKdczRbListThread = new GetKdczRbListThread(this);
    _getKdczYbListThread = new GetKdczYbListThread(this);

    //表头信息
    ui->txt_rpt_count_tel->setText(countStr);
    ui->txt_rpt_money_tel->setText(totalPayString);

    ui->tableWidget_tel->setColumnCount(8);
    ui->tableWidget_tel->setRowCount(10);
    ui->tableWidget_tel->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_tel->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget_tel->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_tel->setAlternatingRowColors(true);
    list.clear();
    list << "Id" << "网点用户" << "电话类型" << "电话号码" << "缴费金额" << "缴费状态" << "号码归属" << "缴费时间";
    ui->tableWidget_tel->setHorizontalHeaderLabels(list);
    ui->tableWidget_tel->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget_tel->hideColumn(0);
    ui->tableWidget_tel->setColumnWidth(1,100);
    ui->tableWidget_tel->setColumnWidth(2,200);
    ui->tableWidget_tel->setColumnWidth(3,150);
    ui->tableWidget_tel->setColumnWidth(4,100);
    ui->tableWidget_tel->setColumnWidth(5,100);
    ui->tableWidget_tel->setColumnWidth(6,100);
    //ui->txi_internetAccount->setValidator(validator);
    ui->txi_money_tel->setValidator(validator);

    //日报
    ui->txt_rpt_total_rb_tel->setText(countStr1);
    ui->txt_rpt_money_rb_tel->setText(totalPayStr1);
    ui->txt_rpt_repay_rb_tel->setText(totalRepayStr1);
    ui->tableWidget_rb_tel->setColumnCount(9);
    ui->tableWidget_rb_tel->setRowCount(20);
    ui->tableWidget_rb_tel->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_rb_tel->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget_rb_tel->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_rb_tel->setAlternatingRowColors(true);
    list1.clear();
    list1 << "Id" << "网点用户" << "电话类型" << "电话号码" << "缴费金额" << "缴费状态" << "号码归属" << "返款金额" << "缴费时间";
    ui->tableWidget_rb_tel->setHorizontalHeaderLabels(list1);
    //ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget_rb_tel->hideColumn(0);
    ui->tableWidget_rb_tel->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget_rb_tel->setColumnWidth(1,100);
    ui->tableWidget_rb_tel->setColumnWidth(2,200);
    ui->tableWidget_rb_tel->setColumnWidth(3,150);
    ui->tableWidget_rb_tel->setColumnWidth(4,100);
    ui->tableWidget_rb_tel->setColumnWidth(5,100);
    ui->tableWidget_rb_tel->setColumnWidth(6,100);
    ui->tableWidget_rb_tel->setColumnWidth(7,100);
    //ui->txi_internetAccount_rb->setValidator( validator );

    //月报
    ui->txt_rpt_total_yb_tel->setText(countStr2);
    ui->txt_rpt_money_yb_tel->setText(totalPayStr2);
    ui->txt_rpt_repay_yb_tel->setText(totalRepayStr2);
    ui->tableWidget_yb_tel->setColumnCount(9);
    ui->tableWidget_yb_tel->setRowCount(20);
    ui->tableWidget_yb_tel->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget_yb_tel->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget_yb_tel->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_yb_tel->setAlternatingRowColors(true);
    list2.clear();
    list2 << "Id" << "网点用户" << "电话类型" << "电话号码" << "缴费金额" << "缴费状态" << "号码归属" << "返款金额" << "缴费时间";
    ui->tableWidget_yb_tel->setHorizontalHeaderLabels(list2);
    //ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget_yb_tel->hideColumn(0);
    ui->tableWidget_yb_tel->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget_yb_tel->setColumnWidth(1,100);
    ui->tableWidget_yb_tel->setColumnWidth(2,200);
    ui->tableWidget_yb_tel->setColumnWidth(3,150);
    ui->tableWidget_yb_tel->setColumnWidth(4,100);
    ui->tableWidget_yb_tel->setColumnWidth(5,100);
    ui->tableWidget_yb_tel->setColumnWidth(6,100);
    ui->tableWidget_yb_tel->setColumnWidth(7,100);

    _getGhczCurrThread = new GetGhczCurrThread(this);
    _getGhczCondtionThread = new GetGhczCondtionThread(this);
    _getGhczRbListThread = new GetGhczRbListThread(this);
    _getGhczYbListThread = new GetGhczYbListThread(this);

    _kd_account_size = 0;
    _kd_money_size = 0;
    _gh_account_size = 0;
    _gh_money_size = 0;

//    ui->tab_4->setEnabled(false);
//    ui->tab_5->setEnabled(false);
//    ui->tab_6->setEnabled(false);

    ui->groupBox->hide();
    ui->groupBox_tel->hide();
}

kdcz_TabWidget::~kdcz_TabWidget()
{
    if (_getKdInfoThread != NULL) {
        _getKdInfoThread->terminate();
        _getKdInfoThread->exit();
        delete _getKdInfoThread;
    }
    if (_getKdczCurrThread != NULL) {
        _getKdczCurrThread->terminate();
        _getKdczCurrThread->exit();
        delete _getKdczCurrThread;
    }
    if (_getKdczCondtionThread != NULL) {
        _getKdczCondtionThread->terminate();
        _getKdczCondtionThread->exit();
        delete _getKdczCondtionThread;
    }
    if (_getKdczRbListThread != NULL) {
        _getKdczRbListThread->terminate();
        _getKdczRbListThread->exit();
        delete _getKdczRbListThread;
    }
    if (_getKdczYbListThread != NULL) {
        _getKdczYbListThread->terminate();
        _getKdczYbListThread->exit();
        delete _getKdczYbListThread;
    }

    if (_getGhczCurrThread != NULL) {
        _getGhczCurrThread->terminate();
        _getGhczCurrThread->exit();
        delete _getGhczCurrThread;
    }
    if (_getGhczCondtionThread != NULL) {
        _getGhczCondtionThread->terminate();
        _getGhczCondtionThread->exit();
        delete _getGhczCondtionThread;
    }
    if (_getGhczRbListThread != NULL) {
        _getGhczRbListThread->terminate();
        _getGhczRbListThread->exit();
        delete _getGhczRbListThread;
    }
    if (_getGhczYbListThread != NULL) {
        _getGhczYbListThread->terminate();
        _getGhczYbListThread->exit();
        delete _getGhczYbListThread;
    }
    delete ui;
}

void kdcz_TabWidget::changeEvent(QEvent *e)
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

void kdcz_TabWidget::resetAll()
{
    resetJF();
    resetRB();
    resetYB();

    resetJF2();
    resetRB2();
    resetYB2();
}

void kdcz_TabWidget::initAll()
{
    initJF();
    initRB();
    initYB();
    getSearchCondition();

    initJF2();
    initRB2();
    initYB2();
    getSearchCondition2();
}

void kdcz_TabWidget::resetJF()
{
    ui->txi_internetAccount->clear();
    ui->txi_money->clear();
    ui->cbx_internetType->setCurrentIndex(0);
    ui->txi_content->clear();
    ui->txi_internetAccount->setFocus();

    ui->txt_name->clear();
    ui->txt_money->clear();
    ui->txt_access_num->clear();

    _kd_account_size = 0;
    _kd_money_size = 0;

}

void kdcz_TabWidget::initJF()
{
    if (!Singleton::GetInstance()->getUser().btnList.contains("宽带批量缴费")) {
        ui->btnPayWithList->setEnabled(false);
    } else {
        ui->btnPayWithList->setEnabled(true);
    }
    resetJF();
    refreshJF();
}

void kdcz_TabWidget::refreshJF()
{
    if (!_getKdczCurrThread->isRunning())
        _getKdczCurrThread->start();
}

void kdcz_TabWidget::resetRB()
{
    ui->cbx_internetType_rb->setCurrentIndex(0);
    ui->cbx_state_rb->setCurrentIndex(0);
    ui->txi_internetAccount_rb->clear();

    ui->tableWidget_rb->clearContents();
    //表头信息
    QString countStr = "缴费:【0】笔";
    QString totalPayStr = "缴费金额:【0】元";
    QString totalRepayStr = "返款:【0】元";
    ui->txt_rpt_total_rb->setText(countStr);
    ui->txt_rpt_money_rb->setText(totalPayStr);
    ui->txt_rpt_repay_rb->setText(totalRepayStr);
}

void kdcz_TabWidget::initRB()
{
    resetRB();
    refreshRB();
}

void kdcz_TabWidget::refreshRB()
{
    _getKdczRbListThread->currentCondition = "";
    if (ui->cbx_internetType_rb->currentText() != "不区分") {
        _getKdczRbListThread->currentCondition += "and [宽带类型] like '%"+ui->cbx_internetType_rb->currentText()+"%' ";
    }
    if (ui->cbx_state_rb->currentText() != "不区分") {
        _getKdczRbListThread->currentCondition += "and [状态] like '%"+ui->cbx_state_rb->currentText()+"%' ";
    }
    if (ui->txi_internetAccount_rb->text() != "") {
        _getKdczRbListThread->currentCondition += "and [宽带账号] like '%"+ui->txi_internetAccount_rb->text()+"%' ";
    }

    if (!_getKdczRbListThread->isRunning())
        _getKdczRbListThread->start();
}

void kdcz_TabWidget::resetYB()
{
    ui->cbx_internetType_yb->setCurrentIndex(0);
    ui->cbx_state_yb->setCurrentIndex(0);
    ui->txi_internetAccount_yb->clear();

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

void kdcz_TabWidget::initYB()
{
    resetYB();
    refreshYB();
}

void kdcz_TabWidget::refreshYB()
{
    _getKdczYbListThread->currentCondition = "";

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

    _getKdczYbListThread->currentCondition += " and [提交日期] between '"+datetime1+"' and '"+datetime2+ "'";

    if (ui->cbx_internetType_yb->currentText() != "不区分") {
        _getKdczYbListThread->currentCondition += "and [宽带类型] like '%"+ui->cbx_internetType_yb->currentText()+"%' ";
    }
    if (ui->cbx_state_yb->currentText() != "不区分") {
        _getKdczYbListThread->currentCondition += "and [状态] like '%"+ui->cbx_state_yb->currentText()+"%' ";
    }
    if (ui->txi_internetAccount_yb->text() != "") {
        _getKdczYbListThread->currentCondition += "and [宽带账号] like '%"+ui->txi_internetAccount_yb->text()+"%' ";
    }

    if (!_getKdczYbListThread->isRunning())
        _getKdczYbListThread->start();
}

void kdcz_TabWidget::submit()
{
    if (ui->txi_internetAccount->text() == "") {
        QMessageBox::warning(this,tr("警告"),tr("宽带账号不能为空!"),QMessageBox::Ok);
        ui->txi_internetAccount->setFocus();
        return;
    }

    if (ui->txi_money->text() == "") {
        QMessageBox::warning(this,tr("警告"),tr("缴费金额不能为空!"),QMessageBox::Ok);
        ui->txi_money->setFocus();
        return;
    } else {
        if (ui->txi_money->text().toDouble() < 10) {
            QMessageBox::warning(this,tr("警告"),tr("宽带最低只能缴费10元!"),QMessageBox::Ok);
            ui->txi_money->setFocus();
            return;
        }
    }

    if (ui->cbx_internetType->currentText() == "") {
        QMessageBox::warning(this,tr("警告"),tr("宽带类型不能为空!"),QMessageBox::Ok);
        ui->cbx_internetType->setFocus();
        return;
    }

    QString str = "确定要为<" +ui->cbx_internetType->currentText()+ ">的账号:" + ui->txi_internetAccount->text() + "进行充值吗？";
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "缴费", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        //TODO 提交服务器处理
        PaymentFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__PayInternet req;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        std::string internetAccount = NetSecurity::encrypt(ui->txi_internetAccount->text());
        strcpy(buffer1, internetAccount.data());
        req.internetAccount = buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        std::string money = NetSecurity::encrypt(ui->txi_money->text());
        strcpy(buffer2, money.data());
        req.money = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        std::string internetType = NetSecurity::encrypt(ui->cbx_internetType->currentText());
        strcpy(buffer3, internetType.data());
        req.internetType = buffer3;

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
        string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        strcpy(buffer7, userId.data());
        req.userId = buffer7;

        char _buffer7[255];
        memset(_buffer7,0,255*sizeof(char));
        string userName = NetSecurity::encrypt(Singleton::GetInstance()->getUser().loggingName);
        strcpy(_buffer7, userName.data());
        req.userName = _buffer7;

        _ns1__PayInternetResponse res;
        this->setCursor(Qt::BusyCursor);
        ui->btn_submit->setEnabled(false);
        ui->txi_internetAccount->setEnabled(false);
        ui->txi_money->setEnabled(false);
        if (soap.__ns3__PayInternet(&req,&res) == SOAP_OK) {
            QString result = QString::fromUtf8(res.PayInternetResult);
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
            ui->txi_internetAccount->setFocus();
        }
        else {
            QMessageBox::warning(this,tr("提示"),"服务器出错！",QMessageBox::Ok);
        }

        this->setCursor(Qt::ArrowCursor);
        ui->btn_submit->setEnabled(true);
        ui->txi_internetAccount->setEnabled(true);
        ui->txi_money->setEnabled(true);
    }
}

void kdcz_TabWidget::getSearchCondition()
{
    ui->cbx_internetType->clear();
    ui->cbx_internetType_rb->clear();
    ui->cbx_internetType_yb->clear();
    ui->cbx_internetType->addItem("","");
    ui->cbx_internetType_rb->addItem("不区分","不区分");
    ui->cbx_internetType_yb->addItem("不区分","不区分");
    ui->cbx_state_rb->clear();
    ui->cbx_state_yb->clear();
    ui->cbx_state_rb->addItem("不区分","不区分");
    ui->cbx_state_yb->addItem("不区分","不区分");

    if (!_getKdczCondtionThread->isRunning()) {
        _getKdczCondtionThread->start();
    }
}

GetKdczCurrThread::GetKdczCurrThread(kdcz_TabWidget *kdcz_TabWidget_ptr)
{
    _ref = kdcz_TabWidget_ptr;
}

void GetKdczCurrThread::run()
{
    qDebug()<<"进入提取当前宽带充值列表的线程";
    int total = 0;
    float totalPay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPayInternetByCondition req;

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

    _ns1__GetPayInternetByConditionResponse res;
    if (soap.__ns3__GetPayInternetByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetPayInternetByConditionResult->__sizePayInternetItem;
        for (int i=0; i<total; ++i) {
            for (int j=0; j<8; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->internentType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->internetAccount);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPayInternetByConditionResult->PayInternetItem[i]->money,'f',2);
                        totalPay += res.GetPayInternetByConditionResult->PayInternetItem[i]->money;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->state);
                        break;
                    case 6:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->location);
                        break;
                    case 7:
                        if (-1 == res.GetPayInternetByConditionResult->PayInternetItem[i]->addDateTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPayInternetByConditionResult->PayInternetItem[i]->addDateTime)));
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
        qDebug()<<"服务器出错！不能获取宽带充值列表";
    }
    qDebug()<<"提取当前宽带充值列表完成";
}

GetKdczCondtionThread::GetKdczCondtionThread(kdcz_TabWidget *kdcz_TabWidget_ptr)
{
    _ref = kdcz_TabWidget_ptr;
}

void GetKdczCondtionThread::run()
{
    qDebug()<<"进入提取宽带充值查询条件线程...";
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetDicContentByCondition req;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='宽带类型' and [Enabled]=1 ";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_internetType->addItem(name,value);
            _ref->ui->cbx_internetType->setCurrentIndex(1);
            _ref->ui->cbx_internetType_rb->addItem(name,value);
            _ref->ui->cbx_internetType_yb->addItem(name,value);
        }
        qDebug()<<"提取宽带类型下拉列表完成";
    } else {
        qDebug()<<"服务器出错，无法提取宽带类型下拉列表";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='查询状态' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer0[255];
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
        qDebug()<<"提取宽带充值状态下拉列表完成";
    } else {
        qDebug()<<"服务器出错，无法提取宽带充值状态下拉列表";
    }
    qDebug()<<"提取宽带充值查询条件完成";
}

GetKdczRbListThread::GetKdczRbListThread(kdcz_TabWidget *kdcz_TabWidget_ptr)
{
    this->_ref = kdcz_TabWidget_ptr;
    this->currentCondition = "";
}

void GetKdczRbListThread::run()
{
    qDebug()<<"进入提取宽带充值日报信息线程...";
    int total = 0;
    float totalPay = 0;
    float totalRepay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPayInternetByCondition req;

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

    _ns1__GetPayInternetByConditionResponse res;
    if (soap.__ns3__GetPayInternetByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget_rb->clearContents();
        QString content = "";
        total = res.GetPayInternetByConditionResult->__sizePayInternetItem;
        _ref->ui->tableWidget_rb->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<9; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->internentType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->internetAccount);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPayInternetByConditionResult->PayInternetItem[i]->money,'f',2);
                        totalPay += res.GetPayInternetByConditionResult->PayInternetItem[i]->money;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->state);
                        break;
                    case 6:
                        content = QString::fromUtf8(res.GetPayInternetByConditionResult->PayInternetItem[i]->location);
                        break;
                    case 7:
                    {
                        content = QString::number(res.GetPayInternetByConditionResult->PayInternetItem[i]->returnMoney,'f',2);
                        totalRepay += res.GetPayInternetByConditionResult->PayInternetItem[i]->returnMoney;
                        //qDebug()<<"return:"+content+",total money:"+QString::number(totalRepay);
                        break;
                    }
                    case 8:
                        if (-1 == res.GetPayInternetByConditionResult->PayInternetItem[i]->addDateTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPayInternetByConditionResult->PayInternetItem[i]->addDateTime)));
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

        if (totalRepay >-0.0000001 && totalRepay< 0.000001) {
            totalRepayStr = "返款:【0】元";;
        }

        _ref->ui->txt_rpt_total_rb->setText(countStr);
        _ref->ui->txt_rpt_money_rb->setText(totalPayStr);
        _ref->ui->txt_rpt_repay_rb->setText(totalRepayStr);
    } else {
        qDebug()<<"服务器出错，无法提取宽带充值日报信息";
    }
    qDebug()<<"提取宽带充值日报信息完成";
}

GetKdczYbListThread::GetKdczYbListThread(kdcz_TabWidget *kdcz_TabWidget_ptr)
{
    this->_ref = kdcz_TabWidget_ptr;
    this->currentCondition = "";
}

void GetKdczYbListThread::run()
{
    qDebug()<<"进入提取宽带充值月报信息线程...";
    int total = 0;
    float totalPay = 0;
    float totalRepay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPayInternetHistoryByCondition req;

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

    _ns1__GetPayInternetHistoryByConditionResponse res;
    if (soap.__ns3__GetPayInternetHistoryByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget_yb->clearContents();
        QString content = "";
        total = res.GetPayInternetHistoryByConditionResult->__sizePayInternetItem;
        _ref->ui->tableWidget_yb->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<9; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->internentType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->internetAccount);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->money,'f',2);
                        totalPay += res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->money;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->state);
                        break;
                    case 6:
                        content = QString::fromUtf8(res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->location);
                        break;
                    case 7:
                    {
                        content = QString::number(res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->returnMoney,'f',2);
                        totalRepay += res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->returnMoney;
                        break;
                    }
                    case 8:
                        if (-1 == res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->addDateTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPayInternetHistoryByConditionResult->PayInternetItem[i]->addDateTime)));
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
        qDebug()<<"服务器出错，无法提取宽带充值月报信息";
    }
    qDebug()<<"提取宽带充值月报信息完成";
}

void kdcz_TabWidget::on_btn_submit_clicked()
{
    submit();
}

void kdcz_TabWidget::on_btn_reset_clicked()
{
    resetJF();
}

void kdcz_TabWidget::on_btn_refresh_clicked()
{
    refreshJF();
}

void kdcz_TabWidget::on_btn_search_rb_clicked()
{
    refreshRB();
}

void kdcz_TabWidget::on_btn_refresh_rb_clicked()
{
    refreshRB();
}

void kdcz_TabWidget::on_btn_search_yb_clicked()
{
    refreshYB();
}

void kdcz_TabWidget::on_btn_refresh_yb_clicked()
{
    refreshYB();
}

void kdcz_TabWidget::on_btn_print_yb_clicked()
{
    if (ui->tableWidget_yb->currentRow() >= 0) {
        int index = ui->tableWidget_yb->currentRow();
        if (ui->tableWidget_yb->item(index, 0) != NULL && ui->tableWidget_yb->item(index, 0)->text() != "") {
            Printer::GetInstance()->printInternet(Singleton::GetInstance()->getUser().shopName,
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

void kdcz_TabWidget::on_btn_print_rb_clicked()
{
    if (ui->tableWidget_rb->currentRow() >= 0) {
        int index = ui->tableWidget_rb->currentRow();
        if (ui->tableWidget_rb->item(index, 0) != NULL && ui->tableWidget_rb->item(index, 0)->text() != "") {
            Printer::GetInstance()->printInternet(Singleton::GetInstance()->getUser().shopName,
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

void kdcz_TabWidget::on_btn_print_clicked()
{
    if (ui->tableWidget->currentRow() >= 0) {
        int index = ui->tableWidget->currentRow();
        if (ui->tableWidget->item(index, 0) != NULL && ui->tableWidget->item(index, 0)->text() != "") {
            Printer::GetInstance()->printInternet(Singleton::GetInstance()->getUser().shopName,
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

GetGhczCurrThread::GetGhczCurrThread(kdcz_TabWidget *kdcz_TabWidget_ptr)
{
    _ref = kdcz_TabWidget_ptr;
}

void GetGhczCurrThread::run()
{
    qDebug()<<"进入提取当前公话充值列表的线程";
    int total = 0;
    float totalPay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPayPublicTelByCondition req;

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

    _ns1__GetPayPublicTelByConditionResponse res;
    if (soap.__ns3__GetPayPublicTelByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget_tel->clearContents();
        QString content = "";
        total = res.GetPayPublicTelByConditionResult->__sizePayPublicTelItem;
        for (int i=0; i<total; ++i) {
            for (int j=0; j<8; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->telType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->telAccount);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->money,'f',2);
                        totalPay += res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->money;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->state);
                        break;
                    case 6:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->location);
                        break;
                    case 7:
                        if (-1 == res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->addDateTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->addDateTime)));
                        content = QString(cTime);
                        break;
                }
                if (i < 10) {
                    QTableWidgetItem *item = new QTableWidgetItem (content);
                    _ref->ui->tableWidget_tel->setItem(i, j, item);
                }
            }
        }
        QString countStr = "最新缴费:【" + QString::number(total) +"】笔";
        QString totalPayString = "缴费金额:【" + QString::number(totalPay,'f',2) +"】元";
        _ref->ui->txt_rpt_count_tel->setText(countStr);
        _ref->ui->txt_rpt_money_tel->setText(totalPayString);
    }
    else {
        qDebug()<<"服务器出错！不能获取宽带充值列表";
    }
    qDebug()<<"提取当前宽带充值列表完成";
}

GetGhczCondtionThread::GetGhczCondtionThread(kdcz_TabWidget *kdcz_TabWidget_ptr)
{
    _ref = kdcz_TabWidget_ptr;
}

void GetGhczCondtionThread::run()
{
    qDebug()<<"进入提取公话充值查询条件线程...";
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetDicContentByCondition req;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='公话类型' and [Enabled]=1 ";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_telType->addItem(name,value);
            _ref->ui->cbx_telType_rb->addItem(name,value);
            _ref->ui->cbx_telType_yb->addItem(name,value);
        }
        qDebug()<<"提取公话类型下拉列表完成";
    } else {
        qDebug()<<"服务器出错，无法提取公话类型下拉列表";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='查询状态' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_state_rb_tel->addItem(name,value);
            _ref->ui->cbx_state_yb_tel->addItem(name,value);
        }
        qDebug()<<"提取公话充值状态下拉列表完成";
    } else {
        qDebug()<<"服务器出错，无法提取公话充值状态下拉列表";
    }
    qDebug()<<"提取宽带充值查询条件完成";
}

GetGhczRbListThread::GetGhczRbListThread(kdcz_TabWidget *kdcz_TabWidget_ptr)
{
    this->_ref = kdcz_TabWidget_ptr;
    this->currentCondition = "";
}

void GetGhczRbListThread::run()
{
    qDebug()<<"进入提取公话充值日报信息线程...";
    int total = 0;
    float totalPay = 0;
    float totalRepay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPayPublicTelByCondition req;

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

    _ns1__GetPayPublicTelByConditionResponse res;
    if (soap.__ns3__GetPayPublicTelByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget_rb_tel->clearContents();
        QString content = "";
        total = res.GetPayPublicTelByConditionResult->__sizePayPublicTelItem;
        _ref->ui->tableWidget_rb_tel->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<9; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->telType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->telAccount);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->money,'f',2);
                        totalPay += res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->money;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->state);
                        break;
                    case 6:
                        content = QString::fromUtf8(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->location);
                        break;
                    case 7:
                    {
                        content = QString::number(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->returnMoney,'f',2);
                        totalRepay += res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->returnMoney;
                        break;
                    }
                    case 8:
                        if (-1 == res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->addDateTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPayPublicTelByConditionResult->PayPublicTelItem[i]->addDateTime)));
                        content = QString(cTime);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget_rb_tel->setItem(i, j, item);
            }
        }
        QString countStr = "缴费:【"+QString::number(total)+"】笔";
        QString totalPayStr = "缴费金额:【"+QString::number(totalPay,'f',2)+"】元";
        QString totalRepayStr = "返款:【"+QString::number(totalRepay,'f',2)+"】元";

        if (totalRepay >-0.0000001 && totalRepay< 0.000001) {
            totalRepayStr = "返款:【0】元";;
        }

        _ref->ui->txt_rpt_total_rb_tel->setText(countStr);
        _ref->ui->txt_rpt_money_rb_tel->setText(totalPayStr);
        _ref->ui->txt_rpt_repay_rb_tel->setText(totalRepayStr);
    } else {
        qDebug()<<"服务器出错，无法提取宽带充值日报信息";
    }
    qDebug()<<"提取宽带充值日报信息完成";
}

GetGhczYbListThread::GetGhczYbListThread(kdcz_TabWidget *kdcz_TabWidget_ptr)
{
    this->_ref = kdcz_TabWidget_ptr;
    this->currentCondition = "";
}

void GetGhczYbListThread::run()
{
    qDebug()<<"今天入提取公话充值月报信息线程...";
    int total = 0;
    float totalPay = 0;
    float totalRepay = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPayPublicTelHistoryByCondition req;

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

    _ns1__GetPayPublicTelHistoryByConditionResponse res;
    if (soap.__ns3__GetPayPublicTelHistoryByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget_yb_tel->clearContents();
        QString content = "";
        total = res.GetPayPublicTelHistoryByConditionResult->__sizePayPublicTelItem;
        _ref->ui->tableWidget_yb_tel->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<9; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->telType);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->telAccount);
                        break;
                    case 4:
                    {
                        content = QString::number(res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->money,'f',2);
                        totalPay += res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->money;
                        break;
                    }
                    case 5:
                        content = QString::fromUtf8(res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->state);
                        break;
                    case 6:
                        content = QString::fromUtf8(res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->location);
                        break;
                    case 7:
                    {
                        content = QString::number(res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->returnMoney,'f',2);
                        totalRepay += res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->returnMoney;
                        break;
                    }
                    case 8:
                        if (-1 == res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->addDateTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPayPublicTelHistoryByConditionResult->PayPublicTelItem[i]->addDateTime)));
                        content = QString(cTime);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget_yb_tel->setItem(i, j, item);
            }
        }
        QString countStr = "缴费:【"+QString::number(total)+"】笔";
        QString totalPayStr = "缴费金额:【"+QString::number(totalPay,'f',2)+"】元";
        QString totalRepayStr = "返款:【"+QString::number(totalRepay,'f',2)+"】元";

        if (totalRepay >-0.0000001 && totalRepay< 0.000001) {
            totalRepayStr = "返款:【0】元";;
        }

        _ref->ui->txt_rpt_total_yb_tel->setText(countStr);
        _ref->ui->txt_rpt_money_yb_tel->setText(totalPayStr);
        _ref->ui->txt_rpt_repay_yb_tel->setText(totalRepayStr);
    } else {
        qDebug()<<"服务器出错，无法提取公话充值月报信息";
    }
    qDebug()<<"提取公话充值月报信息完成";
}

void kdcz_TabWidget::resetJF2()
{
    ui->txi_telAccount->clear();
    ui->txi_money_tel->clear();
    ui->cbx_telType->setCurrentIndex(0);
    ui->txi_content_tel->clear();
    ui->txi_telAccount->setFocus();

    _gh_account_size = 0;
    _gh_money_size = 0;
}

void kdcz_TabWidget::initJF2()
{
    resetJF2();
    refreshJF2();
}

void kdcz_TabWidget::refreshJF2()
{
    if (!_getGhczCurrThread->isRunning())
        _getGhczCurrThread->start();
}

void kdcz_TabWidget::resetRB2()
{
    ui->cbx_telType_rb->setCurrentIndex(0);
    ui->cbx_state_rb_tel->setCurrentIndex(0);
    ui->txi_telAccount_rb->clear();

    ui->tableWidget_rb_tel->clearContents();
    //表头信息
    QString countStr = "缴费:【0】笔";
    QString totalPayStr = "缴费金额:【0】元";
    QString totalRepayStr = "返款:【0】元";
    ui->txt_rpt_total_rb_tel->setText(countStr);
    ui->txt_rpt_money_rb_tel->setText(totalPayStr);
    ui->txt_rpt_repay_rb_tel->setText(totalRepayStr);
}

void kdcz_TabWidget::initRB2()
{
    resetRB2();
    refreshRB2();
}

void kdcz_TabWidget::refreshRB2()
{
    _getGhczRbListThread->currentCondition = "";
    if (ui->cbx_telType_rb->currentText() != "不区分") {
        _getGhczRbListThread->currentCondition += "and [公话类型] like '%"+ui->cbx_telType_rb->currentText()+"%' ";
    }
    if (ui->cbx_state_rb_tel->currentText() != "不区分") {
        _getGhczRbListThread->currentCondition += "and [状态] like '%"+ui->cbx_state_rb_tel->currentText()+"%' ";
    }
    if (ui->txi_telAccount_rb->text() != "") {
        _getGhczRbListThread->currentCondition += "and [公话号码] like '%"+ui->txi_telAccount_rb->text()+"%' ";
    }

    if (!_getGhczRbListThread->isRunning())
        _getGhczRbListThread->start();
}

void kdcz_TabWidget::resetYB2()
{
    ui->cbx_telType_yb->setCurrentIndex(0);
    ui->cbx_state_yb_tel->setCurrentIndex(0);
    ui->txi_telAccount_yb->clear();

    ui->tableWidget_yb_tel->clearContents();
    //表头信息
    QString countStr = "缴费:【0】笔";
    QString totalPayStr = "缴费金额:【0】元";
    QString totalRepayStr = "返款:【0】元";
    ui->txt_rpt_total_yb_tel->setText(countStr);
    ui->txt_rpt_money_yb_tel->setText(totalPayStr);
    ui->txt_rpt_repay_yb_tel->setText(totalRepayStr);
    //时间
    ui->txiStartDate_tel->setDate(QDate::currentDate());
    ui->txiEndDate_tel->setDate(QDate::currentDate());
}

void kdcz_TabWidget::initYB2()
{
    resetYB2();
    refreshYB2();
}

void kdcz_TabWidget::refreshYB2()
{
    _getGhczYbListThread->currentCondition = "";

    if (ui->txiStartDate_tel->date() > ui->txiEndDate_tel->date()) {
        QMessageBox::about(this,tr("日期范围错误"),tr("开单的起始时间不能大于开单的截止时间,请点击'确定'返回重新设置日期间隔！"));
        return;
    }
    //调整日期格式
    QString datetime1,datetime2;
    datetime1=QString::number(ui->txiStartDate_tel->date().year());
    if (ui->txiStartDate_tel->date().month()<10) {
        datetime1=datetime1+tr("-0")+QString::number(ui->txiStartDate_tel->date().month());
    } else {
        datetime1=datetime1+tr("-")+QString::number(ui->txiStartDate_tel->date().month());
    }
    if (ui->txiStartDate_tel->date().day()<10) {
        datetime1=datetime1+tr("-0")+QString::number(ui->txiStartDate_tel->date().day());
    } else {
        datetime1=datetime1+tr("-")+QString::number(ui->txiStartDate_tel->date().day());
    }
    datetime1 += " 00:00:00";

    datetime2=QString::number(ui->txiEndDate_tel->date().year());
    if (ui->txiEndDate_tel->date().month()<10) {
        datetime2=datetime2+tr("-0")+QString::number(ui->txiEndDate_tel->date().month());
    } else {
        datetime2=datetime2+tr("-")+QString::number(ui->txiEndDate_tel->date().month());
    }
    if (ui->txiEndDate_tel->date().day()<10) {
        datetime2=datetime2+tr("-0")+QString::number(ui->txiEndDate_tel->date().day());
    } else {
        datetime2=datetime2+tr("-")+QString::number(ui->txiEndDate_tel->date().day());
    }
    datetime2 += " 23:59:59";

    _getGhczYbListThread->currentCondition += " and [提交日期] between '"+datetime1+"' and '"+datetime2+ "'";

    if (ui->cbx_telType_yb->currentText() != "不区分") {
        _getGhczYbListThread->currentCondition += "and [宽带类型] like '%"+ui->cbx_telType_yb->currentText()+"%' ";
    }
    if (ui->cbx_state_yb_tel->currentText() != "不区分") {
        _getGhczYbListThread->currentCondition += "and [状态] like '%"+ui->cbx_state_yb_tel->currentText()+"%' ";
    }
    if (ui->txi_telAccount_yb->text() != "") {
        _getGhczYbListThread->currentCondition += "and [宽带账号] like '%"+ui->txi_telAccount_yb->text()+"%' ";
    }

    if (!_getGhczYbListThread->isRunning())
        _getGhczYbListThread->start();
}

void kdcz_TabWidget::submit2()
{
    if (ui->txi_telAccount->text() == "") {
        QMessageBox::warning(this,tr("警告"),tr("电话号码不能为空!"),QMessageBox::Ok);
        ui->txi_telAccount->setFocus();
        return;
    } else {
        //区分0871和地州
        if (ui->txi_telAccount->text().at(0) == '0'
                && ui->txi_telAccount->text().at(1) == '8'
                && ui->txi_telAccount->text().at(2) == '7'
                && ui->txi_telAccount->text().at(3) == '1') {
            if (ui->txi_telAccount->text().length() != 12) {
                QMessageBox::warning(this,tr("警告"),tr("昆明市电话号码应该为12位!"),QMessageBox::Ok);
                ui->txi_telAccount->setFocus();
                return;
            }
        } else {
            if (ui->txi_telAccount->text().length() != 11) {
                QMessageBox::warning(this,tr("警告"),tr("电话号码位数不对!"),QMessageBox::Ok);
                ui->txi_telAccount->setFocus();
                return;
            }
        }
    }

    if (ui->txi_money_tel->text() == "") {
        QMessageBox::warning(this,tr("警告"),tr("缴费金额不能为空!"),QMessageBox::Ok);
        ui->txi_money_tel->setFocus();
        return;
    } else {
        if (ui->txi_money_tel->text().toDouble() < 10) {
            QMessageBox::warning(this,tr("警告"),tr("电话最低只能缴费10元!"),QMessageBox::Ok);
            ui->txi_money_tel->setFocus();
            return;
        }
    }

    if (ui->cbx_telType->currentText() == "") {
        QMessageBox::warning(this,tr("警告"),tr("电话类型不能为空!"),QMessageBox::Ok);
        ui->cbx_telType->setFocus();
        return;
    }

    QString str = "确定要为<" +ui->cbx_telType->currentText()+ ">的号码:" + ui->txi_telAccount->text() + "进行缴费吗？";
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "缴费", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        //TODO 提交服务器处理
        PaymentFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__PayPublicTel req;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        std::string internetAccount = NetSecurity::encrypt(ui->txi_telAccount->text());
        strcpy(buffer1, internetAccount.data());
        req.telAccount = buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        std::string money = NetSecurity::encrypt(ui->txi_money_tel->text());
        strcpy(buffer2, money.data());
        req.money = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        std::string internetType = NetSecurity::encrypt(ui->cbx_telType->currentText());
        strcpy(buffer3, internetType.data());
        req.telType = buffer3;

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
        std::string content = NetSecurity::encrypt(ui->txi_content_tel->toPlainText());
        strcpy(buffer6, content.data());
        req.content = buffer6;

        char buffer7[255];
        memset(buffer7,0,255*sizeof(char));
        string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        strcpy(buffer7, userId.data());
        req.userId = buffer7;

        char _buffer7[255];
        memset(_buffer7,0,255*sizeof(char));
        string userName = NetSecurity::encrypt(Singleton::GetInstance()->getUser().loggingName);
        strcpy(_buffer7, userName.data());
        req.userName = _buffer7;

        _ns1__PayPublicTelResponse res;
        this->setCursor(Qt::BusyCursor);
        ui->btn_submit_tel->setEnabled(false);
        ui->txi_telAccount->setEnabled(false);
        ui->txi_money_tel->setEnabled(false);
        if (soap.__ns3__PayPublicTel(&req,&res) == SOAP_OK) {
            QString result = QString::fromUtf8(res.PayPublicTelResult);
            QMessageBox::warning(this,tr("提示"),result,QMessageBox::Ok);
            if (result.contains("成功")) {
                //更新缓存在客户端的money
                double newMoney = Singleton::GetInstance()->getUser().money;
                newMoney -= ui->txi_money_tel->text().toDouble();
                UserVO user = Singleton::GetInstance()->getUser();
                user.money = newMoney;
                Singleton::GetInstance()->setUser(user);
                emit updateMoney();
                refreshJF2();
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
                resetJF2();
            }
            ui->txi_telAccount->setFocus();
        }
        else {
            QMessageBox::warning(this,tr("提示"),"服务器出错！",QMessageBox::Ok);
        }

        this->setCursor(Qt::ArrowCursor);
        ui->btn_submit_tel->setEnabled(true);
        ui->txi_telAccount->setEnabled(true);
        ui->txi_money_tel->setEnabled(true);
    }
}

void kdcz_TabWidget::getSearchCondition2()
{
    ui->cbx_telType->clear();
    ui->cbx_telType_rb->clear();
    ui->cbx_telType_yb->clear();
    ui->cbx_telType->addItem("","");
    ui->cbx_telType_rb->addItem("不区分","不区分");
    ui->cbx_telType_yb->addItem("不区分","不区分");
    ui->cbx_state_rb_tel->clear();
    ui->cbx_state_yb_tel->clear();
    ui->cbx_state_rb_tel->addItem("不区分","不区分");
    ui->cbx_state_yb_tel->addItem("不区分","不区分");

    if (!_getGhczCondtionThread->isRunning()) {
        _getGhczCondtionThread->start();
    }
}

void kdcz_TabWidget::on_btn_submit_tel_clicked()
{
    submit2();
}

void kdcz_TabWidget::on_btn_reset_tel_clicked()
{
    resetJF2();
}

void kdcz_TabWidget::on_btn_refresh_tel_clicked()
{
    refreshJF();
}

void kdcz_TabWidget::on_btn_search_rb_tel_clicked()
{
    refreshRB2();
}

void kdcz_TabWidget::on_btn_refresh_rb_tel_clicked()
{
    refreshRB2();
}

void kdcz_TabWidget::on_btn_search_yb_2_clicked()
{
    refreshYB2();
}

void kdcz_TabWidget::on_btn_refresh_yb_tel_clicked()
{
    refreshYB2();
}

void kdcz_TabWidget::on_btn_print_yb_tel_clicked()
{
    if (ui->tableWidget_yb_tel->currentRow() >= 0) {
        int index = ui->tableWidget_yb_tel->currentRow();
        if (ui->tableWidget_yb_tel->item(index, 0) != NULL && ui->tableWidget_yb_tel->item(index, 0)->text() != "") {
            Printer::GetInstance()->printInternet(Singleton::GetInstance()->getUser().shopName,
                                              ui->tableWidget_yb_tel->item(index, 2)->text(),
                                              ui->tableWidget_yb_tel->item(index, 3)->text(),
                                              ui->tableWidget_yb_tel->item(index, 4)->text(),
                                              ui->tableWidget_yb_tel->item(index, 5)->text(),
                                              ui->tableWidget_yb_tel->item(index, 7)->text());
            QModelIndex _QModelIndex;
            ui->tableWidget_yb_tel->setCurrentIndex(_QModelIndex);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"当前没有选中打印项！",QMessageBox::Ok);
    }
}

void kdcz_TabWidget::on_btn_print_rb_tel_clicked()
{
    if (ui->tableWidget_rb_tel->currentRow() >= 0) {
        int index = ui->tableWidget_rb_tel->currentRow();
        if (ui->tableWidget_rb_tel->item(index, 0) != NULL && ui->tableWidget_rb_tel->item(index, 0)->text() != "") {
            Printer::GetInstance()->printInternet(Singleton::GetInstance()->getUser().shopName,
                                              ui->tableWidget_rb_tel->item(index, 2)->text(),
                                              ui->tableWidget_rb_tel->item(index, 3)->text(),
                                              ui->tableWidget_rb_tel->item(index, 4)->text(),
                                              ui->tableWidget_rb_tel->item(index, 5)->text(),
                                              ui->tableWidget_rb_tel->item(index, 7)->text());
            QModelIndex _QModelIndex;
            ui->tableWidget_rb_tel->setCurrentIndex(_QModelIndex);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"当前没有选中打印项！",QMessageBox::Ok);
    }
}

void kdcz_TabWidget::on_btn_print_tel_clicked()
{
    if (ui->tableWidget_tel->currentRow() >= 0) {
        int index = ui->tableWidget_tel->currentRow();
        if (ui->tableWidget_tel->item(index, 0) != NULL && ui->tableWidget_tel->item(index, 0)->text() != "") {
            Printer::GetInstance()->printInternet(Singleton::GetInstance()->getUser().shopName,
                                              ui->tableWidget_tel->item(index, 2)->text(),
                                              ui->tableWidget_tel->item(index, 3)->text(),
                                              ui->tableWidget_tel->item(index, 4)->text(),
                                              ui->tableWidget_tel->item(index, 5)->text(),
                                              ui->tableWidget_tel->item(index, 6)->text());
            QModelIndex _QModelIndex;
            ui->tableWidget_tel->setCurrentIndex(_QModelIndex);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"当前没有选中打印项！",QMessageBox::Ok);
    }
}

void kdcz_TabWidget::on_txi_internetAccount_textChanged(const QString &arg1)
{
    //新输入则发声
    if (arg1.size() > _kd_account_size) {
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

    _kd_account_size = arg1.size();
}

void kdcz_TabWidget::on_txi_money_textChanged(const QString &arg1)
{
    //新输入则发声
    if (arg1.size() > _kd_money_size) {
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

    _kd_money_size = arg1.size();
}

void kdcz_TabWidget::on_txi_telAccount_textChanged(const QString &arg1)
{
    //新输入则发声
    if (arg1.size() > _gh_account_size) {
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

    _gh_account_size = arg1.size();
}

void kdcz_TabWidget::on_txi_money_tel_textChanged(const QString &arg1)
{
    //新输入则发声
    if (arg1.size() > _gh_money_size) {
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

    _gh_money_size = arg1.size();
}

void kdcz_TabWidget::keyPressEvent(QKeyEvent *event)
{
    //QMessageBox::warning(this,tr("警告"),QString::number(event->key()),QMessageBox::Ok);
    switch (event->key()) {
        case 16777220:
            {
                if (ui->tab_1->isVisible()) {
                    //QMessageBox::warning(this,tr("警告"),"kd click enter",QMessageBox::Ok);
                    submit();
                }
                if (ui->tab_4->isVisible()) {
                    //QMessageBox::warning(this,tr("警告"),"gh click enter",QMessageBox::Ok);
                    submit2();
                }
                break;
            }
        case 16777221:
            {
                if (ui->tab_1->isVisible()) {
                    //QMessageBox::warning(this,tr("警告"),"kd click enter",QMessageBox::Ok);
                    submit();
                }
                if (ui->tab_4->isVisible()) {
                    //QMessageBox::warning(this,tr("警告"),"gh click enter",QMessageBox::Ok);
                    submit2();
                }
                break;
            }
    }
}

void kdcz_TabWidget::getKdInfo()
{
    if (ui->txi_internetAccount->text() == "")
        return;

    ui->txt_name->clear();
    ui->txt_money->clear();
    ui->txt_access_num->clear();
    if (!_getKdInfoThread->isRunning()) {
        _getKdInfoThread->start();
    }
}

void kdcz_TabWidget::on_btn_search_kd_clicked()
{
    getKdInfo();
}

void kdcz_TabWidget::on_txi_internetAccount_lostFocus()
{
    getKdInfo();
}

GetKdInfoThread::GetKdInfoThread(kdcz_TabWidget *kdcz_TabWidget_ptr)
{
    _ref = kdcz_TabWidget_ptr;
}

void GetKdInfoThread::run()
{
    qDebug()<<"进入获取宽带套餐的线程";
    HttpServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__queryPhoneNOInfo req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    //std::string phoneNO = NetSecurity::encrypt(_ref->ui->txi_PhoneNo->text());
    strcpy(buffer1, _ref->ui->txi_internetAccount->text().toUtf8().data());
    req.phoneNO = buffer1;

    _ns1__queryPhoneNOInfoResponse res;
    if (soap.__ns9__queryPhoneNOInfo(&req,&res) == SOAP_OK) {
        if (QString::fromUtf8(res.queryPhoneNOInfoResult->UserName) != "") {
            QString name = QString::fromUtf8(res.queryPhoneNOInfoResult->UserName);
            QString money = QString::fromUtf8(res.queryPhoneNOInfoResult->Balance);
            QString accessNum = QString::fromUtf8(res.queryPhoneNOInfoResult->AccessNum);
            if (name == "") {
                name = "未知";
                money = "0";
                accessNum = "";
            }
            _ref->ui->txt_name->setText(name);
            _ref->ui->txt_money->setText(money);
            _ref->ui->txt_access_num->setText(accessNum);
        }
    }
    else {
        qDebug()<<"服务器出错！不能获取宽带详细信息";
    }
    qDebug()<<"获取宽带详细信息的线程，处理完成";

}

void kdcz_TabWidget::on_btn_kd_fx_clicked()
{
    int index = ui->tableWidget_rb->currentIndex().row();
    if (index < 0) {
        QMessageBox::warning(this,tr("警告"),"错误！您没有选中任何项目",QMessageBox::Ok);
        return;
    }

    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "宽带缴费日报", "确定要返销该条记录?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb != QMessageBox::Yes) {
        return;
    }

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__RequstInternetRollback req;
    QString payment_id = ui->tableWidget_rb->item(index,0)->text();
    qDebug()<<"宽带返销ID"+payment_id;

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
    std::string type = NetSecurity::encrypt(QString("宽带返销"));
    strcpy(buffer4, type.data());
    req.type = buffer4;

    _ns1__RequstInternetRollbackResponse res;
    if (soap.__ns3__RequstInternetRollback(&req,&res) == SOAP_OK) {
        QString result = QString::fromUtf8(res.RequstInternetRollbackResult);
        if (result.contains("成功")) {
            refreshRB();
        }
        QMessageBox::warning(this,tr("提示"),result,QMessageBox::Ok);
    } else {
        QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
    }
}

void kdcz_TabWidget::on_btnPayWithList_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,"选择文件", QDir::currentPath(),QString::fromUtf8("Excel(*.xls *.xlsx)"));
    qDebug()<<file;
    //临时数据
    //QString data = "13087145772,10|12887869241,7|1357706194,5|";
    QString data = "";

    if (!file.isEmpty()) {
        //读取excel
        try {
            QAxObject* excel = new QAxObject("Excel.Application");
            excel->setProperty("Visible", false);
            QAxObject* workbooks = excel->querySubObject("WorkBooks");
            qDebug()<<"准备打开excel:"+file;
            workbooks->dynamicCall("Open (const QString&)", file);
            QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
            QAxObject* worksheets = workbook->querySubObject("WorkSheets");
            QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1);
            QAxObject* usedrange = worksheet->querySubObject("UsedRange");
            QAxObject* rows = usedrange->querySubObject("Rows");
            QAxObject* columns = usedrange->querySubObject("Columns");
            int intRowStart = usedrange->property("Row").toInt();
            int intColStart = usedrange->property("Column").toInt();
            int intCols = columns->property("Count").toInt();
            int intRows = rows->property("Count").toInt();
            QAxObject * cell;
            for (int i = intRowStart; i < intRowStart + intRows; i++)
             {
                    int col_num = 0;
                    for (int j = intColStart; j < intColStart + intCols; j++)
                    {
                        cell = worksheet->querySubObject("Cells(int,int)", i, j);
                        qDebug() << i << j << cell->property("Value");
                        data += cell->property("Value").toString();
                        if (col_num<2) {
                            data += ",";
                            ++col_num;
                        }
                    }
                    data += "|";
            }
            excel->setProperty("DisplayAlerts", 0);
            //workbook->dynamicCall("Save(void)");
            workbook->dynamicCall("Close (Boolean)", false);
            excel->dynamicCall("Quit (void)");
            delete excel;
        } catch(QString ex) {
            QMessageBox::warning(this,tr("提示"),"读取excel出错！"+ex,QMessageBox::Ok);
        }
        qDebug()<<"批量缴费:"<<data;
        //提交缴费
        PaymentFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__PayInternetWithList req;

        std::string _data = NetSecurity::encrypt(data);
        char buffer[_data.length()];
        memset(buffer,0,_data.length()*sizeof(char));
        strcpy(buffer, _data.data());
        req.data = buffer;
        qDebug()<<buffer;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        strcpy(buffer1,  userId.data());
        req.userId = buffer1;
        qDebug()<<buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
        req.sessionId = buffer2;
        qDebug()<<buffer2;

        _ns1__PayInternetWithListResponse res;
        this->setCursor(Qt::BusyCursor);
        ui->btnPayWithList->setEnabled(false);
        if (soap.__ns3__PayInternetWithList(&req,&res) == SOAP_OK) {
            QString result = QString::fromUtf8(res.PayInternetWithListResult->result);
            QMessageBox::warning(this,tr("提示"),result,QMessageBox::Ok);
            if (result.contains("成功")) {
                //更新缓存在客户端的money
                double newMoney = Singleton::GetInstance()->getUser().money;
                newMoney -= res.PayInternetWithListResult->totalMoney;
                UserVO user = Singleton::GetInstance()->getUser();
                user.money = newMoney;
                Singleton::GetInstance()->setUser(user);
                emit updateMoney();
                refreshJF();
                resetJF();
            }
            //如果有错误的记录，写入文件
            if (res.PayInternetWithListResult->failedCount > 0) {
                QFile file("fail.txt");
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream stream(&file);
                    //stream.setCodec(code);//输出流的设置--------必须嘀
                    for (int i=0; i<res.PayInternetWithListResult->list->__sizePayWithListItem; ++i) {
                        stream << res.PayInternetWithListResult->list->PayWithListItem[i]->phoneNo
                               << "\t" << QString::number(res.PayInternetWithListResult->list->PayWithListItem[i]->money,'f',2) << "\n";
                    }
                    file.close();
                }
            }
        }
        else {
            QMessageBox::warning(this,tr("提示"),"服务器出错！",QMessageBox::Ok);
        }
        this->setCursor(Qt::ArrowCursor);
        ui->btnPayWithList->setEnabled(true);
    }
}
