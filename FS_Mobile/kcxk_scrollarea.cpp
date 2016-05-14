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
    QString queryStr = "[Category]='��Ӫ��' and [Enabled]=1 ";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            if ((Config::GetInstance()->_client_type == "�ƶ��ͻ���")) {
                if (name == "�ƶ�") {
                    _ref->ui->cbx_sp->addItem(name,value);
                }
            } else {
                if (name != "�ƶ�") {
                    _ref->ui->cbx_sp->addItem(name,value);
                }
            }
        }
    } else {
        qDebug()<<"�����������޷���ȡ��Ӫ�������б�";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='С��״̬' and [Enabled]=1 ";
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
        qDebug()<<"�����������޷���ȡС��״̬�����б�";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='�Ŷ�' and [Enabled]=1 ";
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
        qDebug()<<"�����������޷���ȡ�ͻ��˽ɷ�״̬�����б�";
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
    QString queryStr = " [�����û�Id]='"+Singleton::GetInstance()->getUser().Id+"' "+currentCondition+" order by [����ʱ��] desc";
    qDebug()<<"��ѯ����:"+queryStr;
    std::string condition = NetSecurity::encrypt(queryStr);
    qDebug()<<"��ѯ����:"+QString::fromStdString(condition);
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
                        qDebug()<<"����ʱ��:"+QString::number(res.GetMiniCardRecordResult->MiniCardItem[i]->sellDate);
                        if (-1 == res.GetMiniCardRecordResult->MiniCardItem[i]->sellDate) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetMiniCardRecordResult->MiniCardItem[i]->sellDate)));
                        content = QString(cTime);
                        break;
                    case 7:
                        qDebug()<<"����ʱ��:"+QString::number(res.GetMiniCardRecordResult->MiniCardItem[i]->usedDate);
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
        QString countStr = "��:��"+QString::number(total)+"����";
        _ref->ui->txt_rpt_total->setText(countStr);
    } else {
        qDebug()<<"�����������޷���ȡ���С����Ϣ";
    }
}

kcxk_ScrollArea::kcxk_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::kcxk_ScrollArea)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ��һ��
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //����ֻ��ѡ��һ�У����ܶ���ѡ��
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //����ÿ�����ݲ��ɸ���
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "�û���" << "С����" << "�Ŷ�" << "��Ӫ��" << "ʹ��״̬" << "ҵ��Ա����" << "����ʱ��" << "ʹ��ʱ��" ;
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //��������ط�
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
    if (ui->cbx_sp->currentText() != "������") {
        _getKcxkListThread->currentCondition += "and [��Ӫ��] like '%"+ui->cbx_sp->currentText()+"%' ";
    } else {
        if ((Config::GetInstance()->_client_type == "�ƶ��ͻ���")) {
            _getKcxkListThread->currentCondition += "and [��Ӫ��] like '%�ƶ�%' ";
        } else {
             _getKcxkListThread->currentCondition += "and ([��Ӫ��] like '%��ͨ%' or [��Ӫ��] like '%����%')";
        }
    }
    if (ui->cbx_state->currentText() != "������") {
        _getKcxkListThread->currentCondition += "and [ʹ��״̬] like '%"+ui->cbx_state->currentText()+"%' ";
    }
    if (ui->cbx_noSection->currentText() != "������") {
        _getKcxkListThread->currentCondition += "and [�Ŷ�] like '%"+ui->cbx_noSection->currentText()+"%' ";
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
    //��ͷ��Ϣ
    QString countStr = "��:��0����";
    ui->txt_rpt_total->setText(countStr);
}

void kcxk_ScrollArea::getSearchCondition()
{
    ui->cbx_sp->clear();
    ui->cbx_state->clear();
    ui->cbx_noSection->clear();
    ui->cbx_sp->addItem("������","������");
    ui->cbx_state->addItem("������","������");
    ui->cbx_noSection->addItem("������","������");

    if (_getKcxkCondtionThread->isRunning()) {
        _getKcxkCondtionThread->terminate();
    }
     _getKcxkCondtionThread->start();
}

void kcxk_ScrollArea::on_btn_search_clicked()
{
    refresh();
}
