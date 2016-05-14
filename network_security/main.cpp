#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QString>
#include <QTextCodec>
#include "NetSecurity.h"

using namespace std;


int main(int argc, char *argv[])
{
    //�����������
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));


    QCoreApplication a(argc, argv);

    QString src = "this is a test";
    QString result = "";

    qDebug()<<"�������ݣ�"+src;
    string tmp = NetSecurity::encrypt(src);
    qDebug()<<"���ܺ�"+QString::fromStdString(tmp);
    result = NetSecurity::decrypt(tmp);

    if(result==src)
    {
        qDebug()<<"���ܳɹ������ܺ���ַ�����"+result;
    }
    else
    {
        qDebug()<<"������󣬽���ʧ�ܣ�";
    }
    return a.exec();
}
