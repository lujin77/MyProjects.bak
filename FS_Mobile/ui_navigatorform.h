/********************************************************************************
** Form generated from reading UI file 'navigatorform.ui'
**
** Created: Sun Apr 15 14:37:59 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAVIGATORFORM_H
#define UI_NAVIGATORFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NavigatorForm
{
public:
    QGridLayout *gridLayout;
    QFrame *topFrame;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_9;
    QLabel *txtSysName;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_6;
    QLabel *txtMoneyAlert;
    QPushButton *btnMoney;
    QLabel *txtWelcome;
    QLabel *txtName;
    QLabel *txtSplacer2;
    QPushButton *btnLoggout;
    QLabel *txtSplacer2_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *mainStack;
    QWidget *page;
    QWidget *page_2;
    QFrame *leftFrame;
    QPushButton *btn_ydjf;
    QPushButton *btn_jfrb;
    QPushButton *btn_skjs;
    QPushButton *btn_ywslcx;
    QPushButton *btn_ywsl;
    QPushButton *btn_xgmm;
    QPushButton *btn_yhxxxg;
    QPushButton *btn_zxgg;
    QPushButton *btn_drjjtj;
    QPushButton *btn_gszh;
    QPushButton *btn_yxcz;
    QPushButton *btn_gmjp;
    QPushButton *btn_gmczk;
    QPushButton *btn_drjymx;
    QPushButton *btn_ydxh;
    QPushButton *btn_dbfjs;
    QPushButton *btn_skcx;
    QPushButton *btn_jfyb;
    QPushButton *btn_kcxk;
    QPushButton *btn_xkkk;
    QPushButton *btn_tczfcx;
    QPushButton *btn_zhye;
    QPushButton *btn_zhcz;
    QPushButton *btn_kdjf;
    QGroupBox *groupBox;
    QLabel *txtTel1;
    QLabel *txtTel2;

    void setupUi(QWidget *NavigatorForm)
    {
        if (NavigatorForm->objectName().isEmpty())
            NavigatorForm->setObjectName(QString::fromUtf8("NavigatorForm"));
        NavigatorForm->resize(1200, 800);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NavigatorForm->sizePolicy().hasHeightForWidth());
        NavigatorForm->setSizePolicy(sizePolicy);
        NavigatorForm->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(NavigatorForm);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        topFrame = new QFrame(NavigatorForm);
        topFrame->setObjectName(QString::fromUtf8("topFrame"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(topFrame->sizePolicy().hasHeightForWidth());
        topFrame->setSizePolicy(sizePolicy1);
        topFrame->setMinimumSize(QSize(1024, 91));
        topFrame->setMaximumSize(QSize(16777215, 91));
        topFrame->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/top.png);"));
        gridLayout_2 = new QGridLayout(topFrame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_9 = new QSpacerItem(200, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 0, 0, 1, 1);

        txtSysName = new QLabel(topFrame);
        txtSysName->setObjectName(QString::fromUtf8("txtSysName"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        txtSysName->setFont(font);
        txtSysName->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 9pt \"Agency FB\";\n"
"font: 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background-image: url(:/bg/images/bg/transparent.png);\n"
"\n"
""));

        gridLayout_2->addWidget(txtSysName, 0, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(356, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 2, 1, 3);

        horizontalSpacer_6 = new QSpacerItem(200, 14, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 2, 1, 1);

        txtMoneyAlert = new QLabel(topFrame);
        txtMoneyAlert->setObjectName(QString::fromUtf8("txtMoneyAlert"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font1.setPointSize(12);
        txtMoneyAlert->setFont(font1);
        txtMoneyAlert->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/bg/images/bg/transparent.png);"));

        gridLayout_2->addWidget(txtMoneyAlert, 1, 3, 1, 1);

        btnMoney = new QPushButton(topFrame);
        btnMoney->setObjectName(QString::fromUtf8("btnMoney"));
        btnMoney->setMinimumSize(QSize(70, 20));
        btnMoney->setMaximumSize(QSize(70, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        btnMoney->setFont(font2);
        btnMoney->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);"));

        gridLayout_2->addWidget(btnMoney, 1, 4, 1, 1);

        txtWelcome = new QLabel(topFrame);
        txtWelcome->setObjectName(QString::fromUtf8("txtWelcome"));
        txtWelcome->setFont(font1);
        txtWelcome->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/bg/images/bg/transparent.png);"));

        gridLayout_2->addWidget(txtWelcome, 1, 5, 1, 1);

        txtName = new QLabel(topFrame);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setFont(font1);
        txtName->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/bg/images/bg/transparent.png);"));

        gridLayout_2->addWidget(txtName, 1, 6, 1, 1);

        txtSplacer2 = new QLabel(topFrame);
        txtSplacer2->setObjectName(QString::fromUtf8("txtSplacer2"));
        txtSplacer2->setFont(font1);
        txtSplacer2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/bg/images/bg/transparent.png);"));

        gridLayout_2->addWidget(txtSplacer2, 1, 7, 1, 1);

        btnLoggout = new QPushButton(topFrame);
        btnLoggout->setObjectName(QString::fromUtf8("btnLoggout"));
        btnLoggout->setMinimumSize(QSize(50, 20));
        btnLoggout->setMaximumSize(QSize(50, 20));
        btnLoggout->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);"));

        gridLayout_2->addWidget(btnLoggout, 1, 8, 1, 1);

        txtSplacer2_2 = new QLabel(topFrame);
        txtSplacer2_2->setObjectName(QString::fromUtf8("txtSplacer2_2"));
        txtSplacer2_2->setFont(font1);
        txtSplacer2_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/bg/images/bg/transparent.png);"));

        gridLayout_2->addWidget(txtSplacer2_2, 1, 9, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 10, 1, 1);


        gridLayout->addWidget(topFrame, 0, 0, 1, 3);

        horizontalSpacer_4 = new QSpacerItem(1, 91, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 3, 1, 1);

        verticalSpacer = new QSpacerItem(1, 695, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(214, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(976, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        mainStack = new QStackedWidget(NavigatorForm);
        mainStack->setObjectName(QString::fromUtf8("mainStack"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mainStack->sizePolicy().hasHeightForWidth());
        mainStack->setSizePolicy(sizePolicy2);
        mainStack->setFrameShape(QFrame::NoFrame);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        mainStack->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        mainStack->addWidget(page_2);

        gridLayout->addWidget(mainStack, 1, 1, 1, 2);

        leftFrame = new QFrame(NavigatorForm);
        leftFrame->setObjectName(QString::fromUtf8("leftFrame"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(leftFrame->sizePolicy().hasHeightForWidth());
        leftFrame->setSizePolicy(sizePolicy3);
        leftFrame->setMinimumSize(QSize(214, 698));
        leftFrame->setMaximumSize(QSize(214, 698));
        leftFrame->setStyleSheet(QString::fromUtf8("background-image: url(:/border/images/bg/btnList.png);"));
        leftFrame->setFrameShape(QFrame::NoFrame);
        leftFrame->setFrameShadow(QFrame::Raised);
        leftFrame->setLineWidth(0);
        btn_ydjf = new QPushButton(leftFrame);
        btn_ydjf->setObjectName(QString::fromUtf8("btn_ydjf"));
        btn_ydjf->setGeometry(QRect(20, 10, 89, 35));
        btn_ydjf->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_ydjf.png);"));
        btn_jfrb = new QPushButton(leftFrame);
        btn_jfrb->setObjectName(QString::fromUtf8("btn_jfrb"));
        btn_jfrb->setGeometry(QRect(20, 50, 89, 35));
        btn_jfrb->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_jfrb.png);"));
        btn_skjs = new QPushButton(leftFrame);
        btn_skjs->setObjectName(QString::fromUtf8("btn_skjs"));
        btn_skjs->setGeometry(QRect(110, 90, 89, 35));
        btn_skjs->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_skjs.png);"));
        btn_ywslcx = new QPushButton(leftFrame);
        btn_ywslcx->setObjectName(QString::fromUtf8("btn_ywslcx"));
        btn_ywslcx->setGeometry(QRect(20, 170, 89, 35));
        btn_ywslcx->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/btn_main/images/btnList/btn_ywslcx.png);"));
        btn_ywsl = new QPushButton(leftFrame);
        btn_ywsl->setObjectName(QString::fromUtf8("btn_ywsl"));
        btn_ywsl->setGeometry(QRect(20, 130, 89, 35));
        btn_ywsl->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_ywsl.png);"));
        btn_xgmm = new QPushButton(leftFrame);
        btn_xgmm->setObjectName(QString::fromUtf8("btn_xgmm"));
        btn_xgmm->setGeometry(QRect(110, 290, 89, 35));
        btn_xgmm->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/btn_main/images/btnList/btn_xgmm.png);"));
        btn_yhxxxg = new QPushButton(leftFrame);
        btn_yhxxxg->setObjectName(QString::fromUtf8("btn_yhxxxg"));
        btn_yhxxxg->setGeometry(QRect(20, 290, 89, 35));
        btn_yhxxxg->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_yhxxxg.png);"));
        btn_zxgg = new QPushButton(leftFrame);
        btn_zxgg->setObjectName(QString::fromUtf8("btn_zxgg"));
        btn_zxgg->setGeometry(QRect(110, 330, 89, 35));
        btn_zxgg->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/btn_main/images/btnList/btn_zxgg.png);"));
        btn_drjjtj = new QPushButton(leftFrame);
        btn_drjjtj->setObjectName(QString::fromUtf8("btn_drjjtj"));
        btn_drjjtj->setGeometry(QRect(110, 370, 89, 35));
        btn_drjjtj->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_drjytj.png);"));
        btn_gszh = new QPushButton(leftFrame);
        btn_gszh->setObjectName(QString::fromUtf8("btn_gszh"));
        btn_gszh->setGeometry(QRect(20, 330, 89, 35));
        btn_gszh->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_gszh.png);"));
        btn_yxcz = new QPushButton(leftFrame);
        btn_yxcz->setObjectName(QString::fromUtf8("btn_yxcz"));
        btn_yxcz->setGeometry(QRect(110, 410, 89, 35));
        btn_yxcz->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_gmqb.png);"));
        btn_gmjp = new QPushButton(leftFrame);
        btn_gmjp->setObjectName(QString::fromUtf8("btn_gmjp"));
        btn_gmjp->setGeometry(QRect(20, 450, 89, 35));
        btn_gmjp->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_gmjp.png);"));
        btn_gmczk = new QPushButton(leftFrame);
        btn_gmczk->setObjectName(QString::fromUtf8("btn_gmczk"));
        btn_gmczk->setGeometry(QRect(20, 410, 89, 35));
        btn_gmczk->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_gmczk.png);"));
        btn_drjymx = new QPushButton(leftFrame);
        btn_drjymx->setObjectName(QString::fromUtf8("btn_drjymx"));
        btn_drjymx->setGeometry(QRect(20, 370, 89, 35));
        btn_drjymx->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_drjymx.png);"));
        btn_ydxh = new QPushButton(leftFrame);
        btn_ydxh->setObjectName(QString::fromUtf8("btn_ydxh"));
        btn_ydxh->setGeometry(QRect(110, 10, 89, 35));
        btn_ydxh->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_ydxh.png);"));
        btn_dbfjs = new QPushButton(leftFrame);
        btn_dbfjs->setObjectName(QString::fromUtf8("btn_dbfjs"));
        btn_dbfjs->setGeometry(QRect(110, 210, 89, 35));
        btn_dbfjs->setContextMenuPolicy(Qt::NoContextMenu);
        btn_dbfjs->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_dbfjs.png);"));
        btn_skcx = new QPushButton(leftFrame);
        btn_skcx->setObjectName(QString::fromUtf8("btn_skcx"));
        btn_skcx->setGeometry(QRect(110, 50, 89, 35));
        btn_skcx->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_skcx.png);"));
        btn_jfyb = new QPushButton(leftFrame);
        btn_jfyb->setObjectName(QString::fromUtf8("btn_jfyb"));
        btn_jfyb->setGeometry(QRect(20, 90, 89, 35));
        btn_jfyb->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_jfyb.png);"));
        btn_kcxk = new QPushButton(leftFrame);
        btn_kcxk->setObjectName(QString::fromUtf8("btn_kcxk"));
        btn_kcxk->setGeometry(QRect(110, 130, 89, 35));
        btn_kcxk->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_kcxk.png);"));
        btn_xkkk = new QPushButton(leftFrame);
        btn_xkkk->setObjectName(QString::fromUtf8("btn_xkkk"));
        btn_xkkk->setGeometry(QRect(110, 170, 89, 35));
        btn_xkkk->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_xkkk.png);"));
        btn_tczfcx = new QPushButton(leftFrame);
        btn_tczfcx->setObjectName(QString::fromUtf8("btn_tczfcx"));
        btn_tczfcx->setGeometry(QRect(20, 210, 89, 35));
        btn_tczfcx->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/btn_main/images/btnList/btn_tczf.png);"));
        btn_zhye = new QPushButton(leftFrame);
        btn_zhye->setObjectName(QString::fromUtf8("btn_zhye"));
        btn_zhye->setGeometry(QRect(20, 250, 89, 35));
        btn_zhye->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_zhye.png);"));
        btn_zhcz = new QPushButton(leftFrame);
        btn_zhcz->setObjectName(QString::fromUtf8("btn_zhcz"));
        btn_zhcz->setGeometry(QRect(110, 250, 89, 35));
        btn_zhcz->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/btn_main/images/btnList/btn_zhcz.png);"));
        btn_kdjf = new QPushButton(leftFrame);
        btn_kdjf->setObjectName(QString::fromUtf8("btn_kdjf"));
        btn_kdjf->setGeometry(QRect(110, 450, 89, 35));
        btn_kdjf->setStyleSheet(QString::fromUtf8("background-image: url(:/btn_main/images/btnList/btn_kdjf.png);"));
        groupBox = new QGroupBox(leftFrame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 490, 175, 71));
        groupBox->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);"));
        txtTel1 = new QLabel(groupBox);
        txtTel1->setObjectName(QString::fromUtf8("txtTel1"));
        txtTel1->setGeometry(QRect(10, 20, 151, 16));
        txtTel2 = new QLabel(groupBox);
        txtTel2->setObjectName(QString::fromUtf8("txtTel2"));
        txtTel2->setGeometry(QRect(10, 40, 151, 16));

        gridLayout->addWidget(leftFrame, 1, 0, 2, 1);


        retranslateUi(NavigatorForm);

        QMetaObject::connectSlotsByName(NavigatorForm);
    } // setupUi

    void retranslateUi(QWidget *NavigatorForm)
    {
        NavigatorForm->setWindowTitle(QApplication::translate("NavigatorForm", "Form", 0, QApplication::UnicodeUTF8));
        txtSysName->setText(QApplication::translate("NavigatorForm", "\347\263\273\347\273\237\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        txtMoneyAlert->setText(QApplication::translate("NavigatorForm", "\345\275\223\345\211\215\344\275\231\351\242\235\357\274\232", 0, QApplication::UnicodeUTF8));
        btnMoney->setText(QApplication::translate("NavigatorForm", "00000", 0, QApplication::UnicodeUTF8));
        txtWelcome->setText(QApplication::translate("NavigatorForm", "\346\254\242\350\277\216\344\275\240\357\274\232", 0, QApplication::UnicodeUTF8));
        txtName->setText(QApplication::translate("NavigatorForm", "XXXX", 0, QApplication::UnicodeUTF8));
        txtSplacer2->setText(QApplication::translate("NavigatorForm", "|", 0, QApplication::UnicodeUTF8));
        btnLoggout->setText(QApplication::translate("NavigatorForm", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        txtSplacer2_2->setText(QApplication::translate("NavigatorForm", "|", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_ydjf->setToolTip(QApplication::translate("NavigatorForm", "\347\247\273\345\212\250\347\274\264\350\264\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_ydjf->setStatusTip(QApplication::translate("NavigatorForm", "\347\247\273\345\212\250\347\274\264\350\264\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_ydjf->setWhatsThis(QApplication::translate("NavigatorForm", "\347\247\273\345\212\250\347\274\264\350\264\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_ydjf->setText(QString());
#ifndef QT_NO_STATUSTIP
        btn_jfrb->setStatusTip(QApplication::translate("NavigatorForm", "\347\274\264\350\264\271\346\227\245\346\212\245", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_jfrb->setWhatsThis(QApplication::translate("NavigatorForm", "\347\274\264\350\264\271\346\227\245\346\212\245", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        btn_jfrb->setAccessibleName(QApplication::translate("NavigatorForm", "\347\274\264\350\264\271\346\227\245\346\212\245", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_jfrb->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_skjs->setToolTip(QApplication::translate("NavigatorForm", "\345\224\256\345\215\241\347\273\223\347\256\227", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_skjs->setStatusTip(QApplication::translate("NavigatorForm", "\345\224\256\345\215\241\347\273\223\347\256\227", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_skjs->setWhatsThis(QApplication::translate("NavigatorForm", "\345\224\256\345\215\241\347\273\223\347\256\227", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_skjs->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_ywslcx->setToolTip(QApplication::translate("NavigatorForm", "\344\270\232\345\212\241\345\217\227\347\220\206\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_ywslcx->setStatusTip(QApplication::translate("NavigatorForm", "\344\270\232\345\212\241\345\217\227\347\220\206\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_ywslcx->setWhatsThis(QApplication::translate("NavigatorForm", "\344\270\232\345\212\241\345\217\227\347\220\206\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_ywslcx->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_ywsl->setToolTip(QApplication::translate("NavigatorForm", "\344\270\232\345\212\241\345\217\227\347\220\206", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_ywsl->setStatusTip(QApplication::translate("NavigatorForm", "\344\270\232\345\212\241\345\217\227\347\220\206", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_ywsl->setWhatsThis(QApplication::translate("NavigatorForm", "\344\270\232\345\212\241\345\217\227\347\220\206", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_ywsl->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_xgmm->setToolTip(QApplication::translate("NavigatorForm", "\345\257\206\347\240\201\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_xgmm->setStatusTip(QApplication::translate("NavigatorForm", "\345\257\206\347\240\201\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_xgmm->setWhatsThis(QApplication::translate("NavigatorForm", "\345\257\206\347\240\201\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_xgmm->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_yhxxxg->setToolTip(QApplication::translate("NavigatorForm", "\347\224\250\346\210\267\344\277\241\346\201\257\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_yhxxxg->setStatusTip(QApplication::translate("NavigatorForm", "\347\224\250\346\210\267\344\277\241\346\201\257\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_yhxxxg->setWhatsThis(QApplication::translate("NavigatorForm", "\347\224\250\346\210\267\344\277\241\346\201\257\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_yhxxxg->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_zxgg->setToolTip(QApplication::translate("NavigatorForm", "\346\234\200\346\226\260\345\205\254\345\221\212", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_zxgg->setStatusTip(QApplication::translate("NavigatorForm", "\346\234\200\346\226\260\345\205\254\345\221\212", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_zxgg->setWhatsThis(QApplication::translate("NavigatorForm", "\346\234\200\346\226\260\345\205\254\345\221\212", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_zxgg->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_drjjtj->setToolTip(QApplication::translate("NavigatorForm", "\345\275\223\346\227\245\344\272\244\346\230\223\347\273\237\350\256\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_drjjtj->setStatusTip(QApplication::translate("NavigatorForm", "\345\275\223\346\227\245\344\272\244\346\230\223\347\273\237\350\256\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_drjjtj->setWhatsThis(QApplication::translate("NavigatorForm", "\345\275\223\346\227\245\344\272\244\346\230\223\347\273\237\350\256\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_drjjtj->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_gszh->setToolTip(QApplication::translate("NavigatorForm", "\345\205\254\345\217\270\350\264\246\346\210\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_gszh->setStatusTip(QApplication::translate("NavigatorForm", "\345\205\254\345\217\270\350\264\246\346\210\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_gszh->setWhatsThis(QApplication::translate("NavigatorForm", "\345\205\254\345\217\270\350\264\246\346\210\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_gszh->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_yxcz->setToolTip(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260Q\345\270\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_yxcz->setStatusTip(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260Q\345\270\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_yxcz->setWhatsThis(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260Q\345\270\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_yxcz->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_gmjp->setToolTip(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260\346\234\272\347\245\250", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_gmjp->setStatusTip(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260\346\234\272\347\245\250", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_gmjp->setWhatsThis(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260\346\234\272\347\245\250", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_gmjp->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_gmczk->setToolTip(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260\345\205\205\345\200\274\345\215\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_gmczk->setStatusTip(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260\345\205\205\345\200\274\345\215\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_gmczk->setWhatsThis(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260\345\205\205\345\200\274\345\215\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_gmczk->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_drjymx->setToolTip(QApplication::translate("NavigatorForm", "\345\275\223\346\227\245\344\272\244\346\230\223\346\230\216\347\273\206", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_drjymx->setStatusTip(QApplication::translate("NavigatorForm", "\345\275\223\346\227\245\344\272\244\346\230\223\346\230\216\347\273\206", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_drjymx->setWhatsThis(QApplication::translate("NavigatorForm", "\345\275\223\346\227\245\344\272\244\346\230\223\346\230\216\347\273\206", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_drjymx->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_ydxh->setToolTip(QApplication::translate("NavigatorForm", "\347\247\273\345\212\250\351\200\211\345\217\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_ydxh->setStatusTip(QApplication::translate("NavigatorForm", "\347\247\273\345\212\250\351\200\211\345\217\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_ydxh->setWhatsThis(QApplication::translate("NavigatorForm", "\347\247\273\345\212\250\351\200\211\345\217\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_ydxh->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_dbfjs->setToolTip(QApplication::translate("NavigatorForm", "\344\273\243\345\212\236\350\264\271\347\273\223\347\256\227", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_dbfjs->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_skcx->setToolTip(QApplication::translate("NavigatorForm", "\345\224\256\345\215\241\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_skcx->setStatusTip(QApplication::translate("NavigatorForm", "\345\224\256\345\215\241\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_skcx->setWhatsThis(QApplication::translate("NavigatorForm", "\345\224\256\345\215\241\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_skcx->setText(QString());
#ifndef QT_NO_STATUSTIP
        btn_jfyb->setStatusTip(QApplication::translate("NavigatorForm", "\347\274\264\350\264\271\346\234\210\346\212\245", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_jfyb->setWhatsThis(QApplication::translate("NavigatorForm", "\347\274\264\350\264\271\346\234\210\346\212\245", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        btn_jfyb->setAccessibleName(QApplication::translate("NavigatorForm", "\347\274\264\350\264\271\346\234\210\346\212\245", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_jfyb->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_kcxk->setToolTip(QApplication::translate("NavigatorForm", "\345\272\223\345\255\230\345\260\217\345\215\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_kcxk->setStatusTip(QApplication::translate("NavigatorForm", "\345\272\223\345\255\230\345\260\217\345\215\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_kcxk->setWhatsThis(QApplication::translate("NavigatorForm", "\345\272\223\345\255\230\345\260\217\345\215\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_kcxk->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_xkkk->setToolTip(QApplication::translate("NavigatorForm", "\345\260\217\345\215\241\346\211\243\346\254\276", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_xkkk->setStatusTip(QApplication::translate("NavigatorForm", "\345\260\217\345\215\241\346\211\243\346\254\276", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_xkkk->setWhatsThis(QApplication::translate("NavigatorForm", "\345\260\217\345\215\241\346\211\243\346\254\276", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_xkkk->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_tczfcx->setToolTip(QApplication::translate("NavigatorForm", "\345\245\227\351\244\220\347\274\264\350\264\271\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_tczfcx->setStatusTip(QApplication::translate("NavigatorForm", "\345\245\227\351\244\220\347\274\264\350\264\271\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_tczfcx->setWhatsThis(QApplication::translate("NavigatorForm", "\345\245\227\351\244\220\347\274\264\350\264\271\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_tczfcx->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_zhye->setToolTip(QApplication::translate("NavigatorForm", "\350\264\246\346\210\267\344\275\231\351\242\235", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_zhye->setStatusTip(QApplication::translate("NavigatorForm", "\350\264\246\346\210\267\344\275\231\351\242\235", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_zhye->setWhatsThis(QApplication::translate("NavigatorForm", "\350\264\246\346\210\267\344\275\231\351\242\235", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_zhye->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_zhcz->setToolTip(QApplication::translate("NavigatorForm", "\350\264\246\346\210\267\345\205\205\345\200\274", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_zhcz->setStatusTip(QApplication::translate("NavigatorForm", "\350\264\246\346\210\267\345\205\205\345\200\274", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_zhcz->setWhatsThis(QApplication::translate("NavigatorForm", "\350\264\246\346\210\267\345\205\205\345\200\274", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_zhcz->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_kdjf->setToolTip(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260\346\234\272\347\245\250", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btn_kdjf->setStatusTip(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260\346\234\272\347\245\250", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_kdjf->setWhatsThis(QApplication::translate("NavigatorForm", "\350\264\255\344\271\260\346\234\272\347\245\250", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        btn_kdjf->setText(QString());
        groupBox->setTitle(QApplication::translate("NavigatorForm", "\345\256\242\346\234\215\347\224\265\350\257\235", 0, QApplication::UnicodeUTF8));
        txtTel1->setText(QApplication::translate("NavigatorForm", "\345\256\242\346\234\215\347\224\265\350\257\2351", 0, QApplication::UnicodeUTF8));
        txtTel2->setText(QApplication::translate("NavigatorForm", "\345\256\242\346\234\215\347\224\265\350\257\2351", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NavigatorForm: public Ui_NavigatorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAVIGATORFORM_H
