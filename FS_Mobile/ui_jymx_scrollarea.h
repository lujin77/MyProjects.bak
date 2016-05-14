/********************************************************************************
** Form generated from reading UI file 'jymx_scrollarea.ui'
**
** Created: Mon Sep 3 21:44:44 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JYMX_SCROLLAREA_H
#define UI_JYMX_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_jymx_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_15;
    QDateEdit *txiStartDate;
    QLabel *label_19;
    QDateEdit *txiEndDate;
    QLabel *label_17;
    QLineEdit *txi_phone_no;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_18;
    QComboBox *cbx_state;
    QLabel *label_16;
    QComboBox *cbx_type;
    QPushButton *btnSearch;
    QPushButton *btnExport;
    QSpacerItem *horizontalSpacer_8;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QLabel *txt_rpt_money;
    QSpacerItem *horizontalSpacer_10;
    QLabel *txt_rpt_charge;
    QSpacerItem *horizontalSpacer_11;
    QLabel *txt_rpt_return;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *jymx_ScrollArea)
    {
        if (jymx_ScrollArea->objectName().isEmpty())
            jymx_ScrollArea->setObjectName(QString::fromUtf8("jymx_ScrollArea"));
        jymx_ScrollArea->resize(900, 650);
        jymx_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        jymx_ScrollArea->setFrameShape(QFrame::NoFrame);
        jymx_ScrollArea->setLineWidth(0);
        jymx_ScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 900, 650));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
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
        horizontalSpacer_5 = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        label_15 = new QLabel(frame);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_15->setFont(font1);

        gridLayout_2->addWidget(label_15, 0, 1, 1, 1);

        txiStartDate = new QDateEdit(frame);
        txiStartDate->setObjectName(QString::fromUtf8("txiStartDate"));
        txiStartDate->setMinimumSize(QSize(0, 22));
        txiStartDate->setMaximumSize(QSize(16777215, 22));
        txiStartDate->setFont(font1);
        txiStartDate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        txiStartDate->setReadOnly(false);
        txiStartDate->setKeyboardTracking(true);
        txiStartDate->setCalendarPopup(true);

        gridLayout_2->addWidget(txiStartDate, 0, 2, 1, 1);

        label_19 = new QLabel(frame);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font1);

        gridLayout_2->addWidget(label_19, 0, 3, 1, 1);

        txiEndDate = new QDateEdit(frame);
        txiEndDate->setObjectName(QString::fromUtf8("txiEndDate"));
        txiEndDate->setMinimumSize(QSize(0, 22));
        txiEndDate->setMaximumSize(QSize(16777215, 22));
        txiEndDate->setFont(font1);
        txiEndDate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        txiEndDate->setCalendarPopup(true);

        gridLayout_2->addWidget(txiEndDate, 0, 4, 1, 1);

        label_17 = new QLabel(frame);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font1);

        gridLayout_2->addWidget(label_17, 0, 5, 1, 1);

        txi_phone_no = new QLineEdit(frame);
        txi_phone_no->setObjectName(QString::fromUtf8("txi_phone_no"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txi_phone_no->sizePolicy().hasHeightForWidth());
        txi_phone_no->setSizePolicy(sizePolicy);
        txi_phone_no->setMinimumSize(QSize(0, 22));
        txi_phone_no->setMaximumSize(QSize(16777215, 22));
        txi_phone_no->setFont(font1);
        txi_phone_no->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_phone_no->setMaxLength(11);

        gridLayout_2->addWidget(txi_phone_no, 0, 6, 1, 2);

        horizontalSpacer_6 = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 8, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(101, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 1, 0, 1, 1);

        label_18 = new QLabel(frame);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font1);

        gridLayout_2->addWidget(label_18, 1, 1, 1, 1);

        cbx_state = new QComboBox(frame);
        cbx_state->setObjectName(QString::fromUtf8("cbx_state"));
        cbx_state->setMinimumSize(QSize(150, 22));
        cbx_state->setMaximumSize(QSize(16777215, 22));
        cbx_state->setFont(font1);
        cbx_state->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbx_state, 1, 2, 1, 1);

        label_16 = new QLabel(frame);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font1);

        gridLayout_2->addWidget(label_16, 1, 3, 1, 1);

        cbx_type = new QComboBox(frame);
        cbx_type->setObjectName(QString::fromUtf8("cbx_type"));
        cbx_type->setMinimumSize(QSize(0, 22));
        cbx_type->setMaximumSize(QSize(16777215, 22));
        cbx_type->setFont(font1);
        cbx_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbx_type, 1, 4, 1, 1);

        btnSearch = new QPushButton(frame);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));
        btnSearch->setFont(font1);
        btnSearch->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout_2->addWidget(btnSearch, 1, 6, 1, 1);

        btnExport = new QPushButton(frame);
        btnExport->setObjectName(QString::fromUtf8("btnExport"));
        btnExport->setFont(font1);
        btnExport->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout_2->addWidget(btnExport, 1, 7, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(101, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 1, 8, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        txt_rpt_money = new QLabel(frame_2);
        txt_rpt_money->setObjectName(QString::fromUtf8("txt_rpt_money"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        txt_rpt_money->setFont(font2);
        txt_rpt_money->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_money, 0, 0, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(167, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 0, 1, 1, 1);

        txt_rpt_charge = new QLabel(frame_2);
        txt_rpt_charge->setObjectName(QString::fromUtf8("txt_rpt_charge"));
        txt_rpt_charge->setFont(font2);
        txt_rpt_charge->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        txt_rpt_charge->setTextFormat(Qt::RichText);

        gridLayout_3->addWidget(txt_rpt_charge, 0, 2, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(166, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 0, 3, 1, 1);

        txt_rpt_return = new QLabel(frame_2);
        txt_rpt_return->setObjectName(QString::fromUtf8("txt_rpt_return"));
        txt_rpt_return->setFont(font2);
        txt_rpt_return->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_return, 0, 4, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 3, 0, 1, 1);

        jymx_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(jymx_ScrollArea);

        QMetaObject::connectSlotsByName(jymx_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *jymx_ScrollArea)
    {
        jymx_ScrollArea->setWindowTitle(QApplication::translate("jymx_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("jymx_ScrollArea", "      \344\272\244\346\230\223\346\230\216\347\273\206\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("jymx_ScrollArea", "\350\265\267\345\247\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("jymx_ScrollArea", "\346\210\252\346\255\242\357\274\232", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("jymx_ScrollArea", "\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_phone_no->setText(QString());
        label_18->setText(QApplication::translate("jymx_ScrollArea", "\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("jymx_ScrollArea", "\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        btnSearch->setText(QApplication::translate("jymx_ScrollArea", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        btnExport->setText(QApplication::translate("jymx_ScrollArea", "\345\257\274\345\207\272Execl", 0, QApplication::UnicodeUTF8));
        txt_rpt_money->setText(QApplication::translate("jymx_ScrollArea", "\345\212\236\347\220\206\346\200\273\351\207\221\351\242\235\357\274\232\343\200\22010\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        txt_rpt_charge->setText(QApplication::translate("jymx_ScrollArea", "\346\211\243\346\254\276\346\200\273\351\207\221\351\242\235\357\274\232\343\200\2200\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        txt_rpt_return->setText(QApplication::translate("jymx_ScrollArea", "\350\277\224\346\254\276\346\200\273\351\207\221\351\242\235\357\274\232\343\200\22010\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class jymx_ScrollArea: public Ui_jymx_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JYMX_SCROLLAREA_H
