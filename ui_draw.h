/********************************************************************************
** Form generated from reading UI file 'draw.ui'
**
** Created: Mon Dec 20 01:41:20 2010
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Draw
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *Draw)
    {
        if (Draw->objectName().isEmpty())
            Draw->setObjectName(QString::fromUtf8("Draw"));
        Draw->resize(538, 785);
        gridLayout = new QGridLayout(Draw);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(Draw);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        retranslateUi(Draw);

        QMetaObject::connectSlotsByName(Draw);
    } // setupUi

    void retranslateUi(QWidget *Draw)
    {
        Draw->setWindowTitle(QApplication::translate("Draw", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Draw: public Ui_Draw {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAW_H
