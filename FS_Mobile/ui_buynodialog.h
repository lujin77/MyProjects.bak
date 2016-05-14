/********************************************************************************
** Form generated from reading UI file 'buynodialog.ui'
**
** Created: Sun Apr 15 14:38:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYNODIALOG_H
#define UI_BUYNODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuyNoDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *txt_No;
    QLabel *label_2;
    QComboBox *cbx_mini_card;
    QLabel *label_11;
    QLabel *label_3;
    QComboBox *cbx_service;
    QLabel *label_4;
    QTextEdit *txt_service_spec;
    QLabel *label_5;
    QLineEdit *txt_price;
    QLabel *label_6;
    QGroupBox *groupBox_ld;
    QRadioButton *rdo_ld_on;
    QRadioButton *rdo_ld_off;
    QLabel *label_7;
    QGroupBox *groupBox_cl;
    QRadioButton *rdo_cl_on;
    QRadioButton *rdo_cl_off;
    QLabel *label_8;
    QLineEdit *txi_name;
    QLabel *label_9;
    QComboBox *cbx_zjlx;
    QLabel *label_10;
    QLineEdit *txi_indentifyNo;
    QGroupBox *groupBox_ld_2;
    QRadioButton *rdo_service_type_on;
    QRadioButton *rdo_service_type_off;
    QPushButton *btn_submit;
    QPushButton *btn_close;

    void setupUi(QDialog *BuyNoDialog)
    {
        if (BuyNoDialog->objectName().isEmpty())
            BuyNoDialog->setObjectName(QString::fromUtf8("BuyNoDialog"));
        BuyNoDialog->resize(700, 650);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BuyNoDialog->sizePolicy().hasHeightForWidth());
        BuyNoDialog->setSizePolicy(sizePolicy);
        BuyNoDialog->setModal(true);
        formLayoutWidget = new QWidget(BuyNoDialog);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(30, 10, 643, 566));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(135, 0));
        label->setMaximumSize(QSize(135, 16777215));
        label->setSizeIncrement(QSize(10, 0));
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        txt_No = new QLineEdit(formLayoutWidget);
        txt_No->setObjectName(QString::fromUtf8("txt_No"));
        sizePolicy.setHeightForWidth(txt_No->sizePolicy().hasHeightForWidth());
        txt_No->setSizePolicy(sizePolicy);
        txt_No->setMinimumSize(QSize(500, 41));
        txt_No->setMaximumSize(QSize(500, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(20);
        txt_No->setFont(font);
        txt_No->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, txt_No);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(135, 0));
        label_2->setMaximumSize(QSize(135, 16777215));
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        cbx_mini_card = new QComboBox(formLayoutWidget);
        cbx_mini_card->setObjectName(QString::fromUtf8("cbx_mini_card"));
        sizePolicy.setHeightForWidth(cbx_mini_card->sizePolicy().hasHeightForWidth());
        cbx_mini_card->setSizePolicy(sizePolicy);
        cbx_mini_card->setMinimumSize(QSize(500, 31));
        cbx_mini_card->setMaximumSize(QSize(500, 31));
        cbx_mini_card->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cbx_mini_card);

        label_11 = new QLabel(formLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(135, 0));
        label_11->setLayoutDirection(Qt::LeftToRight);
        label_11->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_11);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(135, 0));
        label_3->setMaximumSize(QSize(135, 16777215));
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        cbx_service = new QComboBox(formLayoutWidget);
        cbx_service->setObjectName(QString::fromUtf8("cbx_service"));
        sizePolicy.setHeightForWidth(cbx_service->sizePolicy().hasHeightForWidth());
        cbx_service->setSizePolicy(sizePolicy);
        cbx_service->setMinimumSize(QSize(500, 31));
        cbx_service->setMaximumSize(QSize(500, 31));
        cbx_service->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(3, QFormLayout::FieldRole, cbx_service);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(135, 0));
        label_4->setMaximumSize(QSize(135, 16777215));
        label_4->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        txt_service_spec = new QTextEdit(formLayoutWidget);
        txt_service_spec->setObjectName(QString::fromUtf8("txt_service_spec"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txt_service_spec->sizePolicy().hasHeightForWidth());
        txt_service_spec->setSizePolicy(sizePolicy1);
        txt_service_spec->setMinimumSize(QSize(500, 187));
        txt_service_spec->setMaximumSize(QSize(500, 187));
        txt_service_spec->setStyleSheet(QString::fromUtf8("font:12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txt_service_spec->setReadOnly(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, txt_service_spec);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(135, 0));
        label_5->setMaximumSize(QSize(135, 16777215));
        label_5->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(5, QFormLayout::LabelRole, label_5);

        txt_price = new QLineEdit(formLayoutWidget);
        txt_price->setObjectName(QString::fromUtf8("txt_price"));
        sizePolicy.setHeightForWidth(txt_price->sizePolicy().hasHeightForWidth());
        txt_price->setSizePolicy(sizePolicy);
        txt_price->setMinimumSize(QSize(500, 31));
        txt_price->setMaximumSize(QSize(500, 31));
        txt_price->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txt_price->setReadOnly(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, txt_price);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(135, 0));
        label_6->setMaximumSize(QSize(135, 16777215));
        label_6->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        groupBox_ld = new QGroupBox(formLayoutWidget);
        groupBox_ld->setObjectName(QString::fromUtf8("groupBox_ld"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_ld->sizePolicy().hasHeightForWidth());
        groupBox_ld->setSizePolicy(sizePolicy2);
        groupBox_ld->setMinimumSize(QSize(500, 30));
        groupBox_ld->setMaximumSize(QSize(500, 16777215));
        rdo_ld_on = new QRadioButton(groupBox_ld);
        rdo_ld_on->setObjectName(QString::fromUtf8("rdo_ld_on"));
        rdo_ld_on->setGeometry(QRect(10, 5, 89, 16));
        rdo_ld_on->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        rdo_ld_on->setChecked(true);
        rdo_ld_off = new QRadioButton(groupBox_ld);
        rdo_ld_off->setObjectName(QString::fromUtf8("rdo_ld_off"));
        rdo_ld_off->setGeometry(QRect(100, 5, 89, 16));
        rdo_ld_off->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        rdo_ld_off->setChecked(false);

        formLayout->setWidget(6, QFormLayout::FieldRole, groupBox_ld);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(135, 0));
        label_7->setMaximumSize(QSize(135, 16777215));
        label_7->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(7, QFormLayout::LabelRole, label_7);

        groupBox_cl = new QGroupBox(formLayoutWidget);
        groupBox_cl->setObjectName(QString::fromUtf8("groupBox_cl"));
        sizePolicy2.setHeightForWidth(groupBox_cl->sizePolicy().hasHeightForWidth());
        groupBox_cl->setSizePolicy(sizePolicy2);
        groupBox_cl->setMinimumSize(QSize(500, 30));
        groupBox_cl->setMaximumSize(QSize(500, 16777215));
        rdo_cl_on = new QRadioButton(groupBox_cl);
        rdo_cl_on->setObjectName(QString::fromUtf8("rdo_cl_on"));
        rdo_cl_on->setGeometry(QRect(10, 5, 89, 16));
        rdo_cl_on->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        rdo_cl_on->setChecked(false);
        rdo_cl_off = new QRadioButton(groupBox_cl);
        rdo_cl_off->setObjectName(QString::fromUtf8("rdo_cl_off"));
        rdo_cl_off->setGeometry(QRect(100, 5, 89, 16));
        rdo_cl_off->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        rdo_cl_off->setChecked(true);

        formLayout->setWidget(7, QFormLayout::FieldRole, groupBox_cl);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(135, 0));
        label_8->setMaximumSize(QSize(135, 16777215));
        label_8->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(8, QFormLayout::LabelRole, label_8);

        txi_name = new QLineEdit(formLayoutWidget);
        txi_name->setObjectName(QString::fromUtf8("txi_name"));
        sizePolicy.setHeightForWidth(txi_name->sizePolicy().hasHeightForWidth());
        txi_name->setSizePolicy(sizePolicy);
        txi_name->setMinimumSize(QSize(500, 31));
        txi_name->setMaximumSize(QSize(500, 31));
        txi_name->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(8, QFormLayout::FieldRole, txi_name);

        label_9 = new QLabel(formLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(135, 0));
        label_9->setMaximumSize(QSize(135, 16777215));
        label_9->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(9, QFormLayout::LabelRole, label_9);

        cbx_zjlx = new QComboBox(formLayoutWidget);
        cbx_zjlx->setObjectName(QString::fromUtf8("cbx_zjlx"));
        sizePolicy.setHeightForWidth(cbx_zjlx->sizePolicy().hasHeightForWidth());
        cbx_zjlx->setSizePolicy(sizePolicy);
        cbx_zjlx->setMinimumSize(QSize(500, 31));
        cbx_zjlx->setMaximumSize(QSize(500, 31));
        cbx_zjlx->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(9, QFormLayout::FieldRole, cbx_zjlx);

        label_10 = new QLabel(formLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(135, 0));
        label_10->setMaximumSize(QSize(135, 16777215));
        label_10->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(10, QFormLayout::LabelRole, label_10);

        txi_indentifyNo = new QLineEdit(formLayoutWidget);
        txi_indentifyNo->setObjectName(QString::fromUtf8("txi_indentifyNo"));
        sizePolicy.setHeightForWidth(txi_indentifyNo->sizePolicy().hasHeightForWidth());
        txi_indentifyNo->setSizePolicy(sizePolicy);
        txi_indentifyNo->setMinimumSize(QSize(500, 31));
        txi_indentifyNo->setMaximumSize(QSize(500, 31));
        txi_indentifyNo->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(10, QFormLayout::FieldRole, txi_indentifyNo);

        groupBox_ld_2 = new QGroupBox(formLayoutWidget);
        groupBox_ld_2->setObjectName(QString::fromUtf8("groupBox_ld_2"));
        sizePolicy2.setHeightForWidth(groupBox_ld_2->sizePolicy().hasHeightForWidth());
        groupBox_ld_2->setSizePolicy(sizePolicy2);
        groupBox_ld_2->setMinimumSize(QSize(500, 30));
        groupBox_ld_2->setMaximumSize(QSize(500, 16777215));
        rdo_service_type_on = new QRadioButton(groupBox_ld_2);
        rdo_service_type_on->setObjectName(QString::fromUtf8("rdo_service_type_on"));
        rdo_service_type_on->setGeometry(QRect(10, 5, 89, 16));
        rdo_service_type_on->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        rdo_service_type_on->setChecked(true);
        rdo_service_type_off = new QRadioButton(groupBox_ld_2);
        rdo_service_type_off->setObjectName(QString::fromUtf8("rdo_service_type_off"));
        rdo_service_type_off->setGeometry(QRect(100, 5, 89, 16));
        rdo_service_type_off->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        rdo_service_type_off->setChecked(false);

        formLayout->setWidget(2, QFormLayout::FieldRole, groupBox_ld_2);

        btn_submit = new QPushButton(BuyNoDialog);
        btn_submit->setObjectName(QString::fromUtf8("btn_submit"));
        btn_submit->setGeometry(QRect(220, 590, 111, 41));
        btn_submit->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_close = new QPushButton(BuyNoDialog);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(380, 590, 111, 41));
        btn_close->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        retranslateUi(BuyNoDialog);

        QMetaObject::connectSlotsByName(BuyNoDialog);
    } // setupUi

    void retranslateUi(QDialog *BuyNoDialog)
    {
        BuyNoDialog->setWindowTitle(QApplication::translate("BuyNoDialog", "\345\207\206\345\244\207\345\274\200\345\215\241", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BuyNoDialog", "\347\224\265\350\257\235\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("BuyNoDialog", "\347\273\221\345\256\232\345\260\217\345\215\241\357\274\232", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("BuyNoDialog", "\346\230\276\347\244\272\345\245\227\351\244\220\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("BuyNoDialog", "\345\245\227\351\244\220\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("BuyNoDialog", "\350\265\204\350\264\271\344\273\213\347\273\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("BuyNoDialog", "\345\274\200\345\215\241\351\235\242\345\200\274\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("BuyNoDialog", "\345\274\200\351\200\232\346\235\245\347\224\265\346\230\276\347\244\272\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_ld->setTitle(QString());
        rdo_ld_on->setText(QApplication::translate("BuyNoDialog", "\345\274\200\351\200\232", 0, QApplication::UnicodeUTF8));
        rdo_ld_off->setText(QApplication::translate("BuyNoDialog", "\344\270\215\345\274\200\351\200\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("BuyNoDialog", "\345\274\200\351\200\232\345\275\251\351\223\203\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_cl->setTitle(QString());
        rdo_cl_on->setText(QApplication::translate("BuyNoDialog", "\345\274\200\351\200\232", 0, QApplication::UnicodeUTF8));
        rdo_cl_off->setText(QApplication::translate("BuyNoDialog", "\344\270\215\345\274\200\351\200\232", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("BuyNoDialog", "\345\256\242\346\210\267\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("BuyNoDialog", "\350\257\201\344\273\266\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("BuyNoDialog", "\350\257\201\344\273\266\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_ld_2->setTitle(QString());
        rdo_service_type_on->setText(QApplication::translate("BuyNoDialog", "\345\270\270\347\224\250", 0, QApplication::UnicodeUTF8));
        rdo_service_type_off->setText(QApplication::translate("BuyNoDialog", "\346\211\200\346\234\211", 0, QApplication::UnicodeUTF8));
        btn_submit->setText(QApplication::translate("BuyNoDialog", "\347\241\256\350\256\244\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
        btn_close->setText(QApplication::translate("BuyNoDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BuyNoDialog: public Ui_BuyNoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYNODIALOG_H
