/********************************************************************************
** Form generated from reading UI file 'gmqb_scrollarea.ui'
**
** Created: Fri Sep 16 08:47:51 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GMQB_SCROLLAREA_H
#define UI_GMQB_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
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

class Ui_gmqb_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_25;
    QComboBox *cbx_type;
    QLabel *label_23;
    QLineEdit *lineEdit_5;
    QLabel *label_24;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QTableWidget *tableWidget;

    void setupUi(QScrollArea *gmqb_ScrollArea)
    {
        if (gmqb_ScrollArea->objectName().isEmpty())
            gmqb_ScrollArea->setObjectName(QString::fromUtf8("gmqb_ScrollArea"));
        gmqb_ScrollArea->resize(900, 650);
        gmqb_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gmqb_ScrollArea->setFrameShape(QFrame::NoFrame);
        gmqb_ScrollArea->setLineWidth(0);
        gmqb_ScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 900, 650));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(15, 15, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_8 = new QSpacerItem(134, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_25->setFont(font1);

        gridLayout_3->addWidget(label_25, 0, 1, 1, 1);

        cbx_type = new QComboBox(frame);
        cbx_type->setObjectName(QString::fromUtf8("cbx_type"));
        cbx_type->setMinimumSize(QSize(150, 0));
        cbx_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(cbx_type, 0, 2, 1, 1);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_3->addWidget(label_23, 0, 3, 1, 1);

        lineEdit_5 = new QLineEdit(frame);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setMinimumSize(QSize(150, 0));
        lineEdit_5->setFont(font1);
        lineEdit_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_5->setMaxLength(11);

        gridLayout_3->addWidget(lineEdit_5, 0, 4, 1, 1);

        label_24 = new QLabel(frame);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font1);

        gridLayout_3->addWidget(label_24, 0, 5, 1, 1);

        lineEdit_6 = new QLineEdit(frame);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setMinimumSize(QSize(100, 0));
        lineEdit_6->setFont(font1);
        lineEdit_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_6->setMaxLength(11);

        gridLayout_3->addWidget(lineEdit_6, 0, 6, 1, 1);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout_3->addWidget(pushButton, 0, 7, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(134, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 0, 8, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(15, 50, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(313, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 0, 1, 1);

        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        label_12->setFont(font2);
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(label_12, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(275, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 2, 1, 1);

        pushButton_3 = new QPushButton(frame_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(40, 25));
        pushButton_3->setMaximumSize(QSize(40, 25));
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_2->addWidget(pushButton_3, 0, 3, 1, 1);

        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(41, 41));
        pushButton_2->setMaximumSize(QSize(41, 41));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_2->addWidget(pushButton_2, 0, 4, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(15, 40, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(855, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(15, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 2, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 4, 1, 1, 1);

        gmqb_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(gmqb_ScrollArea);

        QMetaObject::connectSlotsByName(gmqb_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *gmqb_ScrollArea)
    {
        gmqb_ScrollArea->setWindowTitle(QApplication::translate("gmqb_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("gmqb_ScrollArea", "      \346\270\270\346\210\217\345\205\205\345\200\274", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("gmqb_ScrollArea", "\346\270\270\346\210\217\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("gmqb_ScrollArea", "\346\270\270\346\210\217\350\264\246\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        lineEdit_5->setText(QString());
        label_24->setText(QApplication::translate("gmqb_ScrollArea", "\345\205\205\345\200\274\351\207\221\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        lineEdit_6->setText(QString());
        pushButton->setText(QApplication::translate("gmqb_ScrollArea", "\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("gmqb_ScrollArea", "\350\264\255\344\271\260\350\256\260\345\275\225\357\274\232\343\200\22010000\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gmqb_ScrollArea: public Ui_gmqb_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GMQB_SCROLLAREA_H
