#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

class Config
{
private:
    Config();//ע��:���췽��˽��
    virtual ~Config();
    static Config* instance;//Ωһʵ��
    QString _version;   //�汾���ַ���
    QString _sversion;  //�������汾��

public:
    static Config* GetInstance();//��������(�������ʵ��)
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
