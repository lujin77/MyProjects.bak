#include "xkkk_scrollarea.h"
#include "ui_xkkk_scrollarea.h"
#include "gsoap/soapBusinessFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "printer.h"
#include "EncryptUtil.h"
#include "config.h"

GetXkkkCondtionThread::GetXkkkCondtionThread(xkkk_ScrollArea *xkkk_ScrollArea_ptr)
{
    this->_ref = xkkk_ScrollArea_ptr;
}

void GetXkkkCondtionThread::run()
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

    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    memset(buffer1,0,255*sizeof(char));
    queryStr = "[Category]='С���ۿ�' and [Name]='С����Ԫ��' and [Enabled]=1 ";
    condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;
    if (soap.__ns7__GetDicContentByCondition(&req,&res) == SOAP_OK) {
        QString price = QString::fromUtf8(res.GetDicContentByConditionResult->DIC_USCOREContent[0]->Code);
        _ref->cardPrice = price.toFloat();
    } else {
        qDebug()<<"�����������޷���ȡ����С���۸�";
    }


    UserFunctionWebServiceSoap soap1;
    soap_set_mode(soap1.soap, SOAP_C_UTFSTRING);
    _ns1__GetWorkNameList req1;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    QString queryStr1 = " [Ա������]='ҵ��Ա' ";
    string condition1 = NetSecurity::encrypt(queryStr1);
    strcpy(buffer3, condition1.data());
    req1.condition = buffer3;

    _ns1__GetWorkNameListResponse res1;
    if (soap1.__ns5__GetWorkNameList(&req1,&res1) == SOAP_OK) {
        qDebug()<<"��ȡ������:"+QString::number(res1.GetWorkNameListResult->__sizeWorker);
        for (int i = 0; i < res1.GetWorkNameListResult->__sizeWorker; ++i) {
            QString name = QString::fromUtf8(res1.GetWorkNameListResult->Worker[i]->WorkerName);
            QString worker_id = QString::fromUtf8(res1.GetWorkNameListResult->Worker[i]->Id);
            _ref->ui->cbx_worker->addItem(name,worker_id);
        }
    } else {
        qDebug()<<"�������������ܻ�ȡҵ��Ա�б�";
    }
}


xkkk_ScrollArea::xkkk_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::xkkk_ScrollArea)
{
    ui->setupUi(this);

    cardPrice = 0;

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this );
    ui->txi_card_count->setValidator( validator );
    ui->txi_pay_money->setValidator( validator );
    ui->txi_suffix1->setValidator( validator );
    ui->txi_suffix2->setValidator( validator );

    _getXkkkCondtionThread = new GetXkkkCondtionThread(this);

    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection); //����ֻ��ѡ��һ�У����ܶ���ѡ��
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //����ÿ�����ݲ��ɸ���
    cardListModel.setStringList(cardNoList);
    ui->listView->setModel(&cardListModel);
}

xkkk_ScrollArea::~xkkk_ScrollArea()
{
    if (_getXkkkCondtionThread != NULL) {
        _getXkkkCondtionThread->terminate();
        _getXkkkCondtionThread->exit();
        delete _getXkkkCondtionThread;
    }
    delete ui;
}

void xkkk_ScrollArea::init()
{
    reset();
    if (!_getXkkkCondtionThread->isRunning()) {
        _getXkkkCondtionThread->start();
    }
}

void xkkk_ScrollArea::reset()
{
    ui->txi_account_name->setText(Singleton::GetInstance()->getUser().loggingName);
    ui->txi_account_money->setText(QString::number(Singleton::GetInstance()->getUser().money,'f',2));
    ui->txi_card_count->setText("0");
    ui->txi_pay_money->setText("0");
    ui->cbx_sp->clear();
    ui->cbx_worker->clear();
    ui->txi_prefix->setText("");
    ui->txi_suffix1->setText("");
    ui->txi_suffix2->setText("");

    cardNoList.clear();
    cardListModel.removeRows(0,cardListModel.rowCount());
    ui->txi_pay_money->setText(QString::number(cardPrice*cardNoList.size()));
    ui->txi_card_count->setText(QString::number(cardNoList.size()));
}

void xkkk_ScrollArea::submit()
{
    if (ui->txi_pay_money->text() == "0") {
        QMessageBox::warning(this,tr("��ʾ"),"�ۿ����Ϊ0��",QMessageBox::Ok);
        ui->txi_pay_money->setFocus();
        return;
    }
    if (ui->txi_card_count->text() == "0" && ui->txi_content->toPlainText() == "") {
        QMessageBox::warning(this,tr("��ʾ"),"��С���ۿ��ע����Ϊ�գ�",QMessageBox::Ok);
        ui->txi_content->setFocus();
        return;
    }

    if (ui->cbx_worker->currentText() == "") {
        QMessageBox::warning(this,tr("��ʾ"),"ҵ��Ա����Ϊ�գ�",QMessageBox::Ok);
        ui->cbx_worker->setFocus();
        return;
    }
    if (ui->cbx_sp->currentText() == "") {
        QMessageBox::warning(this,tr("��ʾ"),"��Ӫ�̲���Ϊ�գ�",QMessageBox::Ok);
        ui->cbx_sp->setFocus();
        return;
    }

    QString str = "ȷ���ύС���ۿ�������";
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "С���ۿ�", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        //TODO �ύ����������
        BusinessFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__BuyMiniCard req;

        QString tmp = "";
        for (int i=0; i<cardNoList.size(); ++i) {
            tmp += cardNoList.at(i)+",";
        }
        std::string data = NetSecurity::encrypt(tmp);
        qDebug()<<"data:"+QString::fromStdString(data);
        char buffer1[data.length()];
        memset(buffer1,0,data.length()*sizeof(char));
        strcpy(buffer1, data.data());
        req.data = buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        QString work_id = ui->cbx_worker->itemData(ui->cbx_worker->currentIndex()).toString();
        std::string workerId = NetSecurity::encrypt(work_id);
        qDebug()<<"work_id:"+QString::fromStdString(workerId);
        strcpy(buffer2, workerId.data());
        req.workerId = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
        qDebug()<<"userId:"+QString::fromStdString(userId);
        strcpy(buffer3, userId.data());
        req.userId = buffer3;

        char _buffer3[255];
        memset(_buffer3,0,255*sizeof(char));
        string count = NetSecurity::encrypt(ui->txi_card_count->text());
        qDebug()<<"count:"+QString::fromStdString(count);
        strcpy(_buffer3, count.data());
        req.count = _buffer3;

        char buffer4[255];
        memset(buffer4,0,255*sizeof(char));
        strcpy(buffer4, Singleton::GetInstance()->session_id.toUtf8().data());
        qDebug()<<"session_id:"+Singleton::GetInstance()->session_id;
        req.sessionId = buffer4;

        char buffer5[255];
        memset(buffer5,0,255*sizeof(char));
        std::string SP = NetSecurity::encrypt(ui->cbx_sp->currentText());
        qDebug()<<"SP:"+QString::fromStdString(SP);
        strcpy(buffer5, SP.data());
        req.SP = buffer5;

        char buffer6[255];
        memset(buffer6,0,255*sizeof(char));
        std::string money = NetSecurity::encrypt(ui->txi_pay_money->text());
        qDebug()<<"money:"+QString::fromStdString(money);
        strcpy(buffer6, money.data());
        req.money = buffer6;

        char buffer7[255];
        memset(buffer7,0,255*sizeof(char));
        std::string content = NetSecurity::encrypt(ui->txi_content->toPlainText());
        qDebug()<<"content:"+QString::fromStdString(content);
        strcpy(buffer7, content.data());
        req.content = buffer7;

        char buffer8[255];
        memset(buffer8,0,255*sizeof(char));
        std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
        qDebug()<<"clientType:"+QString::fromStdString(clientType);
        strcpy(buffer8, clientType.data());
        req.clientType = buffer8;

        _ns1__BuyMiniCardResponse res;
        this->setCursor(Qt::BusyCursor);
        ui->btn_submit->setEnabled(false);
        if (soap.__ns13__BuyMiniCard(&req,&res) == SOAP_OK) {
            QString result = QString::fromUtf8(res.BuyMiniCardResult);
            QMessageBox::warning(this,tr("��ʾ"),result,QMessageBox::Ok);
            if (result.contains("�ɹ�")) {

                UserFunctionWebServiceSoap soap;
                soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
                _ns1__GetUserInfo req1;

                char buffer1[255];
                memset(buffer1,0,255*sizeof(char));
                std::string username = NetSecurity::encrypt(Singleton::GetInstance()->getUser().loggingName);
                strcpy(buffer1, username.data());
                req1.username = buffer1;

                char buffer2[255];
                memset(buffer2,0,255*sizeof(char));
                std::string password = NetSecurity::encrypt(Singleton::GetInstance()->getUser().password);
                strcpy(buffer2, password.data());
                req1.password = buffer2;

                char buffer3[255];
                memset(buffer3,0,255*sizeof(char));
                strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
                req1.sessionId = buffer3;

                char buffer4[255];
                memset(buffer4,0,255*sizeof(char));
                std::string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
                strcpy(buffer4, clientType.data());
                req1.clientType = buffer4;

                _ns1__GetUserInfoResponse res1;
                if (soap.__ns5__GetUserInfo(&req1,&res1) == SOAP_OK) {
                    //���»����ڿͻ��˵�money
                    double newMoney = res1.GetUserInfoResult->money;
                    UserVO user = Singleton::GetInstance()->getUser();
                    user.money = newMoney;
                    Singleton::GetInstance()->setUser(user);
                } else {
                    QMessageBox::warning(this,tr("����"),"��������������ϵ����Ա",QMessageBox::Ok);
                }

                emit updateMoney();
                init();
            }
        }
        else {
            QMessageBox::warning(this,tr("��ʾ"),"����������",QMessageBox::Ok);
        }
        this->setCursor(Qt::ArrowCursor);
        ui->btn_submit->setEnabled(true);
    }
}

void xkkk_ScrollArea::on_btn_generate_clicked()
{
    if (ui->txi_prefix->text() == "") {
        QMessageBox::warning(this,tr("��ʾ"),"��������С������ǰ׺��",QMessageBox::Ok);
        ui->txi_prefix->setFocus();
        return;
    }

    if (ui->txi_suffix1->text() == "") {
        QMessageBox::warning(this,tr("��ʾ"),"С������ǰ׺����Ϊ�գ�",QMessageBox::Ok);
        ui->txi_suffix1->setFocus();
        return;
    }

    if (ui->txi_suffix2->text() == "") {
        QMessageBox::warning(this,tr("��ʾ"),"С�������׺����Ϊ�գ�",QMessageBox::Ok);
        ui->txi_suffix2->setFocus();
        return;
    }

    if (Config::GetInstance()->_client_type == "��ͨ���ſͻ���") {
        int start = ui->txi_suffix1->text().toInt();
        int end = ui->txi_suffix2->text().toInt();
        if (start > end) {
            QMessageBox::warning(this,tr("��ʾ"),"С�������׺��ʼ����С�ں�׺��ֹ��",QMessageBox::Ok);
            ui->txi_suffix2->setFocus();
            return;
        }
        QStringList tmp;
        for (int i = start; i <= end; ++i) {
            tmp += ui->txi_prefix->text()+QString::number(i);
        }
        for (int k=0; k<tmp.size(); ++k) {
            if (cardNoList.contains(tmp.at(k))) {
                QMessageBox::warning(this,tr("��ʾ"),"С����:"+tmp.at(k)+"�Ѵ��ڣ��벻Ҫ�ظ����ɣ�",QMessageBox::Ok);
                return;
            }
        }
        cardNoList.append(tmp);
        cardListModel.setStringList(cardNoList);
        ui->txi_pay_money->setText(QString::number(cardPrice*cardNoList.size()));
        ui->txi_card_count->setText(QString::number(cardNoList.size()));
    } else {
        if (ui->txi_suffix1->text().right(1) != ui->txi_suffix2->text().right(1)) {
            QMessageBox::warning(this,tr("��ʾ"),"�ƶ�С����β�ű�����ͬ��",QMessageBox::Ok);
            ui->txi_suffix1->setFocus();
            return;
        }
        QString mark = ui->txi_suffix1->text().right(1);
        QString front = ui->txi_suffix1->text();
        front = front.mid(0, front.size()-1);
        QString tail = ui->txi_suffix2->text();
        tail = tail.mid(0, tail.size()-1);
        int start = front.toInt();
        int end = tail.toInt();
        if (start > end) {
            QMessageBox::warning(this,tr("��ʾ"),"С�������׺��ʼ����С�ں�׺��ֹ�����һλ���㣩��",QMessageBox::Ok);
            ui->txi_suffix2->setFocus();
            return;
        }
        QStringList tmp;
        for (int i = start; i <= end; ++i) {
            tmp += ui->txi_prefix->text()+QString::number(i)+mark;
        }
        for (int k=0; k<tmp.size(); ++k) {
            if (cardNoList.contains(tmp.at(k))) {
                QMessageBox::warning(this,tr("��ʾ"),"С����:"+tmp.at(k)+"�Ѵ��ڣ��벻Ҫ�ظ����ɣ�",QMessageBox::Ok);
                return;
            }
        }
        cardNoList.append(tmp);
        cardListModel.setStringList(cardNoList);
        ui->txi_pay_money->setText(QString::number(cardPrice*cardNoList.size()));
        ui->txi_card_count->setText(QString::number(cardNoList.size()));
    }
}

void xkkk_ScrollArea::on_bent_delete_clicked()
{
    if (ui->listView < 0) {
        QMessageBox::warning(this,tr("��ʾ"),"û��ѡ��Ҫɾ�����",QMessageBox::Ok);
        return;
    } else {
        cardNoList.removeAt(ui->listView->currentIndex().row());
        cardListModel.removeRow(ui->listView->currentIndex().row());
        ui->txi_pay_money->setText(QString::number(cardPrice*cardNoList.size()));
        ui->txi_card_count->setText(QString::number(cardNoList.size()));
    }

}

void xkkk_ScrollArea::on_btn_clear_clicked()
{
    cardNoList.clear();
    cardListModel.removeRows(0,cardListModel.rowCount());
    ui->txi_pay_money->setText("0");
    ui->txi_card_count->setText("0");
}

void xkkk_ScrollArea::on_btn_submit_clicked()
{
    submit();
}

void xkkk_ScrollArea::on_btn_reset_clicked()
{
    reset();
}

void xkkk_ScrollArea::keyPressEvent(QKeyEvent *event)
{
    //QMessageBox::warning(this,tr("����"),QString::number(event->key()),QMessageBox::Ok);
    switch (event->key()) {
        case 16777220:
            submit();
            break;
    }
}
