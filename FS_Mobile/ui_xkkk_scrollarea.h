/********************************************************************************
** Form generated from reading UI file 'xkkk_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:01 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XKKK_SCROLLAREA_H
#define UI_XKKK_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xkkk_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_2;
    QLabel *label_25;
    QLineEdit *txi_account_name;
    QLabel *label_23;
    QLineEdit *txi_account_money;
    QLabel *label_22;
    QLineEdit *txi_card_count;
    QLabel *label_26;
    QLineEdit *txi_pay_money;
    QLabel *label_27;
    QComboBox *cbx_worker;
    QLabel *label_28;
    QComboBox *cbx_sp;
    QLabel *label_29;
    QTextEdit *txi_content;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_30;
    QLineEdit *txi_prefix;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_31;
    QLineEdit *txi_suffix1;
    QLabel *label_32;
    QLineEdit *txi_suffix2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_generate;
    QPushButton *bent_delete;
    QPushButton *btn_clear;
    QListView *listView;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_submit;
    QPushButton *btn_reset;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QScrollArea *xkkk_ScrollArea)
    {
        if (xkkk_ScrollArea->objectName().isEmpty())
            xkkk_ScrollArea->setObjectName(QString::fromUtf8("xkkk_ScrollArea"));
        xkkk_ScrollArea->resize(900, 650);
        xkkk_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        xkkk_ScrollArea->setFrameShape(QFrame::NoFrame);
        xkkk_ScrollArea->setLineWidth(0);
        xkkk_ScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 900, 650));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 20));
        label->setMaximumSize(QSize(16777215, 20));
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
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 39, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 39, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 0, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(117, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_2->setHorizontalSpacing(6);
        gridLayout_2->setVerticalSpacing(30);
        label_25 = new QLabel(frame);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label_25->setFont(font1);

        gridLayout_2->addWidget(label_25, 0, 0, 1, 1);

        txi_account_name = new QLineEdit(frame);
        txi_account_name->setObjectName(QString::fromUtf8("txi_account_name"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txi_account_name->sizePolicy().hasHeightForWidth());
        txi_account_name->setSizePolicy(sizePolicy1);
        txi_account_name->setMinimumSize(QSize(0, 22));
        txi_account_name->setMaximumSize(QSize(16777215, 22));
        txi_account_name->setFont(font1);
        txi_account_name->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_account_name->setReadOnly(true);

        gridLayout_2->addWidget(txi_account_name, 0, 1, 1, 1);

        label_23 = new QLabel(frame);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_2->addWidget(label_23, 1, 0, 1, 1);

        txi_account_money = new QLineEdit(frame);
        txi_account_money->setObjectName(QString::fromUtf8("txi_account_money"));
        sizePolicy1.setHeightForWidth(txi_account_money->sizePolicy().hasHeightForWidth());
        txi_account_money->setSizePolicy(sizePolicy1);
        txi_account_money->setMinimumSize(QSize(0, 22));
        txi_account_money->setMaximumSize(QSize(16777215, 22));
        txi_account_money->setFont(font1);
        txi_account_money->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_account_money->setReadOnly(true);

        gridLayout_2->addWidget(txi_account_money, 1, 1, 1, 1);

        label_22 = new QLabel(frame);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font1);

        gridLayout_2->addWidget(label_22, 2, 0, 1, 1);

        txi_card_count = new QLineEdit(frame);
        txi_card_count->setObjectName(QString::fromUtf8("txi_card_count"));
        sizePolicy1.setHeightForWidth(txi_card_count->sizePolicy().hasHeightForWidth());
        txi_card_count->setSizePolicy(sizePolicy1);
        txi_card_count->setMinimumSize(QSize(0, 22));
        txi_card_count->setMaximumSize(QSize(16777215, 22));
        txi_card_count->setFont(font1);
        txi_card_count->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_card_count->setReadOnly(true);

        gridLayout_2->addWidget(txi_card_count, 2, 1, 1, 1);

        label_26 = new QLabel(frame);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setFont(font1);

        gridLayout_2->addWidget(label_26, 3, 0, 1, 1);

        txi_pay_money = new QLineEdit(frame);
        txi_pay_money->setObjectName(QString::fromUtf8("txi_pay_money"));
        sizePolicy1.setHeightForWidth(txi_pay_money->sizePolicy().hasHeightForWidth());
        txi_pay_money->setSizePolicy(sizePolicy1);
        txi_pay_money->setMinimumSize(QSize(0, 22));
        txi_pay_money->setMaximumSize(QSize(16777215, 22));
        txi_pay_money->setFont(font1);
        txi_pay_money->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txi_pay_money, 3, 1, 1, 1);

        label_27 = new QLabel(frame);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font1);

        gridLayout_2->addWidget(label_27, 4, 0, 1, 1);

        cbx_worker = new QComboBox(frame);
        cbx_worker->setObjectName(QString::fromUtf8("cbx_worker"));
        sizePolicy1.setHeightForWidth(cbx_worker->sizePolicy().hasHeightForWidth());
        cbx_worker->setSizePolicy(sizePolicy1);
        cbx_worker->setMinimumSize(QSize(150, 20));
        cbx_worker->setMaximumSize(QSize(150, 20));
        cbx_worker->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbx_worker, 4, 1, 1, 1);

        label_28 = new QLabel(frame);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setFont(font1);

        gridLayout_2->addWidget(label_28, 5, 0, 1, 1);

        cbx_sp = new QComboBox(frame);
        cbx_sp->setObjectName(QString::fromUtf8("cbx_sp"));
        sizePolicy1.setHeightForWidth(cbx_sp->sizePolicy().hasHeightForWidth());
        cbx_sp->setSizePolicy(sizePolicy1);
        cbx_sp->setMinimumSize(QSize(150, 20));
        cbx_sp->setMaximumSize(QSize(150, 20));
        cbx_sp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(cbx_sp, 5, 1, 1, 1);

        label_29 = new QLabel(frame);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        sizePolicy.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy);
        label_29->setFont(font1);
        label_29->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(label_29, 6, 0, 1, 1);

        txi_content = new QTextEdit(frame);
        txi_content->setObjectName(QString::fromUtf8("txi_content"));
        sizePolicy1.setHeightForWidth(txi_content->sizePolicy().hasHeightForWidth());
        txi_content->setSizePolicy(sizePolicy1);
        txi_content->setMinimumSize(QSize(180, 100));
        txi_content->setMaximumSize(QSize(180, 150));
        txi_content->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(txi_content, 6, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 1, 1, 3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        label_30 = new QLabel(frame);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        sizePolicy1.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy1);
        label_30->setFont(font1);

        horizontalLayout_2->addWidget(label_30);

        txi_prefix = new QLineEdit(frame);
        txi_prefix->setObjectName(QString::fromUtf8("txi_prefix"));
        sizePolicy1.setHeightForWidth(txi_prefix->sizePolicy().hasHeightForWidth());
        txi_prefix->setSizePolicy(sizePolicy1);
        txi_prefix->setMinimumSize(QSize(0, 22));
        txi_prefix->setMaximumSize(QSize(16777215, 22));
        txi_prefix->setFont(font1);
        txi_prefix->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_prefix->setReadOnly(false);

        horizontalLayout_2->addWidget(txi_prefix);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        label_31 = new QLabel(frame);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        sizePolicy1.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy1);
        label_31->setFont(font1);

        horizontalLayout_3->addWidget(label_31);

        txi_suffix1 = new QLineEdit(frame);
        txi_suffix1->setObjectName(QString::fromUtf8("txi_suffix1"));
        sizePolicy1.setHeightForWidth(txi_suffix1->sizePolicy().hasHeightForWidth());
        txi_suffix1->setSizePolicy(sizePolicy1);
        txi_suffix1->setMinimumSize(QSize(0, 22));
        txi_suffix1->setMaximumSize(QSize(70, 22));
        txi_suffix1->setFont(font1);
        txi_suffix1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_suffix1->setReadOnly(false);

        horizontalLayout_3->addWidget(txi_suffix1);

        label_32 = new QLabel(frame);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        sizePolicy1.setHeightForWidth(label_32->sizePolicy().hasHeightForWidth());
        label_32->setSizePolicy(sizePolicy1);
        label_32->setFont(font1);

        horizontalLayout_3->addWidget(label_32);

        txi_suffix2 = new QLineEdit(frame);
        txi_suffix2->setObjectName(QString::fromUtf8("txi_suffix2"));
        sizePolicy1.setHeightForWidth(txi_suffix2->sizePolicy().hasHeightForWidth());
        txi_suffix2->setSizePolicy(sizePolicy1);
        txi_suffix2->setMinimumSize(QSize(0, 22));
        txi_suffix2->setMaximumSize(QSize(70, 22));
        txi_suffix2->setFont(font1);
        txi_suffix2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_suffix2->setReadOnly(false);

        horizontalLayout_3->addWidget(txi_suffix2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetFixedSize);
        btn_generate = new QPushButton(frame);
        btn_generate->setObjectName(QString::fromUtf8("btn_generate"));
        sizePolicy1.setHeightForWidth(btn_generate->sizePolicy().hasHeightForWidth());
        btn_generate->setSizePolicy(sizePolicy1);
        btn_generate->setStyleSheet(QString::fromUtf8("font: 10pt \"Agency FB\";"));

        horizontalLayout_4->addWidget(btn_generate);

        bent_delete = new QPushButton(frame);
        bent_delete->setObjectName(QString::fromUtf8("bent_delete"));
        sizePolicy1.setHeightForWidth(bent_delete->sizePolicy().hasHeightForWidth());
        bent_delete->setSizePolicy(sizePolicy1);
        bent_delete->setStyleSheet(QString::fromUtf8("font: 10pt \"Agency FB\";"));

        horizontalLayout_4->addWidget(bent_delete);

        btn_clear = new QPushButton(frame);
        btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
        sizePolicy1.setHeightForWidth(btn_clear->sizePolicy().hasHeightForWidth());
        btn_clear->setSizePolicy(sizePolicy1);
        btn_clear->setStyleSheet(QString::fromUtf8("font: 10pt \"Agency FB\";"));

        horizontalLayout_4->addWidget(btn_clear);


        verticalLayout->addLayout(horizontalLayout_4);

        listView = new QListView(frame);
        listView->setObjectName(QString::fromUtf8("listView"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy2);
        listView->setMinimumSize(QSize(0, 350));
        listView->setMaximumSize(QSize(16777215, 350));
        listView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(listView);


        gridLayout_3->addLayout(verticalLayout, 1, 4, 2, 1);

        horizontalSpacer_2 = new QSpacerItem(116, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 5, 1, 1);

        btn_submit = new QPushButton(frame);
        btn_submit->setObjectName(QString::fromUtf8("btn_submit"));
        btn_submit->setMinimumSize(QSize(61, 25));
        btn_submit->setMaximumSize(QSize(61, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btn_submit->setFont(font2);
        btn_submit->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_qrtj.png);"));

        gridLayout_3->addWidget(btn_submit, 2, 2, 1, 1);

        btn_reset = new QPushButton(frame);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        btn_reset->setMinimumSize(QSize(40, 25));
        btn_reset->setMaximumSize(QSize(40, 25));
        btn_reset->setFont(font2);
        btn_reset->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cz.png);"));

        gridLayout_3->addWidget(btn_reset, 2, 3, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 39, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 3, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 39, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 3, 4, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        xkkk_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(xkkk_ScrollArea);

        QMetaObject::connectSlotsByName(xkkk_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *xkkk_ScrollArea)
    {
        xkkk_ScrollArea->setWindowTitle(QApplication::translate("xkkk_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("xkkk_ScrollArea", "      \345\260\217\345\215\241\346\211\243\346\254\276", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("xkkk_ScrollArea", "\350\264\246\346\210\267\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("xkkk_ScrollArea", "\350\264\246\346\210\267\344\275\231\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("xkkk_ScrollArea", "\345\260\217\345\215\241\345\274\240\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("xkkk_ScrollArea", "\346\211\243\346\254\276\351\207\221\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("xkkk_ScrollArea", "\345\217\221\345\215\241\344\270\232\345\212\241\345\221\230\357\274\232", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("xkkk_ScrollArea", "\350\277\220\350\220\245\345\225\206\357\274\232", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("xkkk_ScrollArea", "\345\244\207\346\263\250\357\274\232", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("xkkk_ScrollArea", "\345\260\217\345\215\241\345\217\267\347\240\201\345\205\261\345\220\214\345\211\215\347\274\200\357\274\232", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("xkkk_ScrollArea", "\345\220\216\347\274\200\350\265\267\345\247\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("xkkk_ScrollArea", "\345\220\216\347\274\200\346\210\252\346\255\242\357\274\232", 0, QApplication::UnicodeUTF8));
        btn_generate->setText(QApplication::translate("xkkk_ScrollArea", "\350\207\252\345\212\250\347\224\237\346\210\220\345\260\217\345\215\241\345\217\267\347\240\201", 0, QApplication::UnicodeUTF8));
        bent_delete->setText(QApplication::translate("xkkk_ScrollArea", "\345\210\240\351\231\244\351\200\211\345\256\232\351\241\271", 0, QApplication::UnicodeUTF8));
        btn_clear->setText(QApplication::translate("xkkk_ScrollArea", "\345\205\250\351\203\250\346\270\205\347\251\272", 0, QApplication::UnicodeUTF8));
        btn_submit->setText(QString());
        btn_reset->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class xkkk_ScrollArea: public Ui_xkkk_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XKKK_SCROLLAREA_H
