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
    QString btnList;  //���Բ����Ĺ��ܰ�ť������֮���ã��ŷָ�
};

class Singleton
{
private:
    Singleton();//ע��:���췽��˽��
    virtual ~Singleton();
    static Singleton* instance;//Ωһʵ��
    UserVO _user;//��Ա����(���ڲ���)


public:
    static Singleton* GetInstance();//��������(�������ʵ��)
    UserVO getUser();//���var��ֵ
    void setUser(UserVO);//����var��ֵ
    void setUser(UserVO*);//����var��ֵ
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
