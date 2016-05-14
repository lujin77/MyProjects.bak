/********************************************************************************
** Form generated from reading UI file 'showalertnewsdialog.ui'
**
** Created: Sat Aug 27 01:26:47 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWALERTNEWSDIALOG_H
#define UI_SHOWALERTNEWSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_ShowAlertNewsDialog
{
public:
    QListView *listView;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *ShowAlertNewsDialog)
    {
        if (ShowAlertNewsDialog->objectName().isEmpty())
            ShowAlertNewsDialog->setObjectName(QString::fromUtf8("ShowAlertNewsDialog"));
        ShowAlertNewsDialog->resize(640, 480);
        ShowAlertNewsDialog->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);"));
        listView = new QListView(ShowAlertNewsDialog);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(10, 10, 621, 141));
        listView->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/images/bg/transparent.png);"));
        textBrowser = new QTextBrowser(ShowAlertNewsDialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 160, 621, 311));

        retranslateUi(ShowAlertNewsDialog);

        QMetaObject::connectSlotsByName(ShowAlertNewsDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowAlertNewsDialog)
    {
        ShowAlertNewsDialog->setWindowTitle(QApplication::translate("ShowAlertNewsDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ShowAlertNewsDialog: public Ui_ShowAlertNewsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWALERTNEWSDIALOG_H
