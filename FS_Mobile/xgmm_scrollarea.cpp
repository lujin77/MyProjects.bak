#include "xgmm_scrollarea.h"
#include "ui_xgmm_scrollarea.h"
#include "singleton.h"
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include <QMessageBox>
#include "EncryptUtil.h"

xgmm_ScrollArea::xgmm_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::xgmm_ScrollArea)
{
    ui->setupUi(this);
}

xgmm_ScrollArea::~xgmm_ScrollArea()
{
    delete ui;
}

void xgmm_ScrollArea::init()
{
    ui->txiName->setText(Singleton::GetInstance()->getUser().loggingName);
}

void xgmm_ScrollArea::reset()
{
    ui->txiOldPassword->setText("");
    ui->txiNewPassword->setText("");
    ui->txiReNewPassword->setText("");
}

void xgmm_ScrollArea::submit()
{
    if (ui->txiOldPassword->text() == "") {
        QMessageBox::warning(this,tr("����"),"�����벻��Ϊ��",QMessageBox::Ok);
        return;
    }
    if (ui->txiOldPassword->text() != Singleton::GetInstance()->getUser().password) {
        QMessageBox::warning(this,tr("����"),"���������",QMessageBox::Ok);
        return;
    }
    if (ui->txiNewPassword->text() == "") {
        QMessageBox::warning(this,tr("����"),"�����벻��Ϊ��",QMessageBox::Ok);
        return;
    }
    if (ui->txiReNewPassword->text() == "") {
            QMessageBox::warning(this,tr("����"),"ȷ�������벻��Ϊ��",QMessageBox::Ok);
            return;
        }
    if (ui->txiNewPassword->text() != ui->txiReNewPassword->text()) {
        QMessageBox::warning(this,tr("����"),"������������벻һ��",QMessageBox::Ok);
        return;
    }

    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "�޸�����", "ȷ���޸�����ǰ��������?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb != QMessageBox::Yes) {
        return;
    }

    UserFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__AlterPsw req;

    char buffer1[255];
    memset(buffer1,0,255*sizeof(char));
    std::string userId = NetSecurity::encrypt(Singleton::GetInstance()->getUser().Id);
    strcpy(buffer1, userId.data());
    req.user_USCOREid = buffer1;

    char buffer2[255];
    memset(buffer2,0,255*sizeof(char));
    std::string newPsw = NetSecurity::encrypt(ui->txiReNewPassword->text());
    strcpy(buffer2, newPsw.data());
    req.newPsw = buffer2;

    char buffer3[255];
    memset(buffer3,0,255*sizeof(char));
    strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer3;

    _ns1__AlterPswResponse res;
    this->setCursor(Qt::BusyCursor);
    ui->btnSubmit->setEnabled(false);
    if (soap.__ns5__AlterPsw(&req,&res) == SOAP_OK) {
        QString str = QString::fromUtf8(res.AlterPswResult);
        QMessageBox::warning(this,tr("���"),str,QMessageBox::Ok);
        if (str.contains("�ɹ�")) {
            reset();
        }
    } else {
        QMessageBox::warning(this,tr("����"),"��������������ϵ����Ա",QMessageBox::Ok);
    }
    this->setCursor(Qt::ArrowCursor);
    ui->btnSubmit->setEnabled(true);
}

void xgmm_ScrollArea::on_btnSubmit_clicked()
{
    submit();
}

void xgmm_ScrollArea::on_btnReset_clicked()
{
    reset();
}
