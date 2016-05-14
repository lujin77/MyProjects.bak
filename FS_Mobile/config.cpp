#include "config.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include <QMessageBox>
#include "singleton.h"
#include "EncryptUtil.h"
#include "QDebug"

Config::Config()
{
/*
    _client_type = "�ƶ��ͻ���";
    _sp = "�ƶ�";
    _loginTitle = "���ٿ��";
    _sysTitle = "���ٿ��ҵ��ƽ̨";
*/

    _client_type = "��ͨ���ſͻ���";
    _sp = "��ͨ����";
    _loginTitle = "�Ž��Ƽ����ٿ��";
    _sysTitle = "�Ž��Ƽ����ٿ��ҵ��ƽ̨";

    _version = "1.0.9";         //�汾���ַ���

    _sversion = "999.999.999";  //�������汾��,Ĭ�����

    _is_no_mac = true;         //�Ƿ��ǲ��ж�mac�İ汾
    _is_no_update = true;      //�Ƿ��ǲ������İ汾
}

Config::~Config()
{
    if(instance != NULL)
    {
        delete instance;
    }
}
//��ʼ����̬��Ա
//Singleton* Singleton::instance=new Singleton();
Config* Config::instance=NULL;

Config* Config::GetInstance()
{
 if(instance == NULL)
 {
  instance = new Config();
 }
 return instance;
}

int Config::isEnable()
{
    qDebug()<<"׼����֤����汾��...";
    if (_sversion == "999.999.999") {
        UtilFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);
        _ns1__GetClientVersion req;


        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        std::string clientType = NetSecurity::encrypt(_client_type);
        //qDebug()<<QString::fromStdString(clientType);
        strcpy(buffer1, clientType.data());
        req.clientType = buffer1;

       _ns1__GetClientVersionResponse res;
        qDebug()<<"��ȡ�������汾��";
        if (soap.__ns7__GetClientVersion(&req,&res) == SOAP_OK) {
            _sversion = QString::fromUtf8(res.GetClientVersionResult);
            qDebug()<<"�������汾�ţ�"+_sversion;
            if (_sversion == "") {
                _sversion = "999.999.999";
                return 2;
            }
        } else {
            qDebug()<<"���ӷ���������";
            return -1;
        }
    }

    QStringList list_s = _sversion.split(".");
    QStringList list_c = _version.split(".");

    //�汾�űȽϣ����ȱȽϸ�λ
    //qDebug()<<"1 c:"+list_c.at(0)+" s:"+list_s.at(0);
    if (list_c.at(0).toInt() < list_s.at(0).toInt()) {
        return 0;
    } else if (list_c.at(0).toInt() == list_s.at(0).toInt()){
        //qDebug()<<"2 c:"+list_c.at(1)+" s:"+list_s.at(1);
        if (list_c.at(1).toInt() < list_s.at(1).toInt()) {
            return 0;
        } else if (list_c.at(1).toInt() == list_s.at(1).toInt()){
            //qDebug()<<"3 c:"+list_c.at(2)+" s:"+list_s.at(2);
            if (list_c.at(2).toInt() < list_s.at(2).toInt()) {
                return 0;
            }
        }
    }


    return 1;
}

QString Config::getVersion() {
    return "�汾:"+_version;
}
