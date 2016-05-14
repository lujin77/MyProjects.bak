#include "ywslcx_scrollarea.h"
#include "ui_ywslcx_scrollarea.h"
#include "gsoap/soapBusinessFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "printer.h"
#include "EncryptUtil.h"
#include "config.h"
#include <QDebug>

GetYwblcxCondtionThread::GetYwblcxCondtionThread(ywslcx_ScrollArea *ywslcx_ScrollArea_ptr)
{
    this->_ref = ywslcx_ScrollArea_ptr;
}

void GetYwblcxCondtionThread::run()
{
    qDebug()<<"׼����ǰҵ�����״̬�����б�";
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

    _ns1__GetDicContentByCondition req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='ҵ�����״̬' and [Enabled]=1 ";
    string condition = NetSecurity::encrypt(queryStr);
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
        qDebug()<<"�����������޷���ȡҵ�����״̬�����б�";
    }
}

GetYwblcxListThread::GetYwblcxListThread(ywslcx_ScrollArea *ywslcx_ScrollArea_ptr)
{
    this->_ref = ywslcx_ScrollArea_ptr;
    this->currentCondition = "";
}

void GetYwblcxListThread::run()
{
    qDebug()<<"׼����ȡҵ�������Ϣ";
    int total = 0;

    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GettBusinessRecordHistoryByCondition req;

    req.top = 0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [�ύ�����û�Id]='"+Singleton::GetInstance()->getUser().Id+"' "+currentCondition+"order by [����ʱ��] desc";
    std::string condition = NetSecurity::encrypt(queryStr);
    qDebug()<<"queryStr="+QString::fromStdString(condition);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    qDebug()<<"session="+Singleton::GetInstance()->session_id;
    req.sessionId = buffer2;

    _ns1__GettBusinessRecordHistoryByConditionResponse res;
    if (soap.__ns13__GettBusinessRecordHistoryByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GettBusinessRecordHistoryByConditionResult->__sizeBusinessItem;
        _ref->ui->tableWidget->setRowCount(total);
        for (int i=0; i<res.GettBusinessRecordHistoryByConditionResult->__sizeBusinessItem; ++i) {
            for (int j=0; j<10; ++j) {
                switch (j) {
                    case 0:
                         content = QString::fromUtf8(res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->Id);
                         break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->businessName);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->no);
                        break;
                    case 4:
                        content = QString::fromUtf8(res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->businessSpec);
                        break;
                    case 5:
                        content = QString::fromUtf8(res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->state);
                        break;
                    case 6:
                        content = QString::number(res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->returnMoney,'f',2);
                        break;
                    case 7:
                        content = QString::fromUtf8(res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->content);
                        break;
                    case 8:
                        content = QString::fromUtf8(res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->replay);
                        break;
                    case 9:
                        if (-1 == res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->datetime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GettBusinessRecordHistoryByConditionResult->BusinessItem[i]->datetime)));
                        content = QString(cTime);
                        break;

                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget->setItem(i, j, item);
            }
        }
        QString countStr = "������:��"+QString::number(total)+"����";
        _ref->ui->txt_rpt_total->setText(countStr);
    } else {
        qDebug()<<"�����������޷���ȡҵ�������Ϣ";
    }
}
ywslcx_ScrollArea::ywslcx_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::ywslcx_ScrollArea)
{
    ui->setupUi(this);

    QString countStr = "������:��0����";
    ui->txt_rpt_total->setText(countStr);

    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ��һ��
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //����ֻ��ѡ��һ�У����ܶ���ѡ��
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //����ÿ�����ݲ��ɸ���
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "Id" << "�����û�" << "ҵ������" << "�������" << "ҵ������"
         << "����״̬" << "����" << "��ע" << "�ظ�"<< "����ʱ��";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //��������ط�
    ui->tableWidget->setColumnWidth(1,80);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,200);
    ui->tableWidget->setColumnWidth(5,70);
    ui->tableWidget->setColumnWidth(6,50);
    ui->tableWidget->setColumnWidth(7,150);
    ui->tableWidget->setColumnWidth(8,150);

    _getYwblcxCondtionThread = new GetYwblcxCondtionThread(this);
    _getYwblcxListThread = new GetYwblcxListThread(this);
}

ywslcx_ScrollArea::~ywslcx_ScrollArea()
{
    if (_getYwblcxCondtionThread != NULL) {
        _getYwblcxCondtionThread->terminate();
        _getYwblcxCondtionThread->exit();
        delete _getYwblcxCondtionThread;
    }
    if (_getYwblcxListThread != NULL) {
        _getYwblcxListThread->terminate();
        _getYwblcxListThread->exit();
        delete _getYwblcxListThread;
    }
    delete ui;
}

void ywslcx_ScrollArea::refresh()
{
    _getYwblcxListThread->currentCondition = "";
    if (ui->txiStartDate->date() > ui->txiEndDate->date()) {
        QMessageBox::about(this,tr("���ڷ�Χ����"),tr("��������ʼʱ�䲻�ܴ��ڿ����Ľ�ֹʱ��,����'ȷ��'���������������ڼ����"));
        return;
    }
    //�������ڸ�ʽ
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

    _getYwblcxListThread->currentCondition += " and [����ʱ��] between '"+datetime1+"' and '"+datetime2+ "'";


    if (ui->cbx_state->currentText() != "������") {
        _getYwblcxListThread->currentCondition += " and [����״̬] like '%"+ui->cbx_state->currentText()+"%' ";
    }
    if (ui->txi_no->text() != "") {
        _getYwblcxListThread->currentCondition += " and [�绰����] like '%"+ui->txi_no->text()+"%' ";
    }

    if (_getYwblcxListThread->isRunning()) {
       _getYwblcxListThread->terminate();
    }
     _getYwblcxListThread->start();
}

void ywslcx_ScrollArea::init()
{
    reset();
    getSearchCondition();
    refresh();
}

void ywslcx_ScrollArea::getSearchCondition()
{
    ui->cbx_state->clear();
    ui->cbx_state->addItem("������","������");

    if (_getYwblcxCondtionThread->isRunning()) {
        _getYwblcxCondtionThread->terminate();
    }
    _getYwblcxCondtionThread->start();
}

void ywslcx_ScrollArea::reset()
{
    ui->cbx_state->setCurrentIndex(0);
    ui->txi_no->setText("");
    ui->tableWidget->clearContents();
    //��ͷ��Ϣ
    QString countStr = "������:��0����";
    ui->txt_rpt_total->setText(countStr);
    //ʱ��
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());
}


void ywslcx_ScrollArea::on_btn_search_clicked()
{
    refresh();
}
