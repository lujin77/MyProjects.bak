#ifndef PRINTER_H
#define PRINTER_H

#include <QPrinter>
#include <QTextDocument>
#include <QThread>

//打印缴费记录
class Print_jf_Thread : public  QThread
{
    Q_OBJECT
public:
    QString currentPaymentCondition;
    Print_jf_Thread();
protected:
    void run();
};

class Printer
{
private:
    Printer();//注意:构造方法私有
    virtual ~Printer();
    static Printer* instance;//惟一实例
    Print_jf_Thread *_print_jf_Thread;
    QString getLogoURL();

public:
    static Printer* GetInstance();//工厂方法(用来获得实例)

    void printJF(QString condition);
    void printJF(QString shop_name, QString tel, QString location, QString name,
                 QString brand, QString before_money, QString pay_money,
                 QString after_money, QString state, QString datetime);

    void printGame(QString condition);
    void printGame(QString shop_name, QString game_type, QString game_account,
                    QString charge_money, QString state, QString datetime);

    void printInternet(QString condition);
    void printInternet(QString shop_name, QString internet_type, QString internet_account,
                    QString charge_money, QString state, QString datetime);

    void printPublicTel(QString condition);
    void printPublicTel(QString shop_name, QString tel_type, QString tel_account,
                    QString charge_money, QString state, QString datetime);

    void printSellCard(QString condition);
    void printSellCard(QString shop_name, QString tel_no, QString brand,
                    QString price, QString state, QString datetime);

    void printDoBusiness(QString condition);
    void printDoBusiness(QString shop_name, QString tel_no, QString brand,
                    QString price, QString state, QString datetime);

    void printKlxs(QString condition);
    void printKlxs(QString shop_name, QString cardType, QString cardName,
                   QString seqNo, QString passwd, QString state, QString datetime);
};




#endif // PRINTER_H
