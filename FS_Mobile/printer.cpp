#include "printer.h"
#include "gsoap/soapPaymentFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include "EncryptUtil.h"
#include "config.h"

Print_jf_Thread::Print_jf_Thread()
{
    currentPaymentCondition = "";
}

void Print_jf_Thread::run()
{
    qDebug()<<"�����ӡ�߳�";
    QString queryStr = currentPaymentCondition;
    qDebug()<<"��ȡ����:"+queryStr;
    if (queryStr == "" || queryStr == NULL) {
        qDebug()<<"����Ĵ�ӡ�������˳�";
        return;
    }
    PaymentFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetPaymentItem req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string condition = NetSecurity::encrypt(queryStr);
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    strcpy(buffer2, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer2;

    _ns1__GetPaymentItemResponse res;
    if (soap.__ns3__GetPaymentItem(&req,&res) == SOAP_OK) {

        char cTime[50];
        memset(cTime,0,50);
        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetPaymentItemResult->chargeTime)));
        QString time = QString(cTime);

        qDebug()<<"׼����ӡ";
        Printer::GetInstance()->printJF(Singleton::GetInstance()->getUser().shopName,
                     QString::fromUtf8(res.GetPaymentItemResult->telNo),
                     QString::fromUtf8(res.GetPaymentItemResult->NoLocation),
                     QString::fromUtf8(res.GetPaymentItemResult->customerName),
                     QString::fromUtf8(res.GetPaymentItemResult->brand),
                     QString::number(res.GetPaymentItemResult->customerBeforeMoney),
                     QString::number(res.GetPaymentItemResult->chargeMoney),
                     QString::number(res.GetPaymentItemResult->customerAfterMoney),
                     QString::fromUtf8(res.GetPaymentItemResult->state),
                     time);
        currentPaymentCondition = "";
    }
    else {
        qDebug()<<"�������������ܻ�ȡ��ӡ��Ϣ";
    }
    qDebug()<<"�˳���ӡ�߳�";
}

Printer::Printer()
{
    _print_jf_Thread = new Print_jf_Thread();
}

Printer::~Printer()
{
    if(instance != NULL)
    {
        if (_print_jf_Thread != NULL) {
            _print_jf_Thread->terminate();
            _print_jf_Thread->exit();
            delete _print_jf_Thread;
        }
        delete instance;
    }
}

QString Printer::getLogoURL()
{
    QString url = "";
    if (Config::GetInstance()->_client_type == "�ƶ��ͻ���") {
        url = "\":/icon/images/yd.png\"";
    } else if (Config::GetInstance()->_client_type == "��ͨ���ſͻ���") {
        url = "\":/icon/images/lt.png\"";
    }
    return url;
}

Printer* Printer::instance=NULL;

Printer* Printer::GetInstance()
{
 if(instance == NULL)
 {
  instance = new Printer();
 }
 return instance;
}

void Printer::printJF(QString condition)
{
    _print_jf_Thread->currentPaymentCondition = condition;
    if (_print_jf_Thread->isRunning()) {
        _print_jf_Thread->terminate();
    }
    _print_jf_Thread->start();
}

void Printer::printJF(QString shop_name, QString tel, QString location, QString name, QString brand,
           QString before_money, QString pay_money, QString after_money, QString state, QString datetime)
{
    qDebug()<<"��ʼ��ӡ...";
    QPrinter p;
    QTextDocument doc;
    QString content = QString("<html><head></head><body style=\"font-size:12pt;\">");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src="+getLogoURL()+" /><span style=\" font-size:14pt;\">"+shop_name+"</span></p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�绰����:"+tel+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�������:"+location+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�ͻ�����:"+name+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Ʒ��:"+brand+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����ǰ���:��"+before_money+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Ԥ����:��"+pay_money+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ʵʱ����:��"+after_money+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�ɷ�״̬:"+state+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�ɷ����ڣ�"+datetime+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����绰��"+Singleton::GetInstance()->getUser().tel+"</p>");
    doc.setHtml(content);
    QSizeF s = QSizeF(p.logicalDpiX() * (58 / 25.4), p.logicalDpiY() * (500 / 25.4));
    doc.setPageSize(s);
    p.setOutputFormat(QPrinter::NativeFormat);
    doc.print(&p);
    qDebug()<<"��ɴ�ӡ";
}

void Printer::printGame(QString condition)
{

}

void Printer::printGame(QString shop_name, QString game_type, QString game_account,
                QString charge_money, QString state, QString datetime)
{
    qDebug()<<"��ʼ��ӡ...";
    QPrinter p;
    QTextDocument doc;
    QString content = QString("<html><head></head><body style=\"font-size:12pt;\">");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src="+getLogoURL()+" /><span style=\" font-size:14pt;\">"+shop_name+"</span></p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">��Ϸ����:"+game_type+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">��Ϸ�˺�:"+game_account+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Ԥ����:��"+charge_money+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����״̬:"+state+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">��ֵ���ڣ�"+datetime+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����绰��"+Singleton::GetInstance()->getUser().tel+"</p>");
    doc.setHtml(content);
    QSizeF s = QSizeF(p.logicalDpiX() * (58 / 25.4), p.logicalDpiY() * (500 / 25.4));
    doc.setPageSize(s);
    p.setOutputFormat(QPrinter::NativeFormat);
    doc.print(&p);
    qDebug()<<"��ɴ�ӡ";
}

void Printer::printInternet(QString condition)
{

}

void Printer::printInternet(QString shop_name, QString internet_type, QString internet_account,
                QString charge_money, QString state, QString datetime)
{
    qDebug()<<"��ʼ��ӡ...";
    QPrinter p;
    QTextDocument doc;
    QString content = QString("<html><head></head><body style=\"font-size:12pt;\">");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src="+getLogoURL()+" /><span style=\" font-size:14pt;\">"+shop_name+"</span></p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�������:"+internet_type+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����˺�:"+internet_account+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Ԥ����:��"+charge_money+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����״̬:"+state+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">��ֵ���ڣ�"+datetime+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����绰��"+Singleton::GetInstance()->getUser().tel+"</p>");
    doc.setHtml(content);
    QSizeF s = QSizeF(p.logicalDpiX() * (58 / 25.4), p.logicalDpiY() * (500 / 25.4));
    doc.setPageSize(s);
    p.setOutputFormat(QPrinter::NativeFormat);
    doc.print(&p);
    qDebug()<<"��ɴ�ӡ";
}

void Printer::printPublicTel(QString condition)
{

}

void Printer::printPublicTel(QString shop_name, QString tel_type, QString tel_account,
                QString charge_money, QString state, QString datetime)
{
    qDebug()<<"��ʼ��ӡ...";
    QPrinter p;
    QTextDocument doc;
    QString content = QString("<html><head></head><body style=\"font-size:12pt;\">");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src="+getLogoURL()+" /><span style=\" font-size:14pt;\">"+shop_name+"</span></p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�绰����:"+tel_type+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�绰����:"+tel_account+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Ԥ����:��"+charge_money+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����״̬:"+state+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">��ֵ���ڣ�"+datetime+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����绰��"+Singleton::GetInstance()->getUser().tel+"</p>");
    doc.setHtml(content);
    QSizeF s = QSizeF(p.logicalDpiX() * (58 / 25.4), p.logicalDpiY() * (500 / 25.4));
    doc.setPageSize(s);
    p.setOutputFormat(QPrinter::NativeFormat);
    doc.print(&p);
    qDebug()<<"��ɴ�ӡ";
}

void Printer::printSellCard(QString condition)
{
    return;
}

void Printer::printSellCard(QString shop_name, QString tel_no, QString brand,
                QString price, QString state, QString datetime)
{
    qDebug()<<"��ʼ��ӡ...";
    QPrinter p;
    QTextDocument doc;
    QString content = QString("<html><head></head><body style=\"font-size:12pt;\">");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src="+getLogoURL()+" /><span style=\" font-size:14pt;\">"+shop_name+"</span></p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�绰����:"+tel_no+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�ײ�:"+brand+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">������ֵ:��"+price+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����״̬:"+state+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�������ڣ�"+datetime+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����绰��"+Singleton::GetInstance()->getUser().tel+"</p>");
    doc.setHtml(content);
    QSizeF s = QSizeF(p.logicalDpiX() * (58 / 25.4), p.logicalDpiY() * (500 / 25.4));
    doc.setPageSize(s);
    p.setOutputFormat(QPrinter::NativeFormat);
    doc.print(&p);
    qDebug()<<"��ɴ�ӡ";
}

void Printer::printDoBusiness(QString condition)
{
    return;
}

void Printer::printDoBusiness(QString shop_name, QString tel_no, QString serviceName, QString serviceSpec, QString state, QString datetime)
{
    qDebug()<<"��ʼ��ӡ...";
    QPrinter p;
    QTextDocument doc;
    QString content = QString("<html><head></head><body style=\"font-size:12pt;\">");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src="+getLogoURL()+" /><span style=\" font-size:14pt;\">"+shop_name+"</span></p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�绰����:"+tel_no+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ҵ������:"+serviceName+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ҵ����ϸ:��"+serviceSpec+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����״̬:"+state+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�������ڣ�"+datetime+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����绰��"+Singleton::GetInstance()->getUser().tel+"</p>");
    doc.setHtml(content);
    QSizeF s = QSizeF(p.logicalDpiX() * (58 / 25.4), p.logicalDpiY() * (500 / 25.4));
    doc.setPageSize(s);
    p.setOutputFormat(QPrinter::NativeFormat);
    doc.print(&p);
    qDebug()<<"��ɴ�ӡ";
}

void Printer::printKlxs(QString condition)
{
     return;
}

void Printer::printKlxs(QString shop_name, QString cardType, QString cardName,
               QString seqNo, QString passwd, QString state, QString datetime)
{
    qDebug()<<"��ʼ��ӡ...";
    QPrinter p;
    QTextDocument doc;
    QString content = QString("<html><head></head><body style=\"font-size:12pt;\">");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src="+getLogoURL()+" /><span style=\" font-size:14pt;\">"+shop_name+"</span></p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">������:"+cardType+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">������:"+cardName+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">���к�:��"+seqNo+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����:"+passwd+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����״̬:"+state+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:2px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">�������ڣ�"+datetime+"</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">--------------------------</p>");
    content += QString("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">����绰��"+Singleton::GetInstance()->getUser().tel+"</p>");
    doc.setHtml(content);
    QSizeF s = QSizeF(p.logicalDpiX() * (58 / 25.4), p.logicalDpiY() * (500 / 25.4));
    doc.setPageSize(s);
    p.setOutputFormat(QPrinter::NativeFormat);
    doc.print(&p);
    qDebug()<<"��ɴ�ӡ";
}

