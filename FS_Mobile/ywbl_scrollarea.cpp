#include "ywbl_scrollarea.h"
#include "ui_ywbl_scrollarea.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "printer.h"
#include "EncryptUtil.h"
#include "config.h"
#include "QTableWidgetItem"
#include "businessdialog.h"

GetBusinessListThread::GetBusinessListThread(ywbl_ScrollArea *ywbl_ScrollArea_ptr)
{
    this->_ref = ywbl_ScrollArea_ptr;
}

void GetBusinessListThread::run()
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
    QString queryStr = "[Category]='ҵ���������'";
    if ((Config::GetInstance()->_client_type == "�ƶ��ͻ���")) {
        queryStr += " and [Code]='�ƶ�'";
    } else {
        queryStr += " and [Code]<>'�ƶ�'";
    }
    queryStr += " and [Enabled]=1 order by [�����ֶ�2]";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->setRowCount(res.GetDicContentByConditionResult->__sizeDIC_USCOREContent);
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            BusinessInfo business;
            business.name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            business.winType = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->val1);
            _ref->list.append(business);
            QString content = business.name;
            QTableWidgetItem *item = new QTableWidgetItem (content);
            item->setTextAlignment(Qt::AlignCenter);
            _ref->ui->tableWidget->setItem(i, 0, item);
        }
    } else {
        qDebug()<<"�����������޷���ȡҵ������б�";
    }
}

ywbl_ScrollArea::ywbl_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::ywbl_ScrollArea)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(12);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ��һ��
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //����ֻ��ѡ��һ�У����ܶ���ѡ��
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //����ÿ�����ݲ��ɸ���
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "��ѡ����Ҫ�����ҵ��";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    _getBusinessListThread = new GetBusinessListThread(this);
}

ywbl_ScrollArea::~ywbl_ScrollArea()
{
    if (_getBusinessListThread != NULL) {
        _getBusinessListThread->terminate();
        _getBusinessListThread->exit();
        delete _getBusinessListThread;
    }
    delete ui;
}

void ywbl_ScrollArea::refresh()
{
    if (_getBusinessListThread->isRunning()) {
        _getBusinessListThread->terminate();
    }
    _getBusinessListThread->start();
}

void ywbl_ScrollArea::init()
{
    reset();
    refresh();
}

void ywbl_ScrollArea::reset()
{
    ui->tableWidget->clear();
    list.clear();
}

void ywbl_ScrollArea::on_tableWidget_clicked(const QModelIndex &index)
{
    BusinessDialog dialog;
    QString winType = list.at(index.row()).winType;
    QString name = list.at(index.row()).name;
    dialog.init(winType, name);
    dialog.exec();
}
