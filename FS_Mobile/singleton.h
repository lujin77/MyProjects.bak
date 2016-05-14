#ifndef UTIL_H
#define UTIL_H
#include <qstring>
#include <QSound>
class UserVO
{
public:
    QString Id;
    QString loggingName;
    QString password;
    double money;
    QString tel;
    QString mac;
    QString address;
    QString shopName;
    QString mobilePhone;
    QString pingying;
    QString realName;
    QString indentityNo;
    QString manager_id;
    QString managerName;
    QString moneyTail;
    QString level;
    time_t registerDatetime;
    bool isValidate;
    QString btnList;  //可以操作的功能按钮，名称之间用，号分隔
};

class Singleton
{
private:
    Singleton();//注意:构造方法私有
    virtual ~Singleton();
    static Singleton* instance;//惟一实例
    UserVO _user;//成员变量(用于测试)


public:
    static Singleton* GetInstance();//工厂方法(用来获得实例)
    UserVO getUser();//获得var的值
    void setUser(UserVO);//设置var的值
    void setUser(UserVO*);//设置var的值
    void clear();
    QString session_id;

};

class Util {
private:
    static char _buffer[255];
public:
    static inline char* QString2Char(QString str) {
        memset(_buffer,0,255*sizeof(char));
        strcpy(_buffer, str.toLatin1().data());
        return _buffer;
    }
};



#endif // UTIL_H
