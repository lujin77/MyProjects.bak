#include "singleton.h"

//构造方法实现
Singleton::Singleton()
{
    clear();
    //cout<<"Singleton Constructor"<<endl;
}

Singleton::~Singleton()
{
    if(instance != NULL)
    {
        delete instance;
    }
}
//初始化静态成员
//Singleton* Singleton::instance=new Singleton();
Singleton* Singleton::instance=NULL;
Singleton* Singleton::GetInstance()
{
 if(instance == NULL)
 {
  instance = new Singleton();
 }
 return instance;
}
//seter && getter含数
UserVO Singleton::getUser()
{
    return _user;
}
void Singleton::setUser(UserVO user)
{
    _user.Id = user.Id;
    _user.loggingName = user.loggingName;
    _user.password = user.password;
    _user.money = user.money;
    _user.tel = user.tel;
    _user.mac = user.mac;
    _user.address = user.address;
    _user.shopName = user.shopName;
    _user.mobilePhone = user.mobilePhone;
    _user.pingying = user.pingying;
    _user.realName = user.realName;
    _user.indentityNo = user.indentityNo;
    _user.manager_id = user.manager_id;
    _user.managerName = user.managerName;
    _user.moneyTail = user.moneyTail;
    _user.level = user.level;
    _user.registerDatetime = user.registerDatetime;
    _user.isValidate = user.isValidate;
    _user.btnList = user.btnList;
}

void Singleton::setUser(UserVO *user)
{
    _user.Id = user->Id;
    _user.loggingName = user->loggingName;
    _user.password = user->password;
    _user.money = user->money;
    _user.tel = user->tel;
    _user.mac = user->mac;
    _user.address = user->address;
    _user.shopName = user->shopName;
    _user.mobilePhone = user->mobilePhone;
    _user.pingying = user->pingying;
    _user.realName = user->realName;
    _user.indentityNo = user->indentityNo;
    _user.manager_id = user->manager_id;
    _user.managerName = user->managerName;
    _user.moneyTail = user->moneyTail;
    _user.level = user->level;
    _user.registerDatetime = user->registerDatetime;
    _user.isValidate = user->isValidate;
    _user.btnList = user->btnList;
}

void Singleton::clear()
{
    //清空user信息
    _user.Id = "";
    _user.loggingName = "";
    _user.password = "";
    _user.money = 0;
    _user.tel = "";
    _user.mac = "";
    _user.address = "";
    _user.shopName = "";
    _user.mobilePhone = "";
    _user.pingying = "";
    _user.realName = "";
    _user.indentityNo = "";
    _user.manager_id = "";
    _user.managerName = "";
    _user.moneyTail = "";
    _user.level = "";
    _user.registerDatetime = 0;
    _user.isValidate = false;
    _user.btnList = "";
    //清空session
    session_id = "";
}
