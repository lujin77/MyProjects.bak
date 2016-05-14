#include "dbfjs_scrollarea.h"
#include "ui_dbfjs_scrollarea.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include "QMessageBox"
#include "config.h"
#include "EncryptUtil.h"

GetReturnInfoThread::GetReturnInfoThread(dbfjs_ScrollArea *dbfjs_ScrollArea_ptr)
{
    this->_ref = dbfjs_ScrollArea_ptr;
}

void GetReturnInfoThread::run()
{
    //qDebug()<<"进入线程";
    int total = 0;

    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetReturnInfo req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer1, userId.data());
    req.userId = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    std::string clientLevel = NetSecurity::encrypt(Singleton::GetInstance()->getUser().level);
    strcpy(buffer4, clientLevel.data());
    req.clientLevel = buffer4;

    _ns1__GetReturnInfoResponse res;
    //_ref->ui->btn_refresh->setEnabled(false);
    if (soap.__ns5__GetReturnInfo(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetReturnInfoResult->list->__sizeReturnInfoItem;
        _ref->ui->tableWidget->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<4; ++j) {
                switch (j) {
                case 0:
                    content = QString::fromUtf8(res.GetReturnInfoResult->list->ReturnInfoItem[i]->type);
                    break;
                case 1:
                    content = QString::number(res.GetReturnInfoResult->list->ReturnInfoItem[i]->totalMoney,'f',2);
                    break;
                case 2:
                    content = QString::number(res.GetReturnInfoResult->list->ReturnInfoItem[i]->returnMoney,'f',2);
                    break;
                case 3:
                    content = QString::number(res.GetReturnInfoResult->list->ReturnInfoItem[i]->count);
                    break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget->setItem(i, j, item);
            }
        }
        QTableWidgetItem *item = new QTableWidgetItem ("总计");
        _ref->ui->tableWidget->setItem(total, 0, item);
        item = new QTableWidgetItem (QString::number(res.GetReturnInfoResult->processTotalMoney,'f',2));
        _ref->ui->tableWidget->setItem(total, 1, item);
        item = new QTableWidgetItem (QString::number(res.GetReturnInfoResult->returnTotalMoney,'f',2));
        _ref->ui->tableWidget->setItem(total, 2, item);
        item = new QTableWidgetItem (QString::number(res.GetReturnInfoResult->total));
        _ref->ui->tableWidget->setItem(total, 3, item);

        _ref->ui->txt_last_time->setText(QString::fromUtf8(res.GetReturnInfoResult->lastChargeTime));
        _ref->ui->txt_current_money->setText(QString::number(res.GetReturnInfoResult->curMoney,'f',2));
        _ref->ui->txt_return_money->setText(QString::number(res.GetReturnInfoResult->returnTotalMoney,'f',2));
        _ref->ui->txt_new_money->setText(QString::number(res.GetReturnInfoResult->afterReturnTotalMoney,'f',2));
    } else {
        qDebug()<<"服务器出错！无法提取代办费消息";
    }
}

dbfjs_ScrollArea::dbfjs_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::dbfjs_ScrollArea)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "返款项目" << "办理总金额" << "返款总金额" << "办理数量";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    _getReturnInfoThread = new GetReturnInfoThread(this);
}

dbfjs_ScrollArea::~dbfjs_ScrollArea()
{
    if (_getReturnInfoThread != NULL) {
        _getReturnInfoThread->terminate();
        _getReturnInfoThread->exit();
        delete _getReturnInfoThread;
    }
    delete ui;
}

void dbfjs_ScrollArea::init()
{
    reset();
    refresh();
}

void dbfjs_ScrollArea::reset()
{
    ui->txt_last_time->setText("");
    ui->txt_current_money->setText("");
    ui->txt_return_money->setText("");
    ui->txt_new_money->setText("");
}

void dbfjs_ScrollArea::refresh()
{
    if (!_getReturnInfoThread->isRunning())
        _getReturnInfoThread->start();
}

void dbfjs_ScrollArea::submit()
{
    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__CharegeReturnedMoney req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer1, userId.data());
    req.userId = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
    strcpy(buffer3, clientType.data());
    req.clientType = buffer3;

    char buffer4[255];
    memset(buffer4,0,255*sizeof(char));
    std::string clientLevel = NetSecurity::encrypt(Singleton::GetInstance()->getUser().level);
    strcpy(buffer4, clientLevel.data());
    req.clientLevel = buffer4;

    _ns1__CharegeReturnedMoneyResponse res;
    ui->btnSubmit->setEnabled(false);
    this->setCursor(Qt::BusyCursor);
    if (soap.__ns5__CharegeReturnedMoney(&req,&res) == SOAP_OK) {
        if (res.CharegeReturnedMoneyResult > 0) {
            QString alertInfo = "代办费结算成功!\n结算前余额:"+QString::number(Singleton::GetInstance()->getUser().money,'f',2)+
                    "\n当前实时余额:"+QString::number(res.CharegeReturnedMoneyResult,'f',2);
            QMessageBox::warning(this,tr("提示"),alertInfo,QMessageBox::Ok);
            UserVO user = Singleton::GetInstance()->getUser();
            user.money = res.CharegeReturnedMoneyResult;
            Singleton::GetInstance()->setUser(user);
            emit updateMoney();
            ui->tableWidget->clearContents();
        } else if (res.CharegeReturnedMoneyResult == 0) {
            QMessageBox::warning(this,tr("提示"),"提交结算请求失败，请稍后重试!",QMessageBox::Ok);
        }
    } else {
        QMessageBox::warning(this,tr("提示"),"服务器出错!请联系管理员",QMessageBox::Ok);
    }
    ui->btnSubmit->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
    refresh();
}

void dbfjs_ScrollArea::changeEvent(QEvent *e)
{
    QScrollArea::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void dbfjs_ScrollArea::on_btnSubmit_clicked()
{
    if (ui->txt_return_money->text().toFloat() <= 0) {
        QMessageBox::warning(this,tr("警告"),tr("当前没有可以结算的代办费"),QMessageBox::Ok);
        return;
    }
    QString str = "确定要结算代办吗？\n";
    if (Singleton::GetInstance()->getUser().level == "高级用户") {
        str += "您是高级用户，将结算上一个月（包括之前）的所有未结算代办费";
    } else {
        str += "您是"+Singleton::GetInstance()->getUser().level+"，将结算所有未结算代办费";
    }
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "代办费结算", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        submit();
    }
}
