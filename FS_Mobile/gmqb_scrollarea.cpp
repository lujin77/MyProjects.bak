#include "gmqb_scrollarea.h"
#include "ui_gmqb_scrollarea.h"

gmqb_ScrollArea::gmqb_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::gmqb_ScrollArea)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "提交日期" << "QQ号码" << "Q币数量" << "备注";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,355);

    ui->cbx_type->addItem("--请选择游戏类型--",0);
    ui->cbx_type->addItem("Q币","Q币");
}

gmqb_ScrollArea::~gmqb_ScrollArea()
{
    delete ui;
}
