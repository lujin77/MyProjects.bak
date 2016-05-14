/********************************************************************************
** Form generated from reading UI file 'kcxk_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KCXK_SCROLLAREA_H
#define UI_KCXK_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
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

class Ui_kcxk_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_21;
    QComboBox *cbx_sp;
    QLabel *label_22;
    QComboBox *cbx_state;
    QLabel *label_23;
    QComboBox *cbx_noSection;
    QPushButton *btn_search;
    QSpacerItem *horizontalSpacer_7;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_8;
    QLabel *txt_rpt_total;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_5;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *kcxk_ScrollArea)
    {
        if (kcxk_ScrollArea->objectName().isEmpty())
            kcxk_ScrollArea->setObjectName(QString::fromUtf8("kcxk_ScrollArea"));
        kcxk_ScrollArea->resize(900, 650);
        kcxk_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        kcxk_ScrollArea->setFrameShape(QFrame::NoFrame);
        kcxk_ScrollArea->setLineWidth(0);
        kcxk_ScrollArea->setWidgetResizable(true);
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
        horizontalSpacer_6 = new QSpacerItem(67, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 0, 1, 1);

        label_21 = new QLabel(frame);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_21->setFont(font1);

        gridLayout_2->addWidget(label_21, 0, 1, 1, 1);

        cbx_sp = new QComboBox(frame);
        cbx_sp->setObjectName(QString::fromUtf8("cbx_sp"));
        cbx_sp->setMinimumSize(QSize(150, 22));
        cbx_sp->setMaximumSize(QSize(16777215, 22));
        cbx_sp->setFont(font1);
        cbx_sp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbx_sp, 0, 2, 1, 1);

        label_22 = new QLabel(frame);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font1);

        gridLayout_2->addWidget(label_22, 0, 3, 1, 1);

        cbx_state = new QComboBox(frame);
        cbx_state->setObjectName(QString::fromUtf8("cbx_state"));
        cbx_state->setMinimumSize(QSize(150, 22));
        cbx_state->setMaximumSize(QSize(16777215, 22));
        cbx_state->setFont(font1);
        cbx_state->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbx_state, 0, 4, 1, 1);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_2->addWidget(label_23, 0, 5, 1, 1);

        cbx_noSection = new QComboBox(frame);
        cbx_noSection->setObjectName(QString::fromUtf8("cbx_noSection"));
        cbx_noSection->setMinimumSize(QSize(150, 22));
        cbx_noSection->setMaximumSize(QSize(16777215, 22));
        cbx_noSection->setFont(font1);
        cbx_noSection->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbx_noSection, 0, 6, 1, 1);

        btn_search = new QPushButton(frame);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_search->sizePolicy().hasHeightForWidth());
        btn_search->setSizePolicy(sizePolicy);
        btn_search->setMinimumSize(QSize(40, 25));
        btn_search->setMaximumSize(QSize(40, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btn_search->setFont(font2);
        btn_search->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cx.png);"));

        gridLayout_2->addWidget(btn_search, 0, 7, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(67, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 8, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_8 = new QSpacerItem(371, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        txt_rpt_total = new QLabel(frame_2);
        txt_rpt_total->setObjectName(QString::fromUtf8("txt_rpt_total"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(10);
        txt_rpt_total->setFont(font3);
        txt_rpt_total->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_total, 0, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(370, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 0, 2, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(855, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 4, 0, 1, 1);

        kcxk_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(kcxk_ScrollArea);

        QMetaObject::connectSlotsByName(kcxk_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *kcxk_ScrollArea)
    {
        kcxk_ScrollArea->setWindowTitle(QApplication::translate("kcxk_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("kcxk_ScrollArea", "      \345\272\223\345\255\230\345\260\217\345\215\241", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("kcxk_ScrollArea", "\350\277\220\350\220\245\345\225\206\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("kcxk_ScrollArea", "\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("kcxk_ScrollArea", "\345\217\267\346\256\265\357\274\232", 0, QApplication::UnicodeUTF8));
        btn_search->setText(QString());
        txt_rpt_total->setText(QApplication::translate("kcxk_ScrollArea", "\345\205\261\357\274\232\343\200\22010\343\200\221\345\274\240", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class kcxk_ScrollArea: public Ui_kcxk_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KCXK_SCROLLAREA_H
