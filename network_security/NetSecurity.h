#ifndef NETSECUR_H
#define NETSECUR_H

#include <QString>
#include "QDebug"

using namespace std;

class NetSecurity
{
public:
    string static getKey() {
        //默认密钥
        string key = "<QTextCodec>";
        //qDebug()<<"init key:"+QString::fromStdString(key);
        for(int k=0;k<key.size();++k)
        {
            key[k]=key[k]-10;
        }
        //qDebug()<<"real key:"+QString::fromStdString(key);
        return key;
    }

    string static encrypt(QString src) {
        string encrypt_data, key;
        key = getKey();
        int j=0;
        encrypt_data = src.toLocal8Bit().toBase64().data();
        qDebug()<<"转化后:"+QString::fromStdString(encrypt_data);
        for(int i=0;i<encrypt_data.size();++i)
        {
            //qDebug()<<QString(encrypt_data[i])+" "+QString(key[j]);;
            encrypt_data[i]+=key[j]-'0';
            //qDebug()<<QString(encrypt_data[i]);
            if(encrypt_data[i]>122)
            {
                encrypt_data[i]=encrypt_data[i]%122+32;
            }
            ++j;
            if(j==key.size())
            {
                j=0;
            }
        }
        return encrypt_data;
    }

    QString static decrypt(string src) {
        QString decrypt_data = "";
        string key = getKey();
        for(int i=0,j=0;i<src.size();++i)
        {
            src[i]-=key[j]-'0';
            if(src[i]<32)
            {
                src[i]=src[i]+122-32;
            }
            ++j;
            if(j==key.size())
            {
                j=0;
            }
        }
        qDebug()<<QString::fromStdString(src);
        decrypt_data = QTextCodec::codecForName("GBK")->toUnicode(QByteArray::fromBase64(QString::fromStdString(src).toLocal8Bit()));
        return  decrypt_data;
    }
};

#endif // NETSECUR_H
