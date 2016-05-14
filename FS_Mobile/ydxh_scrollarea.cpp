#include "ydxh_scrollarea.h"
#include "ui_ydxh_scrollarea.h"
#include "config.h"
#include <QMessageBox>
#include "config.h"
#include "EncryptUtil.h"
#include "singleton.h"
#include "buynodialog.h"
#include "gsoap/soapBusinessFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"

GetNoListThread::GetNoListThread(ydxh_ScrollArea *ydxh_ScrollArea_ptr)
{
    currentCondition= "";
    _ref = ydxh_ScrollArea_ptr;
}

void GetNoListThread::run()
{
    qDebug()<<"�����ȡ�����б���߳�";
    //TODO �ύ��������ѯ������
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPhoneNoByCondition req;

    req.pageSize = 60;
    req.pageIndex = 1;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    QString queryStr = "[����] is not null and [ѡ�ŷ�] is not null and [ʹ��״̬]='δʹ��' ";
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        queryStr += "and [��Ӫ��]='�ƶ�' ";
    } else {
        queryStr += "and [��Ӫ��]<>'�ƶ�' ";
    }
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer3, condition.data());
    qDebug()<<"clientType:"+QString::fromStdString(condition);
    req.condition = buffer3;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    //qDebug()<<"session:"+QString::fromStdString(phoneNo);
    req.sessionId = buffer2;

    _ns1__GetPhoneNoByConditionResponse res;
    if (soap.__ns13__GetPhoneNoByCondition(&req,&res) == SOAP_OK) {
        int index = 0;
        int count = res.GetPhoneNoByConditionResult->listOfPhoneNo->__sizePhoneNoItem;
        if (count > 0) {
            _ref->ui->tableWidget->clearContents();
            int i_size = count / 3 + 1;
            for (int i=0; i<i_size; ++i) {
                for (int j=0; j<3; ++j) {
                    double money = res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->NoPrice;
                    QString no = res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->No;
                    QString value = res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->inNetPolicy;
                    QString area = res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->area;
                    QString NoSection = res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->NoSection;
                    _ref->phones[i][j].No = no;
                    _ref->phones[i][j].price = money;
                    _ref->phones[i][j].value = value;
                    _ref->phones[i][j].area = area;
                    _ref->phones[i][j].NoSection = NoSection;
                    QLabel *label = new QLabel();
                    label->setTextFormat(Qt::RichText);
                    QString tmp = "<table width=\"280\" height=\"45px\" border=\"0\" style=\"margin-left:5px; margin-right:5px\">";
                            tmp += "<tr>";
                            tmp += "  <td style=\"text-align:right\">k4</td>";
                            tmp += "  <td rowspan=\"2\" style=\"font-size:36px; color:#00F; text-align:center\">13987145"+no+"</td>";
                            tmp += "  <td style=\"text-align:left\">"+value+"</td>";
                            tmp += "</tr>";
                            tmp += "<tr>";
                            tmp += "  <td style=\"color:#F00; text-align:right\">"+QString::number(money)+"</td>";
                            tmp += "  <td style=\"font-size:12px; text-align:left\">"+area+"</td>";
                            tmp += "</tr>";
                            tmp += "</table>";
                    label->setText(tmp);
                    _ref->ui->tableWidget->setCellWidget(i,j,label);
                    qDebug()<<"���ú��룺"+no;
                    ++count;
                }
            }
        }
    } else {
        qDebug()<<"�������������ܻ�ȡ�����б�";
    }
    qDebug()<<"��ȡ�����б���̣߳��������";
}

GetYdxhCondtionThread::GetYdxhCondtionThread(ydxh_ScrollArea *ydxh_ScrollArea_ptr)
{
    _ref = ydxh_ScrollArea_ptr;
}

void GetYdxhCondtionThread::run()
{
    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

    //�����ҵĺŶ�
    QString myNoSection = " ";
    BusinessFunctionWebServiceSoap soap1;
    soap_set_mode(soap1.soap, SOAP_C_UTFSTRING);
    _ns1__GetMyNoSection req1;

    char buffer0_[255];
    memset(buffer0_,0,255*sizeof(char));
    strcpy(buffer0_, Singleton::GetInstance()->session_id.toUtf8().data());
    req1.sessionId = buffer0_;

    char buffer1_[255];
    memset(buffer1_,0,255*sizeof(char));
    std::string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer1_, userId.data());
    req1.userId = buffer1_;

    _ns1__GetMyNoSectionResponse res1;
    if (soap1.__ns13__GetMyNoSection(&req1,&res1) == SOAP_OK) {
        if (res1.GetMyNoSectionResult->__sizestring > 0) {
            myNoSection += " and (";
            for (int i=0; i<res1.GetMyNoSectionResult->__sizestring; ++i) {
                if (i == 0)
                    myNoSection += " [�Ŷ�] like '%"+QString::fromUtf8(res1.GetMyNoSectionResult->string[i])+"%'";
                else
                    myNoSection += " or [�Ŷ�] like '%"+QString::fromUtf8(res1.GetMyNoSectionResult->string[i])+"%'";
            }
            myNoSection += ")";
        } else {
            myNoSection = " and [�Ŷ�]=NULL";
        }
    } else {
        qDebug()<<"�����������޷���ȡ�Ŷ������б�";
    }
     qDebug()<<"�ҵĺŶ�:"+myNoSection;
    _ref->ui->cbx_hd->addItem("�ҵĺŶ�",myNoSection);

    _ns1__GetDicContentByCondition req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    QString queryStr = "[Category]='�Ŷ�' and [Enabled]=1 ";
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetDicContentByConditionResponse res;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = " and [�Ŷ�] like '%"+name+"%'";
            _ref->ui->cbx_hd->addItem(name,value);
        }
    } else {
        qDebug()<<"�����������޷���ȡ�Ŷ������б�";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='β���ص�' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_tail_format->addItem(name,value);
        }
    } else {
        qDebug()<<"�����������޷���ȡβ���ص������б�";
    }

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='��������' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        for (int i=0; i<res.GetDicContentByConditionResult->__sizeDIC_USCOREContent; ++i) {
            QString name = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Name);
            QString value = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[i]->Code);
            _ref->ui->cbx_rwzc->addItem(name,value);
        }
    } else {
        qDebug()<<"�����������޷���ȡ�������������б�";
    }
}


ydxh_ScrollArea::ydxh_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::ydxh_ScrollArea)
{
    ui->setupUi(this);

    ui->txt_count->setText("��0��");
    ui->txt_rpt_total->setText("��:��0��ҳ");

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //����ÿ�����ݲ��ɸ���
    ui->tableWidget->setAutoScroll(false);
    ui->tableWidget->verticalHeader()->hide();
    QStringList list;
    list << "����" << "����" << "����";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    ui->cbx_xhf->addItem("������",-1);
    ui->cbx_xhf->addItem("0",0);
    ui->cbx_xhf->addItem("1-50",50);
    ui->cbx_xhf->addItem("50-100",100);
    ui->cbx_xhf->addItem("100-200",200);
    ui->cbx_xhf->addItem("200����",300);


    //���ػ�
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        ui->txt_title->setText("      �ƶ�ѡ��");
    } else {
        ui->txt_title->setText("      �ֻ�ѡ��");
    }

    //��ʼ���߳�
    _getNoListThread = new GetNoListThread(this);
    _getYdxhCondtionThread = new GetYdxhCondtionThread(this);

    totalItem = 0;
    totalPage = 0;
    currentPage = 0;
    initPageSize = 60;
    searchCondition = "";

}

ydxh_ScrollArea::~ydxh_ScrollArea()
{
    if (_getNoListThread != NULL) {
        _getNoListThread->terminate();
        _getNoListThread->exit();
        delete _getNoListThread;
    }
    if (_getYdxhCondtionThread != NULL) {
        _getYdxhCondtionThread->terminate();
        _getYdxhCondtionThread->exit();
        delete _getYdxhCondtionThread;
    }
    delete ui;
}


void ydxh_ScrollArea::init()
{
    reset();
    getSearchCondition();
    refresh(initPageSize,1);
}

void ydxh_ScrollArea::getSearchCondition()
{
    ui->cbx_hd->clear();
    ui->cbx_tail_format->clear();
    ui->cbx_rwzc->clear();
    ui->cbx_hd->addItem("������","������");
    ui->cbx_tail_format->addItem("������","������");
    ui->cbx_rwzc->addItem("������","������");

    if (!_getYdxhCondtionThread->isRunning()) {
        _getYdxhCondtionThread->start();
    }
}

void ydxh_ScrollArea::reset()
{
    resetPhoneNo();
    ui->rdo_all->setChecked(true);
    ui->cbx_xhf->setCurrentIndex(0);
    ui->cbx_hd->setCurrentIndex(0);
    ui->cbx_tail_format->setCurrentIndex(0);
    ui->cbx_rwzc->setCurrentIndex(0);
    ui->tableWidget->clearContents();
    ui->txi_exclude->clear();
    ui->txi_exclude_tail->clear();
    ui->txi_include->clear();
    ui->txi_include_tail->clear();
    ui->txi_no1->clear();
    ui->txi_no2->clear();
    ui->txi_no3->clear();
    ui->txi_no4->clear();
    ui->txi_no5->clear();
    ui->txi_no6->clear();
    ui->txi_no7->clear();
    ui->txi_no8->clear();
    ui->txi_no9->clear();
    ui->txi_no10->clear();
    ui->txi_no11->clear();
    ui->txt_count->setText("��0��");
    ui->txt_rpt_total->setText("��:��0��ҳ");
    totalItem = 0;
    totalPage = 0;
    currentPage = 0;
    searchCondition = "";
}

void ydxh_ScrollArea::submit()
{
    searchCondition = "";

    if (ui->rdo_all->isChecked()) {
//        for (int i=0; i<20; ++i) {
//            for (int j=0; j<3; ++j) {
//                int money = rand()%100;
//                int no = rand()%899+100;
//                phones[i][j].No = "13987145"+QString::number(no);
//                QLabel *label = new QLabel();
//                label->setTextFormat(Qt::RichText);
//                QString tmp = "<table width=\"280\" height=\"45px\" border=\"0\" style=\"margin-left:5px; margin-right:5px\">";
//                        tmp += "<tr>";
//                        tmp += "  <td style=\"text-align:right\">k4</td>";
//                        tmp += "  <td rowspan=\"2\" style=\"font-size:36px; color:#00F; text-align:center\">13987145"+QString::number(no)+"</td>";
//                        tmp += "  <td style=\"text-align:left\">80+20</td>";
//                        tmp += "</tr>";
//                        tmp += "<tr>";
//                        tmp += "  <td style=\"color:#F00; text-align:right\">"+QString::number(money)+"</td>";
//                        tmp += "  <td style=\"font-size:12px; text-align:left\">��Ʒ������</td>";
//                        tmp += "</tr>";
//                        tmp += "</table>";
//                label->setText(tmp);
//                ui->tableWidget->setCellWidget(i,j,label);
//            }
//        }

    } if (ui->rdo_1->isChecked()){
        searchCondition += " and [����] like '%��Ʒ������%'";
    } else if (ui->rdo_2->isChecked()){
        searchCondition += " and [����] like '%������һ%'";
    } else if (ui->rdo_3->isChecked()){
        searchCondition += " and [����] like '%��������%'";
    } else if (ui->rdo_4->isChecked()){
        searchCondition += " and [����] like '%��������%'";
    } else if (ui->rdo_5->isChecked()){
        searchCondition += " and [����] like '%50��ֵ%'";
    } else if (ui->rdo_6->isChecked()){
        searchCondition += " and [����] like '%�ؼ���%'";
    }

    //�����������
    if (ui->txi_include->text() != "") {
        searchCondition += " and [����] like '%"+ui->txi_include->text()+"%'";
    }
    //�����ų�����
    if (ui->txi_exclude->text() != "") {
        searchCondition += " and [����] not like '%"+ui->txi_exclude->text()+"%'";
    }
    //�������β��
    if (ui->txi_include_tail->text() != "") {
        searchCondition += " and SUBSTRING(����,LEN(����),1)='"+ui->txi_include_tail->text()+"'";
    }
    //�����ų�β��
    if (ui->txi_exclude_tail->text() != "") {
        searchCondition += " and SUBSTRING(����,LEN(����),1)<>'"+ui->txi_exclude_tail->text()+"'";
    }

    //�����ѯ�ص�λ��
    if (ui->txi_no1->text() != "") {
        searchCondition += " and SUBSTRING(����,1,1)='"+ui->txi_no1->text()+"'";
    }
    if (ui->txi_no2->text() != "") {
        searchCondition += " and SUBSTRING(����,2,1)='"+ui->txi_no2->text()+"'";
    }
    if (ui->txi_no3->text() != "") {
        searchCondition += " and SUBSTRING(����,3,1)='"+ui->txi_no3->text()+"'";
    }
    if (ui->txi_no4->text() != "") {
        searchCondition += " and SUBSTRING(����,4,1)='"+ui->txi_no4->text()+"'";
    }
    if (ui->txi_no5->text() != "") {
        searchCondition += " and SUBSTRING(����,5,1)='"+ui->txi_no5->text()+"'";
    }
    if (ui->txi_no6->text() != "") {
        searchCondition += " and SUBSTRING(����,6,1)='"+ui->txi_no6->text()+"'";
    }
    if (ui->txi_no7->text() != "") {
        searchCondition += " and SUBSTRING(����,7,1)='"+ui->txi_no7->text()+"'";
    }
    if (ui->txi_no8->text() != "") {
        searchCondition += " and SUBSTRING(����,8,1)='"+ui->txi_no8->text()+"'";
    }
    if (ui->txi_no9->text() != "") {
        searchCondition += " and SUBSTRING(����,9,1)='"+ui->txi_no9->text()+"'";
    }
    if (ui->txi_no10->text() != "") {
        searchCondition += " and SUBSTRING(����,10,1)='"+ui->txi_no10->text()+"'";
    }
    if (ui->txi_no11->text() != "") {
        searchCondition += " and SUBSTRING(����,11,1)='"+ui->txi_no11->text()+"'";
    }

    //����ѡ�ŷ�
    if (ui->cbx_xhf->currentText() != "������") {
        if (ui->cbx_xhf->currentText() == "0") {
            searchCondition += " and ѡ�ŷ�=0";
        } else if (ui->cbx_xhf->currentText() == "1-50") {
            searchCondition += " and (ѡ�ŷ�>=1 and ѡ�ŷ�<=50)";
        } else if (ui->cbx_xhf->currentText() == "50-100") {
            searchCondition += " and (ѡ�ŷ�>=50 and ѡ�ŷ�<=100)";
        } else if (ui->cbx_xhf->currentText() == "100-200") {
            searchCondition += " and (ѡ�ŷ�>=100 and ѡ�ŷ�<=200)";
        } else if (ui->cbx_xhf->currentText() == "200����") {
            searchCondition += " and ѡ�ŷ�>=200";
        }
    }

    //����ӵ�кŶ�
    if (ui->cbx_hd->currentText() != "������") {
        searchCondition += ui->cbx_hd->itemData(ui->cbx_hd->currentIndex()).toString();
    }

    //������������
    if (ui->cbx_rwzc->currentText() != "������") {
        searchCondition += " and [��������] like '%"+ui->cbx_rwzc->currentText()+"%'";
    }

    //����β���ص�
    if (ui->cbx_tail_format->currentText() != "������") {
        if (ui->cbx_tail_format->currentText() == "66") {
            searchCondition += " and SUBSTRING(����,LEN(����)-1,2)='66'";
        } else if (ui->cbx_tail_format->currentText() == "88"){
            searchCondition += " and SUBSTRING(����,LEN(����)-1,2)='88'";
        } else if (ui->cbx_tail_format->currentText() == "99"){
            searchCondition += " and SUBSTRING(����,LEN(����)-1,2)='99'";
        } else if (ui->cbx_tail_format->currentText() == "99"){
            searchCondition += " and SUBSTRING(����,LEN(����)-1,2)='99'";
        } else if (ui->cbx_tail_format->currentText() == "AA") {
            searchCondition += " and (SUBSTRING(����,LEN(����),1)=SUBSTRING(����,LEN(����)-1,1))";
        } else if (ui->cbx_tail_format->currentText() == "AAA") {
            searchCondition += " and (SUBSTRING(����,LEN(����),1)=SUBSTRING(����,LEN(����)-1,1) and SUBSTRING(����,LEN(����)-1,1)=SUBSTRING(����,LEN(����)-2,1))";
        } else if (ui->cbx_tail_format->currentText() == "AAAB") {
            searchCondition += " and ((SUBSTRING(����,LEN(����)-1,1)=SUBSTRING(����,LEN(����)-2,1) and SUBSTRING(����,LEN(����)-2,1)=SUBSTRING(����,LEN(����)-3,1)) and (SUBSTRING(����,LEN(����)-1,1)<>SUBSTRING(����,LEN(����),1)))";
        } else if (ui->cbx_tail_format->currentText() == "AABB") {
            searchCondition += " and ((SUBSTRING(����,LEN(����),1)=SUBSTRING(����,LEN(����)-1,1) and SUBSTRING(����,LEN(����)-2,1)=SUBSTRING(����,LEN(����)-3,1)) and (SUBSTRING(����,LEN(����)-2,1)<>SUBSTRING(����,LEN(����)-1,1)))";
        } else if (ui->cbx_tail_format->currentText() == "ABC") {
            searchCondition += " and ((cast(SUBSTRING(����,LEN(����)-2,1) as int)+1)=cast(SUBSTRING(����,LEN(����)-1,1) as int) and ((cast(SUBSTRING(����,LEN(����)-1,1) as int)+1)=cast(SUBSTRING(����,LEN(����),1) as int)))";
        } else if (ui->cbx_tail_format->currentText() == "ABCD") {
            searchCondition += " and ((cast(SUBSTRING(����,LEN(����)-3,1) as int)+1)=cast(SUBSTRING(����,LEN(����)-2,1) as int) and ((cast(SUBSTRING(����,LEN(����)-2,1) as int)+1)=cast(SUBSTRING(����,LEN(����)-1,1) as int))and ((cast(SUBSTRING(����,LEN(����)-1,1) as int)+1)=cast(SUBSTRING(����,LEN(����),1) as int)))";
        } else if (ui->cbx_tail_format->currentText() == "CBA") {
            searchCondition += " and ((cast(SUBSTRING(����,LEN(����)-2,1) as int)-1)=cast(SUBSTRING(����,LEN(����)-1,1) as int))and ((cast(SUBSTRING(����,LEN(����)-1,1) as int)-1)=cast(SUBSTRING(����,LEN(����),1) as int))";
        } else if (ui->cbx_tail_format->currentText() == "DCBA") {
           searchCondition += " and ((cast(SUBSTRING(����,LEN(����)-3,1) as int)-1)=cast(SUBSTRING(����,LEN(����)-2,1) as int) and ((cast(SUBSTRING(����,LEN(����)-2,1) as int)-1)=cast(SUBSTRING(����,LEN(����)-1,1) as int))and ((cast(SUBSTRING(����,LEN(����)-1,1) as int)-1)=cast(SUBSTRING(����,LEN(����),1) as int)))";
       }
    }

    //searchCondition += " order by [Ȩֵ] desc";

    qDebug()<<"��ѯ����������"+searchCondition;
    refresh(initPageSize,1);
}

void ydxh_ScrollArea::resetPhoneNo()
{
    for (int i=0; i<20; ++i) {
        for (int j=0; j<3; ++j) {
            phones[i][j].No = "";
            phones[i][j].price = 0;
            phones[i][j].area = "";
            phones[i][j].value = "";
            phones[i][j].NoSection = "";
        }
    }
}

void ydxh_ScrollArea::refresh(int pageSize, int pageIndex)
{

    qDebug()<<"׼����ȡ�����б�";
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPhoneNoByCondition req;

    req.pageSize = pageSize;
    req.pageIndex = pageIndex;

    QString queryStr = "[����] is not null and [ѡ�ŷ�] is not null and [ʹ��״̬]='δʹ��' ";
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        queryStr += "and [��Ӫ��]='�ƶ�' ";
    } else {
        queryStr += "and [��Ӫ��]<>'�ƶ�' ";
    }
    queryStr += searchCondition;
    qDebug()<<"condition src:"+queryStr;
    std::string condition = NetSecurity::encrypt(queryStr);
    char buffer3[condition.length()];
    memset(buffer3,0,condition.length()*sizeof(char));
    strcpy(buffer3, condition.data());
    qDebug()<<"condition:"+QString::fromStdString(condition);
    req.condition = buffer3;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    qDebug()<<"session:"+Singleton::GetInstance()->session_id;
    req.sessionId = buffer2;

    _ns1__GetPhoneNoByConditionResponse res;
    this->setCursor(Qt::BusyCursor);
    ui->btn_search->setEnabled(false);
    if (soap.__ns13__GetPhoneNoByCondition(&req,&res) == SOAP_OK) {
        int index = 0;
        int count = res.GetPhoneNoByConditionResult->listOfPhoneNo->__sizePhoneNoItem;

            totalItem = res.GetPhoneNoByConditionResult->total;
            totalPage = res.GetPhoneNoByConditionResult->totalPage;
            currentPage = res.GetPhoneNoByConditionResult->currentPageIndex;
            ui->tableWidget->clearContents();
            resetPhoneNo();
            int i_size = count / 3 + 1;
            for (int i=0; i<i_size; ++i) {
                for (int j=0; j<3; ++j) {
                    if (index < count){
                        double money = res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->NoPrice;
                        QString no = QString::fromUtf8(res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->No);
                        QString value = QString::fromUtf8(res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->inNetPolicy);
                        QString area = QString::fromUtf8(res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->area);
                        QString NoSection = QString::fromUtf8(res.GetPhoneNoByConditionResult->listOfPhoneNo->PhoneNoItem[index]->NoSection);
                        phones[i][j].No = no;
                        phones[i][j].price = money;
                        phones[i][j].value = value;
                        phones[i][j].area = area;
                        phones[i][j].NoSection = NoSection;
                        QLabel *label = new QLabel();
                        label->setTextFormat(Qt::RichText);
                        QString tmp = "<table width=\"280\" height=\"45px\" border=\"0\" style=\"margin-left:5px; margin-right:5px\">";
                                tmp += "<tr>";
                                tmp += "  <td style=\"text-align:right\">"+NoSection+"</td>";
                                tmp += "  <td rowspan=\"2\" style=\"font-size:36px; color:#00F; text-align:center\">"+no+"</td>";
                                tmp += "  <td style=\"text-align:left\">"+value+"</td>";
                                tmp += "</tr>";
                                tmp += "<tr>";
                                tmp += "  <td style=\"color:#F00; text-align:right\">"+QString::number(money)+"</td>";
                                tmp += "  <td style=\"font-size:12px; text-align:left\">"+area+"</td>";
                                tmp += "</tr>";
                                tmp += "</table>";
                        label->setText(tmp);
                        ui->tableWidget->setCellWidget(i,j,label);
                        ++index;
                        //qDebug()<<"���ú��룺"+no;
                    }
                }
            }

    } else {
        qDebug()<<"�������������ܻ�ȡ�����б�";
    }
    this->setCursor(Qt::ArrowCursor);
    ui->btn_search->setEnabled(true);
    QString countPageStr = "��:��"+QString::number(totalPage)+"��ҳ";
    ui->txt_rpt_total->setText(countPageStr);
    QString countStr = "��"+QString::number(totalItem)+"��";
    ui->txt_count->setText(countStr);
    ui->spinBox->setValue(currentPage);
    ui->spinBox->setMaximum(totalPage);
    qDebug()<<"��ȡ�����б������";
}

void ydxh_ScrollArea::showNewMoney()
{
    emit updateMoney();
}

void ydxh_ScrollArea::on_txi_no1_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no2->setFocus();
    }
    if (arg1.length() == 0) {

    }
}

void ydxh_ScrollArea::on_txi_no2_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no3->setFocus();
    }
    if (arg1.length() == 0) {
        ui->txi_no1->setFocus();
    }
}

void ydxh_ScrollArea::on_txi_no3_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no4->setFocus();
    }
    if (arg1.length() == 0) {
        ui->txi_no2->setFocus();
    }
}

void ydxh_ScrollArea::on_txi_no4_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no5->setFocus();
    }
    if (arg1.length() == 0) {
        ui->txi_no3->setFocus();
    }
}

void ydxh_ScrollArea::on_txi_no5_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no6->setFocus();
    }
    if (arg1.length() == 0) {
        ui->txi_no4->setFocus();
    }
}

void ydxh_ScrollArea::on_txi_no6_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no7->setFocus();
    }
    if (arg1.length() == 0) {
        ui->txi_no5->setFocus();
    }
}

void ydxh_ScrollArea::on_txi_no7_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no8->setFocus();
    }
    if (arg1.length() == 0) {
        ui->txi_no6->setFocus();
    }
}

void ydxh_ScrollArea::on_txi_no8_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no9->setFocus();
    }
    if (arg1.length() == 0) {
        ui->txi_no7->setFocus();
    }
}

void ydxh_ScrollArea::on_txi_no9_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no10->setFocus();
    }
    if (arg1.length() == 0) {
        ui->txi_no8->setFocus();
    }
}

void ydxh_ScrollArea::on_txi_no10_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {
        ui->txi_no11->setFocus();
    }
    if (arg1.length() == 0) {
        ui->txi_no9->setFocus();
    }
}

void ydxh_ScrollArea::on_txi_no11_textChanged(const QString &arg1)
{
    if (arg1.length() == 1) {

    }
    if (arg1.length() == 0) {
        ui->txi_no10->setFocus();
    }
}

void ydxh_ScrollArea::on_btn_search_clicked()
{
    submit();
}

void ydxh_ScrollArea::on_btn_reset_clicked()
{
    reset();
}

void ydxh_ScrollArea::on_btn_front_clicked()
{
    if (ui->spinBox->value() == 1) {
        QMessageBox::warning(this,tr("����"),"��ǰ�Ѿ��ǵ�һҳ!",QMessageBox::Ok);
        return;
    }
    else if (ui->spinBox->value() < 1) {
        QMessageBox::warning(this,tr("����"),"��ǰҳ������Ϊ����!",QMessageBox::Ok);
    }
    else if (ui->spinBox->value() > totalPage) {
        QMessageBox::warning(this,tr("����"),"��ǰҳ�����ܳ������ҳ��!",QMessageBox::Ok);
    }
    else {
        ui->spinBox->setValue(1);
        refresh(initPageSize, 1);
    }
}

void ydxh_ScrollArea::on_btn_pre_clicked()
{
    if (ui->spinBox->value() == 1) {
        QMessageBox::warning(this,tr("����"),"��ǰ�Ѿ��ǵ�һҳ!",QMessageBox::Ok);
        return;
    }
    else if (ui->spinBox->value() < 1) {
        QMessageBox::warning(this,tr("����"),"��ǰҳ������Ϊ����!",QMessageBox::Ok);
    }
    else if (ui->spinBox->value() > totalPage) {
        QMessageBox::warning(this,tr("����"),"��ǰҳ�����ܳ������ҳ��!",QMessageBox::Ok);
    }
    else {
        --currentPage;
        ui->spinBox->setValue(currentPage);
        refresh(initPageSize, currentPage);
    }
}

void ydxh_ScrollArea::on_ben_next_clicked()
{
    if (ui->spinBox->value() == totalPage) {
        QMessageBox::warning(this,tr("����"),"��ǰ�Ѿ������һҳ!",QMessageBox::Ok);
        return;
    }
    else if (ui->spinBox->value() < 1) {
        QMessageBox::warning(this,tr("����"),"��ǰҳ������Ϊ����!",QMessageBox::Ok);
    }
    else if (ui->spinBox->value() > totalPage) {
        QMessageBox::warning(this,tr("����"),"��ǰҳ�����ܳ������ҳ��!",QMessageBox::Ok);
    }
    else {
        ++currentPage;
        ui->spinBox->setValue(currentPage);
        refresh(initPageSize, currentPage);
    }
}

void ydxh_ScrollArea::on_btn_tail_clicked()
{
    if (ui->spinBox->value() == totalPage) {
        QMessageBox::warning(this,tr("����"),"��ǰ�Ѿ������һҳ!",QMessageBox::Ok);
        return;
    }
    else if (ui->spinBox->value() < 1) {
        QMessageBox::warning(this,tr("����"),"��ǰҳ������Ϊ����!",QMessageBox::Ok);
    }
    else if (ui->spinBox->value() > totalPage) {
        QMessageBox::warning(this,tr("����"),"��ǰҳ�����ܳ������ҳ��!",QMessageBox::Ok);
    }
    else {
        ui->spinBox->setValue(totalPage);
        refresh(initPageSize, totalPage);
    }
}

void ydxh_ScrollArea::on_spinBox_editingFinished()
{
    if (totalPage > 0) {
        refresh(initPageSize, ui->spinBox->value());
    }
}


void ydxh_ScrollArea::on_txi_no1_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no2_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no3_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no4_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no5_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no6_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no7_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no8_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no9_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no10_editingFinished()
{

}

void ydxh_ScrollArea::on_txi_no11_editingFinished()
{

}

void ydxh_ScrollArea::on_tableWidget_doubleClicked(const QModelIndex &index)
{
//    //�жϵ����λ���Ƿ��к���
//    if (phones[index.row()][index.column()].No == "") {
//        return;
//    }

//    //���ж��Ƿ�����������
//    BusinessFunctionWebServiceSoap soap;
//    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
//    _ns1__LockNo req;

//    char buffer1[255];
//    memset(buffer1,0,255*sizeof(char));
//    std::string No = NetSecurity::encrypt(phones[index.row()][index.column()].No);
//    strcpy(buffer1, No.data());
//    req.No = buffer1;

//    char buffer2[255];
//    memset(buffer2,0,255*sizeof(char));
//    string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
//    strcpy(buffer2, userId.data());
//    req.userId = buffer2;

//    char buffer3[255];
//    memset(buffer3,0,255*sizeof(char));
//    strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
//    //qDebug()<<"session:"+QString::fromStdString(phoneNo);
//    req.sessionId = buffer3;

//    _ns1__LockNoResponse res;
//    ui->tableWidget->setEnabled(false);
//    this->setCursor(Qt::BusyCursor);
//    if (soap.__ns13__LockNo(&req,&res) == SOAP_OK) {
//        QString result = QString::fromUtf8(res.LockNoResult);
//        if (result.contains("�ɹ�")) {
//            QString no = phones[index.row()][index.column()].No;
//            QString value = phones[index.row()][index.column()].value;
//            QString noSection = phones[index.row()][index.column()].NoSection;
//            BuyNoDialog buyNoDialog(this);
//            buyNoDialog.init(no,value,noSection);
//            ui->tableWidget->setEnabled(true);
//            this->setCursor(Qt::ArrowCursor);
//            buyNoDialog.exec();
//        } else {
//            QMessageBox::warning(this,tr("��ʾ"),result,QMessageBox::Ok);
//        }

//    } else {
//        qDebug()<<"����������������������";
//    }
//    ui->tableWidget->setEnabled(true);
//    this->setCursor(Qt::ArrowCursor);
}

void ydxh_ScrollArea::on_rdo_all_clicked()
{
    submit();
}

void ydxh_ScrollArea::on_rdo_1_clicked()
{
    submit();
}

void ydxh_ScrollArea::on_rdo_2_clicked()
{
    submit();
}

void ydxh_ScrollArea::on_rdo_3_clicked()
{
    submit();
}

void ydxh_ScrollArea::on_rdo_4_clicked()
{
    submit();
}

void ydxh_ScrollArea::on_rdo_5_clicked()
{
    submit();
}

void ydxh_ScrollArea::on_rdo_6_clicked()
{
    submit();
}

void ydxh_ScrollArea::on_tableWidget_cellPressed(int row, int column)
{
    //�жϵ����λ���Ƿ��к���
    if (phones[row][column].No == "") {
        return;
    }

    //���ж��Ƿ�����������
    BusinessFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__LockNo req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string No = NetSecurity::encrypt(phones[row][column].No);
    strcpy(buffer1, No.data());
    req.No = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer2, userId.data());
    req.userId = buffer2;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
    //qDebug()<<"session:"+QString::fromStdString(phoneNo);
    req.sessionId = buffer3;

    _ns1__LockNoResponse res;
    ui->tableWidget->setEnabled(false);
    this->setCursor(Qt::BusyCursor);
    if (soap.__ns13__LockNo(&req,&res) == SOAP_OK) {
        QString result = QString::fromUtf8(res.LockNoResult);
        if (result.contains("�ɹ�")) {
            QString no = phones[row][column].No;
            QString value = phones[row][column].value;
            QString noSection = phones[row][column].NoSection;
            BuyNoDialog buyNoDialog(this);
            buyNoDialog.init(no,value,noSection);
            ui->tableWidget->setEnabled(true);
            this->setCursor(Qt::ArrowCursor);
            buyNoDialog.exec();
        } else {
            QMessageBox::warning(this,tr("��ʾ"),result,QMessageBox::Ok);
        }

    } else {
        qDebug()<<"����������������������";
    }
    ui->tableWidget->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
}
