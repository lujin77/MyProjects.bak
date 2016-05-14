/********************************************************************************
** Form generated from reading UI file 'dbfjs_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:01 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBFJS_SCROLLAREA_H
#define UI_DBFJS_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_dbfjs_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_27;
    QLineEdit *txt_last_time;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_25;
    QLineEdit *txt_current_money;
    QLabel *label_22;
    QLineEdit *txt_return_money;
    QLabel *label_26;
    QLineEdit *txt_new_money;
    QPushButton *btnSubmit;
    QSpacerItem *horizontalSpacer_11;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QScrollArea *dbfjs_ScrollArea)
    {
        if (dbfjs_ScrollArea->objectName().isEmpty())
            dbfjs_ScrollArea->setObjectName(QString::fromUtf8("dbfjs_ScrollArea"));
        dbfjs_ScrollArea->resize(900, 650);
        dbfjs_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dbfjs_ScrollArea->setFrameShape(QFrame::NoFrame);
        dbfjs_ScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 900, 650));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(0, 70));
        frame->setSizeIncrement(QSize(0, 70));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_8 = new QSpacerItem(175, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        label_27 = new QLabel(frame);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_27->setFont(font1);
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_27, 0, 1, 1, 1);

        txt_last_time = new QLineEdit(frame);
        txt_last_time->setObjectName(QString::fromUtf8("txt_last_time"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txt_last_time->sizePolicy().hasHeightForWidth());
        txt_last_time->setSizePolicy(sizePolicy1);
        txt_last_time->setMinimumSize(QSize(200, 22));
        txt_last_time->setMaximumSize(QSize(200, 22));
        txt_last_time->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";\n"
"background-color: rgb(255, 255, 255);"));
        txt_last_time->setReadOnly(true);

        gridLayout->addWidget(txt_last_time, 0, 2, 1, 2);

        horizontalSpacer_10 = new QSpacerItem(175, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 0, 6, 1, 3);

        horizontalSpacer_9 = new QSpacerItem(149, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 1, 0, 1, 1);

        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font1);
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_25, 1, 1, 1, 1);

        txt_current_money = new QLineEdit(frame);
        txt_current_money->setObjectName(QString::fromUtf8("txt_current_money"));
        sizePolicy1.setHeightForWidth(txt_current_money->sizePolicy().hasHeightForWidth());
        txt_current_money->setSizePolicy(sizePolicy1);
        txt_current_money->setMinimumSize(QSize(100, 22));
        txt_current_money->setMaximumSize(QSize(100, 22));
        txt_current_money->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";\n"
"background-color: rgb(255, 255, 255);"));
        txt_current_money->setReadOnly(true);

        gridLayout->addWidget(txt_current_money, 1, 2, 1, 1);

        label_22 = new QLabel(frame);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font1);

        gridLayout->addWidget(label_22, 1, 3, 1, 1);

        txt_return_money = new QLineEdit(frame);
        txt_return_money->setObjectName(QString::fromUtf8("txt_return_money"));
        sizePolicy1.setHeightForWidth(txt_return_money->sizePolicy().hasHeightForWidth());
        txt_return_money->setSizePolicy(sizePolicy1);
        txt_return_money->setMinimumSize(QSize(100, 22));
        txt_return_money->setMaximumSize(QSize(100, 22));
        txt_return_money->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";\n"
"background-color: rgb(255, 255, 255);"));
        txt_return_money->setReadOnly(true);

        gridLayout->addWidget(txt_return_money, 1, 4, 1, 1);

        label_26 = new QLabel(frame);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setFont(font1);

        gridLayout->addWidget(label_26, 1, 5, 1, 1);

        txt_new_money = new QLineEdit(frame);
        txt_new_money->setObjectName(QString::fromUtf8("txt_new_money"));
        sizePolicy1.setHeightForWidth(txt_new_money->sizePolicy().hasHeightForWidth());
        txt_new_money->setSizePolicy(sizePolicy1);
        txt_new_money->setMinimumSize(QSize(100, 22));
        txt_new_money->setMaximumSize(QSize(100, 22));
        txt_new_money->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";\n"
"background-color: rgb(255, 255, 255);"));
        txt_new_money->setReadOnly(true);

        gridLayout->addWidget(txt_new_money, 1, 6, 1, 1);

        btnSubmit = new QPushButton(frame);
        btnSubmit->setObjectName(QString::fromUtf8("btnSubmit"));
        btnSubmit->setMinimumSize(QSize(60, 25));
        btnSubmit->setMaximumSize(QSize(60, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        btnSubmit->setFont(font2);
        btnSubmit->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\256\213\344\275\223\";"));

        gridLayout->addWidget(btnSubmit, 1, 7, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(150, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_11, 1, 8, 1, 1);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer = new QSpacerItem(122, 60, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(122, 60, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(122, 297, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        tableWidget = new QTableWidget(frame_2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(600, 300));
        tableWidget->setMaximumSize(QSize(600, 300));
        tableWidget->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_3->addWidget(tableWidget, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(122, 297, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_3->addWidget(label_3, 2, 1, 2, 1);

        horizontalSpacer_5 = new QSpacerItem(122, 60, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 3, 2, 1, 1);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(170, 59, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 3, 0, 1, 1);


        gridLayout_2->addWidget(frame_2, 2, 0, 1, 1);

        dbfjs_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(dbfjs_ScrollArea);

        QMetaObject::connectSlotsByName(dbfjs_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *dbfjs_ScrollArea)
    {
        dbfjs_ScrollArea->setWindowTitle(QApplication::translate("dbfjs_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("dbfjs_ScrollArea", "      \344\273\243\345\212\236\350\264\271\347\273\223\347\256\227", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("dbfjs_ScrollArea", "\344\270\212\344\270\200\346\254\241\347\273\223\347\256\227\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("dbfjs_ScrollArea", "\350\264\246\346\210\267\344\275\231\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("dbfjs_ScrollArea", "\344\273\243\345\212\236\350\264\271\346\200\273\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("dbfjs_ScrollArea", "\347\273\223\347\256\227\345\220\216\344\275\231\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        btnSubmit->setText(QApplication::translate("dbfjs_ScrollArea", "\347\273\223\347\256\227", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("dbfjs_ScrollArea", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ff0000;\">\345\244\207\346\263\250\357\274\2321\343\200\201\351\253\230\347\272\247\347\224\250\346\210\267\345\217\252\350\203\275\347\273\223\347\256\227\344\270\212\344\270\200\344\270\252\346\234\210\347\232\204\346\234\252\350\277\224\346\254\276\351\207\221\351\242\235\357\274\210\345\214\205\346\213\254\344\270\212\346\234\210\344\271\213\345\211\215\347\232\204\357\274\211</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\""
                        " font-size:12pt; color:#ff0000;\">      2\343\200\201\345\205\266\344\273\226\347\224\250\346\210\267\345\217\257\344\273\245\347\273\223\347\256\227\345\275\223\345\211\215\346\211\200\346\234\211\347\232\204\346\234\252\347\273\223\347\256\227\351\207\221\351\242\235</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("dbfjs_ScrollArea", "\346\234\252\347\273\223\347\256\227\350\277\224\346\254\276\350\256\260\345\275\225\347\273\237\350\256\241\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dbfjs_ScrollArea: public Ui_dbfjs_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBFJS_SCROLLAREA_H
