/********************************************************************************
** Form generated from reading UI file 'zhye_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZHYE_SCROLLAREA_H
#define UI_ZHYE_SCROLLAREA_H

#include <QtCore/QDate>
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
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_zhye_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_24;
    QDateEdit *txiStartDate;
    QLabel *label_25;
    QDateEdit *txiEndDate;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_23;
    QComboBox *cbxBank;
    QLabel *label_22;
    QComboBox *cbxStoredState;
    QPushButton *btnSearch;
    QSpacerItem *horizontalSpacer_11;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QLabel *txt_rpt_total;
    QSpacerItem *horizontalSpacer_6;
    QLabel *txt_rpt_totoalMoney;
    QSpacerItem *horizontalSpacer_7;
    QLabel *txt_rpt_info;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *zhye_ScrollArea)
    {
        if (zhye_ScrollArea->objectName().isEmpty())
            zhye_ScrollArea->setObjectName(QString::fromUtf8("zhye_ScrollArea"));
        zhye_ScrollArea->resize(900, 650);
        zhye_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        zhye_ScrollArea->setFrameShape(QFrame::NoFrame);
        zhye_ScrollArea->setLineWidth(0);
        zhye_ScrollArea->setWidgetResizable(true);
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
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_8 = new QSpacerItem(175, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        label_24 = new QLabel(frame);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_24->setFont(font1);

        gridLayout_3->addWidget(label_24, 0, 1, 1, 1);

        txiStartDate = new QDateEdit(frame);
        txiStartDate->setObjectName(QString::fromUtf8("txiStartDate"));
        txiStartDate->setMinimumSize(QSize(0, 22));
        txiStartDate->setMaximumSize(QSize(16777215, 22));
        txiStartDate->setFont(font1);
        txiStartDate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        txiStartDate->setCalendarPopup(true);

        gridLayout_3->addWidget(txiStartDate, 0, 2, 1, 1);

        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font1);

        gridLayout_3->addWidget(label_25, 0, 3, 1, 1);

        txiEndDate = new QDateEdit(frame);
        txiEndDate->setObjectName(QString::fromUtf8("txiEndDate"));
        txiEndDate->setMinimumSize(QSize(0, 22));
        txiEndDate->setMaximumSize(QSize(16777215, 22));
        txiEndDate->setFont(font1);
        txiEndDate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        txiEndDate->setDate(QDate(2020, 1, 1));
        txiEndDate->setCalendarPopup(true);

        gridLayout_3->addWidget(txiEndDate, 0, 4, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(175, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 0, 6, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(175, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 1, 0, 1, 1);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_3->addWidget(label_23, 1, 1, 1, 1);

        cbxBank = new QComboBox(frame);
        cbxBank->setObjectName(QString::fromUtf8("cbxBank"));
        cbxBank->setMinimumSize(QSize(0, 22));
        cbxBank->setMaximumSize(QSize(16777215, 22));
        cbxBank->setFont(font1);
        cbxBank->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(cbxBank, 1, 2, 1, 1);

        label_22 = new QLabel(frame);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font1);

        gridLayout_3->addWidget(label_22, 1, 3, 1, 1);

        cbxStoredState = new QComboBox(frame);
        cbxStoredState->setObjectName(QString::fromUtf8("cbxStoredState"));
        cbxStoredState->setMinimumSize(QSize(0, 22));
        cbxStoredState->setMaximumSize(QSize(16777215, 22));
        cbxStoredState->setFont(font1);
        cbxStoredState->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(cbxStoredState, 1, 4, 1, 1);

        btnSearch = new QPushButton(frame);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));
        btnSearch->setMinimumSize(QSize(40, 25));
        btnSearch->setMaximumSize(QSize(40, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btnSearch->setFont(font2);
        btnSearch->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cx.png);"));

        gridLayout_3->addWidget(btnSearch, 1, 5, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(175, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 1, 6, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        txt_rpt_total = new QLabel(frame_2);
        txt_rpt_total->setObjectName(QString::fromUtf8("txt_rpt_total"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(10);
        txt_rpt_total->setFont(font3);
        txt_rpt_total->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_total, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(167, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        txt_rpt_totoalMoney = new QLabel(frame_2);
        txt_rpt_totoalMoney->setObjectName(QString::fromUtf8("txt_rpt_totoalMoney"));
        txt_rpt_totoalMoney->setFont(font3);
        txt_rpt_totoalMoney->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_totoalMoney, 0, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(166, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 3, 1, 1);

        txt_rpt_info = new QLabel(frame_2);
        txt_rpt_info->setObjectName(QString::fromUtf8("txt_rpt_info"));
        txt_rpt_info->setFont(font3);
        txt_rpt_info->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_info, 0, 4, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 3, 0, 1, 1);

        zhye_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(zhye_ScrollArea);

        QMetaObject::connectSlotsByName(zhye_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *zhye_ScrollArea)
    {
        zhye_ScrollArea->setWindowTitle(QApplication::translate("zhye_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("zhye_ScrollArea", "      \345\205\205\345\200\274\346\230\216\347\273\206", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("zhye_ScrollArea", "\350\265\267\345\247\213\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("zhye_ScrollArea", "\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("zhye_ScrollArea", "\345\205\205\345\200\274\351\223\266\350\241\214\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("zhye_ScrollArea", "\345\205\205\345\200\274\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        btnSearch->setText(QString());
        txt_rpt_total->setText(QApplication::translate("zhye_ScrollArea", "\346\200\273\347\254\224\346\225\260\357\274\232\343\200\22010\343\200\221", 0, QApplication::UnicodeUTF8));
        txt_rpt_totoalMoney->setText(QApplication::translate("zhye_ScrollArea", "\346\200\273\351\207\221\351\242\235\357\274\232\343\200\22010\343\200\221", 0, QApplication::UnicodeUTF8));
        txt_rpt_info->setText(QApplication::translate("zhye_ScrollArea", "\345\275\223\345\211\215\347\224\250\346\210\267\357\274\232\343\200\220xxx\343\200\221\347\232\204\345\217\257\347\224\250\344\275\231\351\242\235\344\270\272\357\274\232\343\200\220000.000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class zhye_ScrollArea: public Ui_zhye_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZHYE_SCROLLAREA_H
