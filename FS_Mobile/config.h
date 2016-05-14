#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

class Config
{
private:
    Config();//注意:构造方法私有
    virtual ~Config();
    static Config* instance;//惟一实例
    QString _version;   //版本号字符串
    QString _sversion;  //服务器版本号

public:
    static Config* GetInstance();//工厂方法(用来获得实例)
    int isEnable();
    QString getVersion();
    QString _client_type;
    QString _sp;
    QString _loginTitle;
    QString _sysTitle;
    bool _is_no_mac;
    bool _is_no_update;
};

#endif // CONFIG_H
