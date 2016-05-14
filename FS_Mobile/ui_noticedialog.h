/********************************************************************************
** Form generated from reading UI file 'noticedialog.ui'
**
** Created: Sun Apr 15 14:38:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTICEDIALOG_H
#define UI_NOTICEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_NoticeDialog
{
public:
    QLineEdit *txi_title;
    QLabel *txt_date;
    QTextBrowser *txt_content;

    void setupUi(QDialog *NoticeDialog)
    {
        if (NoticeDialog->objectName().isEmpty())
            NoticeDialog->setObjectName(QString::fromUtf8("NoticeDialog"));
        NoticeDialog->resize(640, 480);
        NoticeDialog->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);"));
        txi_title = new QLineEdit(NoticeDialog);
        txi_title->setObjectName(QString::fromUtf8("txi_title"));
        txi_title->setGeometry(QRect(10, 10, 621, 31));
        txi_title->setMinimumSize(QSize(0, 31));
        txi_title->setMaximumSize(QSize(16777215, 31));
        txi_title->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txi_title->setAlignment(Qt::AlignCenter);
        txi_title->setReadOnly(true);
        txt_date = new QLabel(NoticeDialog);
        txt_date->setObjectName(QString::fromUtf8("txt_date"));
        txt_date->setGeometry(QRect(220, 50, 200, 12));
        txt_date->setAlignment(Qt::AlignCenter);
        txt_content = new QTextBrowser(NoticeDialog);
        txt_content->setObjectName(QString::fromUtf8("txt_content"));
        txt_content->setGeometry(QRect(10, 70, 621, 401));
        txt_content->setMinimumSize(QSize(0, 401));
        txt_content->setMaximumSize(QSize(16777215, 401));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        txt_content->setFont(font);
        txt_content->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(NoticeDialog);

        QMetaObject::connectSlotsByName(NoticeDialog);
    } // setupUi

    void retranslateUi(QDialog *NoticeDialog)
    {
        NoticeDialog->setWindowTitle(QApplication::translate("NoticeDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        txi_title->setText(QApplication::translate("NoticeDialog", "\346\240\207\351\242\230", 0, QApplication::UnicodeUTF8));
        txt_date->setText(QApplication::translate("NoticeDialog", "2011-08-21", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NoticeDialog: public Ui_NoticeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTICEDIALOG_H
