#include "newsalertdialog.h"
#include "ui_newsalertdialog.h"
#include "singleton.h"

NewsAlertDialog::NewsAlertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewsAlertDialog)
{
    ui->setupUi(this);

    _news_list.clear();        //未读消息（包含详细信息）
    _already_read_list.clear();     //已读消息的Id

    //加载已读消息
    readFile();

    //生成消息提示窗口
    noticeDialog = new NoticeDialog(this);

}

NewsAlertDialog::~NewsAlertDialog()
{
    delete ui;
}

void NewsAlertDialog::readFile()
{
    //reset();
    _news_list.clear();             //未读消息（包含详细信息）
    _already_read_list.clear();     //已读消息的Id

    QString filename = Singleton::GetInstance()->getUser().loggingName+".alert";
    QFile file(filename);

    if (!(QFile::exists(filename))) {
        qDebug()<<filename+"文件不存在";
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        //stream.setCodec(code);
        QString line;
        while(stream.atEnd()==0) {
            line = stream.readLine(); // 不包括“\n”的一行文本
            _already_read_list += line;
        }
        file.close();
    }
    qDebug()<< "从文件读取已读的消息: ";
    for (int i=0; i<_already_read_list.length() ; i++) {
        qDebug()<< _already_read_list.at(i)+"\n";
    }
}

void NewsAlertDialog::saveFile()
{
    QString filename = Singleton::GetInstance()->getUser().loggingName+".alert";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        //stream.setCodec(code);//输出流的设置--------必须嘀
        qDebug()<<"有"+QString::number(_already_read_list.length())+"条已读消息";
        for (int i=0; i<_already_read_list.length(); ++i) {
            stream << _already_read_list.at(i) << "\n";
            qDebug()<< "写入记录:" +  _already_read_list.at(i);
        }
        file.close();
        qDebug()<<"已读消息写入文件成功";
    } 
}

void NewsAlertDialog::reset()
{
    ui->txt_count->setText("共有: 0 条未读消息");
    ui->txt_title->setText("");
    _news_list.clear();             //未读消息（包含详细信息）
    _already_read_list.clear();     //已读消息的Id
}

void NewsAlertDialog::testShow()
{

    qDebug()<< "判断是否显示消息提示框，共有: "+QString::number(_news_list.length())+" 条未读消息";
    if (_news_list.length() >0) {
        this->show();
        ui->txt_count->setText("共有: "+QString::number(_news_list.length())+" 条未读消息");
        AlertNews alertNews = (AlertNews)_news_list.first();
        ui->txt_title->setText(alertNews.content);
    } else {
        saveFile();
        this->hide();
    }
    qDebug()<<"判断结束";
}

/*
void NewsAlertDialog::changeAlert()
{
    for (int i=0; i<showAlertNewsDialog->_data.length(); ++i) {
        if (showAlertNewsDialog->_data.at(i).isRead == true) {
            //记录下已读消息
            _already_read_list += showAlertNewsDialog->_data.at(i).id;

            //删除已经被阅读的数据
            for (int j = 0; j<_news_list.length(); ++j) {
                if (_news_list.at(j).id == showAlertNewsDialog->_data.at(i).id) {
                      _news_list.removeAt(j);
                }
            }
        }
    }
    testShow();
}
*/

void NewsAlertDialog::changeEvent(QEvent *e)
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

void NewsAlertDialog::on_btnShow_clicked()
{
    QString title = _news_list.first().title;
    QString date = _news_list.first().date;
    QString content = _news_list.first().content;
    noticeDialog->init(title, date, content);
    noticeDialog->show();

    //记录下已读消息
    _already_read_list += _news_list.first().id;
    //qDebug()<< "记录:" + _already_read_list.back();
    //清空已查看的消息
    _news_list.removeFirst();
    testShow();
}
