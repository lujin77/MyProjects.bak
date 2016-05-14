/********************************************************************************
** Form generated from reading UI file 'jfrb_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JFRB_SCROLLAREA_H
#define UI_JFRB_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
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

class Ui_jfrb_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_15;
    QComboBox *cbx_SP;
    QLabel *label_16;
    QComboBox *cbx_state;
    QLabel *label_17;
    QLineEdit *txi_PhoneNo;
    QPushButton *btn_search;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QLabel *txt_rpt_total;
    QSpacerItem *horizontalSpacer_8;
    QLabel *txt_rpt_money;
    QSpacerItem *horizontalSpacer_9;
    QLabel *txt_rpt_repay;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *btn_fx;
    QPushButton *btn_cx;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *btn_refresh;
    QPushButton *btn_print;
    QSpacerItem *horizontalSpacer_5;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *jfrb_ScrollArea)
    {
        if (jfrb_ScrollArea->objectName().isEmpty())
            jfrb_ScrollArea->setObjectName(QString::fromUtf8("jfrb_ScrollArea"));
        jfrb_ScrollArea->resize(900, 650);
        jfrb_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        jfrb_ScrollArea->setFrameShape(QFrame::NoFrame);
        jfrb_ScrollArea->setWidgetResizable(true);
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

        horizontalSpacer_3 = new QSpacerItem(1, 25, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        label_15 = new QLabel(frame);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_15->setFont(font1);

        gridLayout_2->addWidget(label_15, 0, 1, 1, 1);

        cbx_SP = new QComboBox(frame);
        cbx_SP->setObjectName(QString::fromUtf8("cbx_SP"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cbx_SP->sizePolicy().hasHeightForWidth());
        cbx_SP->setSizePolicy(sizePolicy);
        cbx_SP->setMinimumSize(QSize(150, 22));
        cbx_SP->setMaximumSize(QSize(16777215, 22));
        cbx_SP->setBaseSize(QSize(200, 0));
        cbx_SP->setFont(font1);
        cbx_SP->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        gridLayout_2->addWidget(cbx_SP, 0, 2, 1, 1);

        label_16 = new QLabel(frame);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font1);

        gridLayout_2->addWidget(label_16, 0, 3, 1, 1);

        cbx_state = new QComboBox(frame);
        cbx_state->setObjectName(QString::fromUtf8("cbx_state"));
        sizePolicy.setHeightForWidth(cbx_state->sizePolicy().hasHeightForWidth());
        cbx_state->setSizePolicy(sizePolicy);
        cbx_state->setMinimumSize(QSize(150, 22));
        cbx_state->setMaximumSize(QSize(16777215, 22));
        cbx_state->setBaseSize(QSize(200, 0));
        cbx_state->setFont(font1);
        cbx_state->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbx_state, 0, 4, 1, 1);

        label_17 = new QLabel(frame);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font1);

        gridLayout_2->addWidget(label_17, 0, 5, 1, 1);

        txi_PhoneNo = new QLineEdit(frame);
        txi_PhoneNo->setObjectName(QString::fromUtf8("txi_PhoneNo"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txi_PhoneNo->sizePolicy().hasHeightForWidth());
        txi_PhoneNo->setSizePolicy(sizePolicy1);
        txi_PhoneNo->setMinimumSize(QSize(0, 22));
        txi_PhoneNo->setMaximumSize(QSize(16777215, 22));
        txi_PhoneNo->setFont(font1);
        txi_PhoneNo->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_PhoneNo->setMaxLength(11);

        gridLayout_2->addWidget(txi_PhoneNo, 0, 6, 1, 1);

        btn_search = new QPushButton(frame);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));
        btn_search->setMinimumSize(QSize(40, 25));
        btn_search->setMaximumSize(QSize(40, 25));
        btn_search->setFont(font1);
        btn_search->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cx.png);"));

        gridLayout_2->addWidget(btn_search, 0, 7, 1, 1);

        horizontalSpacer = new QSpacerItem(41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 8, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(1, 50, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 1, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        txt_rpt_total = new QLabel(frame_2);
        txt_rpt_total->setObjectName(QString::fromUtf8("txt_rpt_total"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        txt_rpt_total->setFont(font2);
        txt_rpt_total->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_total, 0, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 0, 1, 1, 1);

        txt_rpt_money = new QLabel(frame_2);
        txt_rpt_money->setObjectName(QString::fromUtf8("txt_rpt_money"));
        txt_rpt_money->setFont(font2);
        txt_rpt_money->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_money, 0, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 0, 3, 1, 1);

        txt_rpt_repay = new QLabel(frame_2);
        txt_rpt_repay->setObjectName(QString::fromUtf8("txt_rpt_repay"));
        txt_rpt_repay->setFont(font2);
        txt_rpt_repay->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_repay, 0, 4, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 0, 5, 1, 1);

        btn_fx = new QPushButton(frame_2);
        btn_fx->setObjectName(QString::fromUtf8("btn_fx"));

        gridLayout_3->addWidget(btn_fx, 0, 6, 1, 1);

        btn_cx = new QPushButton(frame_2);
        btn_cx->setObjectName(QString::fromUtf8("btn_cx"));

        gridLayout_3->addWidget(btn_cx, 0, 7, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 0, 8, 1, 1);

        btn_refresh = new QPushButton(frame_2);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        btn_refresh->setMinimumSize(QSize(40, 25));
        btn_refresh->setMaximumSize(QSize(40, 25));
        btn_refresh->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_3->addWidget(btn_refresh, 0, 9, 1, 1);

        btn_print = new QPushButton(frame_2);
        btn_print->setObjectName(QString::fromUtf8("btn_print"));
        btn_print->setMinimumSize(QSize(41, 41));
        btn_print->setMaximumSize(QSize(41, 41));
        btn_print->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_3->addWidget(btn_print, 0, 10, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(1, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 1, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 3, 0, 1, 1);

        jfrb_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(jfrb_ScrollArea);

        QMetaObject::connectSlotsByName(jfrb_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *jfrb_ScrollArea)
    {
        jfrb_ScrollArea->setWindowTitle(QApplication::translate("jfrb_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("jfrb_ScrollArea", "      \347\274\264\350\264\271\346\227\245\346\212\245", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("jfrb_ScrollArea", "\350\277\220\350\220\245\345\225\206\357\274\232", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("jfrb_ScrollArea", "\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("jfrb_ScrollArea", "\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_PhoneNo->setText(QString());
        btn_search->setText(QString());
        txt_rpt_total->setText(QApplication::translate("jfrb_ScrollArea", "\347\274\264\350\264\271\357\274\232\343\200\220100\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        txt_rpt_money->setText(QApplication::translate("jfrb_ScrollArea", "\347\274\264\350\264\271\351\207\221\351\242\235\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        txt_rpt_repay->setText(QApplication::translate("jfrb_ScrollArea", "\350\277\224\346\254\276\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        btn_fx->setText(QApplication::translate("jfrb_ScrollArea", "\350\277\224\351\224\200", 0, QApplication::UnicodeUTF8));
        btn_cx->setText(QApplication::translate("jfrb_ScrollArea", "\346\222\244\351\224\200", 0, QApplication::UnicodeUTF8));
        btn_refresh->setText(QString());
        btn_print->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class jfrb_ScrollArea: public Ui_jfrb_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JFRB_SCROLLAREA_H
