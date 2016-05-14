/********************************************************************************
** Form generated from reading UI file 'skcx_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKCX_SCROLLAREA_H
#define UI_SKCX_SCROLLAREA_H

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

class Ui_skcx_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QLabel *label_24;
    QDateEdit *txiStartDate;
    QLabel *label_25;
    QDateEdit *txiEndDate;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_21;
    QComboBox *cbx_sp;
    QLabel *label_22;
    QComboBox *cbx_state;
    QLabel *label_23;
    QLineEdit *txi_no;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btn_search;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *txt_rpt_total;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btn_refresh;
    QPushButton *btn_print;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *skcx_ScrollArea)
    {
        if (skcx_ScrollArea->objectName().isEmpty())
            skcx_ScrollArea->setObjectName(QString::fromUtf8("skcx_ScrollArea"));
        skcx_ScrollArea->resize(900, 650);
        skcx_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        skcx_ScrollArea->setFrameShape(QFrame::NoFrame);
        skcx_ScrollArea->setLineWidth(0);
        skcx_ScrollArea->setWidgetResizable(true);
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
        label_24 = new QLabel(frame);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_24->setFont(font1);

        gridLayout_3->addWidget(label_24, 0, 2, 1, 2);

        txiStartDate = new QDateEdit(frame);
        txiStartDate->setObjectName(QString::fromUtf8("txiStartDate"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txiStartDate->sizePolicy().hasHeightForWidth());
        txiStartDate->setSizePolicy(sizePolicy);
        txiStartDate->setMinimumSize(QSize(0, 22));
        txiStartDate->setMaximumSize(QSize(16777215, 22));
        txiStartDate->setFont(font1);
        txiStartDate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txiStartDate->setCalendarPopup(true);

        gridLayout_3->addWidget(txiStartDate, 0, 4, 1, 1);

        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font1);

        gridLayout_3->addWidget(label_25, 0, 5, 1, 2);

        txiEndDate = new QDateEdit(frame);
        txiEndDate->setObjectName(QString::fromUtf8("txiEndDate"));
        txiEndDate->setMinimumSize(QSize(0, 22));
        txiEndDate->setMaximumSize(QSize(16777215, 22));
        txiEndDate->setFont(font1);
        txiEndDate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txiEndDate->setCalendarPopup(true);

        gridLayout_3->addWidget(txiEndDate, 0, 7, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 0, 12, 1, 1);

        label_21 = new QLabel(frame);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font1);

        gridLayout_3->addWidget(label_21, 2, 2, 1, 1);

        cbx_sp = new QComboBox(frame);
        cbx_sp->setObjectName(QString::fromUtf8("cbx_sp"));
        cbx_sp->setMinimumSize(QSize(0, 22));
        cbx_sp->setMaximumSize(QSize(16777215, 22));
        cbx_sp->setFont(font1);
        cbx_sp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(cbx_sp, 2, 3, 1, 2);

        label_22 = new QLabel(frame);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font1);

        gridLayout_3->addWidget(label_22, 2, 5, 1, 1);

        cbx_state = new QComboBox(frame);
        cbx_state->setObjectName(QString::fromUtf8("cbx_state"));
        cbx_state->setMinimumSize(QSize(0, 22));
        cbx_state->setMaximumSize(QSize(16777215, 22));
        cbx_state->setFont(font1);
        cbx_state->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(cbx_state, 2, 6, 1, 2);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_3->addWidget(label_23, 2, 8, 1, 1);

        txi_no = new QLineEdit(frame);
        txi_no->setObjectName(QString::fromUtf8("txi_no"));
        txi_no->setMinimumSize(QSize(0, 22));
        txi_no->setMaximumSize(QSize(16777215, 22));
        txi_no->setFont(font1);
        txi_no->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no->setMaxLength(11);

        gridLayout_3->addWidget(txi_no, 2, 9, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(61, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 2, 12, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 2, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 0, 1, 1, 1);

        btn_search = new QPushButton(frame);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_search->sizePolicy().hasHeightForWidth());
        btn_search->setSizePolicy(sizePolicy1);
        btn_search->setMinimumSize(QSize(40, 25));
        btn_search->setMaximumSize(QSize(40, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btn_search->setFont(font2);
        btn_search->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cx.png);"));

        gridLayout_3->addWidget(btn_search, 2, 11, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        txt_rpt_total = new QLabel(frame_2);
        txt_rpt_total->setObjectName(QString::fromUtf8("txt_rpt_total"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(10);
        txt_rpt_total->setFont(font3);
        txt_rpt_total->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_total, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        btn_refresh = new QPushButton(frame_2);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        sizePolicy1.setHeightForWidth(btn_refresh->sizePolicy().hasHeightForWidth());
        btn_refresh->setSizePolicy(sizePolicy1);
        btn_refresh->setMinimumSize(QSize(40, 25));
        btn_refresh->setMaximumSize(QSize(40, 25));
        btn_refresh->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_2->addWidget(btn_refresh, 0, 3, 1, 1);

        btn_print = new QPushButton(frame_2);
        btn_print->setObjectName(QString::fromUtf8("btn_print"));
        sizePolicy1.setHeightForWidth(btn_print->sizePolicy().hasHeightForWidth());
        btn_print->setSizePolicy(sizePolicy1);
        btn_print->setMinimumSize(QSize(41, 41));
        btn_print->setMaximumSize(QSize(41, 41));
        btn_print->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_2->addWidget(btn_print, 0, 4, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 3, 0, 1, 1);

        skcx_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(skcx_ScrollArea);

        QMetaObject::connectSlotsByName(skcx_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *skcx_ScrollArea)
    {
        skcx_ScrollArea->setWindowTitle(QApplication::translate("skcx_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("skcx_ScrollArea", "      \345\224\256\345\215\241\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("skcx_ScrollArea", "\350\265\267\345\247\213\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("skcx_ScrollArea", "\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("skcx_ScrollArea", "\350\277\220\350\220\245\345\225\206\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("skcx_ScrollArea", "\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("skcx_ScrollArea", "\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_no->setText(QString());
        btn_search->setText(QString());
        txt_rpt_total->setText(QApplication::translate("skcx_ScrollArea", "\345\205\261:\343\200\22010\343\200\221\346\235\241\345\224\256\345\215\241\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        btn_refresh->setText(QString());
        btn_print->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class skcx_ScrollArea: public Ui_skcx_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKCX_SCROLLAREA_H
