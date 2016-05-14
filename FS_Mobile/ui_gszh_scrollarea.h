/********************************************************************************
** Form generated from reading UI file 'gszh_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:01 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSZH_SCROLLAREA_H
#define UI_GSZH_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gszh_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *txt_title;
    QSpacerItem *horizontalSpacer_7;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *gszh_ScrollArea)
    {
        if (gszh_ScrollArea->objectName().isEmpty())
            gszh_ScrollArea->setObjectName(QString::fromUtf8("gszh_ScrollArea"));
        gszh_ScrollArea->resize(900, 650);
        gszh_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gszh_ScrollArea->setFrameShape(QFrame::NoFrame);
        gszh_ScrollArea->setLineWidth(0);
        gszh_ScrollArea->setWidgetResizable(true);
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

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(317, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 0, 1, 1);

        txt_title = new QLabel(frame_2);
        txt_title->setObjectName(QString::fromUtf8("txt_title"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        txt_title->setFont(font1);
        txt_title->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_2->addWidget(txt_title, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(271, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 2, 1, 1);


        gridLayout->addWidget(frame_2, 1, 0, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("font: 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 2, 0, 1, 1);

        gszh_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(gszh_ScrollArea);

        QMetaObject::connectSlotsByName(gszh_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *gszh_ScrollArea)
    {
        gszh_ScrollArea->setWindowTitle(QApplication::translate("gszh_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("gszh_ScrollArea", "      \345\205\254\345\217\270\350\264\246\346\210\267", 0, QApplication::UnicodeUTF8));
        txt_title->setText(QApplication::translate("gszh_ScrollArea", "\347\247\273\345\212\250\345\256\242\346\210\267\347\253\257\344\270\223\347\224\250\350\264\246\345\217\267", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gszh_ScrollArea: public Ui_gszh_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSZH_SCROLLAREA_H
