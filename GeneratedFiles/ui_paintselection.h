/********************************************************************************
** Form generated from reading UI file 'paintselection.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTSELECTION_H
#define UI_PAINTSELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaintSelectionClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PaintSelectionClass)
    {
        if (PaintSelectionClass->objectName().isEmpty())
            PaintSelectionClass->setObjectName(QStringLiteral("PaintSelectionClass"));
        PaintSelectionClass->resize(826, 615);
        actionOpen = new QAction(PaintSelectionClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(PaintSelectionClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PaintSelectionClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PaintSelectionClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 826, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        PaintSelectionClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(PaintSelectionClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PaintSelectionClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(PaintSelectionClass);
        QObject::connect(actionOpen, SIGNAL(triggered()), PaintSelectionClass, SLOT(OpenImage()));

        QMetaObject::connectSlotsByName(PaintSelectionClass);
    } // setupUi

    void retranslateUi(QMainWindow *PaintSelectionClass)
    {
        PaintSelectionClass->setWindowTitle(QApplication::translate("PaintSelectionClass", "PaintSelection", 0));
        actionOpen->setText(QApplication::translate("PaintSelectionClass", "Open", 0));
        menuFile->setTitle(QApplication::translate("PaintSelectionClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class PaintSelectionClass: public Ui_PaintSelectionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTSELECTION_H
