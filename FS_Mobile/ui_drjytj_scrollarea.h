/********************************************************************************
** Form generated from reading UI file 'drjytj_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:01 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRJYTJ_SCROLLAREA_H
#define UI_DRJYTJ_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_drjytj_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_24;
    QDateEdit *txiStartDate;
    QLabel *label_25;
    QDateEdit *txiEndDate;
    QPushButton *btn_submit;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame_3;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_6;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QScrollArea *drjytj_ScrollArea)
    {
        if (drjytj_ScrollArea->objectName().isEmpty())
            drjytj_ScrollArea->setObjectName(QString::fromUtf8("drjytj_ScrollArea"));
        drjytj_ScrollArea->resize(900, 650);
        drjytj_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        drjytj_ScrollArea->setFrameShape(QFrame::NoFrame);
        drjytj_ScrollArea->setLineWidth(0);
        drjytj_ScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 900, 650));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
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

        gridLayout->addWidget(label, 0, 0, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(0, 50));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(268, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 0, 1, 1);

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
        txiEndDate->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(txiEndDate, 0, 4, 1, 1);

        btn_submit = new QPushButton(frame);
        btn_submit->setObjectName(QString::fromUtf8("btn_submit"));
        btn_submit->setFont(font1);
        btn_submit->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout_3->addWidget(btn_submit, 0, 5, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(267, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 6, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        frame_3 = new QFrame(scrollAreaWidgetContents);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(597, 86, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 3);

        horizontalSpacer_6 = new QSpacerItem(122, 297, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        tableWidget = new QTableWidget(frame_3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(600, 300));
        tableWidget->setMaximumSize(QSize(600, 300));
        tableWidget->setAutoFillBackground(false);
        tableWidget->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setTabKeyNavigation(true);
        tableWidget->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(tableWidget, 1, 1, 1, 3);

        horizontalSpacer_7 = new QSpacerItem(122, 297, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 1, 4, 1, 1);

        verticalSpacer_2 = new QSpacerItem(193, 125, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer_2, 2, 2, 1, 1);


        gridLayout->addWidget(frame_3, 2, 0, 1, 1);

        drjytj_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(drjytj_ScrollArea);

        QMetaObject::connectSlotsByName(drjytj_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *drjytj_ScrollArea)
    {
        drjytj_ScrollArea->setWindowTitle(QApplication::translate("drjytj_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("drjytj_ScrollArea", "      \345\275\223\346\227\245\344\272\244\346\230\223\347\273\237\350\256\241", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("drjytj_ScrollArea", "\350\265\267\345\247\213\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("drjytj_ScrollArea", "\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        btn_submit->setText(QApplication::translate("drjytj_ScrollArea", "\345\274\200\345\247\213\347\273\237\350\256\241", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class drjytj_ScrollArea: public Ui_drjytj_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRJYTJ_SCROLLAREA_H
