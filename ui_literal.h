/********************************************************************************
** Form generated from reading UI file 'literal.ui'
**
** Created: Thu Apr 14 10:01:11 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LITERAL_H
#define UI_LITERAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QSplitter>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Literal
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QPlainTextEdit *literalEdit;
    QTableView *table;

    void setupUi(QWidget *Literal)
    {
        if (Literal->objectName().isEmpty())
            Literal->setObjectName(QString::fromUtf8("Literal"));
        Literal->resize(428, 670);
        gridLayout = new QGridLayout(Literal);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(Literal);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        literalEdit = new QPlainTextEdit(splitter);
        literalEdit->setObjectName(QString::fromUtf8("literalEdit"));
        literalEdit->setFocusPolicy(Qt::WheelFocus);
        splitter->addWidget(literalEdit);
        table = new QTableView(splitter);
        table->setObjectName(QString::fromUtf8("table"));
        table->setFocusPolicy(Qt::NoFocus);
        splitter->addWidget(table);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(Literal);

        QMetaObject::connectSlotsByName(Literal);
    } // setupUi

    void retranslateUi(QWidget *Literal)
    {
        Literal->setWindowTitle(QApplication::translate("Literal", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Literal: public Ui_Literal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LITERAL_H
