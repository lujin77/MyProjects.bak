/********************************************************************************
** Form generated from reading UI file 'zhcz_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZHCZ_SCROLLAREA_H
#define UI_ZHCZ_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_zhcz_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_25;
    QLineEdit *txiAccountName;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_23;
    QLineEdit *txiAccountMoney;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_30;
    QLineEdit *txiAccountTail;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_22;
    QLineEdit *txiStoredMoney;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *horizontalSpacer_16;
    QLabel *label_24;
    QComboBox *cbxBankName;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_18;
    QLabel *label_26;
    QLineEdit *txiSubBankName;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *horizontalSpacer_20;
    QLabel *label_27;
    QComboBox *cbxStoredType;
    QSpacerItem *horizontalSpacer_21;
    QSpacerItem *horizontalSpacer_22;
    QLabel *label_time;
    QDateTimeEdit *txiDatetime;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *horizontalSpacer_26;
    QLabel *label_29;
    QTextEdit *txiContent;
    QSpacerItem *horizontalSpacer_27;
    QPushButton *btnSubmit;
    QPushButton *btnReset;
    QSpacerItem *horizontalSpacer_24;
    QSpacerItem *horizontalSpacer_25;
    QLabel *label_16;

    void setupUi(QScrollArea *zhcz_ScrollArea)
    {
        if (zhcz_ScrollArea->objectName().isEmpty())
            zhcz_ScrollArea->setObjectName(QString::fromUtf8("zhcz_ScrollArea"));
        zhcz_ScrollArea->resize(900, 650);
        zhcz_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        zhcz_ScrollArea->setFrameShape(QFrame::NoFrame);
        zhcz_ScrollArea->setLineWidth(0);
        zhcz_ScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 900, 650));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 25));
        label->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(253, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 2, 1, 3);

        horizontalSpacer_7 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 5, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 1, 0, 1, 1);

        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_25->setFont(font1);

        gridLayout_2->addWidget(label_25, 1, 1, 1, 1);

        txiAccountName = new QLineEdit(frame);
        txiAccountName->setObjectName(QString::fromUtf8("txiAccountName"));
        txiAccountName->setMinimumSize(QSize(0, 22));
        txiAccountName->setMaximumSize(QSize(16777215, 22));
        txiAccountName->setFont(font1);
        txiAccountName->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txiAccountName->setReadOnly(true);

        gridLayout_2->addWidget(txiAccountName, 1, 2, 1, 2);

        horizontalSpacer_9 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 1, 5, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 2, 0, 1, 1);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_2->addWidget(label_23, 2, 1, 1, 1);

        txiAccountMoney = new QLineEdit(frame);
        txiAccountMoney->setObjectName(QString::fromUtf8("txiAccountMoney"));
        txiAccountMoney->setMinimumSize(QSize(0, 22));
        txiAccountMoney->setMaximumSize(QSize(16777215, 22));
        txiAccountMoney->setFont(font1);
        txiAccountMoney->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txiAccountMoney->setReadOnly(true);

        gridLayout_2->addWidget(txiAccountMoney, 2, 2, 1, 2);

        horizontalSpacer_11 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 2, 5, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 3, 0, 1, 1);

        label_30 = new QLabel(frame);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font1);

        gridLayout_2->addWidget(label_30, 3, 1, 1, 1);

        txiAccountTail = new QLineEdit(frame);
        txiAccountTail->setObjectName(QString::fromUtf8("txiAccountTail"));
        txiAccountTail->setMinimumSize(QSize(0, 22));
        txiAccountTail->setMaximumSize(QSize(16777215, 22));
        txiAccountTail->setFont(font1);
        txiAccountTail->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txiAccountTail->setReadOnly(true);

        gridLayout_2->addWidget(txiAccountTail, 3, 2, 1, 2);

        horizontalSpacer_13 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_13, 3, 5, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_14, 4, 0, 1, 1);

        label_22 = new QLabel(frame);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font1);

        gridLayout_2->addWidget(label_22, 4, 1, 1, 1);

        txiStoredMoney = new QLineEdit(frame);
        txiStoredMoney->setObjectName(QString::fromUtf8("txiStoredMoney"));
        txiStoredMoney->setMinimumSize(QSize(0, 22));
        txiStoredMoney->setMaximumSize(QSize(16777215, 22));
        txiStoredMoney->setFont(font1);
        txiStoredMoney->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txiStoredMoney, 4, 2, 1, 2);

        horizontalSpacer_15 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_15, 4, 5, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_16, 5, 0, 1, 1);

        label_24 = new QLabel(frame);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font1);

        gridLayout_2->addWidget(label_24, 5, 1, 1, 1);

        cbxBankName = new QComboBox(frame);
        cbxBankName->setObjectName(QString::fromUtf8("cbxBankName"));
        cbxBankName->setMinimumSize(QSize(0, 22));
        cbxBankName->setMaximumSize(QSize(16777215, 22));
        cbxBankName->setFont(font1);
        cbxBankName->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbxBankName, 5, 2, 1, 2);

        horizontalSpacer_17 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_17, 5, 5, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_18, 6, 0, 1, 1);

        label_26 = new QLabel(frame);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setFont(font1);

        gridLayout_2->addWidget(label_26, 6, 1, 1, 1);

        txiSubBankName = new QLineEdit(frame);
        txiSubBankName->setObjectName(QString::fromUtf8("txiSubBankName"));
        txiSubBankName->setMinimumSize(QSize(0, 22));
        txiSubBankName->setMaximumSize(QSize(16777215, 22));
        txiSubBankName->setFont(font1);
        txiSubBankName->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txiSubBankName, 6, 2, 1, 2);

        horizontalSpacer_19 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_19, 6, 5, 1, 1);

        horizontalSpacer_20 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_20, 7, 0, 1, 1);

        label_27 = new QLabel(frame);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font1);

        gridLayout_2->addWidget(label_27, 7, 1, 1, 1);

        cbxStoredType = new QComboBox(frame);
        cbxStoredType->setObjectName(QString::fromUtf8("cbxStoredType"));
        cbxStoredType->setMinimumSize(QSize(0, 22));
        cbxStoredType->setMaximumSize(QSize(16777215, 22));
        cbxStoredType->setFont(font1);
        cbxStoredType->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbxStoredType, 7, 2, 1, 2);

        horizontalSpacer_21 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_21, 7, 5, 1, 1);

        horizontalSpacer_22 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_22, 8, 0, 1, 1);

        label_time = new QLabel(frame);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setFont(font1);

        gridLayout_2->addWidget(label_time, 8, 1, 1, 1);

        txiDatetime = new QDateTimeEdit(frame);
        txiDatetime->setObjectName(QString::fromUtf8("txiDatetime"));
        txiDatetime->setEnabled(false);
        txiDatetime->setMinimumSize(QSize(0, 22));
        txiDatetime->setMaximumSize(QSize(16777215, 22));
        txiDatetime->setFont(font1);
        txiDatetime->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        txiDatetime->setDateTime(QDateTime(QDate(2011, 8, 15), QTime(0, 0, 0)));
        txiDatetime->setCurrentSection(QDateTimeEdit::MonthSection);
        txiDatetime->setCalendarPopup(true);

        gridLayout_2->addWidget(txiDatetime, 8, 2, 1, 2);

        horizontalSpacer_23 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_23, 8, 5, 1, 1);

        horizontalSpacer_26 = new QSpacerItem(227, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_26, 9, 0, 2, 1);

        label_29 = new QLabel(frame);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setFont(font1);

        gridLayout_2->addWidget(label_29, 9, 1, 1, 1);

        txiContent = new QTextEdit(frame);
        txiContent->setObjectName(QString::fromUtf8("txiContent"));
        txiContent->setMinimumSize(QSize(0, 192));
        txiContent->setMaximumSize(QSize(16777215, 192));
        txiContent->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txiContent, 9, 2, 2, 3);

        horizontalSpacer_27 = new QSpacerItem(226, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_27, 10, 5, 1, 1);

        btnSubmit = new QPushButton(frame);
        btnSubmit->setObjectName(QString::fromUtf8("btnSubmit"));
        btnSubmit->setMinimumSize(QSize(61, 25));
        btnSubmit->setMaximumSize(QSize(61, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btnSubmit->setFont(font2);
        btnSubmit->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_qrtj.png);"));

        gridLayout_2->addWidget(btnSubmit, 11, 3, 1, 1);

        btnReset = new QPushButton(frame);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        btnReset->setMinimumSize(QSize(40, 25));
        btnReset->setMaximumSize(QSize(40, 25));
        btnReset->setFont(font2);
        btnReset->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cz.png);"));

        gridLayout_2->addWidget(btnReset, 11, 4, 1, 1);

        horizontalSpacer_24 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_24, 12, 0, 1, 1);

        horizontalSpacer_25 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_25, 12, 5, 1, 1);

        label_16 = new QLabel(frame);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font1);
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(label_16, 13, 1, 1, 4);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        zhcz_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(zhcz_ScrollArea);

        QMetaObject::connectSlotsByName(zhcz_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *zhcz_ScrollArea)
    {
        zhcz_ScrollArea->setWindowTitle(QApplication::translate("zhcz_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("zhcz_ScrollArea", "      \350\264\246\346\210\267\345\205\205\345\200\274", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("zhcz_ScrollArea", "\350\264\246\346\210\267\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("zhcz_ScrollArea", "\350\264\246\346\210\267\344\275\231\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("zhcz_ScrollArea", "\345\255\230\346\254\276\345\260\276\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("zhcz_ScrollArea", "\345\205\205\345\200\274\351\207\221\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("zhcz_ScrollArea", "\351\223\266\350\241\214\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("zhcz_ScrollArea", "\346\224\257\350\241\214\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("zhcz_ScrollArea", "\345\255\230\346\254\276\346\226\271\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        label_time->setText(QApplication::translate("zhcz_ScrollArea", "\345\255\230\346\254\276\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("zhcz_ScrollArea", "\345\244\207\346\263\250\357\274\232", 0, QApplication::UnicodeUTF8));
        txiContent->setHtml(QApplication::translate("zhcz_ScrollArea", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnSubmit->setText(QString());
        btnReset->setText(QString());
        label_16->setText(QApplication::translate("zhcz_ScrollArea", "* \350\257\267\350\276\223\345\205\245\346\202\250\347\241\256\345\210\207\347\232\204\345\255\230\346\254\276\346\227\266\351\227\264\357\274\214\345\220\246\345\210\231\344\270\215\350\203\275\345\277\253\351\200\237\345\270\256\344\275\240\350\275\254\350\264\246 *", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class zhcz_ScrollArea: public Ui_zhcz_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZHCZ_SCROLLAREA_H
