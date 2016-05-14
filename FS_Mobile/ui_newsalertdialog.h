/********************************************************************************
** Form generated from reading UI file 'newsalertdialog.ui'
**
** Created: Sun Apr 15 14:38:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSALERTDIALOG_H
#define UI_NEWSALERTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_NewsAlertDialog
{
public:
    QPushButton *btnShow;
    QTextBrowser *txt_title;
    QLabel *txt_count;

    void setupUi(QDialog *NewsAlertDialog)
    {
        if (NewsAlertDialog->objectName().isEmpty())
            NewsAlertDialog->setObjectName(QString::fromUtf8("NewsAlertDialog"));
        NewsAlertDialog->resize(210, 210);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewsAlertDialog->sizePolicy().hasHeightForWidth());
        NewsAlertDialog->setSizePolicy(sizePolicy);
        NewsAlertDialog->setMinimumSize(QSize(210, 210));
        NewsAlertDialog->setMaximumSize(QSize(210, 210));
        NewsAlertDialog->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/news_alert.png);"));
        btnShow = new QPushButton(NewsAlertDialog);
        btnShow->setObjectName(QString::fromUtf8("btnShow"));
        btnShow->setGeometry(QRect(70, 160, 75, 23));
        btnShow->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);"));
        txt_title = new QTextBrowser(NewsAlertDialog);
        txt_title->setObjectName(QString::fromUtf8("txt_title"));
        txt_title->setGeometry(QRect(30, 50, 161, 101));
        txt_title->setMinimumSize(QSize(0, 101));
        txt_title->setMaximumSize(QSize(16777215, 101));
        txt_title->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);"));
        txt_title->setLineWrapMode(QTextEdit::WidgetWidth);
        txt_count = new QLabel(NewsAlertDialog);
        txt_count->setObjectName(QString::fromUtf8("txt_count"));
        txt_count->setGeometry(QRect(40, 20, 141, 16));
        txt_count->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);\n"
"color: rgb(255, 0, 0);\n"
"font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txt_count->setAlignment(Qt::AlignCenter);

        retranslateUi(NewsAlertDialog);

        QMetaObject::connectSlotsByName(NewsAlertDialog);
    } // setupUi

    void retranslateUi(QDialog *NewsAlertDialog)
    {
        NewsAlertDialog->setWindowTitle(QApplication::translate("NewsAlertDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        btnShow->setText(QApplication::translate("NewsAlertDialog", "\347\202\271\345\207\273\346\237\245\347\234\213", 0, QApplication::UnicodeUTF8));
        txt_title->setHtml(QApplication::translate("NewsAlertDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">tttttttttttttttttttttttttttttttttttttttttttttttttttt</p></body></html>", 0, QApplication::UnicodeUTF8));
        txt_count->setText(QApplication::translate("NewsAlertDialog", "\345\205\261\346\234\211: 10 \346\235\241\346\234\252\350\257\273\346\266\210\346\201\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewsAlertDialog: public Ui_NewsAlertDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSALERTDIALOG_H
