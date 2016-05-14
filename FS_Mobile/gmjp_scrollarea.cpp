#include "gmjp_scrollarea.h"
#include "ui_gmjp_scrollarea.h"

gmjp_ScrollArea::gmjp_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::gmjp_ScrollArea)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ��һ��
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //����ֻ��ѡ��һ�У����ܶ���ѡ��
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //����ÿ�����ݲ��ɸ���
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "ʱ��" << "���չ�˾" << "����" << "��վ¥" << "��ͣ"
         << "�۸񣨲���˰��" << "��λ" << "Ʊ��" << "��ע";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

gmjp_ScrollArea::~gmjp_ScrollArea()
{
    delete ui;
}
