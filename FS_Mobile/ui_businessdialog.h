/********************************************************************************
** Form generated from reading UI file 'businessdialog.ui'
**
** Created: Sun Apr 15 14:38:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUSINESSDIALOG_H
#define UI_BUSINESSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BusinessDialog
{
public:
    QLabel *label;
    QLineEdit *txi_no;
    QLabel *label_2;
    QLineEdit *txi_passwd;
    QStackedWidget *stackedWidget;
    QWidget *page_5;
    QWidget *page_4;
    QLabel *label_9;
    QTextEdit *txi_comment;
    QTextEdit *txi_content;
    QLabel *label_10;
    QWidget *page;
    QComboBox *cbx_service;
    QLabel *label_3;
    QLabel *label_11;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rdo_service_type_on;
    QRadioButton *rdo_service_type_off;
    QWidget *page_2;
    QLabel *label_4;
    QComboBox *cbx_card_type;
    QLabel *label_5;
    QLineEdit *txi_name;
    QLabel *label_6;
    QLineEdit *txi_card_no;
    QWidget *page_3;
    QLabel *label_7;
    QTextEdit *txi_add_no;
    QLabel *label_8;
    QTextEdit *txi_delete_no;
    QPushButton *btn_submit;
    QPushButton *btn_reset;

    void setupUi(QDialog *BusinessDialog)
    {
        if (BusinessDialog->objectName().isEmpty())
            BusinessDialog->setObjectName(QString::fromUtf8("BusinessDialog"));
        BusinessDialog->resize(500, 400);
        label = new QLabel(BusinessDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 30, 71, 31));
        label->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_no = new QLineEdit(BusinessDialog);
        txi_no->setObjectName(QString::fromUtf8("txi_no"));
        txi_no->setGeometry(QRect(140, 30, 191, 41));
        txi_no->setMinimumSize(QSize(0, 41));
        txi_no->setMaximumSize(QSize(16777215, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        txi_no->setFont(font);
        txi_no->setStyleSheet(QString::fromUtf8("font: 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_no->setMaxLength(11);
        label_2 = new QLabel(BusinessDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 80, 71, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_passwd = new QLineEdit(BusinessDialog);
        txi_passwd->setObjectName(QString::fromUtf8("txi_passwd"));
        txi_passwd->setGeometry(QRect(140, 80, 191, 41));
        txi_passwd->setMinimumSize(QSize(0, 41));
        txi_passwd->setMaximumSize(QSize(16777215, 41));
        txi_passwd->setFont(font);
        txi_passwd->setStyleSheet(QString::fromUtf8("font: 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_passwd->setMaxLength(11);
        stackedWidget = new QStackedWidget(BusinessDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(30, 140, 431, 231));
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        stackedWidget->addWidget(page_5);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        label_9 = new QLabel(page_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 0, 121, 31));
        label_9->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_comment = new QTextEdit(page_4);
        txi_comment->setObjectName(QString::fromUtf8("txi_comment"));
        txi_comment->setGeometry(QRect(10, 140, 411, 81));
        txi_comment->setMinimumSize(QSize(0, 81));
        txi_comment->setMaximumSize(QSize(16777215, 81));
        txi_content = new QTextEdit(page_4);
        txi_content->setObjectName(QString::fromUtf8("txi_content"));
        txi_content->setGeometry(QRect(10, 30, 411, 81));
        txi_content->setMinimumSize(QSize(0, 81));
        txi_content->setMaximumSize(QSize(16777215, 81));
        label_10 = new QLabel(page_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 110, 121, 31));
        label_10->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        stackedWidget->addWidget(page_4);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        cbx_service = new QComboBox(page);
        cbx_service->setObjectName(QString::fromUtf8("cbx_service"));
        cbx_service->setGeometry(QRect(100, 50, 311, 31));
        cbx_service->setMinimumSize(QSize(0, 31));
        cbx_service->setMaximumSize(QSize(16777215, 31));
        cbx_service->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_3 = new QLabel(page);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 50, 81, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_11 = new QLabel(page);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 10, 81, 31));
        label_11->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(100, 10, 141, 36));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        rdo_service_type_on = new QRadioButton(groupBox);
        rdo_service_type_on->setObjectName(QString::fromUtf8("rdo_service_type_on"));
        rdo_service_type_on->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(rdo_service_type_on);

        rdo_service_type_off = new QRadioButton(groupBox);
        rdo_service_type_off->setObjectName(QString::fromUtf8("rdo_service_type_off"));
        rdo_service_type_off->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        rdo_service_type_off->setChecked(true);

        horizontalLayout->addWidget(rdo_service_type_off);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_4 = new QLabel(page_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 70, 81, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        cbx_card_type = new QComboBox(page_2);
        cbx_card_type->setObjectName(QString::fromUtf8("cbx_card_type"));
        cbx_card_type->setGeometry(QRect(100, 70, 311, 31));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(31);
        sizePolicy.setHeightForWidth(cbx_card_type->sizePolicy().hasHeightForWidth());
        cbx_card_type->setSizePolicy(sizePolicy);
        cbx_card_type->setMinimumSize(QSize(0, 31));
        cbx_card_type->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_5 = new QLabel(page_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 81, 31));
        label_5->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_name = new QLineEdit(page_2);
        txi_name->setObjectName(QString::fromUtf8("txi_name"));
        txi_name->setGeometry(QRect(100, 20, 311, 31));
        txi_name->setMinimumSize(QSize(0, 31));
        txi_name->setMaximumSize(QSize(16777215, 31));
        txi_name->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 120, 81, 31));
        label_6->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_card_no = new QLineEdit(page_2);
        txi_card_no->setObjectName(QString::fromUtf8("txi_card_no"));
        txi_card_no->setGeometry(QRect(100, 120, 311, 31));
        txi_card_no->setMinimumSize(QSize(0, 31));
        txi_card_no->setMaximumSize(QSize(16777215, 31));
        txi_card_no->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        label_7 = new QLabel(page_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 0, 121, 31));
        label_7->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_add_no = new QTextEdit(page_3);
        txi_add_no->setObjectName(QString::fromUtf8("txi_add_no"));
        txi_add_no->setGeometry(QRect(10, 30, 411, 81));
        txi_add_no->setMinimumSize(QSize(0, 81));
        txi_add_no->setMaximumSize(QSize(16777215, 81));
        label_8 = new QLabel(page_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 110, 121, 31));
        label_8->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_delete_no = new QTextEdit(page_3);
        txi_delete_no->setObjectName(QString::fromUtf8("txi_delete_no"));
        txi_delete_no->setGeometry(QRect(10, 140, 411, 81));
        stackedWidget->addWidget(page_3);
        btn_submit = new QPushButton(BusinessDialog);
        btn_submit->setObjectName(QString::fromUtf8("btn_submit"));
        btn_submit->setGeometry(QRect(350, 30, 91, 41));
        btn_submit->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_reset = new QPushButton(BusinessDialog);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        btn_reset->setGeometry(QRect(350, 80, 91, 41));
        btn_reset->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        retranslateUi(BusinessDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(BusinessDialog);
    } // setupUi

    void retranslateUi(QDialog *BusinessDialog)
    {
        BusinessDialog->setWindowTitle(QApplication::translate("BusinessDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BusinessDialog", "\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_no->setText(QString());
        label_2->setText(QApplication::translate("BusinessDialog", "\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_passwd->setText(QString());
        label_9->setText(QApplication::translate("BusinessDialog", "\345\212\236\347\220\206\345\206\205\345\256\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("BusinessDialog", "\345\244\207\346\263\250\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("BusinessDialog", "\351\200\211\346\213\251\345\245\227\351\244\220\357\274\232", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("BusinessDialog", "\346\230\276\347\244\272\345\245\227\351\244\220\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        rdo_service_type_on->setText(QApplication::translate("BusinessDialog", "\345\270\270\347\224\250", 0, QApplication::UnicodeUTF8));
        rdo_service_type_off->setText(QApplication::translate("BusinessDialog", "\346\211\200\346\234\211", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("BusinessDialog", "\350\257\201\344\273\266\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("BusinessDialog", "\345\256\242\346\210\267\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("BusinessDialog", "\350\257\201\344\273\266\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("BusinessDialog", "\346\226\260\345\242\236\344\272\262\346\203\205\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("BusinessDialog", "\345\210\240\351\231\244\344\272\262\346\203\205\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        btn_submit->setText(QApplication::translate("BusinessDialog", "\346\217\220\344\272\244\345\212\236\347\220\206", 0, QApplication::UnicodeUTF8));
        btn_reset->setText(QApplication::translate("BusinessDialog", "\351\207\215\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BusinessDialog: public Ui_BusinessDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUSINESSDIALOG_H
