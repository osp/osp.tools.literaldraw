/********************************************************************************
** Form generated from reading UI file 'svgview.ui'
**
** Created: Thu Apr 14 10:01:11 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVGVIEW_H
#define UI_SVGVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SvgView
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QLabel *label;

    void setupUi(QWidget *SvgView)
    {
        if (SvgView->objectName().isEmpty())
            SvgView->setObjectName(QString::fromUtf8("SvgView"));
        SvgView->resize(400, 762);
        gridLayout = new QGridLayout(SvgView);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(SvgView);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(textBrowser, 1, 0, 1, 1);

        label = new QLabel(SvgView);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(SvgView);

        QMetaObject::connectSlotsByName(SvgView);
    } // setupUi

    void retranslateUi(QWidget *SvgView)
    {
        SvgView->setWindowTitle(QApplication::translate("SvgView", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SvgView", "SVG", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SvgView: public Ui_SvgView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVGVIEW_H
