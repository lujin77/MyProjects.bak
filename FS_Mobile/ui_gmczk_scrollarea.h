/********************************************************************************
** Form generated from reading UI file 'gmczk_scrollarea.ui'
**
** Created: Mon Jan 2 10:33:18 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GMCZK_SCROLLAREA_H
#define UI_GMCZK_SCROLLAREA_H

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

class Ui_gmczk_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_3;
    QComboBox *cbx_type;
    QLabel *label_2;
    QComboBox *cbx_money;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_4;
    QComboBox *comboBox;
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

    void setupUi(QScrollArea *gmczk_ScrollArea)
    {
        if (gmczk_ScrollArea->objectName().isEmpty())
            gmczk_ScrollArea->setObjectName(QString::fromUtf8("gmczk_ScrollArea"));
        gmczk_ScrollArea->resize(900, 650);
        gmczk_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gmczk_ScrollArea->setFrameShape(QFrame::NoFrame);
        gmczk_ScrollArea->setLineWidth(0);
        gmczk_ScrollArea->setWidgetResizable(true);
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
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_8 = new QSpacerItem(220, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_3->setFont(font1);

        gridLayout_3->addWidget(label_3, 0, 1, 1, 1);

        cbx_type = new QComboBox(frame);
        cbx_type->setObjectName(QString::fromUtf8("cbx_type"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cbx_type->sizePolicy().hasHeightForWidth());
        cbx_type->setSizePolicy(sizePolicy);
        cbx_type->setMinimumSize(QSize(150, 0));
        cbx_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(cbx_type, 0, 2, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        gridLayout_3->addWidget(label_2, 0, 3, 1, 1);

        cbx_money = new QComboBox(frame);
        cbx_money->setObjectName(QString::fromUtf8("cbx_money"));
        sizePolicy.setHeightForWidth(cbx_money->sizePolicy().hasHeightForWidth());
        cbx_money->setSizePolicy(sizePolicy);
        cbx_money->setMinimumSize(QSize(150, 0));
        cbx_money->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(cbx_money, 0, 4, 1, 1);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout_3->addWidget(pushButton, 0, 7, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(219, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 0, 8, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        gridLayout_3->addWidget(label_4, 0, 5, 1, 1);

        comboBox = new QComboBox(frame);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setMinimumSize(QSize(100, 0));
        comboBox->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(comboBox, 0, 6, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(15, 50, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(317, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 0, 1, 1);

        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        label_12->setFont(font2);
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(label_12, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(271, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 2, 1, 1);

        pushButton_3 = new QPushButton(frame_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(40, 25));
        pushButton_3->setMaximumSize(QSize(40, 25));
        pushButton_3->setBaseSize(QSize(41, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_2->addWidget(pushButton_3, 0, 3, 1, 1);

        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(41, 41));
        pushButton_2->setMaximumSize(QSize(41, 41));
        pushButton_2->setBaseSize(QSize(41, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_2->addWidget(pushButton_2, 0, 4, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(15, 40, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(855, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(15, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 1, 1, 1);

        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableWidget, 4, 0, 1, 2);

        gmczk_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(gmczk_ScrollArea);

        QMetaObject::connectSlotsByName(gmczk_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *gmczk_ScrollArea)
    {
        gmczk_ScrollArea->setWindowTitle(QApplication::translate("gmczk_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("gmczk_ScrollArea", "      \345\215\241\347\261\273\351\224\200\345\224\256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("gmczk_ScrollArea", "\351\200\211\346\213\251\345\215\241\347\232\204\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("gmczk_ScrollArea", "\345\205\205\345\200\274\345\215\241\351\235\242\345\200\274\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("gmczk_ScrollArea", "\347\241\256\350\256\244\350\264\255\344\271\260", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("gmczk_ScrollArea", "\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("gmczk_ScrollArea", "\350\264\255\344\271\260\350\256\260\345\275\225\357\274\232\343\200\22010000\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gmczk_ScrollArea: public Ui_gmczk_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GMCZK_SCROLLAREA_H
