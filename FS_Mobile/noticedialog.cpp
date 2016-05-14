#include "noticedialog.h"
#include "ui_noticedialog.h"

NoticeDialog::NoticeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoticeDialog)
{
    ui->setupUi(this);
}

NoticeDialog::~NoticeDialog()
{
    delete ui;
}

void NoticeDialog::init(QString title, QString date, QString content)
{
    ui->txi_title->setText(title);
    ui->txt_date->setText(date);
    if (content.contains("html")) {
        ui->txt_content->setHtml(content);
    } else {
        ui->txt_content->setText(content);
    }
}

void NoticeDialog::reset()
{
    ui->txi_title->setText("");
    ui->txt_date->setText("");
    ui->txt_content->setText("");
    this->setWindowTitle("");
}

void NoticeDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
