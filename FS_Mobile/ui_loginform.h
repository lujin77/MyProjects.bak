/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created: Sun Apr 15 14:37:59 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:
    QLineEdit *txiUsername;
    QLineEdit *txiPassword;
    QPushButton *btnLogin;
    QPushButton *btnLoginCancle;
    QLineEdit *txiMAC;
    QPushButton *btnRegister;
    QGroupBox *groupBox;
    QRadioButton *rdo_save;
    QRadioButton *rdo_unsave;
    QLabel *txtTitle;
    QLabel *txt_version;

    void setupUi(QWidget *LoginForm)
    {
        if (LoginForm->objectName().isEmpty())
            LoginForm->setObjectName(QString::fromUtf8("LoginForm"));
        LoginForm->resize(858, 459);
        LoginForm->setMinimumSize(QSize(858, 459));
        LoginForm->setMaximumSize(QSize(858, 459));
        LoginForm->setStyleSheet(QString::fromUtf8(""));
        txiUsername = new QLineEdit(LoginForm);
        txiUsername->setObjectName(QString::fromUtf8("txiUsername"));
        txiUsername->setGeometry(QRect(510, 203, 161, 25));
        txiUsername->setMinimumSize(QSize(0, 25));
        txiUsername->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(12);
        txiUsername->setFont(font);
        txiUsername->setMaxLength(16);
        txiPassword = new QLineEdit(LoginForm);
        txiPassword->setObjectName(QString::fromUtf8("txiPassword"));
        txiPassword->setGeometry(QRect(510, 238, 161, 25));
        txiPassword->setMinimumSize(QSize(0, 25));
        txiPassword->setMaximumSize(QSize(16777215, 25));
        txiPassword->setFont(font);
        txiPassword->setMaxLength(16);
        txiPassword->setEchoMode(QLineEdit::Password);
        btnLogin = new QPushButton(LoginForm);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(510, 320, 76, 30));
        btnLogin->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/login_btn.png);"));
        btnLoginCancle = new QPushButton(LoginForm);
        btnLoginCancle->setObjectName(QString::fromUtf8("btnLoginCancle"));
        btnLoginCancle->setGeometry(QRect(595, 320, 76, 30));
        btnLoginCancle->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/cancle_btn.png);"));
        txiMAC = new QLineEdit(LoginForm);
        txiMAC->setObjectName(QString::fromUtf8("txiMAC"));
        txiMAC->setGeometry(QRect(510, 275, 161, 25));
        txiMAC->setMinimumSize(QSize(0, 25));
        txiMAC->setMaximumSize(QSize(16777215, 25));
        txiMAC->setFont(font);
        txiMAC->setMaxLength(20);
        txiMAC->setEchoMode(QLineEdit::Normal);
        txiMAC->setReadOnly(true);
        btnRegister = new QPushButton(LoginForm);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));
        btnRegister->setGeometry(QRect(410, 320, 75, 31));
        groupBox = new QGroupBox(LoginForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(160, 340, 91, 41));
        rdo_save = new QRadioButton(groupBox);
        rdo_save->setObjectName(QString::fromUtf8("rdo_save"));
        rdo_save->setGeometry(QRect(10, 20, 41, 16));
        rdo_unsave = new QRadioButton(groupBox);
        rdo_unsave->setObjectName(QString::fromUtf8("rdo_unsave"));
        rdo_unsave->setGeometry(QRect(50, 20, 41, 16));
        rdo_unsave->setChecked(true);
        txtTitle = new QLabel(LoginForm);
        txtTitle->setObjectName(QString::fromUtf8("txtTitle"));
        txtTitle->setGeometry(QRect(380, 100, 301, 31));
        txtTitle->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);\n"
"color: rgb(255, 255, 255);\n"
"font: 24pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txtTitle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        txt_version = new QLabel(LoginForm);
        txt_version->setObjectName(QString::fromUtf8("txt_version"));
        txt_version->setGeometry(QRect(520, 370, 151, 20));
        txt_version->setAlignment(Qt::AlignCenter);
        QWidget::setTabOrder(txiUsername, txiPassword);
        QWidget::setTabOrder(txiPassword, txiMAC);
        QWidget::setTabOrder(txiMAC, btnLogin);
        QWidget::setTabOrder(btnLogin, btnLoginCancle);
        QWidget::setTabOrder(btnLoginCancle, btnRegister);

        retranslateUi(LoginForm);
        QObject::connect(btnLogin, SIGNAL(clicked()), LoginForm, SLOT(logging()));
        QObject::connect(btnLoginCancle, SIGNAL(clicked()), LoginForm, SLOT(reset()));
        QObject::connect(btnRegister, SIGNAL(clicked()), LoginForm, SLOT(showRegisterBox()));

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QWidget *LoginForm)
    {
        LoginForm->setWindowTitle(QApplication::translate("LoginForm", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txiUsername->setToolTip(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        txiUsername->setStatusTip(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        txiUsername->setWhatsThis(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        txiPassword->setToolTip(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        txiPassword->setStatusTip(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        txiPassword->setWhatsThis(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        btnLogin->setToolTip(QApplication::translate("LoginForm", "\347\202\271\345\207\273\346\214\211\351\222\256\347\231\273\345\275\225\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btnLogin->setStatusTip(QApplication::translate("LoginForm", "\347\202\271\345\207\273\346\214\211\351\222\256\347\231\273\345\275\225\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btnLogin->setWhatsThis(QApplication::translate("LoginForm", "\347\202\271\345\207\273\346\214\211\351\222\256\347\231\273\345\275\225\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btnLogin->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnLoginCancle->setToolTip(QApplication::translate("LoginForm", "\347\202\271\345\207\273\346\214\211\351\222\256\346\270\205\347\251\272\347\224\250\346\210\267\345\220\215\345\222\214\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btnLoginCancle->setStatusTip(QApplication::translate("LoginForm", "\347\202\271\345\207\273\346\214\211\351\222\256\346\270\205\347\251\272\347\224\250\346\210\267\345\220\215\345\222\214\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btnLoginCancle->setWhatsThis(QApplication::translate("LoginForm", "\347\202\271\345\207\273\346\214\211\351\222\256\346\270\205\347\251\272\347\224\250\346\210\267\345\220\215\345\222\214\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btnLoginCancle->setText(QString());
#ifndef QT_NO_TOOLTIP
        txiMAC->setToolTip(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        txiMAC->setStatusTip(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        txiMAC->setWhatsThis(QApplication::translate("LoginForm", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btnRegister->setText(QApplication::translate("LoginForm", "\346\226\260\347\224\250\346\210\267\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("LoginForm", "\350\256\260\344\275\217\345\257\206\347\240\201\357\274\237", 0, QApplication::UnicodeUTF8));
        rdo_save->setText(QApplication::translate("LoginForm", "\346\230\257", 0, QApplication::UnicodeUTF8));
        rdo_unsave->setText(QApplication::translate("LoginForm", "\345\220\246", 0, QApplication::UnicodeUTF8));
        txtTitle->setText(QApplication::translate("LoginForm", "\351\243\236\351\200\237\347\247\221\346\212\200", 0, QApplication::UnicodeUTF8));
        txt_version->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
