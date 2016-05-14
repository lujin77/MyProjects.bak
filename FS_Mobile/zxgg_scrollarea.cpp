#include "zxgg_scrollarea.h"
#include "ui_zxgg_scrollarea.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <QMessageBox>
#include "config.h"
#include "EncryptUtil.h"

zxgg_ScrollArea::zxgg_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::zxgg_ScrollArea)
{
    ui->setupUi(this);
    totalPage = 0;
    currentPage = 0;
    initPageSize = 10;

    //��ͷ��Ϣ
    QString countStr = "��:��0��ҳ";
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(initPageSize);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ��һ��
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //����ֻ��ѡ��һ�У����ܶ���ѡ��
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //����ÿ�����ݲ��ɸ���
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "Id" << "��������" << "��Ϣ����" << "�������" << "����";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    //ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //��������ط�
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->hideColumn(4);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,300);
    ui->txt_rpt_total->setText(countStr);
    ui->spinBox->setValue(currentPage);

    _notice_dialog = new NoticeDialog();
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this);
    ui->txi_line_num->setValidator(validator);
    ui->txi_line_num->setText(QString::number(initPageSize));
}

zxgg_ScrollArea::~zxgg_ScrollArea()
{
    delete ui;
}

void zxgg_ScrollArea::init()
{
    refresh(initPageSize, 1);
}

void zxgg_ScrollArea::reset()
{
    totalPage = 0;
    currentPage = 0;
    ui->tableWidget->clearContents();
    QString countStr = "��:��0��ҳ";
    ui->txt_rpt_total->setText(countStr);
    ui->spinBox->setValue(currentPage);
}

void zxgg_ScrollArea::refresh(int pageSize, int pageIndex)
{
    reset();
    ui->tableWidget->setRowCount(initPageSize);

    UtilFunctionWebServiceSoap soap;
    soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
    _ns1__GetNoticeListByCondition req;

    char buffer0[255];
    memset(buffer0,0,255*sizeof(char));
    strcpy(buffer0, Singleton::GetInstance()->session_id.toUtf8().data());
    req.sessionId = buffer0;

    req.pageSize = pageSize;
    req.pageIndex = pageIndex;

    QString queryStr = "[�Ƿ���ʾ]=1 and [�ͻ�������]='"+Config::GetInstance()->_client_type+"'";
    queryStr += " and Id not in (select [ϵͳ����Id] from [dbo].[ϵͳ����_��ʱ��Ϣ_ӳ���] where [�����û�Id]<>'"+Singleton::GetInstance()->getUser().Id+"')";
    std::string condition = NetSecurity::encrypt(queryStr);
    char buffer1[condition.size()];
    memset(buffer1,0,condition.size()*sizeof(char));
    strcpy(buffer1, condition.data());
    req.condition = buffer1;

    _ns1__GetNoticeListByConditionResponse res;
    this->setCursor(Qt::BusyCursor);
    if (soap.__ns7__GetNoticeListByCondition(&req,&res) == SOAP_OK) {
        QString content = "";
        totalPage = res.GetNoticeListByConditionResult->totalPage;
        currentPage = res.GetNoticeListByConditionResult->currentPageIndex;
        for (int i=0; i<res.GetNoticeListByConditionResult->listOfNotice->__sizeNoticeItem; ++i) {
            for (int j=0; j<5; ++j) {
                switch (j) {
                    case 0:
                        content = QString::fromUtf8(res.GetNoticeListByConditionResult->listOfNotice->NoticeItem[i]->Id);
                        break;
                    case 1:
                        if (-1 == res.GetNoticeListByConditionResult->listOfNotice->NoticeItem[i]->publishDatetime) continue;
                        char cTime[50];
                        memset(cTime,0,50);
                        strftime(cTime,32,"%Y-%m-%d %H:%M:%S",localtime(&(res.GetNoticeListByConditionResult->listOfNotice->NoticeItem[i]->publishDatetime)));
                        content = QString(cTime);
                        break;
                    case 2:
                        content = QString::fromUtf8(res.GetNoticeListByConditionResult->listOfNotice->NoticeItem[i]->type);
                        break;
                    case 3:
                        content = QString::fromUtf8(res.GetNoticeListByConditionResult->listOfNotice->NoticeItem[i]->title);
                        break;
                    case 4:
                        content = QString::fromUtf8(res.GetNoticeListByConditionResult->listOfNotice->NoticeItem[i]->content);
                        break;
                }
                QTableWidgetItem *item = new QTableWidgetItem (content);
                ui->tableWidget->setItem(i, j, item);
            }
        }
    } else {
        QMessageBox::warning(this,tr("����"),"��������������ϵ����Ա",QMessageBox::Ok);
    }
    this->setCursor(Qt::ArrowCursor);

    QString countStr = "��:��"+QString::number(totalPage)+"��ҳ";
    ui->txt_rpt_total->setText(countStr);
    ui->spinBox->setValue(currentPage);
    ui->spinBox->setMaximum(totalPage);
}

void zxgg_ScrollArea::on_tableWidget_doubleClicked(const QModelIndex &index)
{
//    _notice_dialog->reset();
//    int i = index.row();
//    QString title = ui->tableWidget->item(i,3)->text();
//    QString date = "��������: "+ui->tableWidget->item(i,1)->text();
//    QString content = ui->tableWidget->item(i,4)->text();
//    _notice_dialog->setWindowTitle("���¹���");
//    _notice_dialog->init(title, date, content);
//    _notice_dialog->show();
}

void zxgg_ScrollArea::on_btnFront_clicked()
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

void zxgg_ScrollArea::on_btnPre_clicked()
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

void zxgg_ScrollArea::on_btnNext_clicked()
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

void zxgg_ScrollArea::on_btnTail_clicked()
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

void zxgg_ScrollArea::on_spinBox_editingFinished()
{
    if (totalPage > 0) {
        refresh(initPageSize, ui->spinBox->value());
    }
}

void zxgg_ScrollArea::on_txi_line_num_editingFinished()
{
    if (ui->txi_line_num->text().toInt() > 0) {
        qDebug()<<"�µ��к�:"+ui->txi_line_num->text();
        initPageSize = ui->txi_line_num->text().toInt();
        refresh(initPageSize, currentPage);
        qDebug()<<"ˢ��";
    } else {
        QMessageBox::warning(this,tr("����"),"���������ʾ�������Ϸ�!",QMessageBox::Ok);
    }
}

void zxgg_ScrollArea::on_tableWidget_clicked(const QModelIndex &index)
{
    _notice_dialog->reset();
    int i = index.row();
    if (ui->tableWidget->item(i,3) == NULL) {
        return;
    }
    QString title = ui->tableWidget->item(i,3)->text();
    QString date = "��������: "+ui->tableWidget->item(i,1)->text();
    QString content = ui->tableWidget->item(i,4)->text();
    _notice_dialog->setWindowTitle("���¹���");
    _notice_dialog->init(title, date, content);
    _notice_dialog->show();
}
