/********************************************************************************
** Form generated from reading UI file 'ydxh_scrollarea.ui'
**
** Created: Sun Apr 15 14:38:00 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YDXH_SCROLLAREA_H
#define UI_YDXH_SCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ydxh_ScrollArea
{
public:
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *txt_title;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QWidget *widget_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QRadioButton *rdo_all;
    QRadioButton *rdo_1;
    QRadioButton *rdo_2;
    QRadioButton *rdo_3;
    QRadioButton *rdo_4;
    QRadioButton *rdo_5;
    QLabel *txt_count;
    QRadioButton *rdo_6;
    QLineEdit *txi_include;
    QLabel *label_23;
    QLineEdit *txi_exclude;
    QLabel *label_27;
    QLineEdit *txi_exclude_tail;
    QLabel *label_26;
    QLabel *label_25;
    QLineEdit *txi_include_tail;
    QLineEdit *txi_no11;
    QLineEdit *txi_no9;
    QLabel *label_24;
    QComboBox *cbx_xhf;
    QLineEdit *txi_no7;
    QLineEdit *txi_no5;
    QLineEdit *txi_no6;
    QLineEdit *txi_no10;
    QLineEdit *txi_no1;
    QLineEdit *txi_no3;
    QLabel *label_28;
    QLineEdit *txi_no2;
    QLineEdit *txi_no8;
    QLabel *label_30;
    QLineEdit *txi_no4;
    QComboBox *cbx_hd;
    QPushButton *btn_search;
    QPushButton *btn_reset;
    QLabel *label_29;
    QComboBox *cbx_tail_format;
    QComboBox *cbx_rwzc;
    QLabel *label_31;
    QSpacerItem *horizontalSpacer_8;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QLabel *txt_rpt_total;
    QPushButton *btn_front;
    QPushButton *btn_pre;
    QLabel *label_2;
    QSpinBox *spinBox;
    QLabel *label;
    QPushButton *ben_next;
    QPushButton *btn_tail;
    QSpacerItem *horizontalSpacer;
    QFrame *frame_3;
    QGridLayout *gridLayout_5;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QScrollArea *ydxh_ScrollArea)
    {
        if (ydxh_ScrollArea->objectName().isEmpty())
            ydxh_ScrollArea->setObjectName(QString::fromUtf8("ydxh_ScrollArea"));
        ydxh_ScrollArea->resize(1000, 650);
        ydxh_ScrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        ydxh_ScrollArea->setFrameShape(QFrame::NoFrame);
        ydxh_ScrollArea->setLineWidth(0);
        ydxh_ScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 983, 1290));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        txt_title = new QLabel(scrollAreaWidgetContents);
        txt_title->setObjectName(QString::fromUtf8("txt_title"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txt_title->sizePolicy().hasHeightForWidth());
        txt_title->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        txt_title->setFont(font);
        txt_title->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/mainframe/navigator.png);\n"
"background-repeat: no-repeat;"));

        gridLayout->addWidget(txt_title, 0, 0, 1, 1);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 0, 0, 1, 1);

        widget_3 = new QWidget(frame);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        widget_3->setMinimumSize(QSize(750, 110));
        widget_3->setMaximumSize(QSize(750, 110));
        widget_3->setBaseSize(QSize(820, 100));
        groupBox = new QGroupBox(widget_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 70, 741, 36));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(-1, 0, -1, 0);
        rdo_all = new QRadioButton(groupBox);
        rdo_all->setObjectName(QString::fromUtf8("rdo_all"));
        rdo_all->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        rdo_all->setChecked(true);

        gridLayout_4->addWidget(rdo_all, 0, 0, 1, 1);

        rdo_1 = new QRadioButton(groupBox);
        rdo_1->setObjectName(QString::fromUtf8("rdo_1"));
        rdo_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_4->addWidget(rdo_1, 0, 1, 1, 1);

        rdo_2 = new QRadioButton(groupBox);
        rdo_2->setObjectName(QString::fromUtf8("rdo_2"));
        rdo_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_4->addWidget(rdo_2, 0, 2, 1, 1);

        rdo_3 = new QRadioButton(groupBox);
        rdo_3->setObjectName(QString::fromUtf8("rdo_3"));
        rdo_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_4->addWidget(rdo_3, 0, 3, 1, 1);

        rdo_4 = new QRadioButton(groupBox);
        rdo_4->setObjectName(QString::fromUtf8("rdo_4"));
        rdo_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_4->addWidget(rdo_4, 0, 4, 1, 1);

        rdo_5 = new QRadioButton(groupBox);
        rdo_5->setObjectName(QString::fromUtf8("rdo_5"));
        rdo_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_4->addWidget(rdo_5, 0, 5, 1, 1);

        txt_count = new QLabel(groupBox);
        txt_count->setObjectName(QString::fromUtf8("txt_count"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(10);
        txt_count->setFont(font1);
        txt_count->setLayoutDirection(Qt::RightToLeft);
        txt_count->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_4->addWidget(txt_count, 0, 7, 1, 1);

        rdo_6 = new QRadioButton(groupBox);
        rdo_6->setObjectName(QString::fromUtf8("rdo_6"));
        rdo_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_4->addWidget(rdo_6, 0, 6, 1, 1);

        txi_include = new QLineEdit(widget_3);
        txi_include->setObjectName(QString::fromUtf8("txi_include"));
        txi_include->setGeometry(QRect(70, 10, 35, 20));
        txi_include->setMinimumSize(QSize(0, 20));
        txi_include->setMaximumSize(QSize(16777215, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(12);
        txi_include->setFont(font2);
        txi_include->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_include->setMaxLength(11);
        label_23 = new QLabel(widget_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(0, 10, 71, 21));
        label_23->setFont(font2);
        txi_exclude = new QLineEdit(widget_3);
        txi_exclude->setObjectName(QString::fromUtf8("txi_exclude"));
        txi_exclude->setGeometry(QRect(70, 40, 35, 20));
        txi_exclude->setMinimumSize(QSize(0, 20));
        txi_exclude->setMaximumSize(QSize(16777215, 20));
        txi_exclude->setFont(font2);
        txi_exclude->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_exclude->setMaxLength(11);
        label_27 = new QLabel(widget_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(0, 40, 71, 21));
        label_27->setFont(font2);
        txi_exclude_tail = new QLineEdit(widget_3);
        txi_exclude_tail->setObjectName(QString::fromUtf8("txi_exclude_tail"));
        txi_exclude_tail->setGeometry(QRect(180, 40, 20, 20));
        txi_exclude_tail->setMinimumSize(QSize(0, 20));
        txi_exclude_tail->setMaximumSize(QSize(16777215, 20));
        txi_exclude_tail->setFont(font2);
        txi_exclude_tail->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_exclude_tail->setMaxLength(1);
        label_26 = new QLabel(widget_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(110, 40, 71, 21));
        label_26->setFont(font2);
        label_25 = new QLabel(widget_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(110, 10, 71, 21));
        label_25->setFont(font2);
        txi_include_tail = new QLineEdit(widget_3);
        txi_include_tail->setObjectName(QString::fromUtf8("txi_include_tail"));
        txi_include_tail->setGeometry(QRect(180, 10, 20, 20));
        txi_include_tail->setMinimumSize(QSize(0, 20));
        txi_include_tail->setMaximumSize(QSize(16777215, 20));
        txi_include_tail->setFont(font2);
        txi_include_tail->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_include_tail->setMaxLength(1);
        txi_no11 = new QLineEdit(widget_3);
        txi_no11->setObjectName(QString::fromUtf8("txi_no11"));
        txi_no11->setGeometry(QRect(465, 40, 21, 20));
        txi_no11->setMinimumSize(QSize(0, 20));
        txi_no11->setMaximumSize(QSize(16777215, 20));
        txi_no11->setFont(font2);
        txi_no11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no11->setMaxLength(1);
        txi_no9 = new QLineEdit(widget_3);
        txi_no9->setObjectName(QString::fromUtf8("txi_no9"));
        txi_no9->setGeometry(QRect(425, 40, 21, 20));
        txi_no9->setMinimumSize(QSize(0, 20));
        txi_no9->setMaximumSize(QSize(16777215, 20));
        txi_no9->setFont(font2);
        txi_no9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no9->setMaxLength(1);
        label_24 = new QLabel(widget_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(210, 10, 61, 21));
        label_24->setFont(font2);
        cbx_xhf = new QComboBox(widget_3);
        cbx_xhf->setObjectName(QString::fromUtf8("cbx_xhf"));
        cbx_xhf->setGeometry(QRect(265, 10, 91, 22));
        cbx_xhf->setMinimumSize(QSize(0, 22));
        cbx_xhf->setMaximumSize(QSize(16777215, 22));
        cbx_xhf->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no7 = new QLineEdit(widget_3);
        txi_no7->setObjectName(QString::fromUtf8("txi_no7"));
        txi_no7->setGeometry(QRect(385, 40, 21, 20));
        txi_no7->setMinimumSize(QSize(0, 20));
        txi_no7->setMaximumSize(QSize(16777215, 20));
        txi_no7->setFont(font2);
        txi_no7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no7->setMaxLength(1);
        txi_no5 = new QLineEdit(widget_3);
        txi_no5->setObjectName(QString::fromUtf8("txi_no5"));
        txi_no5->setGeometry(QRect(345, 40, 21, 20));
        txi_no5->setMinimumSize(QSize(0, 20));
        txi_no5->setMaximumSize(QSize(16777215, 20));
        txi_no5->setFont(font2);
        txi_no5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no5->setMaxLength(1);
        txi_no6 = new QLineEdit(widget_3);
        txi_no6->setObjectName(QString::fromUtf8("txi_no6"));
        txi_no6->setGeometry(QRect(365, 40, 21, 20));
        txi_no6->setMinimumSize(QSize(0, 20));
        txi_no6->setMaximumSize(QSize(16777215, 20));
        txi_no6->setFont(font2);
        txi_no6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no6->setMaxLength(1);
        txi_no10 = new QLineEdit(widget_3);
        txi_no10->setObjectName(QString::fromUtf8("txi_no10"));
        txi_no10->setGeometry(QRect(445, 40, 21, 20));
        txi_no10->setMinimumSize(QSize(0, 20));
        txi_no10->setMaximumSize(QSize(16777215, 20));
        txi_no10->setFont(font2);
        txi_no10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no10->setMaxLength(1);
        txi_no1 = new QLineEdit(widget_3);
        txi_no1->setObjectName(QString::fromUtf8("txi_no1"));
        txi_no1->setGeometry(QRect(265, 40, 21, 20));
        txi_no1->setMinimumSize(QSize(0, 20));
        txi_no1->setMaximumSize(QSize(16777215, 20));
        txi_no1->setFont(font2);
        txi_no1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no1->setMaxLength(1);
        txi_no3 = new QLineEdit(widget_3);
        txi_no3->setObjectName(QString::fromUtf8("txi_no3"));
        txi_no3->setGeometry(QRect(305, 40, 21, 20));
        txi_no3->setMinimumSize(QSize(0, 20));
        txi_no3->setMaximumSize(QSize(16777215, 20));
        txi_no3->setFont(font2);
        txi_no3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no3->setMaxLength(1);
        label_28 = new QLabel(widget_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(360, 10, 71, 21));
        label_28->setFont(font2);
        txi_no2 = new QLineEdit(widget_3);
        txi_no2->setObjectName(QString::fromUtf8("txi_no2"));
        txi_no2->setGeometry(QRect(285, 40, 21, 20));
        txi_no2->setMinimumSize(QSize(0, 20));
        txi_no2->setMaximumSize(QSize(16777215, 20));
        txi_no2->setFont(font2);
        txi_no2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no2->setMaxLength(1);
        txi_no8 = new QLineEdit(widget_3);
        txi_no8->setObjectName(QString::fromUtf8("txi_no8"));
        txi_no8->setGeometry(QRect(405, 40, 21, 20));
        txi_no8->setMinimumSize(QSize(0, 20));
        txi_no8->setMaximumSize(QSize(16777215, 20));
        txi_no8->setFont(font2);
        txi_no8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no8->setMaxLength(1);
        label_30 = new QLabel(widget_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(210, 40, 55, 21));
        label_30->setFont(font2);
        txi_no4 = new QLineEdit(widget_3);
        txi_no4->setObjectName(QString::fromUtf8("txi_no4"));
        txi_no4->setGeometry(QRect(325, 40, 21, 20));
        txi_no4->setMinimumSize(QSize(0, 20));
        txi_no4->setMaximumSize(QSize(16777215, 20));
        txi_no4->setFont(font2);
        txi_no4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        txi_no4->setMaxLength(1);
        cbx_hd = new QComboBox(widget_3);
        cbx_hd->setObjectName(QString::fromUtf8("cbx_hd"));
        cbx_hd->setGeometry(QRect(435, 10, 91, 22));
        cbx_hd->setMinimumSize(QSize(0, 22));
        cbx_hd->setMaximumSize(QSize(16777215, 22));
        cbx_hd->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        btn_search = new QPushButton(widget_3);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));
        btn_search->setGeometry(QRect(700, 10, 38, 25));
        btn_search->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_cx.png);"));
        btn_reset = new QPushButton(widget_3);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        btn_reset->setGeometry(QRect(700, 40, 38, 25));
        btn_reset->setStyleSheet(QString::fromUtf8("background-image: url(:/btn/images/mainframe/btn_qk.png);"));
        label_29 = new QLabel(widget_3);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(530, 10, 71, 21));
        label_29->setFont(font2);
        cbx_tail_format = new QComboBox(widget_3);
        cbx_tail_format->setObjectName(QString::fromUtf8("cbx_tail_format"));
        cbx_tail_format->setGeometry(QRect(605, 10, 91, 22));
        cbx_tail_format->setMinimumSize(QSize(0, 22));
        cbx_tail_format->setMaximumSize(QSize(16777215, 22));
        cbx_tail_format->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        cbx_rwzc = new QComboBox(widget_3);
        cbx_rwzc->setObjectName(QString::fromUtf8("cbx_rwzc"));
        cbx_rwzc->setGeometry(QRect(605, 40, 91, 22));
        cbx_rwzc->setMinimumSize(QSize(0, 22));
        cbx_rwzc->setMaximumSize(QSize(16777215, 22));
        cbx_rwzc->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_31 = new QLabel(widget_3);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(530, 40, 71, 21));
        label_31->setFont(font2);

        gridLayout_3->addWidget(widget_3, 0, 1, 2, 1);

        horizontalSpacer_8 = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 1, 2, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        txt_rpt_total = new QLabel(frame_2);
        txt_rpt_total->setObjectName(QString::fromUtf8("txt_rpt_total"));
        txt_rpt_total->setFont(font1);
        txt_rpt_total->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(txt_rpt_total, 0, 0, 1, 1);

        btn_front = new QPushButton(frame_2);
        btn_front->setObjectName(QString::fromUtf8("btn_front"));

        gridLayout_2->addWidget(btn_front, 0, 2, 1, 1);

        btn_pre = new QPushButton(frame_2);
        btn_pre->setObjectName(QString::fromUtf8("btn_pre"));

        gridLayout_2->addWidget(btn_pre, 0, 3, 1, 1);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(label_2, 0, 4, 1, 1);

        spinBox = new QSpinBox(frame_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimumSize(QSize(0, 20));
        spinBox->setMaximumSize(QSize(16777215, 20));
        spinBox->setMinimum(1);
        spinBox->setValue(99);

        gridLayout_2->addWidget(spinBox, 0, 5, 1, 1);

        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        gridLayout_2->addWidget(label, 0, 6, 1, 1);

        ben_next = new QPushButton(frame_2);
        ben_next->setObjectName(QString::fromUtf8("ben_next"));

        gridLayout_2->addWidget(ben_next, 0, 7, 1, 1);

        btn_tail = new QPushButton(frame_2);
        btn_tail->setObjectName(QString::fromUtf8("btn_tail"));

        gridLayout_2->addWidget(btn_tail, 0, 8, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);

        frame_3 = new QFrame(scrollAreaWidgetContents);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setMinimumSize(QSize(0, 1060));
        frame_3->setMaximumSize(QSize(16777215, 1060));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 244, 252);"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tableWidget = new QTableWidget(frame_3);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        if (tableWidget->rowCount() < 20)
            tableWidget->setRowCount(20);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMinimumSize(QSize(910, 0));
        tableWidget->setMaximumSize(QSize(910, 16777215));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tableWidget->setRowCount(20);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setDefaultSectionSize(300);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(50);

        gridLayout_5->addWidget(tableWidget, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(9, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(8, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 0, 0, 1, 1);


        gridLayout->addWidget(frame_3, 3, 0, 1, 1);

        ydxh_ScrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(ydxh_ScrollArea);

        QMetaObject::connectSlotsByName(ydxh_ScrollArea);
    } // setupUi

    void retranslateUi(QScrollArea *ydxh_ScrollArea)
    {
        ydxh_ScrollArea->setWindowTitle(QApplication::translate("ydxh_ScrollArea", "ScrollArea", 0, QApplication::UnicodeUTF8));
        txt_title->setText(QApplication::translate("ydxh_ScrollArea", "      \347\247\273\345\212\250\351\200\211\345\217\267", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        rdo_all->setText(QApplication::translate("ydxh_ScrollArea", "\346\211\200\346\234\211\345\217\267\347\240\201", 0, QApplication::UnicodeUTF8));
        rdo_1->setText(QApplication::translate("ydxh_ScrollArea", "\347\262\276\345\223\201\351\235\223\345\217\267\345\214\272", 0, QApplication::UnicodeUTF8));
        rdo_2->setText(QApplication::translate("ydxh_ScrollArea", "\344\277\203\351\224\200\345\214\272\344\270\200", 0, QApplication::UnicodeUTF8));
        rdo_3->setText(QApplication::translate("ydxh_ScrollArea", "\344\277\203\351\224\200\345\214\272\344\272\214", 0, QApplication::UnicodeUTF8));
        rdo_4->setText(QApplication::translate("ydxh_ScrollArea", "\344\277\203\351\224\200\345\214\272\344\270\211", 0, QApplication::UnicodeUTF8));
        rdo_5->setText(QApplication::translate("ydxh_ScrollArea", "50\351\235\242\345\200\274", 0, QApplication::UnicodeUTF8));
        txt_count->setText(QApplication::translate("ydxh_ScrollArea", "\343\200\220102\343\200\221", 0, QApplication::UnicodeUTF8));
        rdo_6->setText(QApplication::translate("ydxh_ScrollArea", "\347\211\271\344\273\267\345\214\272", 0, QApplication::UnicodeUTF8));
        txi_include->setText(QString());
        label_23->setText(QApplication::translate("ydxh_ScrollArea", "\345\214\205\345\220\253\346\225\260\345\255\227\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_exclude->setText(QString());
        label_27->setText(QApplication::translate("ydxh_ScrollArea", "\346\216\222\351\231\244\346\225\260\345\255\227\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_exclude_tail->setText(QString());
        label_26->setText(QApplication::translate("ydxh_ScrollArea", "\346\216\222\351\231\244\345\260\276\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("ydxh_ScrollArea", "\345\214\205\345\220\253\345\260\276\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_include_tail->setText(QApplication::translate("ydxh_ScrollArea", "9", 0, QApplication::UnicodeUTF8));
        txi_no11->setText(QString());
        txi_no9->setText(QString());
        label_24->setText(QApplication::translate("ydxh_ScrollArea", "\351\200\211\345\217\267\350\264\271\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_no7->setText(QString());
        txi_no5->setText(QString());
        txi_no6->setText(QString());
        txi_no10->setText(QString());
        txi_no1->setText(QString());
        txi_no3->setText(QString());
        label_28->setText(QApplication::translate("ydxh_ScrollArea", "\346\213\245\346\234\211\345\217\267\346\256\265\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_no2->setText(QString());
        txi_no8->setText(QString());
        label_30->setText(QApplication::translate("ydxh_ScrollArea", "\346\220\234\347\264\242\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        txi_no4->setText(QString());
        btn_search->setText(QString());
        btn_reset->setText(QString());
        label_29->setText(QApplication::translate("ydxh_ScrollArea", "\345\260\276\345\217\267\347\211\271\347\202\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("ydxh_ScrollArea", "\345\205\245\347\275\221\346\224\277\347\255\226\357\274\232", 0, QApplication::UnicodeUTF8));
        txt_rpt_total->setText(QApplication::translate("ydxh_ScrollArea", "\345\205\261\343\200\220\343\200\221\351\241\265", 0, QApplication::UnicodeUTF8));
        btn_front->setText(QApplication::translate("ydxh_ScrollArea", "\351\246\226\351\241\265", 0, QApplication::UnicodeUTF8));
        btn_pre->setText(QApplication::translate("ydxh_ScrollArea", "\344\270\212\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ydxh_ScrollArea", "\347\254\254\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ydxh_ScrollArea", "\351\241\265", 0, QApplication::UnicodeUTF8));
        ben_next->setText(QApplication::translate("ydxh_ScrollArea", "\344\270\213\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
        btn_tail->setText(QApplication::translate("ydxh_ScrollArea", "\345\260\276\351\241\265", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ydxh_ScrollArea: public Ui_ydxh_ScrollArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YDXH_SCROLLAREA_H
