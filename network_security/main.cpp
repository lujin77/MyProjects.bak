#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QString>
#include <QTextCodec>
#include "NetSecurity.h"

using namespace std;


int main(int argc, char *argv[])
{
    //解决中文乱码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));


    QCoreApplication a(argc, argv);

    QString src = "this is a test";
    QString result = "";

    qDebug()<<"加密数据："+src;
    string tmp = NetSecurity::encrypt(src);
    qDebug()<<"加密后："+QString::fromStdString(tmp);
    result = NetSecurity::decrypt(tmp);

    if(result==src)
    {
        qDebug()<<"解密成功，解密后的字符串："+result;
    }
    else
    {
        qDebug()<<"密码错误，解密失败！";
    }
    return a.exec();
}
