/********************************************************************************
** Form generated from reading UI file 'xgmm_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:01 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XGMM_SCROLLAREA_H
#define UI_XGMM_SCROLLAREA_H

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

class Ui_xgmm_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_25;
    QLineEdit *txiName;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_23;
    QLineEdit *txiOldPassword;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_24;
    QLineEdit *txiNewPassword;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_26;
    QLineEdit *txiReNewPassword;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *btnSubmit;
    QPushButton *btnReset;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QScrollArea *xgmm_ScrollArea)
    {
        if (xgmm_ScrollArea->objectName().isEmpty())
            xgmm_ScrollArea->setObjectName(QString::fromUtf8("xgmm_ScrollArea"));
        xgmm_ScrollArea->resize(900, 650);
        xgmm_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        xgmm_ScrollArea->setFrameShape(QFrame::NoFrame);
        xgmm_ScrollArea->setLineWidth(0);
        xgmm_ScrollArea->setWidgetResizable(true);
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
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 74, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 2, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(259, 117, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_15, 1, 0, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(197, 117, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_16, 1, 2, 1, 3);

        horizontalSpacer_17 = new QSpacerItem(259, 117, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_17, 1, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(259, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 2, 0, 1, 1);

        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_25->setFont(font1);

        gridLayout_2->addWidget(label_25, 2, 1, 1, 1);

        txiName = new QLineEdit(frame);
        txiName->setObjectName(QString::fromUtf8("txiName"));
        txiName->setMinimumSize(QSize(200, 22));
        txiName->setMaximumSize(QSize(200, 22));
        txiName->setFont(font1);
        txiName->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txiName->setReadOnly(true);

        gridLayout_2->addWidget(txiName, 2, 2, 1, 3);

        horizontalSpacer_10 = new QSpacerItem(259, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 2, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(259, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 3, 0, 1, 1);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_2->addWidget(label_23, 3, 1, 1, 1);

        txiOldPassword = new QLineEdit(frame);
        txiOldPassword->setObjectName(QString::fromUtf8("txiOldPassword"));
        txiOldPassword->setMinimumSize(QSize(200, 22));
        txiOldPassword->setMaximumSize(QSize(200, 22));
        txiOldPassword->setFont(font1);
        txiOldPassword->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txiOldPassword->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(txiOldPassword, 3, 2, 1, 3);

        horizontalSpacer_11 = new QSpacerItem(259, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 3, 5, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(259, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 4, 0, 1, 1);

        label_24 = new QLabel(frame);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font1);

        gridLayout_2->addWidget(label_24, 4, 1, 1, 1);

        txiNewPassword = new QLineEdit(frame);
        txiNewPassword->setObjectName(QString::fromUtf8("txiNewPassword"));
        txiNewPassword->setMinimumSize(QSize(200, 22));
        txiNewPassword->setMaximumSize(QSize(200, 22));
        txiNewPassword->setFont(font1);
        txiNewPassword->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txiNewPassword->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(txiNewPassword, 4, 2, 1, 3);

        horizontalSpacer_12 = new QSpacerItem(259, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 4, 5, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(259, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 5, 0, 1, 1);

        label_26 = new QLabel(frame);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setFont(font1);

        gridLayout_2->addWidget(label_26, 5, 1, 1, 1);

        txiReNewPassword = new QLineEdit(frame);
        txiReNewPassword->setObjectName(QString::fromUtf8("txiReNewPassword"));
        txiReNewPassword->setMinimumSize(QSize(200, 22));
        txiReNewPassword->setMaximumSize(QSize(200, 22));
        txiReNewPassword->setFont(font1);
        txiReNewPassword->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txiReNewPassword->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(txiReNewPassword, 5, 2, 1, 3);

        horizontalSpacer_13 = new QSpacerItem(259, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_13, 5, 5, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(259, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 6, 0, 1, 1);

        btnSubmit = new QPushButton(frame);
        btnSubmit->setObjectName(QString::fromUtf8("btnSubmit"));
        btnSubmit->setMinimumSize(QSize(61, 25));
        btnSubmit->setMaximumSize(QSize(61, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btnSubmit->setFont(font2);
        btnSubmit->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_qrxg.png);"));

        gridLayout_2->addWidget(btnSubmit, 6, 3, 1, 1);

        btnReset = new QPushButton(frame);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        btnReset->setMinimumSize(QSize(40, 25));
        btnReset->setMaximumSize(QSize(40, 25));
        btnReset->setFont(font2);
        btnReset->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cz.png);"));

        gridLayout_2->addWidget(btnReset, 6, 4, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(259, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_14, 6, 5, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(259, 117, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_18, 7, 0, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(197, 117, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_19, 7, 2, 1, 3);

        horizontalSpacer_20 = new QSpacerItem(259, 117, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_20, 7, 5, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 74, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 8, 2, 1, 2);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(15, 500, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        xgmm_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(xgmm_ScrollArea);

        QMetaObject::connectSlotsByName(xgmm_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *xgmm_ScrollArea)
    {
        xgmm_ScrollArea->setWindowTitle(QApplication::translate("xgmm_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("xgmm_ScrollArea", "      \344\277\256\346\224\271\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("xgmm_ScrollArea", "\347\231\273\345\275\225\347\224\250\346\210\267\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("xgmm_ScrollArea", "\346\227\247\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("xgmm_ScrollArea", "\346\226\260\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("xgmm_ScrollArea", "\347\241\256\350\256\244\346\226\260\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        btnSubmit->setText(QString());
        btnReset->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class xgmm_ScrollArea: public Ui_xgmm_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XGMM_SCROLLAREA_H
