#include "loginform.h"
#include "ui_loginform.h"
#include <QBitmap>
#include <QMessageBox>
#include "gsoap/soapUserFunctionWebServiceSoapProxy.h"
#include "singleton.h"
#include <registerbox.h>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include "EncryptUtil.h"
#include "config.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    QNetworkInterface localInterface;
    QString MAC =localInterface.allInterfaces().first().hardwareAddress();
    ui->txiMAC->setText(MAC);
    if (localInterface.allInterfaces().first().addressEntries().size() >0) {
        if (!localInterface.allInterfaces().first().addressEntries().first().ip().isNull()) {
            _ip = localInterface.allInterfaces().first().addressEntries().first().ip().toString();
        }
    } else if (localInterface.allInterfaces().at(1).addressEntries().size() > 0) {
        if (!localInterface.allInterfaces().at(1).addressEntries().first().ip().isNull()) {
            _ip = localInterface.allInterfaces().at(1).addressEntries().first().ip().toString();
        }
    } else {
        _ip="127.0.0.1";
    }
    //QMessageBox::warning(this,tr("警告"),_ip,QMessageBox::Ok);
    QPixmap mypixmap1;
    mypixmap1.load("images/login_btn.png");
    ui->btnLogin->clearMask();
    ui->btnLogin->setBackgroundRole( QPalette::Base);
    ui->btnLogin->setFixedSize( mypixmap1.width(), mypixmap1.height() );
    ui->btnLogin->setMask(mypixmap1.createHeuristicMask());
    ui->btnLogin->setIcon(mypixmap1);
    ui->btnLogin->setIconSize(QSize(mypixmap1.width(),mypixmap1.height()));
    ui->btnLogin->setToolTip("登录");

    QPixmap mypixmap2;
    mypixmap2.load("images/cancle_btn.png");
    ui->btnLoginCancle->clearMask();
    ui->btnLoginCancle->setBackgroundRole( QPalette::Base);
    ui->btnLoginCancle->setFixedSize( mypixmap2.width(), mypixmap2.height() );
    ui->btnLoginCancle->setMask(mypixmap2.createHeuristicMask());
    ui->btnLoginCancle->setIcon(mypixmap2);
    ui->btnLoginCancle->setIconSize(QSize(mypixmap2.width(),mypixmap2.height()));
    ui->btnLoginCancle->setToolTip("取消");


    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
    QBrush(QPixmap("images/loginBox.png").scaled( // 缩放背景图.
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation))); // 使用平滑的缩放方式
    this->setPalette(palette); // 至此, 已给widget加上了背景图.

    //this->connect(ui->btnRegister, SIGNAL(clicked()), this, SLOT(on_btnRegister_clicked()));

    //读取保存密码
    readPsw();
    //设置标题
    ui->txtTitle->setText(Config::GetInstance()->_loginTitle);

    if (!Config::GetInstance()->_is_no_mac) {
        //显示当前版本号
        ui->txt_version->setText(Config::GetInstance()->getVersion());
    } else {
        ui->txt_version->setText(Config::GetInstance()->getVersion()+"(no mac)");
    }
}

LoginForm::~LoginForm()
{
    delete ui;
}

bool LoginForm::readPsw()
{
    if (!QFile::exists("info.dat")) {
        ui->rdo_save->setChecked(false);
        ui->rdo_unsave->setChecked(true);
        return false;
    }
    QFile file("info.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString name;
        QString password;
        name = stream.readLine();
        name = EncryptUtil::QDecrypKey(name, EncryptUtil::getKey().data());
        password = stream.readLine();
        password = EncryptUtil::QDecrypKey(password, EncryptUtil::getKey().data());
        file.close();
        ui->txiUsername->setText(name);
        ui->txiPassword->setText(password);
        ui->rdo_save->setChecked(true);
        ui->rdo_unsave->setChecked(false);
    } else {
        ui->rdo_save->setChecked(false);
        ui->rdo_unsave->setChecked(true);
        return false;
    }

}

bool LoginForm::savePsw()
{
    QFile file("info.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        QString name = ui->txiUsername->text();
        QString password = ui->txiPassword->text();
        name = EncryptUtil::QEncrypKey(name, EncryptUtil::getKey().data());
        stream<<name+"\n";
        password = EncryptUtil::QEncrypKey(password, EncryptUtil::getKey().data());
        stream<<password+"\n";
        file.close();
        ui->rdo_save->setChecked(true);
        ui->rdo_unsave->setChecked(false);
    } else {
        QMessageBox::warning(this,tr("警告"),tr("记住密码出错!"),QMessageBox::Ok);
        return false;
    }
}


void LoginForm::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case 16777220:
            logging();
            break;
    }
}


void LoginForm::logging()
{
    //对不更新版本特殊处理
    if (!Config::GetInstance()->_is_no_update) {
        if (Config::GetInstance()->isEnable() == -1) {
            QMessageBox::warning(this,tr("警告"),tr("服务器出错!请联系管理员"),QMessageBox::Ok);
            return;
        } else if (Config::GetInstance()->isEnable() == 0) {
            QMessageBox::warning(this,tr("警告"),tr("您当前的程序版本太老，请先升级!"),QMessageBox::Ok);
            return;
        } else if (Config::GetInstance()->isEnable() == 2) {
            QMessageBox::warning(this,tr("警告"),tr("版本号设置有误！请联系管理员"),QMessageBox::Ok);
            return;
        }
    }

    if(0 == ui->txiUsername->text().size() || 0 == ui->txiPassword->text().size()) {
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码不能为空!"),QMessageBox::Ok);
        ui->txiUsername->setFocus();
        return;
    }
    else {
        //升级临时使用
//        QMessageBox::warning(this,tr("警告"),tr("系统正在升级中!\n请于12点之后再登录，谢谢"),QMessageBox::Ok);
//        return;

        UserFunctionWebServiceSoap soap;
        soap_set_mode(soap.soap, SOAP_C_UTFSTRING);

        _ns1__TestLogin req;

        char buffer1[255];
        memset(buffer1,0,255*sizeof(char));
        string user_name = NetSecurity::encrypt(ui->txiUsername->text());
        qDebug()<<"加密后user_name："+QString::fromStdString(user_name);
        strcpy(buffer1, user_name.data());
        req.Username = buffer1;

        char buffer2[255];
        memset(buffer2,0,255*sizeof(char));
        string password = NetSecurity::encrypt(ui->txiPassword->text());
        qDebug()<<"加密后password："+QString::fromStdString(password);
        strcpy(buffer2, password.data());
        req.Password = buffer2;

        char buffer3[255];
        memset(buffer3,0,255*sizeof(char));
        string mac;
        //对no mac版本进行特殊处理
        if (Config::GetInstance()->_is_no_mac) {
            mac = NetSecurity::encrypt(QString("no_mac"));
        } else {
            mac = NetSecurity::encrypt(ui->txiMAC->text());
        }
        qDebug()<<"加密后Mac："+QString::fromStdString(mac);
        strcpy(buffer3, mac.data());
        req.Mac = buffer3;

        char buffer4[255];
        memset(buffer4,0,255*sizeof(char));
        string ip = NetSecurity::encrypt(_ip);
        qDebug()<<"加密后ip："+QString::fromStdString(ip);
        strcpy(buffer4, ip.data());
        req.ip = buffer4;

        char buffer5[255];
        memset(buffer5,0,255*sizeof(char));
        string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
        qDebug()<<"加密后客户端类型："+QString::fromStdString(clientType);
        strcpy(buffer5, clientType.data());
        req.clientType = buffer5;

        _ns1__TestLoginResponse res;
        this->setCursor(Qt::BusyCursor);
        ui->btnLogin->setEnabled(false);
        if (soap.__ns5__TestLogin(&req,&res) == SOAP_OK) {
            QString str = QString::fromUtf8(res.TestLoginResult);
            if (str != "账户尚未通过审核！请等待..." && str != "用户名或密码错误" && str != "该账户已经被登录！请不要重复登录") {
                //加密获取到的session
                //qDebug()<<"原始session:"+str;
                string session = NetSecurity::encrypt(str);
                //qDebug()<<"加密后session:"+QString::fromStdString(session);
                Singleton::GetInstance()->session_id = QString::fromStdString(session);
                //获取用户详细信息
                _ns1__GetUserInfo req1;
                char buffer1[255];
                memset(buffer1,0,255*sizeof(char));
                string username = NetSecurity::encrypt(ui->txiUsername->text());
                qDebug()<<"username："+QString::fromStdString(username);
                strcpy(buffer1, username.data());
                req1.username = buffer1;

                char buffer2[255];
                memset(buffer2,0,255*sizeof(char));
                string password = NetSecurity::encrypt(ui->txiPassword->text());
                qDebug()<<"password："+QString::fromStdString(password);
                strcpy(buffer2, password.data());
                req1.password = buffer2;

                char buffer3[255];
                memset(buffer3,0,255*sizeof(char));
                qDebug()<<"sessionId："+Singleton::GetInstance()->session_id;
                strcpy(buffer3, Singleton::GetInstance()->session_id.toUtf8().data());
                req1.sessionId = buffer3;

                char buffer4[255];
                memset(buffer4,0,255*sizeof(char));
                string clientType = NetSecurity::encrypt(Config::GetInstance()->_client_type);
                qDebug()<<"clientType："+QString::fromStdString(clientType);
                strcpy(buffer4, clientType.data());
                req1.clientType = buffer4;

                _ns1__GetUserInfoResponse res1;
                if (soap.__ns5__GetUserInfo(&req1,&res1) == SOAP_OK) {

                   ns1__User *soap_user = res1.GetUserInfoResult;

                   UserVO userVO;
                   //加密获取到的userId
                   userVO.Id = QString::fromUtf8(soap_user->Id);
                   userVO.loggingName = QString::fromUtf8(soap_user->loggingName);
                   userVO.password = QString::fromUtf8(soap_user->password);
                   userVO.money = soap_user->money;
                   userVO.tel = QString::fromUtf8(soap_user->tel);
                   userVO.mac = QString::fromUtf8(soap_user->mac);
                   userVO.address = QString::fromUtf8(soap_user->address);
                   userVO.shopName = QString::fromUtf8(soap_user->shopName);
                   userVO.mobilePhone = QString::fromUtf8(soap_user->mobilePhone);
                   userVO.pingying = QString::fromUtf8(soap_user->pingying);
                   userVO.realName = QString::fromUtf8(soap_user->realName);
                   userVO.indentityNo = QString::fromUtf8(soap_user->indentityNo);
                   userVO.manager_id = QString::fromUtf8(soap_user->manager_USCOREid);
                   userVO.managerName = QString::fromUtf8(soap_user->managerName);
                   userVO.moneyTail = QString::fromUtf8(soap_user->moneyTail);
                   userVO.level = QString::fromUtf8(soap_user->level);
                   userVO.registerDatetime = soap_user->registerDatetime;
                   userVO.isValidate = soap_user->isValidate;
                   userVO.btnList = QString::fromUtf8(soap_user->btnList);
                   Singleton::GetInstance()->setUser(userVO);

                } else {
                    QMessageBox::warning(this,tr("警告"),tr("获取个人信息出错！请联系管理员"),QMessageBox::Ok);
                    return;
                }
                //判断是否记住密码
                if (ui->rdo_save->isChecked() == true) {
                    savePsw();
                } else {
                    if (QFile::exists("info.dat")) QFile::remove("info.dat");
                    //清空，跳转
                    ui->txiUsername->clear();
                    ui->txiPassword->clear();
                }
                emit loggingSuccess();
            } else {
                ui->txiUsername->setFocus();
                ui->txiPassword->clear();
                QMessageBox::warning(this,tr("结果"),str,QMessageBox::Ok);
            }
        } else {
            QMessageBox::warning(this,tr("警告"),"服务器出错！请联系管理员",QMessageBox::Ok);
        }
        this->setCursor(Qt::ArrowCursor);
        ui->btnLogin->setEnabled(true);
        /*
        if(str != NULL) {
            ui->txiUsername->clear();
            ui->txiPassword->clear();
            Singleton::GetInstance()->setVar(str);
            emit loggingSuccess();
        } else {
            QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Ok);
            ui->txiUsername->setFocus();
            ui->txiPassword->clear();
        }
        */
            /*
                if("test" == ui->txiUsername->text() && "123" == ui->txiPassword->text()) {
                    ui->txiUsername->clear();
                    ui->txiPassword->clear();
                    emit loggingSuccess();
                }
                else {
                    QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Ok);
                    ui->txiUsername->setFocus();
                    ui->txiPassword->clear();
                }
            */
    }
}

void LoginForm::reset()
{
    ui->txiUsername->clear();
    ui->txiPassword->clear();
}

void LoginForm::showRegisterBox()
{
    RegisterBox registerBox(this);
    registerBox.exec();
}
