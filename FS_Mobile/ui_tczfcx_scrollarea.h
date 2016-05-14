/********************************************************************************
** Form generated from reading UI file 'tczfcx_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCZFCX_SCROLLAREA_H
#define UI_TCZFCX_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tczfcx_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *tczfcx_ScrollArea)
    {
        if (tczfcx_ScrollArea->objectName().isEmpty())
            tczfcx_ScrollArea->setObjectName(QString::fromUtf8("tczfcx_ScrollArea"));
        tczfcx_ScrollArea->resize(900, 650);
        tczfcx_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tczfcx_ScrollArea->setFrameShape(QFrame::NoFrame);
        tczfcx_ScrollArea->setLineWidth(0);
        tczfcx_ScrollArea->setWidgetResizable(true);
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

        horizontalSpacer_3 = new QSpacerItem(855, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(15, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setLineWidth(0);
        tableWidget->setAutoScrollMargin(0);
        tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setSortingEnabled(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);

        gridLayout->addWidget(tableWidget, 2, 0, 1, 2);

        tczfcx_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(tczfcx_ScrollArea);

        QMetaObject::connectSlotsByName(tczfcx_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *tczfcx_ScrollArea)
    {
        tczfcx_ScrollArea->setWindowTitle(QApplication::translate("tczfcx_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("tczfcx_ScrollArea", "      \345\245\227\351\244\220\350\265\204\350\264\271\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class tczfcx_ScrollArea: public Ui_tczfcx_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCZFCX_SCROLLAREA_H
