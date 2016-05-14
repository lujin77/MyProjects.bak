#include <QtGui/QApplication>
#include <QTextCodec>
#include <QPlastiqueStyle>
#include "mainwindow.h"
#include "navigatorform.h"
#include "gsoap/UtilFunctionWebServiceSoap.nsmap"
#include <QProcess>
#include "gsoap/stdsoap2.h"
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QTranslator>
#include "config.h"

int main(int argc, char *argv[])
{
    //�����������
    QApplication::addLibraryPath("./plugins");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    //������
    if (!Config::GetInstance()->_is_no_update) {
        QProcess *myProcess = new QProcess();
        myProcess->start("update.exe");
    }

    QApplication a(argc, argv);

    //���Ĳ˵�
    QTranslator translator(0);
    translator.load("qt_zh_CN.qm");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    a.setActiveWindow(&w);
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

    a.setStyle(new QPlastiqueStyle);
    //�ȼ�������Ƿ�����
//    QNetworkInterface localInterface;
//    int index = 0;
//    if (localInterface.allInterfaces().at(index).addressEntries().size() > 0) {
//        qDebug()<<"ip:"+localInterface.allInterfaces().at(index).addressEntries().first().ip().toString();
//    } else {
//        qDebug()<< "null point";
//    }

    return a.exec();
}
