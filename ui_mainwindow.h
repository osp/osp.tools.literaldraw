/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Apr 14 15:52:54 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "draw.h"
#include "literal.h"
#include "svgview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Text;
    QAction *actionSave_SVG;
    QAction *actionLoad_Text;
    QAction *actionSave_Text_As;
    QAction *actionNew_Text;
    QAction *actionQuit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    Literal *L;
    QSplitter *splitter;
    Draw *D;
    SvgView *S;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(686, 747);
        actionSave_Text = new QAction(MainWindow);
        actionSave_Text->setObjectName(QString::fromUtf8("actionSave_Text"));
        actionSave_SVG = new QAction(MainWindow);
        actionSave_SVG->setObjectName(QString::fromUtf8("actionSave_SVG"));
        actionLoad_Text = new QAction(MainWindow);
        actionLoad_Text->setObjectName(QString::fromUtf8("actionLoad_Text"));
        actionSave_Text_As = new QAction(MainWindow);
        actionSave_Text_As->setObjectName(QString::fromUtf8("actionSave_Text_As"));
        actionNew_Text = new QAction(MainWindow);
        actionNew_Text->setObjectName(QString::fromUtf8("actionNew_Text"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        L = new Literal(splitter_2);
        L->setObjectName(QString::fromUtf8("L"));
        splitter_2->addWidget(L);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        D = new Draw(splitter);
        D->setObjectName(QString::fromUtf8("D"));
        splitter->addWidget(D);
        S = new SvgView(splitter);
        S->setObjectName(QString::fromUtf8("S"));
        splitter->addWidget(S);
        splitter_2->addWidget(splitter);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 686, 24));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew_Text);
        menuFile->addAction(actionLoad_Text);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_Text);
        menuFile->addAction(actionSave_Text_As);
        menuFile->addAction(actionSave_SVG);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionSave_Text->setText(QApplication::translate("MainWindow", "Save Text", 0, QApplication::UnicodeUTF8));
        actionSave_Text->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSave_SVG->setText(QApplication::translate("MainWindow", "Save SVG...", 0, QApplication::UnicodeUTF8));
        actionLoad_Text->setText(QApplication::translate("MainWindow", "Load Text...", 0, QApplication::UnicodeUTF8));
        actionLoad_Text->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave_Text_As->setText(QApplication::translate("MainWindow", "Save Text As...", 0, QApplication::UnicodeUTF8));
        actionSave_Text_As->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionNew_Text->setText(QApplication::translate("MainWindow", "New Text", 0, QApplication::UnicodeUTF8));
        actionNew_Text->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
