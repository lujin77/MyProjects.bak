/********************************************************************************
** Form generated from reading UI file 'jf_scrollarea.ui'
**
** Created: Sun Dec 16 13:43:32 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JF_SCROLLAREA_H
#define UI_JF_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_jf_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *txt_title;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QLineEdit *txi_PhoneNo;
    QPushButton *btn_submit;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QLineEdit *txi_money;
    QPushButton *btn_search;
    QPushButton *btn_reset;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QLabel *txt_area;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_6;
    QLabel *txt_name;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_8;
    QLabel *txt_now_money;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *horizontalSpacer_18;
    QLabel *label_10;
    QLabel *txt_brand;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_15;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QLabel *txt_rpt_count;
    QSpacerItem *horizontalSpacer_17;
    QLabel *txt_rpt_money;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *btnPayWithList;
    QGroupBox *groupBox;
    QRadioButton *rdo_print_on;
    QRadioButton *rdo_print_off;
    QPushButton *btn_refresh;
    QPushButton *btn_print;
    QTableWidget *tbl_detail;

    void setupUi(QScrollArea *jf_ScrollArea)
    {
        if (jf_ScrollArea->objectName().isEmpty())
            jf_ScrollArea->setObjectName(QString::fromUtf8("jf_ScrollArea"));
        jf_ScrollArea->resize(900, 650);
        jf_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        jf_ScrollArea->setFrameShape(QFrame::NoFrame);
        jf_ScrollArea->setLineWidth(0);
        jf_ScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 900, 650));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        txt_title = new QLabel(scrollAreaWidgetContents);
        txt_title->setObjectName(QString::fromUtf8("txt_title"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txt_title->sizePolicy().hasHeightForWidth());
        txt_title->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        txt_title->setFont(font);
        txt_title->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout_2->addWidget(txt_title, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(1, 25, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_3 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(28);
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 0, 1, 2, 1);

        txi_PhoneNo = new QLineEdit(frame);
        txi_PhoneNo->setObjectName(QString::fromUtf8("txi_PhoneNo"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txi_PhoneNo->sizePolicy().hasHeightForWidth());
        txi_PhoneNo->setSizePolicy(sizePolicy1);
        txi_PhoneNo->setMinimumSize(QSize(240, 46));
        txi_PhoneNo->setMaximumSize(QSize(220, 46));
        txi_PhoneNo->setFont(font1);
        txi_PhoneNo->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 0, 0);"));
        txi_PhoneNo->setMaxLength(12);
        txi_PhoneNo->setCursorPosition(0);

        gridLayout->addWidget(txi_PhoneNo, 0, 2, 2, 1);

        btn_submit = new QPushButton(frame);
        btn_submit->setObjectName(QString::fromUtf8("btn_submit"));
        btn_submit->setMinimumSize(QSize(110, 40));
        btn_submit->setMaximumSize(QSize(110, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btn_submit->setFont(font2);
        btn_submit->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout->addWidget(btn_submit, 0, 3, 2, 2);

        horizontalSpacer_8 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 1, 5, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        txi_money = new QLineEdit(frame);
        txi_money->setObjectName(QString::fromUtf8("txi_money"));
        sizePolicy1.setHeightForWidth(txi_money->sizePolicy().hasHeightForWidth());
        txi_money->setSizePolicy(sizePolicy1);
        txi_money->setMinimumSize(QSize(240, 46));
        txi_money->setMaximumSize(QSize(220, 46));
        txi_money->setFont(font1);
        txi_money->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_money->setMaxLength(11);

        gridLayout->addWidget(txi_money, 2, 2, 1, 1);

        btn_search = new QPushButton(frame);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));
        btn_search->setMinimumSize(QSize(50, 40));
        btn_search->setMaximumSize(QSize(50, 40));
        btn_search->setFont(font2);
        btn_search->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout->addWidget(btn_search, 2, 3, 1, 1);

        btn_reset = new QPushButton(frame);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        btn_reset->setMinimumSize(QSize(50, 40));
        btn_reset->setMaximumSize(QSize(50, 40));
        btn_reset->setFont(font2);
        btn_reset->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout->addWidget(btn_reset, 2, 4, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 2, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);

        gridLayout->addWidget(label_4, 3, 1, 1, 1);

        txt_area = new QLabel(frame);
        txt_area->setObjectName(QString::fromUtf8("txt_area"));
        txt_area->setFont(font2);
        txt_area->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout->addWidget(txt_area, 3, 2, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 3, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 4, 0, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font2);

        gridLayout->addWidget(label_6, 4, 1, 1, 1);

        txt_name = new QLabel(frame);
        txt_name->setObjectName(QString::fromUtf8("txt_name"));
        txt_name->setFont(font2);
        txt_name->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout->addWidget(txt_name, 4, 2, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_11, 4, 5, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 5, 0, 1, 1);

        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font2);

        gridLayout->addWidget(label_8, 5, 1, 1, 1);

        txt_now_money = new QLabel(frame);
        txt_now_money->setObjectName(QString::fromUtf8("txt_now_money"));
        txt_now_money->setFont(font2);
        txt_now_money->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout->addWidget(txt_now_money, 5, 2, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_12, 5, 5, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(79, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_18, 6, 0, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font2);

        gridLayout->addWidget(label_10, 6, 1, 1, 1);

        txt_brand = new QLabel(frame);
        txt_brand->setObjectName(QString::fromUtf8("txt_brand"));
        txt_brand->setFont(font2);
        txt_brand->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout->addWidget(txt_brand, 6, 2, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(78, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_19, 6, 5, 1, 1);


        gridLayout_2->addWidget(frame, 1, 0, 3, 1);

        horizontalSpacer_2 = new QSpacerItem(1, 200, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(1, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_13, 2, 1, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_15, 3, 1, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        txt_rpt_count = new QLabel(frame_2);
        txt_rpt_count->setObjectName(QString::fromUtf8("txt_rpt_count"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(10);
        txt_rpt_count->setFont(font3);
        txt_rpt_count->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_count, 0, 0, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_17, 0, 1, 1, 1);

        txt_rpt_money = new QLabel(frame_2);
        txt_rpt_money->setObjectName(QString::fromUtf8("txt_rpt_money"));
        txt_rpt_money->setFont(font3);
        txt_rpt_money->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_money, 0, 2, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_14, 0, 3, 1, 1);

        btnPayWithList = new QPushButton(frame_2);
        btnPayWithList->setObjectName(QString::fromUtf8("btnPayWithList"));

        gridLayout_3->addWidget(btnPayWithList, 0, 4, 1, 1);

        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(91, 41));
        rdo_print_on = new QRadioButton(groupBox);
        rdo_print_on->setObjectName(QString::fromUtf8("rdo_print_on"));
        rdo_print_on->setGeometry(QRect(10, 17, 41, 16));
        rdo_print_off = new QRadioButton(groupBox);
        rdo_print_off->setObjectName(QString::fromUtf8("rdo_print_off"));
        rdo_print_off->setGeometry(QRect(50, 17, 31, 16));
        rdo_print_off->setChecked(true);

        gridLayout_3->addWidget(groupBox, 0, 5, 1, 1);

        btn_refresh = new QPushButton(frame_2);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        btn_refresh->setMinimumSize(QSize(40, 25));
        btn_refresh->setMaximumSize(QSize(40, 25));
        btn_refresh->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_3->addWidget(btn_refresh, 0, 6, 1, 1);

        btn_print = new QPushButton(frame_2);
        btn_print->setObjectName(QString::fromUtf8("btn_print"));
        sizePolicy1.setHeightForWidth(btn_print->sizePolicy().hasHeightForWidth());
        btn_print->setSizePolicy(sizePolicy1);
        btn_print->setMinimumSize(QSize(41, 41));
        btn_print->setMaximumSize(QSize(41, 41));
        btn_print->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_3->addWidget(btn_print, 0, 7, 1, 1);


        gridLayout_2->addWidget(frame_2, 4, 0, 1, 1);

        tbl_detail = new QTableWidget(scrollAreaWidgetContents);
        tbl_detail->setObjectName(QString::fromUtf8("tbl_detail"));
        tbl_detail->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tbl_detail->setFrameShape(QFrame::NoFrame);
        tbl_detail->setGridStyle(Qt::SolidLine);

        gridLayout_2->addWidget(tbl_detail, 5, 0, 1, 1);

        jf_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(jf_ScrollArea);

        QMetaObject::connectSlotsByName(jf_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *jf_ScrollArea)
    {
        jf_ScrollArea->setWindowTitle(QApplication::translate("jf_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        txt_title->setText(QApplication::translate("jf_ScrollArea", "      \347\247\273\345\212\250\347\274\264\350\264\271", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("jf_ScrollArea", "\347\224\265\350\257\235\345\217\267\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_PhoneNo->setText(QString());
        btn_submit->setText(QApplication::translate("jf_ScrollArea", "\347\241\256\350\256\244\347\274\264\350\264\271", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("jf_ScrollArea", "\347\274\264\350\264\271\351\207\221\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_money->setText(QString());
        btn_search->setText(QApplication::translate("jf_ScrollArea", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        btn_reset->setText(QApplication::translate("jf_ScrollArea", "\351\207\215\347\275\256", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("jf_ScrollArea", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\217\267\347\240\201\345\275\222\345\261\236\357\274\232</p></body></html>", 0, QApplication::UnicodeUTF8));
        txt_area->setText(QString());
        label_6->setText(QApplication::translate("jf_ScrollArea", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\224\250\346\210\267\345\247\223\345\220\215\357\274\232</p></body></html>", 0, QApplication::UnicodeUTF8));
        txt_name->setText(QString());
        label_8->setText(QApplication::translate("jf_ScrollArea", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\275\223\345\211\215\344\275\231\351\242\235\357\274\232</p></body></html>", 0, QApplication::UnicodeUTF8));
        txt_now_money->setText(QString());
        label_10->setText(QApplication::translate("jf_ScrollArea", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\256\213\344\275\223'; font-size:14pt;\">\345\275\223\345\211\215\345\223\201\347\211\214\357\274\232</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        txt_brand->setText(QString());
        txt_rpt_count->setText(QApplication::translate("jf_ScrollArea", "\347\274\264\350\264\271\357\274\232\343\200\220100\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        txt_rpt_money->setText(QApplication::translate("jf_ScrollArea", "\347\274\264\350\264\271\351\207\221\351\242\235\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        btnPayWithList->setText(QApplication::translate("jf_ScrollArea", "\346\211\271\351\207\217\347\274\264\350\264\271", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("jf_ScrollArea", "\351\273\230\350\256\244\346\211\223\345\215\260", 0, QApplication::UnicodeUTF8));
        rdo_print_on->setText(QApplication::translate("jf_ScrollArea", "\345\274\200", 0, QApplication::UnicodeUTF8));
        rdo_print_off->setText(QApplication::translate("jf_ScrollArea", "\345\205\263", 0, QApplication::UnicodeUTF8));
        btn_refresh->setText(QString());
        btn_print->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class jf_ScrollArea: public Ui_jf_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JF_SCROLLAREA_H
