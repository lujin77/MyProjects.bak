#include "gmqb_scrollarea.h"
#include "ui_gmqb_scrollarea.h"

gmqb_ScrollArea::gmqb_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::gmqb_ScrollArea)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ��һ��
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //����ֻ��ѡ��һ�У����ܶ���ѡ��
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //����ÿ�����ݲ��ɸ���
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "�ύ����" << "QQ����" << "Q������" << "��ע";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,355);

    ui->cbx_type->addItem("--��ѡ����Ϸ����--",0);
    ui->cbx_type->addItem("Q��","Q��");
}

gmqb_ScrollArea::~gmqb_ScrollArea()
{
    delete ui;
}
