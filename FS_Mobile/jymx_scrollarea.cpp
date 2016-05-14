#include "jymx_scrollarea.h"
#include "ui_jymx_scrollarea.h"
#include "gsoap/soapPaymentFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "EncryptUtil.h"
#include <QFileDialog>
#include <exception>
#include <QAxObject>

GetJymxCondtionThread::GetJymxCondtionThread(jymx_ScrollArea *jymx_ScrollArea_ptr)
{
    this->_ref = jymx_ScrollArea_ptr;
}

void GetJymxCondtionThread::run()
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
    QString queryStr = "[Category]='ҵ������' and [Enabled]=1 ";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_type->addItem(name,value);
        }
    } else {
        qDebug()<<"�����������޷���ȡҵ�����������б�";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='������ϸ״̬' and [Enabled]=1 ";
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
        qDebug()<<"�����������޷���ȡ�ͻ��˽ɷ�״̬�����б�";
    }
}

GetJymxListThread::GetJymxListThread(jymx_ScrollArea *jymx_ScrollArea_ptr)
{
    _ref = jymx_ScrollArea_ptr;
    currentCondition = "";
}

void GetJymxListThread::run()
{
    float totalMoney = 0;
    float totalPay = 0;
    float totalReturn = 0;
    float money = 0;
    int total = 0;

    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetTransactionByCondition req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = " [�����û�Id]='"+Singleton::GetInstance()->getUser().Id+"' "+currentCondition+"order by [����ʱ��] desc";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetTransactionByConditionResponse res;
    if (soap.__ns3__GetTransactionByCondition(&req,&res) == SOAP_OK) {
        _ref->ui->tableWidget->clearContents();
        QString content = "";
        total = res.GetTransactionByConditionResult->__sizeTransaction;
        _ref->ui->tableWidget->setRowCount(total);
        //�����Ƿ��˻���ֵ
        bool is_zhcz = false;
        for (int i=0; i<res.GetTransactionByConditionResult->__sizeTransaction; ++i) {
            is_zhcz = false;
            for (int j=0; j<11; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetTransactionByConditionResult->Transaction[i]->Id);
                        break;
                    case 1:
                        content = Singleton::GetInstance()->getUser().loggingName;
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetTransactionByConditionResult->Transaction[i]->type);
                        if (content == "�˻���ֵ") {
                            is_zhcz = true;
                        } else {
                            is_zhcz = false;
                        }
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetTransactionByConditionResult->Transaction[i]->phoneNo);
                        break;
                    case 4:
                        content = QString::number(res.GetTransactionByConditionResult->Transaction[i]->accountBefore,'f',2);
                        break;
                    case 5:
                    {
                        content = QString::number(res.GetTransactionByConditionResult->Transaction[i]->processMoney,'f',2);
                        if (!is_zhcz) totalMoney += res.GetTransactionByConditionResult->Transaction[i]->processMoney;
                        break;
                    }
                    case 6:
                    {
                        if (QString::fromUtf8(res.GetTransactionByConditionResult->Transaction[i]->type) == "����ѽ���") {
                            //qDebug()<<QString::fromUtf8(res.GetTransactionByConditionResult->Transaction[i]->type);
                            content = "0";
                        } else {
                            content = QString::number(res.GetTransactionByConditionResult->Transaction[i]->processMoney,'f',2);
                            if (!is_zhcz) totalPay += res.GetTransactionByConditionResult->Transaction[i]->processMoney;
                            else content = "0";
                        }
                        break;
                    }
                    case 7:
                    {
                        content = QString::number(res.GetTransactionByConditionResult->Transaction[i]->returnMoney,'f',2);
                        float money = res.GetTransactionByConditionResult->Transaction[i]->returnMoney;
                        if (!is_zhcz) totalReturn += money;
                        break;
                    }
                    case 8:
                        content = QString::number(res.GetTransactionByConditionResult->Transaction[i]->accountAfter,'f',2);
                        break;
                    case 9:
                        content = QString::fromUtf8(res.GetTransactionByConditionResult->Transaction[i]->state);
                        break;
                    case 10:
                        if (-1 == res.GetTransactionByConditionResult->Transaction[i]->processTime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetTransactionByConditionResult->Transaction[i]->processTime)));
                        content = QString(cTime);
                        break;

                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                _ref->ui->tableWidget->setItem(i, j, item);
            }
        }
        QString totalMoneyStr = "�����ܽ��:��"+QString::number(totalMoney,'f',2)+"��Ԫ";
        QString totalPayStr = "�ۿ��ܽ��:��"+QString::number(totalPay,'f',2)+"��Ԫ";
        QString totalReturnStr = "�����ܽ��:��"+QString::number(totalReturn,'f',2)+"��Ԫ";
        _ref->ui->txt_rpt_money->setText(totalMoneyStr);
        _ref->ui->txt_rpt_charge->setText(totalPayStr);
        _ref->ui->txt_rpt_return->setText(totalReturnStr);
    } else {
        qDebug()<<"�����������޷���ȡ�ɷ��ձ���Ϣ";
    }
}

jymx_ScrollArea::jymx_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::jymx_ScrollArea)
{
    ui->setupUi(this);
    //��ͷ��Ϣ
    QString totalMoneyStr = "�����ܽ��:��0��Ԫ";
    QString totalPayStr = "�ۿ��ܽ��:��0��Ԫ";
    QString totalReturnStr = "�����ܽ��:��0��Ԫ";
    ui->txt_rpt_money->setText(totalMoneyStr);
    ui->txt_rpt_charge->setText(totalPayStr);
    ui->txt_rpt_return->setText(totalReturnStr);

    ui->tableWidget->setColumnCount(11);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ��һ��
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //����ֻ��ѡ��һ�У����ܶ���ѡ��
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //����ÿ�����ݲ��ɸ���
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "Id" << "�����û�" << "ҵ������" << "�������" << "����ǰ���"
         << "������" << "�ۿ���" << "������" << "��������" << "״̬" << "����ʱ��";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //��������ط�
    ui->tableWidget->setColumnWidth(1,80);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,80);
    ui->tableWidget->setColumnWidth(5,80);
    ui->tableWidget->setColumnWidth(6,80);
    ui->tableWidget->setColumnWidth(7,80);
    ui->tableWidget->setColumnWidth(8,80);
    ui->tableWidget->setColumnWidth(9,80);

    _getJymxCondtionThread = new GetJymxCondtionThread(this);
    _getJymxListThread = new GetJymxListThread(this);
}

jymx_ScrollArea::~jymx_ScrollArea()
{
    if (_getJymxCondtionThread != NULL) {
        _getJymxCondtionThread->terminate();
        _getJymxCondtionThread->exit();
        delete _getJymxCondtionThread;
    }
    if (_getJymxListThread != NULL) {
        _getJymxListThread->terminate();
        _getJymxListThread->exit();
        delete _getJymxListThread;
    }

    delete ui;
}

void jymx_ScrollArea::refresh()
{
    _getJymxListThread->currentCondition = "";
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

    _getJymxListThread->currentCondition = " and [����ʱ��] between '"+datetime1+"' and '"+datetime2+ "'";

    if (ui->cbx_type->currentText() != "������") {
        _getJymxListThread->currentCondition += "and [ҵ������] like '%"+ui->cbx_type->currentText()+"%' ";
    }
    if (ui->cbx_state->currentText() != "������") {
        _getJymxListThread->currentCondition += "and [״̬] like '%"+ui->cbx_state->currentText()+"%' ";
    }
    if (ui->txi_phone_no->text() != "") {
        _getJymxListThread->currentCondition += "and [�������] like '%"+ui->txi_phone_no->text()+"%' ";
    }

    //�����߳�
    if (!this->_getJymxListThread->isRunning()) {
        _getJymxListThread->start();
    } else {
        return;
    }
}

void jymx_ScrollArea::init()
{
    reset();
    getSearchCondition();
    refresh();
}

void jymx_ScrollArea::getSearchCondition()
{
    ui->cbx_type->clear();
    ui->cbx_state->clear();
    ui->cbx_type->addItem("������","������");
    ui->cbx_state->addItem("������","������");

    if (!this->_getJymxCondtionThread->isRunning()) {
        _getJymxCondtionThread->start();
    }
}

void jymx_ScrollArea::reset()
{
    ui->cbx_type->setCurrentIndex(0);
    ui->cbx_state->setCurrentIndex(0);
    ui->txi_phone_no->setText("");
    ui->tableWidget->clearContents();
    //��ͷ��Ϣ
    QString totalMoneyStr = "�����ܽ��:��0��Ԫ";
    QString totalPayStr = "�ۿ��ܽ��:��0��Ԫ";
    QString totalReturnStr = "�����ܽ��:��0��Ԫ";
    ui->txt_rpt_money->setText(totalMoneyStr);
    ui->txt_rpt_charge->setText(totalPayStr);
    ui->txt_rpt_return->setText(totalReturnStr);
    //ʱ��
    ui->txiStartDate->setDate(QDate::currentDate());
    ui->txiEndDate->setDate(QDate::currentDate());
}

void jymx_ScrollArea::on_btnSearch_clicked()
{
    refresh();
}

void jymx_ScrollArea::on_btnExport_clicked()
{
    QString dir = QDir::currentPath()+"/������ϸ��¼.xls";
    QString file = QFileDialog::getSaveFileName(this,"�����ļ�", dir, QString::fromUtf8("Excel(*.xls)"));
    qDebug()<<file;

    if (!file.isEmpty()) {

        //����excel
        try {
            QAxObject* excel = new QAxObject("Excel.Application");
            excel->setProperty("Visible", true);
            QAxObject* workbooks = excel->querySubObject("WorkBooks");
            QAxObject* workbook = workbooks->querySubObject("Add()");
            QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1 );
            qDebug()<<"�� excel:"+file;
            workbooks->dynamicCall("Open (const QString&)", file);
            for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
                QString index1 = "A"+QString::number(i+1)+":A"+QString::number(i+1);
                QAxObject *range1 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index1));
                range1->dynamicCall( "Clear()");
                QString data1 = ui->tableWidget->item(i,1)->text();
                range1->dynamicCall( "SetValue(const QVariant&)", QVariant(data1));

                QString index2 = "B"+QString::number(i+1)+":B"+QString::number(i+1);
                QAxObject *range2 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index2));
                range2->dynamicCall( "Clear()" );
                QString data2 = ui->tableWidget->item(i,2)->text();
                range2->dynamicCall( "SetValue(const QVariant&)", QVariant(data2));

                QString index3 = "C"+QString::number(i+1)+":C"+QString::number(i+1);
                QAxObject *range3 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index3));
                range3->dynamicCall( "Clear()" );
                QString data3 = ui->tableWidget->item(i,3)->text();
                range3->dynamicCall( "SetValue(const QVariant&)", QVariant(data3));

                QString index4 = "D"+QString::number(i+1)+":D"+QString::number(i+1);
                QAxObject *range4 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index4));
                range4->dynamicCall( "Clear()" );
                QString data4 = ui->tableWidget->item(i,4)->text();
                range4->dynamicCall( "SetValue(const QVariant&)", QVariant(data4));

                QString index5 = "E"+QString::number(i+1)+":E"+QString::number(i+1);
                QAxObject *range5 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index5));
                range5->dynamicCall( "Clear()" );
                QString data5 = ui->tableWidget->item(i,5)->text();
                range5->dynamicCall( "SetValue(const QVariant&)", QVariant(data5));

                QString index6 = "F"+QString::number(i+1)+":F"+QString::number(i+1);
                QAxObject *range6 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index6));
                range6->dynamicCall( "Clear()" );
                QString data6 = ui->tableWidget->item(i,6)->text();
                range6->dynamicCall( "SetValue(const QVariant&)", QVariant(data6));

                QString index7 = "G"+QString::number(i+1)+":G"+QString::number(i+1);
                QAxObject *range7 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index7));
                range7->dynamicCall( "Clear()" );
                QString data7 = ui->tableWidget->item(i,7)->text();
                range7->dynamicCall( "SetValue(const QVariant&)", QVariant(data7));

                QString index8 = "H"+QString::number(i+1)+":H"+QString::number(i+1);
                QAxObject *range8 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index8));
                range8->dynamicCall( "Clear()" );
                QString data8 = ui->tableWidget->item(i,8)->text();
                range8->dynamicCall( "SetValue(const QVariant&)", QVariant(data8));

                QString index9 = "I"+QString::number(i+1)+":I"+QString::number(i+1);
                QAxObject *range9 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index9));
                range9->dynamicCall( "Clear()" );
                QString data9 = ui->tableWidget->item(i,9)->text();
                range9->dynamicCall( "SetValue(const QVariant&)", QVariant(data9));

                QString index10 = "J"+QString::number(i+1)+":J"+QString::number(i+1);
                QAxObject *range10 = worksheet->querySubObject( "Range(const QVariant&)", QVariant(index10));
                range10->dynamicCall( "Clear()" );
                QString data10 = ui->tableWidget->item(i,10)->text();
                range10->dynamicCall( "SetValue(const QVariant&)", QVariant(data10));
            }
            excel->dynamicCall(" SetScreenUpdating(bool)",true);

            //��n
            workbook->querySubObject( "SaveAs(const QString&)",file );

            //workbook->dynamicCall("Close (Boolean)", false);
            excel->dynamicCall("Quit (void)");
            delete excel;
        } catch(QString ex) {
            QMessageBox::warning(this,tr("��ʾ"),"����excel����"+ex,QMessageBox::Ok);
        }
    }
}
