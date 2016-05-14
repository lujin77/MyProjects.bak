/********************************************************************************
** Form generated from reading UI file 'yxcz_tabwidget.ui'
**
** Created: Sun Apr 15 14:38:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YXCZ_TABWIDGET_H
#define UI_YXCZ_TABWIDGET_H

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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_yxcz_TabWidget
{
public:
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QLineEdit *txi_gameAccount;
    QPushButton *btn_submit;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QLineEdit *txi_money;
    QPushButton *btn_reset;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QComboBox *cbx_gameType;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_6;
    QTextEdit *txi_content;
    QSpacerItem *horizontalSpacer_11;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QLabel *txt_rpt_count;
    QSpacerItem *horizontalSpacer_17;
    QLabel *txt_rpt_money;
    QSpacerItem *horizontalSpacer_14;
    QGroupBox *groupBox;
    QRadioButton *rdo_print_on;
    QRadioButton *rdo_print_off;
    QPushButton *btn_refresh;
    QPushButton *btn_print;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout_10;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_30;
    QFrame *frame_4;
    QGridLayout *gridLayout_9;
    QSpacerItem *horizontalSpacer_31;
    QLabel *label_21;
    QComboBox *cbx_gameType_rb;
    QLabel *label_22;
    QComboBox *cbx_state_rb;
    QLabel *label_23;
    QLineEdit *txi_gameAccount_rb;
    QPushButton *btn_search_rb;
    QSpacerItem *horizontalSpacer_32;
    QSpacerItem *horizontalSpacer_12;
    QFrame *frame_3;
    QGridLayout *gridLayout_8;
    QLabel *txt_rpt_total_rb;
    QSpacerItem *horizontalSpacer_24;
    QLabel *txt_rpt_money_rb;
    QSpacerItem *horizontalSpacer_27;
    QLabel *txt_rpt_repay_rb;
    QSpacerItem *horizontalSpacer_29;
    QPushButton *btn_refresh_rb;
    QPushButton *btn_print_rb;
    QSpacerItem *horizontalSpacer_7;
    QTableWidget *tableWidget_rb;
    QWidget *tab_3;
    QGridLayout *gridLayout_13;
    QLabel *label_7;
    QFrame *frame_5;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_34;
    QLabel *label_24;
    QDateEdit *txiStartDate;
    QLabel *label_25;
    QDateEdit *txiEndDate;
    QLabel *label_26;
    QComboBox *cbx_gameType_yb;
    QSpacerItem *horizontalSpacer_35;
    QSpacerItem *horizontalSpacer_36;
    QLabel *label_27;
    QComboBox *cbx_state_yb;
    QLabel *label_28;
    QLineEdit *txi_gameAccount_yb;
    QPushButton *btn_search_yb;
    QSpacerItem *horizontalSpacer_37;
    QFrame *frame_6;
    QGridLayout *gridLayout_12;
    QLabel *txt_rpt_total_yb;
    QSpacerItem *horizontalSpacer_42;
    QLabel *txt_rpt_money_yb;
    QSpacerItem *horizontalSpacer_43;
    QLabel *txt_rpt_repay_yb;
    QSpacerItem *horizontalSpacer_44;
    QPushButton *btn_refresh_yb;
    QPushButton *btn_print_yb;
    QTableWidget *tableWidget_yb;

    void setupUi(QTabWidget *yxcz_TabWidget)
    {
        if (yxcz_TabWidget->objectName().isEmpty())
            yxcz_TabWidget->setObjectName(QString::fromUtf8("yxcz_TabWidget"));
        yxcz_TabWidget->resize(900, 650);
        yxcz_TabWidget->setMinimumSize(QSize(0, 0));
        yxcz_TabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
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

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(1, 25, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_3 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(28);
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 0, 1, 2, 1);

        txi_gameAccount = new QLineEdit(frame);
        txi_gameAccount->setObjectName(QString::fromUtf8("txi_gameAccount"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txi_gameAccount->sizePolicy().hasHeightForWidth());
        txi_gameAccount->setSizePolicy(sizePolicy1);
        txi_gameAccount->setMinimumSize(QSize(0, 46));
        txi_gameAccount->setMaximumSize(QSize(16777215, 46));
        txi_gameAccount->setFont(font1);
        txi_gameAccount->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_gameAccount->setMaxLength(20);

        gridLayout->addWidget(txi_gameAccount, 0, 2, 2, 1);

        btn_submit = new QPushButton(frame);
        btn_submit->setObjectName(QString::fromUtf8("btn_submit"));
        btn_submit->setMinimumSize(QSize(110, 40));
        btn_submit->setMaximumSize(QSize(110, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(14);
        btn_submit->setFont(font2);
        btn_submit->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout->addWidget(btn_submit, 0, 3, 2, 1);

        horizontalSpacer_8 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 1, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        txi_money = new QLineEdit(frame);
        txi_money->setObjectName(QString::fromUtf8("txi_money"));
        sizePolicy1.setHeightForWidth(txi_money->sizePolicy().hasHeightForWidth());
        txi_money->setSizePolicy(sizePolicy1);
        txi_money->setMinimumSize(QSize(0, 46));
        txi_money->setMaximumSize(QSize(16777215, 46));
        txi_money->setFont(font1);
        txi_money->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_money->setMaxLength(10);

        gridLayout->addWidget(txi_money, 2, 2, 1, 1);

        btn_reset = new QPushButton(frame);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        btn_reset->setMinimumSize(QSize(110, 40));
        btn_reset->setMaximumSize(QSize(110, 40));
        btn_reset->setFont(font2);
        btn_reset->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);"));

        gridLayout->addWidget(btn_reset, 2, 3, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 2, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);

        gridLayout->addWidget(label_4, 3, 1, 1, 1);

        cbx_gameType = new QComboBox(frame);
        cbx_gameType->setObjectName(QString::fromUtf8("cbx_gameType"));
        cbx_gameType->setMinimumSize(QSize(0, 27));
        cbx_gameType->setMaximumSize(QSize(16777215, 27));
        cbx_gameType->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(cbx_gameType, 3, 2, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 3, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 4, 0, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font2);

        gridLayout->addWidget(label_6, 4, 1, 1, 1);

        txi_content = new QTextEdit(frame);
        txi_content->setObjectName(QString::fromUtf8("txi_content"));
        txi_content->setMinimumSize(QSize(0, 60));
        txi_content->setMaximumSize(QSize(16777215, 60));
        txi_content->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_content->setReadOnly(false);
        txi_content->setAcceptRichText(false);

        gridLayout->addWidget(txi_content, 4, 2, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(54, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_11, 4, 4, 1, 1);


        gridLayout_2->addWidget(frame, 1, 0, 2, 1);

        frame_2 = new QFrame(tab);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        txt_rpt_count = new QLabel(frame_2);
        txt_rpt_count->setObjectName(QString::fromUtf8("txt_rpt_count"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(10);
        txt_rpt_count->setFont(font3);
        txt_rpt_count->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_count, 0, 0, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_17, 0, 1, 1, 1);

        txt_rpt_money = new QLabel(frame_2);
        txt_rpt_money->setObjectName(QString::fromUtf8("txt_rpt_money"));
        txt_rpt_money->setFont(font3);
        txt_rpt_money->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_3->addWidget(txt_rpt_money, 0, 2, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_14, 0, 3, 1, 1);

        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(91, 41));
        rdo_print_on = new QRadioButton(groupBox);
        rdo_print_on->setObjectName(QString::fromUtf8("rdo_print_on"));
        rdo_print_on->setGeometry(QRect(10, 17, 41, 16));
        rdo_print_off = new QRadioButton(groupBox);
        rdo_print_off->setObjectName(QString::fromUtf8("rdo_print_off"));
        rdo_print_off->setGeometry(QRect(50, 17, 31, 16));
        rdo_print_off->setChecked(true);

        gridLayout_3->addWidget(groupBox, 0, 4, 1, 1);

        btn_refresh = new QPushButton(frame_2);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        btn_refresh->setMinimumSize(QSize(40, 25));
        btn_refresh->setMaximumSize(QSize(40, 25));
        btn_refresh->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_3->addWidget(btn_refresh, 0, 5, 1, 1);

        btn_print = new QPushButton(frame_2);
        btn_print->setObjectName(QString::fromUtf8("btn_print"));
        sizePolicy1.setHeightForWidth(btn_print->sizePolicy().hasHeightForWidth());
        btn_print->setSizePolicy(sizePolicy1);
        btn_print->setMinimumSize(QSize(41, 41));
        btn_print->setMaximumSize(QSize(41, 41));
        btn_print->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_3->addWidget(btn_print, 0, 6, 1, 1);


        gridLayout_2->addWidget(frame_2, 3, 0, 1, 1);

        tableWidget = new QTableWidget(tab);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setGridStyle(Qt::SolidLine);

        gridLayout_2->addWidget(tableWidget, 5, 0, 1, 1);

        yxcz_TabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_10 = new QGridLayout(tab_2);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout_10->addWidget(label_5, 0, 0, 1, 1);

        horizontalSpacer_30 = new QSpacerItem(1, 25, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_30, 0, 1, 1, 1);

        frame_4 = new QFrame(tab_2);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_9 = new QGridLayout(frame_4);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalSpacer_31 = new QSpacerItem(41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_31, 0, 0, 1, 1);

        label_21 = new QLabel(frame_4);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font4.setPointSize(12);
        label_21->setFont(font4);

        gridLayout_9->addWidget(label_21, 0, 1, 1, 1);

        cbx_gameType_rb = new QComboBox(frame_4);
        cbx_gameType_rb->setObjectName(QString::fromUtf8("cbx_gameType_rb"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cbx_gameType_rb->sizePolicy().hasHeightForWidth());
        cbx_gameType_rb->setSizePolicy(sizePolicy2);
        cbx_gameType_rb->setMinimumSize(QSize(150, 22));
        cbx_gameType_rb->setMaximumSize(QSize(16777215, 22));
        cbx_gameType_rb->setBaseSize(QSize(200, 0));
        cbx_gameType_rb->setFont(font4);
        cbx_gameType_rb->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        gridLayout_9->addWidget(cbx_gameType_rb, 0, 2, 1, 1);

        label_22 = new QLabel(frame_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font4);

        gridLayout_9->addWidget(label_22, 0, 3, 1, 1);

        cbx_state_rb = new QComboBox(frame_4);
        cbx_state_rb->setObjectName(QString::fromUtf8("cbx_state_rb"));
        sizePolicy2.setHeightForWidth(cbx_state_rb->sizePolicy().hasHeightForWidth());
        cbx_state_rb->setSizePolicy(sizePolicy2);
        cbx_state_rb->setMinimumSize(QSize(150, 22));
        cbx_state_rb->setMaximumSize(QSize(16777215, 22));
        cbx_state_rb->setBaseSize(QSize(200, 0));
        cbx_state_rb->setFont(font4);
        cbx_state_rb->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_9->addWidget(cbx_state_rb, 0, 4, 1, 1);

        label_23 = new QLabel(frame_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font4);

        gridLayout_9->addWidget(label_23, 0, 5, 1, 1);

        txi_gameAccount_rb = new QLineEdit(frame_4);
        txi_gameAccount_rb->setObjectName(QString::fromUtf8("txi_gameAccount_rb"));
        sizePolicy1.setHeightForWidth(txi_gameAccount_rb->sizePolicy().hasHeightForWidth());
        txi_gameAccount_rb->setSizePolicy(sizePolicy1);
        txi_gameAccount_rb->setMinimumSize(QSize(0, 22));
        txi_gameAccount_rb->setMaximumSize(QSize(16777215, 22));
        txi_gameAccount_rb->setFont(font4);
        txi_gameAccount_rb->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_gameAccount_rb->setMaxLength(20);

        gridLayout_9->addWidget(txi_gameAccount_rb, 0, 6, 1, 1);

        btn_search_rb = new QPushButton(frame_4);
        btn_search_rb->setObjectName(QString::fromUtf8("btn_search_rb"));
        btn_search_rb->setMinimumSize(QSize(40, 25));
        btn_search_rb->setMaximumSize(QSize(40, 25));
        btn_search_rb->setFont(font4);
        btn_search_rb->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cx.png);"));

        gridLayout_9->addWidget(btn_search_rb, 0, 7, 1, 1);

        horizontalSpacer_32 = new QSpacerItem(41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_32, 0, 8, 1, 1);


        gridLayout_10->addWidget(frame_4, 1, 0, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(1, 50, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_12, 1, 1, 1, 1);

        frame_3 = new QFrame(tab_2);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_8 = new QGridLayout(frame_3);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        txt_rpt_total_rb = new QLabel(frame_3);
        txt_rpt_total_rb->setObjectName(QString::fromUtf8("txt_rpt_total_rb"));
        txt_rpt_total_rb->setFont(font3);
        txt_rpt_total_rb->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_8->addWidget(txt_rpt_total_rb, 0, 0, 1, 1);

        horizontalSpacer_24 = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_24, 0, 1, 1, 1);

        txt_rpt_money_rb = new QLabel(frame_3);
        txt_rpt_money_rb->setObjectName(QString::fromUtf8("txt_rpt_money_rb"));
        txt_rpt_money_rb->setFont(font3);
        txt_rpt_money_rb->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_8->addWidget(txt_rpt_money_rb, 0, 2, 1, 1);

        horizontalSpacer_27 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_27, 0, 3, 1, 1);

        txt_rpt_repay_rb = new QLabel(frame_3);
        txt_rpt_repay_rb->setObjectName(QString::fromUtf8("txt_rpt_repay_rb"));
        txt_rpt_repay_rb->setFont(font3);
        txt_rpt_repay_rb->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_8->addWidget(txt_rpt_repay_rb, 0, 4, 1, 1);

        horizontalSpacer_29 = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_29, 0, 5, 1, 1);

        btn_refresh_rb = new QPushButton(frame_3);
        btn_refresh_rb->setObjectName(QString::fromUtf8("btn_refresh_rb"));
        btn_refresh_rb->setMinimumSize(QSize(40, 25));
        btn_refresh_rb->setMaximumSize(QSize(40, 25));
        btn_refresh_rb->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_8->addWidget(btn_refresh_rb, 0, 6, 1, 1);

        btn_print_rb = new QPushButton(frame_3);
        btn_print_rb->setObjectName(QString::fromUtf8("btn_print_rb"));
        btn_print_rb->setMinimumSize(QSize(41, 41));
        btn_print_rb->setMaximumSize(QSize(41, 41));
        btn_print_rb->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_8->addWidget(btn_print_rb, 0, 7, 1, 1);


        gridLayout_10->addWidget(frame_3, 2, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(1, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_7, 2, 1, 1, 1);

        tableWidget_rb = new QTableWidget(tab_2);
        tableWidget_rb->setObjectName(QString::fromUtf8("tableWidget_rb"));
        tableWidget_rb->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget_rb->setFrameShape(QFrame::NoFrame);
        tableWidget_rb->setGridStyle(Qt::SolidLine);

        gridLayout_10->addWidget(tableWidget_rb, 3, 0, 1, 1);

        yxcz_TabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_13 = new QGridLayout(tab_3);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout_13->addWidget(label_7, 0, 0, 1, 1);

        frame_5 = new QFrame(tab_3);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_34 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_34, 0, 0, 1, 1);

        label_24 = new QLabel(frame_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font4);

        gridLayout_4->addWidget(label_24, 0, 1, 1, 1);

        txiStartDate = new QDateEdit(frame_5);
        txiStartDate->setObjectName(QString::fromUtf8("txiStartDate"));
        txiStartDate->setMinimumSize(QSize(0, 22));
        txiStartDate->setMaximumSize(QSize(16777215, 22));
        txiStartDate->setFont(font4);
        txiStartDate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        txiStartDate->setCalendarPopup(true);

        gridLayout_4->addWidget(txiStartDate, 0, 2, 1, 1);

        label_25 = new QLabel(frame_5);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font4);

        gridLayout_4->addWidget(label_25, 0, 3, 1, 1);

        txiEndDate = new QDateEdit(frame_5);
        txiEndDate->setObjectName(QString::fromUtf8("txiEndDate"));
        txiEndDate->setMinimumSize(QSize(0, 22));
        txiEndDate->setMaximumSize(QSize(16777215, 22));
        txiEndDate->setFont(font4);
        txiEndDate->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(txiEndDate, 0, 4, 1, 1);

        label_26 = new QLabel(frame_5);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setFont(font4);

        gridLayout_4->addWidget(label_26, 0, 5, 1, 1);

        cbx_gameType_yb = new QComboBox(frame_5);
        cbx_gameType_yb->setObjectName(QString::fromUtf8("cbx_gameType_yb"));
        cbx_gameType_yb->setMinimumSize(QSize(0, 22));
        cbx_gameType_yb->setMaximumSize(QSize(16777215, 22));
        cbx_gameType_yb->setFont(font4);
        cbx_gameType_yb->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(cbx_gameType_yb, 0, 6, 1, 1);

        horizontalSpacer_35 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_35, 0, 7, 1, 1);

        horizontalSpacer_36 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_36, 1, 0, 1, 1);

        label_27 = new QLabel(frame_5);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font4);
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_27, 1, 1, 1, 1);

        cbx_state_yb = new QComboBox(frame_5);
        cbx_state_yb->setObjectName(QString::fromUtf8("cbx_state_yb"));
        cbx_state_yb->setMinimumSize(QSize(0, 22));
        cbx_state_yb->setMaximumSize(QSize(16777215, 22));
        cbx_state_yb->setFont(font4);
        cbx_state_yb->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(cbx_state_yb, 1, 2, 1, 1);

        label_28 = new QLabel(frame_5);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setFont(font4);

        gridLayout_4->addWidget(label_28, 1, 3, 1, 1);

        txi_gameAccount_yb = new QLineEdit(frame_5);
        txi_gameAccount_yb->setObjectName(QString::fromUtf8("txi_gameAccount_yb"));
        txi_gameAccount_yb->setMinimumSize(QSize(0, 22));
        txi_gameAccount_yb->setMaximumSize(QSize(16777215, 22));
        txi_gameAccount_yb->setFont(font4);
        txi_gameAccount_yb->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_gameAccount_yb->setMaxLength(20);

        gridLayout_4->addWidget(txi_gameAccount_yb, 1, 4, 1, 2);

        btn_search_yb = new QPushButton(frame_5);
        btn_search_yb->setObjectName(QString::fromUtf8("btn_search_yb"));
        btn_search_yb->setMinimumSize(QSize(40, 25));
        btn_search_yb->setMaximumSize(QSize(40, 25));
        btn_search_yb->setFont(font2);
        btn_search_yb->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cx.png);"));

        gridLayout_4->addWidget(btn_search_yb, 1, 6, 1, 1);

        horizontalSpacer_37 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_37, 1, 7, 1, 1);


        gridLayout_13->addWidget(frame_5, 1, 0, 1, 1);

        frame_6 = new QFrame(tab_3);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        gridLayout_12 = new QGridLayout(frame_6);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        txt_rpt_total_yb = new QLabel(frame_6);
        txt_rpt_total_yb->setObjectName(QString::fromUtf8("txt_rpt_total_yb"));
        txt_rpt_total_yb->setFont(font3);
        txt_rpt_total_yb->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_12->addWidget(txt_rpt_total_yb, 0, 0, 1, 1);

        horizontalSpacer_42 = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_42, 0, 1, 1, 1);

        txt_rpt_money_yb = new QLabel(frame_6);
        txt_rpt_money_yb->setObjectName(QString::fromUtf8("txt_rpt_money_yb"));
        txt_rpt_money_yb->setFont(font3);
        txt_rpt_money_yb->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_12->addWidget(txt_rpt_money_yb, 0, 2, 1, 1);

        horizontalSpacer_43 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_43, 0, 3, 1, 1);

        txt_rpt_repay_yb = new QLabel(frame_6);
        txt_rpt_repay_yb->setObjectName(QString::fromUtf8("txt_rpt_repay_yb"));
        txt_rpt_repay_yb->setFont(font3);
        txt_rpt_repay_yb->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_12->addWidget(txt_rpt_repay_yb, 0, 4, 1, 1);

        horizontalSpacer_44 = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_44, 0, 5, 1, 1);

        btn_refresh_yb = new QPushButton(frame_6);
        btn_refresh_yb->setObjectName(QString::fromUtf8("btn_refresh_yb"));
        btn_refresh_yb->setMinimumSize(QSize(40, 25));
        btn_refresh_yb->setMaximumSize(QSize(40, 25));
        btn_refresh_yb->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_sx.png);"));

        gridLayout_12->addWidget(btn_refresh_yb, 0, 6, 1, 1);

        btn_print_yb = new QPushButton(frame_6);
        btn_print_yb->setObjectName(QString::fromUtf8("btn_print_yb"));
        btn_print_yb->setMinimumSize(QSize(41, 41));
        btn_print_yb->setMaximumSize(QSize(41, 41));
        btn_print_yb->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/print.png);"));

        gridLayout_12->addWidget(btn_print_yb, 0, 7, 1, 1);


        gridLayout_13->addWidget(frame_6, 2, 0, 1, 1);

        tableWidget_yb = new QTableWidget(tab_3);
        tableWidget_yb->setObjectName(QString::fromUtf8("tableWidget_yb"));
        tableWidget_yb->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget_yb->setFrameShape(QFrame::NoFrame);
        tableWidget_yb->setGridStyle(Qt::SolidLine);

        gridLayout_13->addWidget(tableWidget_yb, 3, 0, 1, 2);

        yxcz_TabWidget->addTab(tab_3, QString());
        QWidget::setTabOrder(txi_gameAccount, txi_money);
        QWidget::setTabOrder(txi_money, cbx_gameType);
        QWidget::setTabOrder(cbx_gameType, txi_content);
        QWidget::setTabOrder(txi_content, btn_submit);
        QWidget::setTabOrder(btn_submit, btn_reset);
        QWidget::setTabOrder(btn_reset, rdo_print_on);
        QWidget::setTabOrder(rdo_print_on, rdo_print_off);
        QWidget::setTabOrder(rdo_print_off, btn_refresh);
        QWidget::setTabOrder(btn_refresh, btn_print);
        QWidget::setTabOrder(btn_print, tableWidget);
        QWidget::setTabOrder(tableWidget, cbx_gameType_rb);
        QWidget::setTabOrder(cbx_gameType_rb, cbx_state_rb);
        QWidget::setTabOrder(cbx_state_rb, txi_gameAccount_rb);
        QWidget::setTabOrder(txi_gameAccount_rb, btn_search_rb);
        QWidget::setTabOrder(btn_search_rb, btn_refresh_rb);
        QWidget::setTabOrder(btn_refresh_rb, btn_print_rb);
        QWidget::setTabOrder(btn_print_rb, tableWidget_rb);
        QWidget::setTabOrder(tableWidget_rb, txiStartDate);
        QWidget::setTabOrder(txiStartDate, txiEndDate);
        QWidget::setTabOrder(txiEndDate, cbx_gameType_yb);
        QWidget::setTabOrder(cbx_gameType_yb, cbx_state_yb);
        QWidget::setTabOrder(cbx_state_yb, txi_gameAccount_yb);
        QWidget::setTabOrder(txi_gameAccount_yb, btn_search_yb);
        QWidget::setTabOrder(btn_search_yb, btn_refresh_yb);
        QWidget::setTabOrder(btn_refresh_yb, btn_print_yb);
        QWidget::setTabOrder(btn_print_yb, tableWidget_yb);

        retranslateUi(yxcz_TabWidget);

        yxcz_TabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(yxcz_TabWidget);
    } // setupUi

    void retranslateUi(QTabWidget *yxcz_TabWidget)
    {
        yxcz_TabWidget->setWindowTitle(QApplication::translate("yxcz_TabWidget", "TabWidget", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("yxcz_TabWidget", "      \346\270\270\346\210\217\345\205\205\345\200\274", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("yxcz_TabWidget", "\346\270\270\346\210\217\350\264\246\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_gameAccount->setText(QString());
        btn_submit->setText(QApplication::translate("yxcz_TabWidget", "\347\241\256\350\256\244\347\274\264\350\264\271", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("yxcz_TabWidget", "\345\205\205\345\200\274\351\207\221\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_money->setText(QString());
        btn_reset->setText(QApplication::translate("yxcz_TabWidget", "\351\207\215\347\275\256", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("yxcz_TabWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\256\213\344\275\223'; font-size:14pt;\">\346\270\270\346\210\217\347\261\273\345\236\213\357\274\232</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("yxcz_TabWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\345\256\213\344\275\223'; font-size:14pt;\">\345\244\207\346\263\250\357\274\232</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        txi_content->setHtml(QApplication::translate("yxcz_TabWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        txt_rpt_count->setText(QApplication::translate("yxcz_TabWidget", "\347\274\264\350\264\271\357\274\232\343\200\220100\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        txt_rpt_money->setText(QApplication::translate("yxcz_TabWidget", "\347\274\264\350\264\271\351\207\221\351\242\235\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("yxcz_TabWidget", "\351\273\230\350\256\244\346\211\223\345\215\260", 0, QApplication::UnicodeUTF8));
        rdo_print_on->setText(QApplication::translate("yxcz_TabWidget", "\345\274\200", 0, QApplication::UnicodeUTF8));
        rdo_print_off->setText(QApplication::translate("yxcz_TabWidget", "\345\205\263", 0, QApplication::UnicodeUTF8));
        btn_refresh->setText(QString());
        btn_print->setText(QString());
        yxcz_TabWidget->setTabText(yxcz_TabWidget->indexOf(tab), QApplication::translate("yxcz_TabWidget", "\346\270\270\346\210\217\345\205\205\345\200\274", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("yxcz_TabWidget", "      \346\270\270\346\210\217\345\205\205\345\200\274\346\227\245\346\212\245", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("yxcz_TabWidget", "\346\270\270\346\210\217\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("yxcz_TabWidget", "\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("yxcz_TabWidget", "\346\270\270\346\210\217\350\264\246\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_gameAccount_rb->setText(QString());
        btn_search_rb->setText(QString());
        txt_rpt_total_rb->setText(QApplication::translate("yxcz_TabWidget", "\347\274\264\350\264\271\357\274\232\343\200\220100\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        txt_rpt_money_rb->setText(QApplication::translate("yxcz_TabWidget", "\347\274\264\350\264\271\351\207\221\351\242\235\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        txt_rpt_repay_rb->setText(QApplication::translate("yxcz_TabWidget", "\350\277\224\346\254\276\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        btn_refresh_rb->setText(QString());
        btn_print_rb->setText(QString());
        yxcz_TabWidget->setTabText(yxcz_TabWidget->indexOf(tab_2), QApplication::translate("yxcz_TabWidget", "\346\270\270\346\210\217\345\205\205\345\200\274\346\227\245\346\212\245", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("yxcz_TabWidget", "      \346\270\270\346\210\217\345\205\205\345\200\274\346\234\210\346\212\245", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("yxcz_TabWidget", "\350\265\267\345\247\213\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("yxcz_TabWidget", "\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("yxcz_TabWidget", "\346\270\270\346\210\217\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("yxcz_TabWidget", "\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("yxcz_TabWidget", "\346\270\270\346\210\217\350\264\246\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_gameAccount_yb->setText(QString());
        btn_search_yb->setText(QString());
        txt_rpt_total_yb->setText(QApplication::translate("yxcz_TabWidget", "\347\274\264\350\264\271\357\274\232\343\200\220100\343\200\221\347\254\224", 0, QApplication::UnicodeUTF8));
        txt_rpt_money_yb->setText(QApplication::translate("yxcz_TabWidget", "\347\274\264\350\264\271\351\207\221\351\242\235\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        txt_rpt_repay_yb->setText(QApplication::translate("yxcz_TabWidget", "\350\277\224\346\254\276\357\274\232\343\200\22010000\343\200\221\345\205\203", 0, QApplication::UnicodeUTF8));
        btn_refresh_yb->setText(QString());
        btn_print_yb->setText(QString());
        yxcz_TabWidget->setTabText(yxcz_TabWidget->indexOf(tab_3), QApplication::translate("yxcz_TabWidget", "\346\270\270\346\210\217\345\205\205\345\200\274\346\234\210\346\212\245", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class yxcz_TabWidget: public Ui_yxcz_TabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YXCZ_TABWIDGET_H
