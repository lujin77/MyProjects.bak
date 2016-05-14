#ifndef ENCRYPTUITL_H
#define ENCRYPTUITL_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <QDebug>
#include <QTextCodec>
#include <QString>

using namespace std;

class EncryptUtil
{
public:
    //Qt加密
    QString static QEncrypKey(QString src,  const char* key)
    {
        QByteArray a = src.toLocal8Bit().toBase64();
        QString newStr(a);
        std::string encrypt_str = EncrypKey(a.data(), key);
        qDebug()<<"加密前:"+src+" | 加密后:"+QString::fromStdString(encrypt_str);
        return QString::fromStdString(encrypt_str);
    }

    //Qt解密
    QString static QDecrypKey(QString src,  const char* key)
    {
        std::string decrypt_str = UncrypKey(src.toStdString().data(), key);
        qDebug()<<"解密前:"+ src +" | 解密后:"+QString::fromStdString(decrypt_str);
        QString result = QTextCodec::codecForName("GBK")->toUnicode(QByteArray::fromBase64(QString::fromStdString(decrypt_str).toLocal8Bit()));
        return result;
    }

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

private:
    static char* substr(const char* _str, int pos, int len)
    {
        static char ptr[10];

        memcpy(ptr, _str+pos-1, len);
        ptr[len] = '\0';

        return ptr;
    }

    //加密函数
    std::string static EncrypKey(const char* src,  const char* key)
    {
        int KeyPos = -1;
        int SrcPos = 0;
        int SrcAsc = 0;
        time_t t;

        int KeyLen = strlen(key);
        if(KeyLen == 0)
              return "";

        srand((unsigned) time(&t));
        int offset = rand() % 255;

        char buff[3];
        sprintf(buff, "%1.2x", offset);
        std::string dest = buff;

        for(int i = 0; i < strlen(src); i++)
        {
            SrcAsc = (src[i] + offset) % 255;

            if (KeyPos < KeyLen-1)
                KeyPos++;
            else
                KeyPos = 0;

            SrcAsc = SrcAsc ^ key[KeyPos];

            memset(buff, 0, sizeof(buff));
            sprintf(buff, "%1.2x", SrcAsc);
            dest = dest + (std::string)buff;

            offset = SrcAsc;
        }
        return dest;
    }


    //解密函数
    std::string static UncrypKey(const char* src, const char* key)
    {
        int KeyLen = strlen(key);
        if(KeyLen == 0)
            return "";

        int KeyPos = -1;
        int offset = 0;
        std::string dest = "";
        int SrcPos = 0;
        int SrcAsc = 0;
        int TmpSrcAsc = 0;

        char buff[5];
        sprintf(buff, "0x%s", substr(src, 1, 2));
        sscanf(buff, "%x", &offset);
        SrcPos = 3;
        while(SrcPos <= strlen(src))
        {
            sprintf(buff, "0x%s", substr(src, SrcPos, 2));
            sscanf(buff, "%x", &SrcAsc);
            if (KeyPos < KeyLen-1)
                KeyPos++;
            else
                KeyPos = 0;

            TmpSrcAsc = SrcAsc ^ key[KeyPos];

            if (TmpSrcAsc <= offset)
                TmpSrcAsc = 255 + TmpSrcAsc - offset;
            else
                TmpSrcAsc = TmpSrcAsc - offset;

            dest += char(TmpSrcAsc);
            offset = SrcAsc;
            SrcPos = SrcPos + 2;
        }

        return dest;
    }

};

class NetSecurity
{
public:
    string static getKey() {
        //默认密钥
        string key = "6F5EDFF6C1AE490FA3650920BA611D2E";
        for(int k=0;k<key.size();++k)
        {
            key[k]=key[k]%10;
        }
        return key;
    }

    string static encrypt(QString src) {
        string encrypt_data, key;
        key = getKey();
        int j=0;
        encrypt_data = src.toUtf8().toBase64().data();
        for(int i=0;i<encrypt_data.size();++i)
        {

//            encrypt_data[i]+=key[j]-'0';
//            if(encrypt_data[i]>122)
//            {
//                encrypt_data[i]=encrypt_data[i]%122+32;
//            }
            //encrypt_data[i] = (char)(encrypt_data[i]^key[j]);
            encrypt_data[i] = (char)(encrypt_data[i]-key[j]);
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
//            src[i]-=key[j]-'0';
//            if(src[i]<32)
//            {
//                src[i]=src[i]+122-32;
//            }
            //src[i] = (char)(src[i]^key[j]);
            src[i] = (char)(src[i]+key[j]);
            ++j;
            if(j==key.size())
            {
                j=0;
            }
        }
        qDebug()<<"还原后:"+QString::fromStdString(src);
        decrypt_data = QTextCodec::codecForName("UTF8")->toUnicode(QByteArray::fromBase64(src.data()));
        return  decrypt_data;
    }
};

#endif // ENCRYPTUITL_H
