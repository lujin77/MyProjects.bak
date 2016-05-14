#include "gmjp_scrollarea.h"
#include "ui_gmjp_scrollarea.h"

gmjp_ScrollArea::gmjp_ScrollArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::gmjp_ScrollArea)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);   //设置每行内容不可更改
    ui->tableWidget->setAlternatingRowColors(true);
    QStringList list;
    list << "时间" << "航空公司" << "机型" << "航站楼" << "经停"
         << "价格（不含税）" << "仓位" << "票里" << "备注";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

gmjp_ScrollArea::~gmjp_ScrollArea()
{
    delete ui;
}
