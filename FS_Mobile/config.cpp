#include "config.h"
#include "gsoap/soapUtilFunctionWebServiceSoapProxy.h"
#include <QMessageBox>
#include "singleton.h"
#include "EncryptUtil.h"
#include "QDebug"

Config::Config()
{
/*
    _client_type = "移动客户端";
    _sp = "移动";
    _loginTitle = "飞速快缴";
    _sysTitle = "飞速快缴业务平台";
*/

    _client_type = "联通电信客户端";
    _sp = "联通电信";
    _loginTitle = "优健科技飞速快缴";
    _sysTitle = "优健科技飞速快缴业务平台";

    _version = "1.0.9";         //版本号字符串

    _sversion = "999.999.999";  //服务器版本号,默认最大

    _is_no_mac = true;         //是否是不判断mac的版本
    _is_no_update = true;      //是否是不升级的版本
}

Config::~Config()
{
    if(instance != NULL)
    {
        delete instance;
    }
}
//初始化静态成员
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
    qDebug()<<"准备验证程序版本号...";
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
        qDebug()<<"提取服务器版本号";
        if (soap.__ns7__GetClientVersion(&req,&res) == SOAP_OK) {
            _sversion = QString::fromUtf8(res.GetClientVersionResult);
            qDebug()<<"服务器版本号："+_sversion;
            if (_sversion == "") {
                _sversion = "999.999.999";
                return 2;
            }
        } else {
            qDebug()<<"连接服务器出错";
            return -1;
        }
    }

    QStringList list_s = _sversion.split(".");
    QStringList list_c = _version.split(".");

    //版本号比较，优先比较高位
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
    return "版本:"+_version;
}
