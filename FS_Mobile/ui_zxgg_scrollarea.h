/********************************************************************************
** Form generated from reading UI file 'zxgg_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZXGG_SCROLLAREA_H
#define UI_ZXGG_SCROLLAREA_H

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
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_zxgg_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QLabel *txt_rpt_total;
    QSpacerItem *horizontalSpacer_8;
    QLabel *txt_rpt_current_3;
    QLineEdit *txi_line_num;
    QLabel *txt_rpt_current_4;
    QPushButton *btnFront;
    QPushButton *btnPre;
    QLabel *txt_rpt_current;
    QSpinBox *spinBox;
    QLabel *txt_rpt_current_2;
    QPushButton *btnNext;
    QPushButton *btnTail;
    QSpacerItem *horizontalSpacer_11;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *zxgg_ScrollArea)
    {
        if (zxgg_ScrollArea->objectName().isEmpty())
            zxgg_ScrollArea->setObjectName(QString::fromUtf8("zxgg_ScrollArea"));
        zxgg_ScrollArea->resize(900, 650);
        zxgg_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        zxgg_ScrollArea->setFrameShape(QFrame::NoFrame);
        zxgg_ScrollArea->setWidgetResizable(true);
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
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(0, 50));
        frame_2->setMaximumSize(QSize(16777215, 50));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        txt_rpt_total = new QLabel(frame_2);
        txt_rpt_total->setObjectName(QString::fromUtf8("txt_rpt_total"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(10);
        txt_rpt_total->setFont(font1);
        txt_rpt_total->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_total, 0, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 1, 1, 1);

        txt_rpt_current_3 = new QLabel(frame_2);
        txt_rpt_current_3->setObjectName(QString::fromUtf8("txt_rpt_current_3"));
        txt_rpt_current_3->setFont(font1);
        txt_rpt_current_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_current_3, 0, 2, 1, 1);

        txi_line_num = new QLineEdit(frame_2);
        txi_line_num->setObjectName(QString::fromUtf8("txi_line_num"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txi_line_num->sizePolicy().hasHeightForWidth());
        txi_line_num->setSizePolicy(sizePolicy1);
        txi_line_num->setMinimumSize(QSize(30, 20));
        txi_line_num->setMaximumSize(QSize(30, 20));

        gridLayout_2->addWidget(txi_line_num, 0, 3, 1, 1);

        txt_rpt_current_4 = new QLabel(frame_2);
        txt_rpt_current_4->setObjectName(QString::fromUtf8("txt_rpt_current_4"));
        txt_rpt_current_4->setFont(font1);
        txt_rpt_current_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_current_4, 0, 4, 1, 1);

        btnFront = new QPushButton(frame_2);
        btnFront->setObjectName(QString::fromUtf8("btnFront"));

        gridLayout_2->addWidget(btnFront, 0, 5, 1, 1);

        btnPre = new QPushButton(frame_2);
        btnPre->setObjectName(QString::fromUtf8("btnPre"));

        gridLayout_2->addWidget(btnPre, 0, 6, 1, 1);

        txt_rpt_current = new QLabel(frame_2);
        txt_rpt_current->setObjectName(QString::fromUtf8("txt_rpt_current"));
        txt_rpt_current->setFont(font1);
        txt_rpt_current->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_current, 0, 7, 1, 1);

        spinBox = new QSpinBox(frame_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimumSize(QSize(0, 20));
        spinBox->setMaximumSize(QSize(16777215, 20));
        spinBox->setWrapping(true);
        spinBox->setMinimum(1);

        gridLayout_2->addWidget(spinBox, 0, 8, 1, 1);

        txt_rpt_current_2 = new QLabel(frame_2);
        txt_rpt_current_2->setObjectName(QString::fromUtf8("txt_rpt_current_2"));
        txt_rpt_current_2->setFont(font1);
        txt_rpt_current_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_current_2, 0, 9, 1, 1);

        btnNext = new QPushButton(frame_2);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));

        gridLayout_2->addWidget(btnNext, 0, 10, 1, 1);

        btnTail = new QPushButton(frame_2);
        btnTail->setObjectName(QString::fromUtf8("btnTail"));

        gridLayout_2->addWidget(btnTail, 0, 11, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(30, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 0, 12, 1, 1);


        gridLayout->addWidget(frame_2, 1, 0, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 2, 0, 1, 1);

        zxgg_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(zxgg_ScrollArea);

        QMetaObject::connectSlotsByName(zxgg_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *zxgg_ScrollArea)
    {
        zxgg_ScrollArea->setWindowTitle(QApplication::translate("zxgg_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("zxgg_ScrollArea", "      \346\234\200\346\226\260\345\205\254\345\221\212", 0, QApplication::UnicodeUTF8));
        txt_rpt_total->setText(QApplication::translate("zxgg_ScrollArea", "\345\205\261:\343\200\2200\343\200\221\351\241\265", 0, QApplication::UnicodeUTF8));
        txt_rpt_current_3->setText(QApplication::translate("zxgg_ScrollArea", "\346\257\217\351\241\265\346\230\276\347\244\272:", 0, QApplication::UnicodeUTF8));
        txt_rpt_current_4->setText(QApplication::translate("zxgg_ScrollArea", "\350\241\214", 0, QApplication::UnicodeUTF8));
        btnFront->setText(QApplication::translate("zxgg_ScrollArea", "\351\246\226\351\241\265", 0, QApplication::UnicodeUTF8));
        btnPre->setText(QApplication::translate("zxgg_ScrollArea", "\344\270\212\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
        txt_rpt_current->setText(QApplication::translate("zxgg_ScrollArea", "\347\254\254:", 0, QApplication::UnicodeUTF8));
        txt_rpt_current_2->setText(QApplication::translate("zxgg_ScrollArea", "\351\241\265", 0, QApplication::UnicodeUTF8));
        btnNext->setText(QApplication::translate("zxgg_ScrollArea", "\344\270\213\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
        btnTail->setText(QApplication::translate("zxgg_ScrollArea", "\345\260\276\351\241\265", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class zxgg_ScrollArea: public Ui_zxgg_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZXGG_SCROLLAREA_H
