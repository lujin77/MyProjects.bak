/********************************************************************************
** Form generated from reading UI file 'yhxxxg_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:01 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YHXXXG_SCROLLAREA_H
#define UI_YHXXXG_SCROLLAREA_H

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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_yhxxxg_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_25;
    QLineEdit *txi_LoggingName;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_23;
    QLineEdit *txi_phone;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_24;
    QLineEdit *txi_address;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_26;
    QLineEdit *txi_shop_name;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_27;
    QLineEdit *txi_mobile_phone;
    QSpacerItem *horizontalSpacer_21;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_28;
    QLineEdit *txi_real_name;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_30;
    QLineEdit *txi_identify_no;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *horizontalSpacer_15;
    QLabel *label_29;
    QLineEdit *txi_worker_name;
    QSpacerItem *horizontalSpacer_24;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *btnSubmit;
    QPushButton *btnReset;
    QSpacerItem *horizontalSpacer_25;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *horizontalSpacer_27;
    QSpacerItem *horizontalSpacer_28;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QScrollArea *yhxxxg_ScrollArea)
    {
        if (yhxxxg_ScrollArea->objectName().isEmpty())
            yhxxxg_ScrollArea->setObjectName(QString::fromUtf8("yhxxxg_ScrollArea"));
        yhxxxg_ScrollArea->resize(900, 650);
        yhxxxg_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        yhxxxg_ScrollArea->setFrameShape(QFrame::NoFrame);
        yhxxxg_ScrollArea->setLineWidth(0);
        yhxxxg_ScrollArea->setWidgetResizable(true);
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

        horizontalSpacer_2 = new QSpacerItem(15, 500, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 74, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(262, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(150, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 2, 1, 2);

        horizontalSpacer_7 = new QSpacerItem(161, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 1, 4, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(273, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 2, 0, 1, 1);

        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_25->setFont(font1);

        gridLayout_2->addWidget(label_25, 2, 1, 1, 1);

        txi_LoggingName = new QLineEdit(frame);
        txi_LoggingName->setObjectName(QString::fromUtf8("txi_LoggingName"));
        txi_LoggingName->setMinimumSize(QSize(0, 22));
        txi_LoggingName->setMaximumSize(QSize(16777215, 22));
        txi_LoggingName->setFont(font1);
        txi_LoggingName->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_LoggingName->setReadOnly(true);

        gridLayout_2->addWidget(txi_LoggingName, 2, 2, 1, 2);

        horizontalSpacer_17 = new QSpacerItem(278, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_17, 2, 4, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(273, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 3, 0, 1, 1);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_2->addWidget(label_23, 3, 1, 1, 1);

        txi_phone = new QLineEdit(frame);
        txi_phone->setObjectName(QString::fromUtf8("txi_phone"));
        txi_phone->setMinimumSize(QSize(0, 22));
        txi_phone->setMaximumSize(QSize(16777215, 22));
        txi_phone->setFont(font1);
        txi_phone->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txi_phone, 3, 2, 1, 2);

        horizontalSpacer_18 = new QSpacerItem(278, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_18, 3, 4, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(273, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 4, 0, 1, 1);

        label_24 = new QLabel(frame);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font1);

        gridLayout_2->addWidget(label_24, 4, 1, 1, 1);

        txi_address = new QLineEdit(frame);
        txi_address->setObjectName(QString::fromUtf8("txi_address"));
        txi_address->setMinimumSize(QSize(0, 22));
        txi_address->setMaximumSize(QSize(16777215, 22));
        txi_address->setFont(font1);
        txi_address->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txi_address, 4, 2, 1, 2);

        horizontalSpacer_19 = new QSpacerItem(278, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_19, 4, 4, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(273, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 5, 0, 1, 1);

        label_26 = new QLabel(frame);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setFont(font1);

        gridLayout_2->addWidget(label_26, 5, 1, 1, 1);

        txi_shop_name = new QLineEdit(frame);
        txi_shop_name->setObjectName(QString::fromUtf8("txi_shop_name"));
        txi_shop_name->setMinimumSize(QSize(0, 22));
        txi_shop_name->setMaximumSize(QSize(16777215, 22));
        txi_shop_name->setFont(font1);
        txi_shop_name->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txi_shop_name, 5, 2, 1, 2);

        horizontalSpacer_20 = new QSpacerItem(272, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_20, 5, 4, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(273, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 6, 0, 1, 1);

        label_27 = new QLabel(frame);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font1);

        gridLayout_2->addWidget(label_27, 6, 1, 1, 1);

        txi_mobile_phone = new QLineEdit(frame);
        txi_mobile_phone->setObjectName(QString::fromUtf8("txi_mobile_phone"));
        txi_mobile_phone->setMinimumSize(QSize(0, 22));
        txi_mobile_phone->setMaximumSize(QSize(16777215, 22));
        txi_mobile_phone->setFont(font1);
        txi_mobile_phone->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txi_mobile_phone, 6, 2, 1, 2);

        horizontalSpacer_21 = new QSpacerItem(278, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_21, 6, 4, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(273, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_13, 7, 0, 1, 1);

        label_28 = new QLabel(frame);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setFont(font1);

        gridLayout_2->addWidget(label_28, 7, 1, 1, 1);

        txi_real_name = new QLineEdit(frame);
        txi_real_name->setObjectName(QString::fromUtf8("txi_real_name"));
        txi_real_name->setMinimumSize(QSize(0, 22));
        txi_real_name->setMaximumSize(QSize(16777215, 22));
        txi_real_name->setFont(font1);
        txi_real_name->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txi_real_name, 7, 2, 1, 2);

        horizontalSpacer_22 = new QSpacerItem(272, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_22, 7, 4, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(273, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_14, 8, 0, 1, 1);

        label_30 = new QLabel(frame);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font1);

        gridLayout_2->addWidget(label_30, 8, 1, 1, 1);

        txi_identify_no = new QLineEdit(frame);
        txi_identify_no->setObjectName(QString::fromUtf8("txi_identify_no"));
        txi_identify_no->setMinimumSize(QSize(0, 22));
        txi_identify_no->setMaximumSize(QSize(16777215, 22));
        txi_identify_no->setFont(font1);
        txi_identify_no->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txi_identify_no, 8, 2, 1, 2);

        horizontalSpacer_23 = new QSpacerItem(272, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_23, 8, 4, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(273, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_15, 9, 0, 1, 1);

        label_29 = new QLabel(frame);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setFont(font1);

        gridLayout_2->addWidget(label_29, 9, 1, 1, 1);

        txi_worker_name = new QLineEdit(frame);
        txi_worker_name->setObjectName(QString::fromUtf8("txi_worker_name"));
        txi_worker_name->setMinimumSize(QSize(0, 22));
        txi_worker_name->setMaximumSize(QSize(16777215, 22));
        txi_worker_name->setFont(font1);
        txi_worker_name->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txi_worker_name, 9, 2, 1, 2);

        horizontalSpacer_24 = new QSpacerItem(272, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_24, 9, 4, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(273, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_16, 10, 0, 1, 1);

        btnSubmit = new QPushButton(frame);
        btnSubmit->setObjectName(QString::fromUtf8("btnSubmit"));
        btnSubmit->setMinimumSize(QSize(62, 25));
        btnSubmit->setMaximumSize(QSize(62, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btnSubmit->setFont(font2);
        btnSubmit->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_qrxg.png);"));

        gridLayout_2->addWidget(btnSubmit, 10, 2, 1, 1);

        btnReset = new QPushButton(frame);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        btnReset->setMinimumSize(QSize(40, 25));
        btnReset->setMaximumSize(QSize(40, 25));
        btnReset->setFont(font2);
        btnReset->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cz.png);"));

        gridLayout_2->addWidget(btnReset, 10, 3, 1, 1);

        horizontalSpacer_25 = new QSpacerItem(272, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_25, 10, 4, 1, 1);

        horizontalSpacer_26 = new QSpacerItem(273, 69, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_26, 11, 0, 1, 1);

        horizontalSpacer_27 = new QSpacerItem(155, 69, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_27, 11, 2, 1, 2);

        horizontalSpacer_28 = new QSpacerItem(272, 69, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_28, 11, 4, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 73, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 12, 2, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        yhxxxg_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(yhxxxg_ScrollArea);

        QMetaObject::connectSlotsByName(yhxxxg_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *yhxxxg_ScrollArea)
    {
        yhxxxg_ScrollArea->setWindowTitle(QApplication::translate("yhxxxg_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("yhxxxg_ScrollArea", "      \344\277\256\346\224\271\347\224\250\346\210\267\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("yhxxxg_ScrollArea", "\347\231\273\345\275\225\347\224\250\346\210\267\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("yhxxxg_ScrollArea", "\350\201\224\347\263\273\347\224\265\350\257\235\357\274\232", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("yhxxxg_ScrollArea", "\345\225\206\351\223\272\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("yhxxxg_ScrollArea", "\345\225\206\351\223\272\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("yhxxxg_ScrollArea", "\347\247\273\345\212\250\347\224\265\350\257\235\357\274\232", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("yhxxxg_ScrollArea", "\347\234\237\345\256\236\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("yhxxxg_ScrollArea", "\350\272\253\344\273\275\350\257\201\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("yhxxxg_ScrollArea", "\344\270\232\345\212\241\350\264\237\350\264\243\344\272\272\357\274\232", 0, QApplication::UnicodeUTF8));
        btnSubmit->setText(QString());
        btnReset->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class yhxxxg_ScrollArea: public Ui_yhxxxg_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YHXXXG_SCROLLAREA_H
