/********************************************************************************
** Form generated from reading UI file 'jfyb_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JFYB_SCROLLAREA_H
#define UI_JFYB_SCROLLAREA_H

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

class Ui_jfyb_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_24;
    QDateEdit *txiStartDate;
    QLabel *label_25;
    QDateEdit *txiEndDate;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_21;
    QComboBox *cbx_sp;
    QLabel *label_22;
    QComboBox *cbx_state;
    QLabel *label_23;
    QLineEdit *txi_phone_no;
    QPushButton *btn_search;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QLabel *txt_rpt_total;
    QSpacerItem *horizontalSpacer_12;
    QLabel *txt_rpt_money;
    QSpacerItem *horizontalSpacer_14;
    QLabel *txt_rpt_repay;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *btn_refresh;
    QPushButton *btn_print;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_6;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *jfyb_ScrollArea)
    {
        if (jfyb_ScrollArea->objectName().isEmpty())
            jfyb_ScrollArea->setObjectName(QString::fromUtf8("jfyb_ScrollArea"));
        jfyb_ScrollArea->resize(900, 650);
        jfyb_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        jfyb_ScrollArea->setFrameShape(QFrame::NoFrame);
        jfyb_ScrollArea->setWidgetResizable(true);
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

        horizontalSpacer = new QSpacerItem(15, 25, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_8 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        label_24 = new QLabel(frame);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_24->setFont(font1);

        gridLayout_3->addWidget(label_24, 0, 1, 1, 2);

        txiStartDate = new QDateEdit(frame);
        txiStartDate->setObjectName(QString::fromUtf8("txiStartDate"));
        txiStartDate->setMinimumSize(QSize(0, 22));
        txiStartDate->setMaximumSize(QSize(16777215, 22));
        txiStartDate->setFont(font1);
        txiStartDate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        txiStartDate->setCalendarPopup(true);

        gridLayout_3->addWidget(txiStartDate, 0, 3, 1, 1);

        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font1);

        gridLayout_3->addWidget(label_25, 0, 4, 1, 2);

        txiEndDate = new QDateEdit(frame);
        txiEndDate->setObjectName(QString::fromUtf8("txiEndDate"));
        txiEndDate->setMinimumSize(QSize(0, 22));
        txiEndDate->setMaximumSize(QSize(16777215, 22));
        txiEndDate->setFont(font1);
        txiEndDate->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(txiEndDate, 0, 6, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 0, 10, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 1, 0, 1, 1);

        label_21 = new QLabel(frame);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font1);

        gridLayout_3->addWidget(label_21, 1, 1, 1, 1);

        cbx_sp = new QComboBox(frame);
        cbx_sp->setObjectName(QString::fromUtf8("cbx_sp"));
        cbx_sp->setMinimumSize(QSize(0, 22));
        cbx_sp->setMaximumSize(QSize(16777215, 22));
        cbx_sp->setFont(font1);
        cbx_sp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(cbx_sp, 1, 2, 1, 2);

        label_22 = new QLabel(frame);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font1);

        gridLayout_3->addWidget(label_22, 1, 4, 1, 1);

        cbx_state = new QComboBox(frame);
        cbx_state->setObjectName(QString::fromUtf8("cbx_state"));
        cbx_state->setMinimumSize(QSize(0, 22));
        cbx_state->setMaximumSize(QSize(16777215, 22));
        cbx_state->setFont(font1);
        cbx_state->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(cbx_state, 1, 5, 1, 2);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_3->addWidget(label_23, 1, 7, 1, 1);

        txi_phone_no = new QLineEdit(frame);
        txi_phone_no->setObjectName(QString::fromUtf8("txi_phone_no"));
        txi_phone_no->setMinimumSize(QSize(0, 22));
        txi_phone_no->setMaximumSize(QSize(16777215, 22));
        txi_phone_no->setFont(font1);
        txi_phone_no->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_phone_no->setMaxLength(11);

        gridLayout_3->addWidget(txi_phone_no, 1, 8, 1, 1);

        btn_search = new QPushButton(frame);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));
        btn_search->setMinimumSize(QSize(40, 25));
        btn_search->setMaximumSize(QSize(40, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btn_search->setFont(font2);
        btn_search->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cx.png);"));

        gridLayout_3->addWidget(btn_search, 1, 9, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 1, 10, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(15, 100, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

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

        horizontalSpacer_12 = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 0, 1, 1, 1);

        txt_rpt_money = new QLabel(frame_2);
        txt_rpt_money->setObjectName(QString::fromUtf8("txt_rpt_money"));
        txt_rpt_money->setFont(font3);
        txt_rpt_money->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_money, 0, 2, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_14, 0, 3, 1, 1);

        txt_rpt_repay = new QLabel(frame_2);
        txt_rpt_repay->setObjectName(QString::fromUtf8("txt_rpt_repay"));
        txt_rpt_repay->setFont(font3);
        txt_rpt_repay->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_repay, 0, 4, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_13, 0, 5, 1, 1);

        btn_refresh = new QPushButton(frame_2);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        btn_refresh->setMinimumSize(QSize(40, 25));
        btn_refresh->setMaximumSize(QSize(40, 25));
        btn_refresh->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_2->addWidget(btn_refresh, 0, 6, 1, 1);

        btn_print = new QPushButton(frame_2);
        btn_print->setObjectName(QString::fromUtf8("btn_print"));
        btn_print->setMinimumSize(QSize(41, 41));
        btn_print->setMaximumSize(QSize(41, 41));
        btn_print->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_2->addWidget(btn_print, 0, 7, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(15, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(855, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 3, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(15, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 3, 1, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setAutoFillBackground(false);
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 4, 0, 1, 2);

        jfyb_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(jfyb_ScrollArea);

        QMetaObject::connectSlotsByName(jfyb_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *jfyb_ScrollArea)
    {
        jfyb_ScrollArea->setWindowTitle(QApplication::translate("jfyb_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("jfyb_ScrollArea", "      \347\274\264\350\264\271\346\234\210\346\212\245", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("jfyb_ScrollArea", "\350\265\267\345\247\213\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("jfyb_ScrollArea", "\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("jfyb_ScrollArea", "\350\277\220\350\220\245\345\225\206\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("jfyb_ScrollArea", "\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("jfyb_ScrollArea", "\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_phone_no->setText(QString());
        btn_search->setText(QString());
        txt_rpt_total->setText(QApplication::translate("jfyb_ScrollArea", "\347\274\264\350\264\271\357\274\232\343\200\220100\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        txt_rpt_money->setText(QApplication::translate("jfyb_ScrollArea", "\347\274\264\350\264\271\351\207\221\351\242\235\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        txt_rpt_repay->setText(QApplication::translate("jfyb_ScrollArea", "\350\277\224\346\254\276\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        btn_refresh->setText(QString());
        btn_print->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class jfyb_ScrollArea: public Ui_jfyb_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JFYB_SCROLLAREA_H
