/********************************************************************************
** Form generated from reading UI file 'gmjp_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:01 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GMJP_SCROLLAREA_H
#define UI_GMJP_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
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

class Ui_gmjp_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_23;
    QComboBox *comboBox_2;
    QLabel *label_24;
    QComboBox *comboBox_3;
    QLabel *label_25;
    QDateEdit *dateEdit;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *gmjp_ScrollArea)
    {
        if (gmjp_ScrollArea->objectName().isEmpty())
            gmjp_ScrollArea->setObjectName(QString::fromUtf8("gmjp_ScrollArea"));
        gmjp_ScrollArea->resize(900, 650);
        gmjp_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gmjp_ScrollArea->setFrameShape(QFrame::NoFrame);
        gmjp_ScrollArea->setLineWidth(0);
        gmjp_ScrollArea->setWidgetResizable(true);
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
        horizontalSpacer_5 = new QSpacerItem(64, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_23->setFont(font1);

        gridLayout_2->addWidget(label_23, 0, 1, 1, 1);

        comboBox_2 = new QComboBox(frame);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(150, 20));
        comboBox_2->setMaximumSize(QSize(16777215, 20));
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(comboBox_2, 0, 2, 1, 2);

        label_24 = new QLabel(frame);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font1);

        gridLayout_2->addWidget(label_24, 0, 4, 1, 1);

        comboBox_3 = new QComboBox(frame);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setMinimumSize(QSize(150, 20));
        comboBox_3->setMaximumSize(QSize(16777215, 20));
        comboBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(comboBox_3, 0, 5, 1, 1);

        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font1);

        gridLayout_2->addWidget(label_25, 0, 6, 1, 1);

        dateEdit = new QDateEdit(frame);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setMinimumSize(QSize(0, 22));
        dateEdit->setMaximumSize(QSize(16777215, 22));
        dateEdit->setFont(font1);
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(dateEdit, 0, 7, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(63, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 8, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(64, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout_2->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(63, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 1, 8, 1, 1);

        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(80, 0));
        pushButton_4->setFont(font1);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout_2->addWidget(pushButton_4, 1, 4, 1, 1);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(80, 0));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout_2->addWidget(pushButton_2, 1, 3, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(15, 100, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(855, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(15, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 1, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 3, 0, 1, 2);

        gmjp_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(gmjp_ScrollArea);

        QMetaObject::connectSlotsByName(gmjp_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *gmjp_ScrollArea)
    {
        gmjp_ScrollArea->setWindowTitle(QApplication::translate("gmjp_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("gmjp_ScrollArea", "      \350\264\255\344\271\260\346\234\272\347\245\250", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("gmjp_ScrollArea", "\345\207\272\345\217\221\345\237\216\345\270\202\357\274\232", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("gmjp_ScrollArea", "\345\210\260\350\276\276\345\237\216\345\270\202\357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("gmjp_ScrollArea", "\345\210\260\350\276\276\345\237\216\345\270\202\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("gmjp_ScrollArea", "\346\237\245\350\257\242\350\210\252\347\217\255", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("gmjp_ScrollArea", "\351\242\204\345\256\232\345\233\236\347\250\213", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("gmjp_ScrollArea", "\351\242\204\345\256\232\350\210\252\347\217\255", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gmjp_ScrollArea: public Ui_gmjp_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GMJP_SCROLLAREA_H
