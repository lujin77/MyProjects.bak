#ifndef PRINTER_H
#define PRINTER_H

#include <QPrinter>
#include <QTextDocument>
#include <QThread>

//��ӡ�ɷѼ�¼
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
    Printer();//ע��:���췽��˽��
    virtual ~Printer();
    static Printer* instance;//Ωһʵ��
    Print_jf_Thread *_print_jf_Thread;
    QString getLogoURL();

public:
    static Printer* GetInstance();//��������(�������ʵ��)

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
