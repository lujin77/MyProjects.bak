#include "tczfcx_scrollarea.h"
#include "ui_tczfcx_scrollarea.h"
#include "gsoap/soapBusinessFunctionWebServiceSoapProxy.h"
#include "EncryptUtil.h"
#include "config.h"
#include "singleton.h"
#include "noticedialog.h"

GetCardServiceThread::GetCardServiceThread(tczfcx_ScrollArea *tczfcx_ScrollArea_ptr)
{
    _ref = tczfcx_ScrollArea_ptr;
}

void GetCardServiceThread::run()
{
    qDebug()<<"进入获取套餐字符信息的线程";
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetCardService req;

    req.top = 0;

    QString queryStr = "";
    if (Config::GetInstance()->_client_type == "移动客户端") {
        queryStr = "[运营商]='移动'";
    } else {
        queryStr = "[运营商]='联通' or [运营商]='电信'";
    }
    queryStr += " order by [套餐名称]";
    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    //qDebug()<<"phoneNo:"+QString::fromStdString(phoneNo);
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    //qDebug()<<"session:"+QString::fromStdString(phoneNo);
    req.sessionId = buffer2;

   _ns1__GetCardServiceResponse res;
    if (soap.__ns13__GetCardService(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        int total = res.GetCardServiceResult->__sizeCardService;
        _ref->ui->tableWidget->setRowCount(total);
        for (int i=0; i<total; ++i) {
            for (int j=0; j<9; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetCardServiceResult->CardService[i]->serviceName);
                        break;
                    case 1:
                        content = QString::fromUtf8(res.GetCardServiceResult->CardService[i]->serviceSpec);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget->setItem(i, j, item);
            }
        }

    } else {
        qDebug()<<"服务器出错！不能获取套餐类型";
    }
    qDebug()<<"获取套餐类型的线程，处理完成";
}

tczfcx_ScrollArea::tczfcx_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::tczfcx_ScrollArea)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "套餐名称" << "详细介绍";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    ui->tableWidget->setColumnWidth(0,300);

    //初始化线程
    _getCardServiceThread = new GetCardServiceThread(this);
}

tczfcx_ScrollArea::~tczfcx_ScrollArea()
{
    if (_getCardServiceThread != NULL) {
        _getCardServiceThread->terminate();
        _getCardServiceThread->exit();
        delete _getCardServiceThread;
    }
    delete ui;
}

void tczfcx_ScrollArea::init()
{
    reset();
    refresh();
}

void tczfcx_ScrollArea::refresh()
{
    if (!_getCardServiceThread->isRunning())
        _getCardServiceThread->start();
}

void tczfcx_ScrollArea::reset()
{
    ui->tableWidget->clearContents();
}

void tczfcx_ScrollArea::on_tableWidget_doubleClicked(const QModelIndex &index)
{
//    NoticeDialog dialog;
//    dialog.reset();
//    int i = index.row();
//    QString title = ui->tableWidget->item(i,0)->text();
//    QString content = ui->tableWidget->item(i,1)->text();
//    dialog.setWindowTitle("套餐资费介绍");
//    dialog.init(title, "", content);
//    dialog.exec();
}

void tczfcx_ScrollArea::on_tableWidget_clicked(const QModelIndex &index)
{
    NoticeDialog dialog;
    dialog.reset();
    int i = index.row();
    QString title = ui->tableWidget->item(i,0)->text();
    QString content = ui->tableWidget->item(i,1)->text();
    dialog.setWindowTitle("套餐资费介绍");
    dialog.init(title, "", content);
    dialog.exec();
}
