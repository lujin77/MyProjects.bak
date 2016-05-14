/********************************************************************************
** Form generated from reading UI file 'ywbl_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YWBL_SCROLLAREA_H
#define UI_YWBL_SCROLLAREA_H

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

class Ui_ywbl_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *ywbl_ScrollArea)
    {
        if (ywbl_ScrollArea->objectName().isEmpty())
            ywbl_ScrollArea->setObjectName(QString::fromUtf8("ywbl_ScrollArea"));
        ywbl_ScrollArea->resize(900, 650);
        ywbl_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        ywbl_ScrollArea->setFrameShape(QFrame::NoFrame);
        ywbl_ScrollArea->setLineWidth(0);
        ywbl_ScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 900, 650));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(197, 523, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 3, 1);

        horizontalSpacer_2 = new QSpacerItem(197, 523, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 3, 1);

        tableWidget = new QTableWidget(frame);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(450, 0));
        tableWidget->setMaximumSize(QSize(450, 16777215));
        tableWidget->setLayoutDirection(Qt::LeftToRight);
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidget->setTextElideMode(Qt::ElideNone);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setColumnCount(1);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);

        gridLayout->addWidget(tableWidget, 1, 1, 1, 1);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        ywbl_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(ywbl_ScrollArea);

        QMetaObject::connectSlotsByName(ywbl_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *ywbl_ScrollArea)
    {
        ywbl_ScrollArea->setWindowTitle(QApplication::translate("ywbl_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ywbl_ScrollArea", "      \344\270\232\345\212\241\345\217\227\347\220\206", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ywbl_ScrollArea: public Ui_ywbl_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YWBL_SCROLLAREA_H
