#include "newsalertdialog.h"
#include "ui_newsalertdialog.h"
#include "singleton.h"

NewsAlertDialog::NewsAlertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewsAlertDialog)
{
    ui->setupUi(this);

    _news_list.clear();        //δ����Ϣ��������ϸ��Ϣ��
    _already_read_list.clear();     //�Ѷ���Ϣ��Id

    //�����Ѷ���Ϣ
    readFile();

    //������Ϣ��ʾ����
    noticeDialog = new NoticeDialog(this);

}

NewsAlertDialog::~NewsAlertDialog()
{
    delete ui;
}

void NewsAlertDialog::readFile()
{
    //reset();
    _news_list.clear();             //δ����Ϣ��������ϸ��Ϣ��
    _already_read_list.clear();     //�Ѷ���Ϣ��Id

    QString filename = Singleton::GetInstance()->getUser().loggingName+".alert";
    QFile file(filename);

    if (!(QFile::exists(filename))) {
        qDebug()<<filename+"�ļ�������";
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        //stream.setCodec(code);
        QString line;
        while(stream.atEnd()==0) {
            line = stream.readLine(); // ��������\n����һ���ı�
            _already_read_list += line;
        }
        file.close();
    }
    qDebug()<< "���ļ���ȡ�Ѷ�����Ϣ: ";
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
        //stream.setCodec(code);//�����������--------������
        qDebug()<<"��"+QString::number(_already_read_list.length())+"���Ѷ���Ϣ";
        for (int i=0; i<_already_read_list.length(); ++i) {
            stream << _already_read_list.at(i) << "\n";
            qDebug()<< "д���¼:" +  _already_read_list.at(i);
        }
        file.close();
        qDebug()<<"�Ѷ���Ϣд���ļ��ɹ�";
    } 
}

void NewsAlertDialog::reset()
{
    ui->txt_count->setText("����: 0 ��δ����Ϣ");
    ui->txt_title->setText("");
    _news_list.clear();             //δ����Ϣ��������ϸ��Ϣ��
    _already_read_list.clear();     //�Ѷ���Ϣ��Id
}

void NewsAlertDialog::testShow()
{

    qDebug()<< "�ж��Ƿ���ʾ��Ϣ��ʾ�򣬹���: "+QString::number(_news_list.length())+" ��δ����Ϣ";
    if (_news_list.length() >0) {
        this->show();
        ui->txt_count->setText("����: "+QString::number(_news_list.length())+" ��δ����Ϣ");
        AlertNews alertNews = (AlertNews)_news_list.first();
        ui->txt_title->setText(alertNews.content);
    } else {
        saveFile();
        this->hide();
    }
    qDebug()<<"�жϽ���";
}

/*
void NewsAlertDialog::changeAlert()
{
    for (int i=0; i<showAlertNewsDialog->_data.length(); ++i) {
        if (showAlertNewsDialog->_data.at(i).isRead == true) {
            //��¼���Ѷ���Ϣ
            _already_read_list += showAlertNewsDialog->_data.at(i).id;

            //ɾ���Ѿ����Ķ�������
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

    //��¼���Ѷ���Ϣ
    _already_read_list += _news_list.first().id;
    //qDebug()<< "��¼:" + _already_read_list.back();
    //����Ѳ鿴����Ϣ
    _news_list.removeFirst();
    testShow();
}
