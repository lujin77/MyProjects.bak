/********************************************************************************
** Form generated from reading UI file 'klxs_tabwidget.ui'
**
** Created: Sat Apr 20 10:13:45 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KLXS_TABWIDGET_H
#define UI_KLXS_TABWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_klxs_TabWidget
{
public:
    QWidget *tab_klxs;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget_cardlist;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QLabel *txt_rpt_count;
    QSpacerItem *horizontalSpacer_18;
    QLabel *txt_alert;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *btn_refresh;
    QPushButton *btn_print;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QRadioButton *rdo_tx;
    QRadioButton *rdo_yx;
    QRadioButton *rdo_qt;
    QTableWidget *tableWidget;
    QWidget *tab_klxscx;
    QGridLayout *gridLayout_11;
    QLabel *label_3;
    QFrame *frame_4;
    QGridLayout *gridLayout_10;
    QSpacerItem *horizontalSpacer_19;
    QLabel *label_26;
    QDateEdit *txiStartDate;
    QLabel *label_27;
    QDateEdit *txiEndDate;
    QLabel *label_4;
    QComboBox *cbx_state;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *horizontalSpacer_21;
    QLabel *label_28;
    QComboBox *cbx_card_type;
    QLabel *label_29;
    QComboBox *cbx_card_name;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_search_cx;
    QSpacerItem *horizontalSpacer_22;
    QFrame *frame_3;
    QGridLayout *gridLayout_9;
    QLabel *txt_rpt_count_cx;
    QSpacerItem *horizontalSpacer_17;
    QPushButton *btn_refresh_cx;
    QSpacerItem *horizontalSpacer_16;
    QTableWidget *tableWidget_cx;

    void setupUi(QTabWidget *klxs_TabWidget)
    {
        if (klxs_TabWidget->objectName().isEmpty())
            klxs_TabWidget->setObjectName(QString::fromUtf8("klxs_TabWidget"));
        klxs_TabWidget->resize(900, 800);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(klxs_TabWidget->sizePolicy().hasHeightForWidth());
        klxs_TabWidget->setSizePolicy(sizePolicy);
        klxs_TabWidget->setMinimumSize(QSize(900, 800));
        klxs_TabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tab_klxs = new QWidget();
        tab_klxs->setObjectName(QString::fromUtf8("tab_klxs"));
        gridLayout = new QGridLayout(tab_klxs);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(tab_klxs);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        frame = new QFrame(tab_klxs);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(0, 250));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableWidget_cardlist = new QTableWidget(frame);
        tableWidget_cardlist->setObjectName(QString::fromUtf8("tableWidget_cardlist"));
        QFont font1;
        font1.setPointSize(12);
        tableWidget_cardlist->setFont(font1);
        tableWidget_cardlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_cardlist->setTabKeyNavigation(false);
        tableWidget_cardlist->setProperty("showDropIndicator", QVariant(false));
        tableWidget_cardlist->setDragDropOverwriteMode(false);
        tableWidget_cardlist->horizontalHeader()->setVisible(false);
        tableWidget_cardlist->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(tableWidget_cardlist, 0, 0, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        frame_2 = new QFrame(tab_klxs);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setMinimumSize(QSize(0, 60));
        frame_2->setMaximumSize(QSize(16777215, 60));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        txt_rpt_count = new QLabel(frame_2);
        txt_rpt_count->setObjectName(QString::fromUtf8("txt_rpt_count"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        txt_rpt_count->setFont(font2);
        txt_rpt_count->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_count, 0, 0, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_18, 0, 1, 1, 1);

        txt_alert = new QLabel(frame_2);
        txt_alert->setObjectName(QString::fromUtf8("txt_alert"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(14);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        txt_alert->setFont(font3);
        txt_alert->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_3->addWidget(txt_alert, 0, 2, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_14, 0, 3, 1, 1);

        btn_refresh = new QPushButton(frame_2);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        btn_refresh->setMinimumSize(QSize(40, 25));
        btn_refresh->setMaximumSize(QSize(40, 25));
        btn_refresh->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_3->addWidget(btn_refresh, 0, 5, 1, 1);

        btn_print = new QPushButton(frame_2);
        btn_print->setObjectName(QString::fromUtf8("btn_print"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_print->sizePolicy().hasHeightForWidth());
        btn_print->setSizePolicy(sizePolicy2);
        btn_print->setMinimumSize(QSize(41, 41));
        btn_print->setMaximumSize(QSize(41, 41));
        btn_print->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_3->addWidget(btn_print, 0, 6, 1, 1);

        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(0, 45));
        groupBox->setMaximumSize(QSize(16777215, 45));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        rdo_tx = new QRadioButton(groupBox);
        rdo_tx->setObjectName(QString::fromUtf8("rdo_tx"));
        rdo_tx->setChecked(true);

        gridLayout_4->addWidget(rdo_tx, 0, 0, 1, 1);

        rdo_yx = new QRadioButton(groupBox);
        rdo_yx->setObjectName(QString::fromUtf8("rdo_yx"));

        gridLayout_4->addWidget(rdo_yx, 0, 1, 1, 1);

        rdo_qt = new QRadioButton(groupBox);
        rdo_qt->setObjectName(QString::fromUtf8("rdo_qt"));

        gridLayout_4->addWidget(rdo_qt, 0, 2, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 4, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);

        tableWidget = new QTableWidget(tab_klxs);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(tableWidget, 3, 0, 1, 1);

        klxs_TabWidget->addTab(tab_klxs, QString());
        tab_klxscx = new QWidget();
        tab_klxscx->setObjectName(QString::fromUtf8("tab_klxscx"));
        gridLayout_11 = new QGridLayout(tab_klxscx);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_3 = new QLabel(tab_klxscx);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout_11->addWidget(label_3, 0, 0, 1, 1);

        frame_4 = new QFrame(tab_klxscx);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_10 = new QGridLayout(frame_4);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        horizontalSpacer_19 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_19, 0, 0, 1, 1);

        label_26 = new QLabel(frame_4);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setMinimumSize(QSize(60, 0));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font4.setPointSize(12);
        label_26->setFont(font4);

        gridLayout_10->addWidget(label_26, 0, 1, 1, 1);

        txiStartDate = new QDateEdit(frame_4);
        txiStartDate->setObjectName(QString::fromUtf8("txiStartDate"));
        txiStartDate->setMinimumSize(QSize(150, 0));
        txiStartDate->setFont(font4);
        txiStartDate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        txiStartDate->setCalendarPopup(true);

        gridLayout_10->addWidget(txiStartDate, 0, 2, 1, 1);

        label_27 = new QLabel(frame_4);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setMinimumSize(QSize(60, 0));
        label_27->setFont(font4);

        gridLayout_10->addWidget(label_27, 0, 3, 1, 1);

        txiEndDate = new QDateEdit(frame_4);
        txiEndDate->setObjectName(QString::fromUtf8("txiEndDate"));
        txiEndDate->setMinimumSize(QSize(150, 0));
        txiEndDate->setFont(font4);
        txiEndDate->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));

        gridLayout_10->addWidget(txiEndDate, 0, 4, 1, 1);

        label_4 = new QLabel(frame_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(label_4, 0, 5, 1, 1);

        cbx_state = new QComboBox(frame_4);
        cbx_state->setObjectName(QString::fromUtf8("cbx_state"));
        cbx_state->setMinimumSize(QSize(150, 22));
        cbx_state->setFont(font4);
        cbx_state->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_10->addWidget(cbx_state, 0, 6, 1, 2);

        horizontalSpacer_20 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_20, 0, 8, 1, 1);

        horizontalSpacer_21 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_21, 1, 0, 1, 1);

        label_28 = new QLabel(frame_4);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setMinimumSize(QSize(60, 0));
        label_28->setFont(font4);
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(label_28, 1, 1, 1, 1);

        cbx_card_type = new QComboBox(frame_4);
        cbx_card_type->setObjectName(QString::fromUtf8("cbx_card_type"));
        cbx_card_type->setMinimumSize(QSize(150, 0));
        cbx_card_type->setFont(font4);
        cbx_card_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_10->addWidget(cbx_card_type, 1, 2, 1, 1);

        label_29 = new QLabel(frame_4);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setMinimumSize(QSize(60, 0));
        label_29->setFont(font4);
        label_29->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(label_29, 1, 3, 1, 1);

        cbx_card_name = new QComboBox(frame_4);
        cbx_card_name->setObjectName(QString::fromUtf8("cbx_card_name"));
        cbx_card_name->setMinimumSize(QSize(200, 0));
        cbx_card_name->setFont(font4);
        cbx_card_name->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_10->addWidget(cbx_card_name, 1, 4, 1, 2);

        horizontalSpacer = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer, 1, 6, 1, 1);

        btn_search_cx = new QPushButton(frame_4);
        btn_search_cx->setObjectName(QString::fromUtf8("btn_search_cx"));
        btn_search_cx->setMinimumSize(QSize(40, 25));
        btn_search_cx->setMaximumSize(QSize(40, 25));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font5.setPointSize(14);
        btn_search_cx->setFont(font5);
        btn_search_cx->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cx.png);"));

        gridLayout_10->addWidget(btn_search_cx, 1, 7, 1, 1);

        horizontalSpacer_22 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_22, 1, 8, 1, 1);


        gridLayout_11->addWidget(frame_4, 1, 0, 1, 1);

        frame_3 = new QFrame(tab_klxscx);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_9 = new QGridLayout(frame_3);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        txt_rpt_count_cx = new QLabel(frame_3);
        txt_rpt_count_cx->setObjectName(QString::fromUtf8("txt_rpt_count_cx"));
        txt_rpt_count_cx->setFont(font2);
        txt_rpt_count_cx->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_9->addWidget(txt_rpt_count_cx, 0, 1, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_17, 0, 2, 1, 1);

        btn_refresh_cx = new QPushButton(frame_3);
        btn_refresh_cx->setObjectName(QString::fromUtf8("btn_refresh_cx"));
        btn_refresh_cx->setMinimumSize(QSize(40, 25));
        btn_refresh_cx->setMaximumSize(QSize(40, 25));
        btn_refresh_cx->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_9->addWidget(btn_refresh_cx, 0, 3, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_16, 0, 0, 1, 1);


        gridLayout_11->addWidget(frame_3, 2, 0, 1, 1);

        tableWidget_cx = new QTableWidget(tab_klxscx);
        tableWidget_cx->setObjectName(QString::fromUtf8("tableWidget_cx"));
        tableWidget_cx->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget_cx->setFrameShape(QFrame::NoFrame);
        tableWidget_cx->setGridStyle(Qt::SolidLine);

        gridLayout_11->addWidget(tableWidget_cx, 3, 0, 1, 1);

        klxs_TabWidget->addTab(tab_klxscx, QString());

        retranslateUi(klxs_TabWidget);

        klxs_TabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(klxs_TabWidget);
    } // setupUi

    void retranslateUi(QTabWidget *klxs_TabWidget)
    {
        klxs_TabWidget->setWindowTitle(QApplication::translate("klxs_TabWidget", "TabWidget", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("klxs_TabWidget", "      \345\215\241\347\261\273\351\224\200\345\224\256", 0, QApplication::UnicodeUTF8));
        txt_rpt_count->setText(QApplication::translate("klxs_TabWidget", "\350\264\255\344\271\260\350\256\260\345\275\225:\343\200\2200\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        txt_alert->setText(QApplication::translate("klxs_TabWidget", "\350\257\267\347\202\271\345\207\273\345\215\241\347\261\273\345\220\215\347\247\260\350\277\233\350\241\214\351\224\200\345\224\256", 0, QApplication::UnicodeUTF8));
        btn_refresh->setText(QString());
        btn_print->setText(QString());
        groupBox->setTitle(QApplication::translate("klxs_TabWidget", "\345\210\207\346\215\242\345\275\223\345\211\215\346\230\276\347\244\272\345\215\241\347\261\273", 0, QApplication::UnicodeUTF8));
        rdo_tx->setText(QApplication::translate("klxs_TabWidget", "\351\200\232\344\277\241\347\261\273", 0, QApplication::UnicodeUTF8));
        rdo_yx->setText(QApplication::translate("klxs_TabWidget", "\346\270\270\346\210\217\347\261\273", 0, QApplication::UnicodeUTF8));
        rdo_qt->setText(QApplication::translate("klxs_TabWidget", "\345\205\266\344\273\226\347\261\273", 0, QApplication::UnicodeUTF8));
        klxs_TabWidget->setTabText(klxs_TabWidget->indexOf(tab_klxs), QApplication::translate("klxs_TabWidget", "\345\215\241\347\261\273\351\224\200\345\224\256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("klxs_TabWidget", "      \345\215\241\347\261\273\351\224\200\345\224\256\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("klxs_TabWidget", "\350\265\267\345\247\213\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("klxs_TabWidget", "\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("klxs_TabWidget", "\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("klxs_TabWidget", "\345\215\241\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("klxs_TabWidget", "\345\215\241\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        btn_search_cx->setText(QString());
        txt_rpt_count_cx->setText(QApplication::translate("klxs_TabWidget", "\350\264\255\344\271\260\350\256\260\345\275\225:\343\200\2200\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        btn_refresh_cx->setText(QString());
        klxs_TabWidget->setTabText(klxs_TabWidget->indexOf(tab_klxscx), QApplication::translate("klxs_TabWidget", "\345\215\241\347\261\273\351\224\200\345\224\256\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class klxs_TabWidget: public Ui_klxs_TabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KLXS_TABWIDGET_H
