/********************************************************************************
** Form generated from reading UI file 'registerbox.ui'
**
** Created: Sun Apr 15 14:38:01 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERBOX_H
#define UI_REGISTERBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterBox
{
public:
    QLabel *label_14;
    QLabel *txtPswAlert;
    QPushButton *btnSubmit;
    QLabel *label_10;
    QLabel *label_15;
    QPushButton *btnReset;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *txiUsername;
    QLabel *label_2;
    QLineEdit *txiPassword;
    QLabel *label_3;
    QLineEdit *txiRePassword;
    QLabel *label_4;
    QLineEdit *txiMac;
    QLabel *label_5;
    QLineEdit *txiAdrTel;
    QLabel *label_6;
    QLineEdit *txiAddress;
    QLabel *label_7;
    QLineEdit *txiShopName;
    QLabel *label_8;
    QLineEdit *txiMobilePhone;
    QLabel *label_9;
    QLineEdit *txiIdentityNo;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *txiAcountTail;
    QLabel *label_13;
    QLineEdit *lineEdit;
    QLabel *label_17;
    QLineEdit *txiRealName;
    QComboBox *cbxWorkList;

    void setupUi(QDialog *RegisterBox)
    {
        if (RegisterBox->objectName().isEmpty())
            RegisterBox->setObjectName(QString::fromUtf8("RegisterBox"));
        RegisterBox->resize(640, 480);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/images/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        RegisterBox->setWindowIcon(icon);
        label_14 = new QLabel(RegisterBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(220, 10, 141, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(20);
        label_14->setFont(font);
        txtPswAlert = new QLabel(RegisterBox);
        txtPswAlert->setObjectName(QString::fromUtf8("txtPswAlert"));
        txtPswAlert->setGeometry(QRect(470, 115, 141, 16));
        txtPswAlert->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        btnSubmit = new QPushButton(RegisterBox);
        btnSubmit->setObjectName(QString::fromUtf8("btnSubmit"));
        btnSubmit->setGeometry(QRect(290, 440, 75, 23));
        label_10 = new QLabel(RegisterBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(470, 145, 111, 16));
        label_15 = new QLabel(RegisterBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(470, 355, 111, 16));
        btnReset = new QPushButton(RegisterBox);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        btnReset->setGeometry(QRect(380, 440, 75, 23));
        formLayoutWidget = new QWidget(RegisterBox);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(120, 50, 341, 382));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setHorizontalSpacing(6);
        formLayout->setVerticalSpacing(10);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        txiUsername = new QLineEdit(formLayoutWidget);
        txiUsername->setObjectName(QString::fromUtf8("txiUsername"));
        txiUsername->setMinimumSize(QSize(0, 20));
        txiUsername->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(0, QFormLayout::FieldRole, txiUsername);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        txiPassword = new QLineEdit(formLayoutWidget);
        txiPassword->setObjectName(QString::fromUtf8("txiPassword"));
        txiPassword->setMinimumSize(QSize(0, 20));
        txiPassword->setMaximumSize(QSize(16777215, 20));
        txiPassword->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, txiPassword);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        txiRePassword = new QLineEdit(formLayoutWidget);
        txiRePassword->setObjectName(QString::fromUtf8("txiRePassword"));
        txiRePassword->setMinimumSize(QSize(0, 20));
        txiRePassword->setMaximumSize(QSize(16777215, 20));
        txiRePassword->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, txiRePassword);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        txiMac = new QLineEdit(formLayoutWidget);
        txiMac->setObjectName(QString::fromUtf8("txiMac"));
        txiMac->setMinimumSize(QSize(0, 20));
        txiMac->setMaximumSize(QSize(16777215, 20));
        txiMac->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, txiMac);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        txiAdrTel = new QLineEdit(formLayoutWidget);
        txiAdrTel->setObjectName(QString::fromUtf8("txiAdrTel"));
        txiAdrTel->setMinimumSize(QSize(0, 20));
        txiAdrTel->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(4, QFormLayout::FieldRole, txiAdrTel);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        txiAddress = new QLineEdit(formLayoutWidget);
        txiAddress->setObjectName(QString::fromUtf8("txiAddress"));
        txiAddress->setMinimumSize(QSize(0, 20));
        txiAddress->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(5, QFormLayout::FieldRole, txiAddress);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        txiShopName = new QLineEdit(formLayoutWidget);
        txiShopName->setObjectName(QString::fromUtf8("txiShopName"));
        txiShopName->setMinimumSize(QSize(0, 20));
        txiShopName->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(6, QFormLayout::FieldRole, txiShopName);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_8);

        txiMobilePhone = new QLineEdit(formLayoutWidget);
        txiMobilePhone->setObjectName(QString::fromUtf8("txiMobilePhone"));
        txiMobilePhone->setMinimumSize(QSize(0, 20));
        txiMobilePhone->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(8, QFormLayout::FieldRole, txiMobilePhone);

        label_9 = new QLabel(formLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_9);

        txiIdentityNo = new QLineEdit(formLayoutWidget);
        txiIdentityNo->setObjectName(QString::fromUtf8("txiIdentityNo"));
        txiIdentityNo->setMinimumSize(QSize(0, 20));
        txiIdentityNo->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(9, QFormLayout::FieldRole, txiIdentityNo);

        label_11 = new QLabel(formLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(10, QFormLayout::LabelRole, label_11);

        label_12 = new QLabel(formLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_12);

        txiAcountTail = new QLineEdit(formLayoutWidget);
        txiAcountTail->setObjectName(QString::fromUtf8("txiAcountTail"));
        txiAcountTail->setMinimumSize(QSize(0, 20));
        txiAcountTail->setMaximumSize(QSize(16777215, 20));
        txiAcountTail->setReadOnly(true);

        formLayout->setWidget(11, QFormLayout::FieldRole, txiAcountTail);

        label_13 = new QLabel(formLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_13);

        lineEdit = new QLineEdit(formLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 20));
        lineEdit->setMaximumSize(QSize(16777215, 20));
        lineEdit->setReadOnly(true);

        formLayout->setWidget(12, QFormLayout::FieldRole, lineEdit);

        label_17 = new QLabel(formLayoutWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_17);

        txiRealName = new QLineEdit(formLayoutWidget);
        txiRealName->setObjectName(QString::fromUtf8("txiRealName"));
        txiRealName->setMinimumSize(QSize(0, 20));
        txiRealName->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(7, QFormLayout::FieldRole, txiRealName);

        cbxWorkList = new QComboBox(formLayoutWidget);
        cbxWorkList->setObjectName(QString::fromUtf8("cbxWorkList"));
        cbxWorkList->setMinimumSize(QSize(0, 20));
        cbxWorkList->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(10, QFormLayout::FieldRole, cbxWorkList);

        QWidget::setTabOrder(txiUsername, txiPassword);
        QWidget::setTabOrder(txiPassword, txiRePassword);
        QWidget::setTabOrder(txiRePassword, txiMac);
        QWidget::setTabOrder(txiMac, txiAdrTel);
        QWidget::setTabOrder(txiAdrTel, txiAddress);
        QWidget::setTabOrder(txiAddress, txiShopName);
        QWidget::setTabOrder(txiShopName, txiRealName);
        QWidget::setTabOrder(txiRealName, txiMobilePhone);
        QWidget::setTabOrder(txiMobilePhone, txiIdentityNo);
        QWidget::setTabOrder(txiIdentityNo, txiAcountTail);
        QWidget::setTabOrder(txiAcountTail, lineEdit);
        QWidget::setTabOrder(lineEdit, btnSubmit);
        QWidget::setTabOrder(btnSubmit, btnReset);

        retranslateUi(RegisterBox);

        QMetaObject::connectSlotsByName(RegisterBox);
    } // setupUi

    void retranslateUi(QDialog *RegisterBox)
    {
        RegisterBox->setWindowTitle(QApplication::translate("RegisterBox", "\346\226\260\347\224\250\346\210\267\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("RegisterBox", "\346\226\260\347\224\250\346\210\267\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        txtPswAlert->setText(QString());
        btnSubmit->setText(QApplication::translate("RegisterBox", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("RegisterBox", "\351\273\230\350\256\244\346\230\276\347\244\272\346\234\254\346\234\272\347\232\204MAC", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("RegisterBox", "\345\217\257\351\200\211\351\241\271", 0, QApplication::UnicodeUTF8));
        btnReset->setText(QApplication::translate("RegisterBox", "\351\207\215\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RegisterBox", "\347\231\273\345\275\225\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        txiUsername->setText(QString());
        label_2->setText(QApplication::translate("RegisterBox", "\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RegisterBox", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("RegisterBox", "MAC\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("RegisterBox", "\345\233\272\345\256\232\347\224\265\350\257\235\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("RegisterBox", "\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("RegisterBox", "\345\272\227\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("RegisterBox", "\346\211\213\346\234\272\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("RegisterBox", "\350\272\253\344\273\275\350\257\201\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("RegisterBox", "\344\270\232\345\212\241\350\264\237\350\264\243\344\272\272\357\274\232", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("RegisterBox", "\345\255\230\346\254\276\345\260\276\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("RegisterBox", "\347\224\250\346\210\267\347\272\247\345\210\253\357\274\232", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("RegisterBox", "\345\210\235\347\272\247\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("RegisterBox", "\347\234\237\345\256\236\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RegisterBox: public Ui_RegisterBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERBOX_H
